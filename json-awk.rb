#!/usr/bin/env ruby
#
#  REQUIREMENTS:
#
#    $ sudo gem install json
#
#  SPECIAL VARIABLES:
#
#    $_
#    $nr
#
#  DESCRIPTION:
#
#    Read from standard input JSON objects, one per line.
#    Parse each JSON object and put the data in the special
#    variable $_.  Execute the command line specified
#    script.
#
#    If the -j or -t flags are specifed, write the
#    value in the $_ to standard out as JSON or in tab delimited
#    format.

output_format = nil

if ['-j', '--json'].include?(ARGV[0])
  output_format = :json
  ARGV.shift
elsif ['-t', '--tab'].include?(ARGV[0])
  output_format = :tab
  ARGV.shift
end

if ARGV.size != 1
  $stderr.puts("USAGE: json-awk.rb [-t|--tab|-j|--json] JSON_AWK_SCRIPT")
  exit(1)
end

cmd = ['ruby', '-n']

cmd << '-e'
cmd << 'BEGIN {require "rubygems"; require "json"; $nr = 0}'

cmd << '-e'
cmd << '$_ = JSON.parse($_); $nr += 1'

cmd << '-e'
cmd << ARGV[0]

case output_format
when :json
  cmd << '-e'
  cmd << 'puts $_.to_json'
when :tab
  cmd << '-e'
  cmd << 'puts $_.join("\t")'
end

exec(*cmd)
