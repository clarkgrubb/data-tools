#!/usr/bin/env ruby

require 'getoptlong'

def usage
    $stderr.puts "USAGE: jar-awk -l REGEX [-F REGEX] -(-f SCRIPT_FILE | SCRIPT) [RECORD_JAR_FILE]"
    exit 1
end

opts = GetoptLong.new(
                      ['--file', '-f',
                       GetoptLong::REQUIRED_ARGUMENT],
                      ['--line-delimiter', '-l',
                       GetoptLong::REQUIRED_ARGUMENT],
                      ['--field-delimiter', '-F',
                       GetoptLong::OPTIONAL_ARGUMENT],
                      ['--help',
                       GetoptLong::NO_ARGUMENT]
                      )


script = nil
field_delimiter = nil
line_delimiter = nil
ignore_parse_errors = false

opts.each do |opt, arg|
  case opt
  when '--file'
    script = File.open(arg).read
  when '--field-delimiter'
    field_delimiter = /#{arg}/
  when '--line-delimiter'
    line_delimiter = /#{arg}/
  when '--help'
    usage
  end
end

if not script
  if ARGV.size > 0
    script = ARGV.shift
  else
    $stderr.puts "ERROR: no SCRIPT or SCRIPT_FILE specified"
    usage
  end
end

# TODO: BEGIN and END blocks?
#
processor = eval("lambda { |line| $_ = line; #{script} }")

if ARGV.size > 0
  input_stream = File.open(ARGV[0])
else
  input_stream = $stdin
end

record_num = 0
if field_delimiter
  record = {}
else
  record = ''
end

input_stream.each do |line|
  if line_delimiter.match(line)
    # TODO: save the match
    if record_num > 0
      processor.call(record)
    end
    record_num += 1
    if field_delimiter
      record = {}
    else
      record = ''
    end
  else
    if field_delimiter
      key, value = line.split(field_delimiter, 2)
      record[key] = value
    else
      record += line
    end
  end
end

if record
  processor.call(record)
end
