#!/usr/bin/env ruby

require 'csv'
require 'nokogiri'
require 'optparse'

options = { table: 0 }
OptionParser.new do |opts|
  opts.banner =
    "usage: #{$PROGRAM_NAME} [-t NUM] [FILE]"

  opts.on('-t', '--table NUM') do |arg|
    options[:table] = arg.to_i
  end
end.parse!

noko = if ARGV[0]
         Nokigiri::HTML(File.open(ARGV[0]))
       else
         Nokogiri::HTML($stdin)
       end

tables = noko.xpath('//table')
table = tables[options[:table]]
output = CSV.generate do |csv|
  trows = table.xpath('.//tr')
  trows.each do |trow|
    row = []
    cells = trow.xpath('.//th|.//td')
    cells.each do |cell|
      row << cell.content.strip
    end
    csv << row
  end
end
puts output
