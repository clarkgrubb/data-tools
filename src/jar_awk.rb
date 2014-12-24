#!/usr/bin/env ruby

require 'getoptlong'

def usage
  $stderr.puts 'USAGE: jar-awk [-t] -l REGEX [-F REGEX] [-B SCRIPT] [-E SCRIPT] (-f SCRIPT_FILE | SCRIPT) [RECORD_FILE]'
  $stderr.puts
  $stderr.puts '  -t (--trim): trim whitespace'
  $stderr.puts '  -l (--line-delimiter): regex identifying lines between records'
  $stderr.puts '  -B (--BEGIN): script to execute before processing records'
  $stderr.puts '  -E (--END): script to execute after processing records'
  $stderr.puts '  -f (--file): execute script in file for each record instead of script on cmd line'
  $stderr.puts
  $stderr.puts '  $_: variable containing record'
  $stderr.puts '  $md: variable containing match data for -l REGEX'
  exit 1
end

opts = GetoptLong.new(
                      ['--BEGIN', '-B',
                       GetoptLong::REQUIRED_ARGUMENT],
                      ['--END', '-E',
                       GetoptLong::REQUIRED_ARGUMENT],
                      ['--file', '-f',
                       GetoptLong::REQUIRED_ARGUMENT],
                      ['--line-delimiter', '-l',
                       GetoptLong::REQUIRED_ARGUMENT],
                      ['--field-delimiter', '-F',
                       GetoptLong::OPTIONAL_ARGUMENT],
                      ['--strict', '-s',
                       GetoptLong::NO_ARGUMENT],
                      ['--silent', '-S',
                       GetoptLong::NO_ARGUMENT],
                      ['--trim', '-t',
                       GetoptLong::NO_ARGUMENT],
                      ['--no-trim', '-T',
                       GetoptLong::NO_ARGUMENT],
                      ['--skip-record-zero', '-Z',
                       GetoptLong::NO_ARGUMENT],
                      ['--help',
                       GetoptLong::NO_ARGUMENT]
                      )

script = nil
line_delimiter = nil
begin_script = nil
end_script = nil
use_zero = true

strict = false
silent = false
field_delimiter = nil
trim = nil

opts.each do |opt, arg|
  case opt
  when '--BEGIN'
    begin_script = arg
  when '--END'
    end_script = arg
  when '--file'
    script = File.open(arg).read
  when '--field-delimiter'
    field_delimiter = /#{arg}/
  when '--line-delimiter'
    line_delimiter = /#{arg}/
  when '--strict'
    strict = true
  when '--silent'
    silent = true
  when '--no-trim'
    trim = false
  when '--trim'
    trim = true
  when '--skip-record-zero'
    use_zero = false
  when '--help'
    usage
  end
end

trim = field_delimiter ? true : false if trim.nil?

unless script
  if ARGV.size > 0
    script = ARGV.shift
  else
    $stderr.puts 'ERROR: no SCRIPT or SCRIPT_FILE specified'
    usage
  end
end

unless line_delimiter
  $stderr.puts 'ERROR: no --line-delimiter or -l specified'
  usage
end

variables = binding
processor = eval("lambda { |line, md| $_ = line; $md = md; #{script} }", variables)

if ARGV.size > 0
  input_stream = File.open(ARGV[0])
else
  input_stream = $stdin
end

class EmptyMatchData
  def pre_match
    ''
  end

  def post_match
    ''
  end

  def [](_)
    nil
  end

  def length
    0
  end

  def size
    0
  end

  def names
    []
  end
end

class Record
  def initialize(match_data, field_delimiter, trim, processor)
    @field_delimiter = field_delimiter
    @trim = trim
    @processor = processor
    @match_data = match_data
    if @field_delimiter
      @record = {}
    else
      @record = ''
    end
  end

  def add_line(line)
    if @field_delimiter
      key, value = line.split(@field_delimiter, 2)
      if value.nil? && !silent && !strict
        $stderr.puts "WARNING: record line does not have field delimiter: #{line}"
      end
      if value.nil? && strict
        $stderr.puts "ERROR: line does not have field delimiter: #{line}"
        exit 1
      end
      if @trim
        key.strip!
        value.strip! if value
      end
      @record[key] = value
    else
      @record += line
    end
  end

  def process
    @record.strip! if @trim && !@field_delimiter
    @processor.call(@record, @match_data)
  end
end

eval(begin_script, variables) if begin_script

record_num = 0
record = Record.new(EmptyMatchData.new, field_delimiter, trim, processor)

input_stream.each_with_index do |line, line_num|
  md = line_delimiter.match(line)
  if md
    if (use_zero && record_num == 0 && line_num > 0) || record_num > 0
      record.process
    end
    record_num += 1
    record = Record.new(md, field_delimiter, trim, processor)
  else
    record.add_line(line)
  end
end

if (use_zero && record_num == 0 && line_num > 0) || record_num > 0
  record.process
end

eval(end_script, variables) if end_script
