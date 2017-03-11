#!/usr/bin/env ruby

require 'erb'
require 'pp'

INDENT = '  '.freeze

class DecisionNode
  attr_reader :left_node, :right_node, :left, :right, :x, :n, :script

  def initialize(scripts, left, right, x = nil)
    @scripts = scripts
    @left = left
    @right = right
    @n = @scripts.ranges_intersecting_interval(left, right)
    if @n > 1
      raise 'software error' if right - left <= 1
      @x = x.nil? ? best_x : x
      @left_node = DecisionNode.new(scripts, @left, @x)
      @right_node = DecisionNode.new(scripts, @x, @right)
      @script = nil
    else
      @x = nil
      @left_node = nil
      @right_node = nil
      @script = scripts.name_of_intersecting_script(@left, @right)
    end
  end

  def best_x
    best_x = nil
    max_entropy = -1
    @scripts.starts.each do |x|
      next if x < @left
      break if x > @right
      entropy = @scripts.entropy(@left, x) + @scripts.entropy(x, @right)
      # puts "DEBUG: entropy #{entropy}"
      if entropy > max_entropy
        max_entropy = entropy
        best_x = x
      end
    end
    raise "software error: #{@left} #{@right} #{@n}" if best_x.nil?
    best_x
  end

  def render_increment_counts(indent = INDENT + INDENT)
    s = ''
    if @script.nil?
      s += indent + 'if (ch < ' + @x.to_s + ") {\n"
      s += @left_node.render_increment_counts(indent + INDENT) + "\n"
      s += indent + "} else {\n"
      s += @right_node.render_increment_counts(indent + INDENT) + "\n"
      s += indent + '}'
    else
      s += indent + 'counts[' + @script.downcase + '] += 1;'
    end
    s
  end
end

class Scripts
  #
  # From http://unicode.org/Public/UNIDATA/Scripts.txt:
  #
  #   0000..001F    ; Common # Cc  [32] <control-0000>..<control-001F>
  #   0020          ; Common # Zs       SPACE
  #
  REGEX = /^(?<start>\h{4,6})(?:\.\.(?<ending>\h{4,6}))?\s+;\s+(?<script>\S+)/

  def initialize(path)
    @data = Hash.new { |h, k| h[k] = [] }
    File.open(path) do |f|
      f.each do |line|
        md = REGEX.match(line)
        next unless md
        raw_start = md['start']
        raw_ending = md['ending']
        script = md['script']
        start = raw_start.to_i(16)
        ending = (raw_ending ? raw_ending : raw_start).to_i(16)
        @data[script] << [start, ending]
      end
    end
    collapse_ranges
    add_unknown_ranges
    @range_count = ranges.size
    @script_map = @data.keys.sort
    @inverse_script_map = {}
    @script_map.each_with_index { |script, i| @inverse_script_map[script] = i }
  end

  def dump
    pp @data
  end

  def count
    @data.size
  end

  def render_enum
    s = "enum unicode_script {\n"
    @script_map.each_with_index do |script, i|
      s += INDENT + script.downcase + ' = ' + i.to_s + ",\n"
    end
    s += '};'
    s
  end

  def render_script_strings
    s = "char *scripts[] = {\n"
    s += INDENT
    s += @script_map.map { |script| '"' + script + '"' }.join(",\n" + INDENT)
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

  def name_of_intersecting_script(start, ending)
    @data.each do |script, a|
      a.each do |left, right|
        return script unless left >= ending || right < start
      end
    end
    raise 'software error'
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
          raise "point #{'%x' % i} used multiple times" unless unknown[i]
          unknown[i] = false
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
    @data.each do |script, a|
      new_a = []
      last_start = nil
      last_ending = nil
      a.each do |start, ending|
        if last_ending && start == last_ending + 1
        elsif last_ending
          new_a << [last_start, last_ending]
          last_start = start
        else
          last_start = start
        end
        last_ending = ending
      end
      new_a << [last_start, last_ending] if last_ending
      new_data[script] = new_a
    end
    @data = new_data
  end
end

def generate(scripts, tree, template, output_stream)
  enum = scripts.render_enum
  script_strings = scripts.render_script_strings
  num_scripts = scripts.count
  increment_counts = tree.render_increment_counts
  output_stream.puts ERB.new(File.open(template).read).result(binding)
end

if $PROGRAM_NAME == __FILE__
  if ARGV.size == 2
    scripts = Scripts.new(ARGV[0])
    tree = DecisionNode.new(scripts, 0, 0x1020000, 128)
    generate(scripts, tree, ARGV[1], $stdout)
  else
    $stderr.puts 'USAGE: generate_script.rb SCRIPTS_FILE TEMPLATE'
  end
end
