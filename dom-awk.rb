#!/usr/bin/env ruby

# A script which accepts a Ruby script on the command line.
#
# Standard input is parsed using Nokogiri and the resulting
# DOM tree is available to the Ruby script in $_.
#
# Here are a couple of examples:
#
#   curl www.google.com | dom-awk.rb \
#     '$_.xpath("//a").each {|o| puts o["href"] }'
#
#
#   echo '<xml><foo>bar</foo></xml>' | dom-awk.rb \
#     '$_.xpath("//foo").each { |o| puts o.content }'
#

require 'getoptlong'

opts = GetoptLong.new(
  ['--file', '-f',
   GetoptLong::REQUIRED_ARGUMENT],
  ['--xml', '-x',
   GetoptLong::NO_ARGUMENT],
  ['--html', '-h',
   GetoptLong::NO_ARGUMENT]
)

script = nil
constructor = 'Nokogiri::HTML'

opts.each do |opt, arg|
  case opt
  when '--file'
    script = File.open(arg).read
  when '--xml'
    #
    #  Not sure if the --xml and --html flags
    #  are necessary, since Nokogiri doesn't
    #  complain about malformed XML documents
    #  and the resulting DOM trees appear to
    #  behave identically.
    #
    constructor = 'Nokogiri::XML'
  when '--html'
    constructor = 'Nokogiri::HTML'
  end
end

if not script
  if ARGV.size > 0
    script = ARGV.shift
  else
    raise "no script specified"
  end
end

cmd = ['ruby']
cmd << '-e'
cmd << 'require "rubygems"'
cmd << '-e'
cmd << 'require "nokogiri"'
cmd << '-e'
if (ARGV[0])
  cmd << '$_ = ' + constructor + "(File.open('#{ARGV[0]}'))"
else
  cmd << '$_ = ' + constructor + '($stdin)'
end
cmd << '-e'
cmd << script

exec(*cmd)
