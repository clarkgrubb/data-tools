#!/usr/bin/env ruby

require 'erb'
require 'pp'

INDENT = '  '

class DecisionNode
  attr_reader :left_node, :right_node, :left, :right, :x, :n, :category

  def initialize(categories, left, right, x = nil)
    @categories = categories
    @left = left
    @right = right
    @n = @categories.ranges_intersecting_interval(left, right)
    if @n > 1
      fail 'software error' if right - left <= 1
      @x = x.nil? ? best_x : x
      @left_node = DecisionNode.new(categories, @left, @x)
      @right_node = DecisionNode.new(categories, @x, @right)
      @category = nil
    else
      @x = nil
      @left_node = nil
      @right_node = nil
      @category = categories.name_of_intersecting_category(@left, @right)
    end
  end

  def best_x
    best_x = nil
    max_entropy = -1
    @categories.starts.each do |x|
      next if x < @left
      break if x > @right
      entropy = @categories.entropy(@left, x) + @categories.entropy(x, @right)
      # puts "DEBUG: entropy #{entropy}"
      if entropy > max_entropy
        max_entropy = entropy
        best_x = x
      end
    end
    fail "software error: #{@left} #{@right} #{@n}" if best_x.nil?
    best_x
  end

  def render_increment_counts(indent = INDENT + INDENT)
    s = ''
    if @category.nil?
      s += indent + 'if (ch < ' + @x.to_s + ") {\n"
      s += @left_node.render_increment_counts(indent + INDENT) + "\n"
      s += indent + "} else {\n"
      s += @right_node.render_increment_counts(indent + INDENT) + "\n"
      s += indent + '}'
    else
      s += indent + 'counts[' + @category.downcase + '] += 1;'
    end
    s
  end
end

class Categories
  #
  #  0060;GRAVE ACCENT;Sk;0;ON;;;;;N;SPACING GRAVE;;;;
  #  0061;LATIN SMALL LETTER A;Ll;0;L;;;;;N;;;0041;;0041
  #  0062;LATIN SMALL LETTER B;Ll;0;L;;;;;N;;;0042;;0042
  #
  def initialize(path)
    @data = Hash.new { |h, k| h[k] = [] }
    File.open(path) do |f|
      f.each do |line|
        a = line.split(';')
        point, category = a[0].to_i(16), a[2]
        @data[category] << [point, point]
      end
    end
    collapse_ranges
    add_unknown_ranges
    @range_count = ranges.size
    @category_map = @data.keys.sort
    @inverse_category_map = {}
    @category_map.each_with_index { |category, i| @inverse_category_map[category] = i }
  end

  def dump
    pp @data
  end

  def count
    @data.size
  end

  def render_enum
    s = "enum unicode_category {\n"
    @category_map.each_with_index do |category, i|
      s += INDENT + category.downcase + ' = ' + i.to_s + ",\n"
    end
    s += '};'
    s
  end

  def render_category_strings
    s = "char *categories[] = {\n"
    s += INDENT
    s += @category_map.map { |category| '"' + category + '"' }.join(",\n" + INDENT)
    s += "\n};"
    s
  end

  def starts
    @starts = ranges.collect { |o| o[0] }.sort if @starts.nil?
    @starts
  end

  def ranges
    @data.keys.inject([]) { |m, k| m.concat(@data[k]) }
  end

  def ranges_intersecting_interval(start, ending)
    count = 0
    ranges.each do |left, right|
      count += 1 unless left >= ending || right < start
    end
    count
  end

  def name_of_intersecting_category(start, ending)
    @data.each do |category, a|
      a.each do |left, right|
        return category unless left >= ending || right < start
      end
    end
    fail 'software error'
  end

  def probability(start, ending)
    1.0 * ranges_intersecting_interval(start, ending) / @range_count
  end

  def entropy(start, ending)
    p = probability(start, ending)
    -1.0 * Math.log(p) * p
  end

  def add_unknown_ranges
    unknown = [true] * 0x10ffff
    @data.each do |_, a|
      a.each do |start, ending|
        (start..ending).each do |i|
          if unknown[i]
            unknown[i] = false
          else
            fail "point #{'%x' % i} used multiple times"
          end
        end
      end
    end
    unknown_ranges = []
    start = nil
    ending = nil
    (0..0x10ffff).each do |i|
      if unknown[i]
        start = i if start.nil?
        ending = i
      else
        unless start.nil?
          unknown_ranges << [start, ending]
          start = nil
          ending = nil
        end
      end
    end
    unknown_ranges << [start, ending] unless start.nil?
    @data['Unknown'] = unknown_ranges
  end

  def collapse_ranges
    new_data = {}
    @data.each do |category, a|
      new_a = []
      last_start, last_ending = nil, nil
      a.each do |start, ending|
        if last_ending && start == last_ending + 1
          last_ending = ending
        elsif last_ending
          new_a << [last_start, last_ending]
          last_start, last_ending = start, ending
        else
          last_start, last_ending = start, ending
        end
      end
      new_a << [last_start, last_ending] if last_ending
      new_data[category] = new_a
    end
    @data = new_data
  end
end

def generate(categories, tree, template, output_stream)
  enum = categories.render_enum
  category_strings = categories.render_category_strings
  num_categories = categories.count
  increment_counts = tree.render_increment_counts
  output_stream.puts ERB.new(File.open(template).read).result(binding)
end

if $PROGRAM_NAME == __FILE__
  if ARGV.size == 2
    categories = Categories.new(ARGV[0])
    tree = DecisionNode.new(categories, 0, 0x1020000, 128)
    generate(categories, tree, ARGV[1], $stdout)
  else
    $stderr.puts 'USAGE: generate_category.rb UNICODE_DATA_FILE TEMPLATE'
  end
end
