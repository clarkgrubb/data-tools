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

require 'getoptlong'

opts = GetoptLong.new(
  ['--file', '-f',
   GetoptLong::OPTIONAL_ARGUMENT],
  ['--json', '-j',
   GetoptLong::NO_ARGUMENT],
  ['--tsv', '-t',
   GetoptLong::NO_ARGUMENT]
)

script = nil
output_format = nil

opts.each do |opt, arg|
  case opt
  when '--file'
    script = File.open(arg).read
  when '--json'
    output_format = :json
  when '--tsv'
    output_format = :tsv
  end
end

if not script
  if ARGV.size > 0
    script = ARGV.shift
  else
    raise "no script specified"
  end
end

cmd = ['ruby', '-n']
cmd << '-e'
cmd << 'BEGIN {require "rubygems"; require "json"; $nr = 0}'
cmd << '-e'
cmd << '$_ = JSON.parse($_); $nr += 1'
cmd << '-e'
cmd << script

case output_format
when :json
  cmd << '-e'
  cmd << 'puts $_.to_json'
when :tsv
  cmd << '-e'
  cmd << 'puts $_.join("\t")'
end

cmd.concat(ARGV)

exec(*cmd)
