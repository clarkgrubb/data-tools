#!/usr/bin/env ruby

require 'optparse'

UNICODE_DATA_CACHE = '/tmp/UnicodeData.txt'

class UnicodeData

  UNICODE_DATA_URL = 'ftp://ftp.unicode.org/Public/UNIDATA/UnicodeData.txt'

  POINT_IDX = 0
  NAME_IDX = 1
  GENERAL_CATEGORY_IDX = 2
  GENERAL_COMBINING_CLASS_IDX = 3
  BIDI_CLASS_IDX = 4
  DECOMPOSITION_TYPE_MAPPING_IDX = 5
  NUMERIC_TYPE_VALUE_IDX = 6
  BIDI_MIRRORED_IDX = 7
  DONT_USE_ME_1_IDX = 8
  DONE_USE_ME_2_IDX = 9
  SIMPLE_UPPERCASE_MAPPING_IDX = 10
  SIMPLE_LOWERCASE_MAPPING_IDX = 11
  SIMPLE_TITLECASE_MAPPING_IDX = 12

  RIGHT_TO_LEFT_CLASSES = ["R", "AL", "RLE", "RLO", "AN"]

  GENERAL_CATEGORIES = {
    "Lu" => "Letter, Uppercase",
    "Ll" => "Letter, Lowercase",
    "Lt" => "Letter, Titlecase",
    "Mn" => "Mark, Non-Spacing",
    "Mc" => "Mark, Spacing Combining",
    "Me" => "Mark, Enclosing",
    "Nd" => "Number, Decimal Digit",
    "Nl" => "Number, Letter",
    "No" => "Number, Other",
    "Zs" => "Separator, Space",
    "Zl" => "Separator, Line",
    "Zp" => "Separator, Paragraph",
    "Cc" => "Other, Control",
    "Cf" => "Other, Format",
    "Cs" => "Other, Surrogate",
    "Co" => "Other, Private Use",
    "Cn" => "Other, Not Assigned",
    "Lm" => "Letter, Modifier",
    "Lo" => "Letter, Other",
    "Pc" => "Punctuation, Connector",
    "Pd" => "Punctuation, Dash",
    "Ps" => "Punctuation, Open",
    "Pe" => "Punctuation, Close",
    "Pi" => "Punctuation, Initial quote",
    "Pf" => "Punctuation, Final quote",
    "Po" => "Punctuation, Other",
    "Sm" => "Symbol, Math",
    "Sc" => "Symbol, Currency",
    "Sk" => "Symbol, Modifier",
    "So" => "Symbol, Other",
  }

  def initialize(path)
    @unicode_data = {}

    download(path) if not File.exists?(path)

    File.open(path).each do |line|
      a = line.split(';')
      # FIXME: throw exception if not 13 fields
      code_point = a[0].to_i(16)
      # $stderr.puts(code_point)
      @unicode_data[code_point] = a
    end

    # FIXME: throw exception if not of a certain size
  end

  def right_to_left?(code_point)
    RIGHT_TO_LEFT_CLASSES.include?(@unicode_data[code_point][BIDI_CLASS_IDX])
  end

  def download(path)
    if not system("curl #{UNICODE_DATA_URL} 2> /dev/null > #{path}")
      raise "failed to download #{UNICODE_DATA_URL}"
    end
  end
end

# track number of violations
# --stats to get number of violations
# --quiet
# suppression flags
# scripts
# control characters C0, C1
# whitespace characters
# tests

def utf8_lint(inf)

  unicode_data = UnicodeData.new(UNICODE_DATA_CACHE)

  non_ascii = 0
  left_to_right = 0
  right_to_left = 0
  non_bmp = 0

  inf.each_char do |ch|

    code_point = ch.ord

    if code_point > 127
      non_ascii += 1
    end

    if unicode_data.right_to_left?(code_point)
      right_to_left += 1
    else
      left_to_right += 1
    end

    if code_point > 0xFFFF
      non_bmp += 1
    end

  end

  ret = 0
  if non_ascii > 0
    $stderr.puts("non_ascii: #{non_ascii}")
    ret = 1
  end

  if left_to_right > 0 and right_to_left > 0
    $stderr.puts("bidi text")
  end

  if non_bmp > 0
    $stderr.puts("non_bmp: #{non_bmp}")
    ret = 1
  end

  ret

end

if $0 == __FILE__

  options = {}

  OptionParser.new do |opts|
    opts.banner =
      "usage: #{$0} [OPTIONS] [FILE]\n"

    opts.on("-f", "--foo") do |arg|
      options[:foo] = arg
    end

  end.parse!

  if ARGV[0]
    input_stream = File.open(ARGV[0])
  else
    input_stream = $stdin
  end

  exit(utf8_lint(input_stream))

end
