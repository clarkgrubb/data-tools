#!/usr/bin/env ruby

require 'optparse'

UNICODE_DATA_CACHE = '/tmp/UnicodeData.txt'
NOT_FOUND = '<NOT FOUND>'

COLUMN_SEP = ' '
SECTION_SEP = '   '
OFFSET_SEP = ':'

ZEROS_BYTE = 0
ONES_BYTE = 2**8 - 1

DEFAULT_WIDTH = 8

# black square
INVALID_BYTES = "25A0".to_i(16)
INVALID_CODE_POINT = -1
INVALID_CODE_POINT_HEX = "----"

# white square
UNPRINTABLE_CODE_POINT = "25A1".to_i(16)

# http://en.wikipedia.org/wiki/UTF-8#Description

MASK1 = 0b10000000
MASK2 = 0b11000000
MASK3 = 0b11100000
MASK4 = 0b11110000
MASK5 = 0b11111000

PREFIX_MASK = {
  1 => [MASK1],
  2 => [MASK3, MASK2],
  3 => [MASK4, MASK2, MASK2],
  4 => [MASK5, MASK2, MASK2, MASK2],
}

PREFIX = {
  1 => [0b00000000],

  2 => [0b11000000,
        0b10000000],

  3 => [0b11100000,
        0b10000000,
        0b10000000],

  4 => [0b11110000,
        0b10000000,
        0b10000000,
        0b10000000],
}

SHIFTS = {
  1 => [0],
  2 => [6, 0],
  3 => [12, 6, 0],
  4 => [18, 12, 6, 0],
}

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
      @unicode_data[code_point] = a
    end

    # FIXME: throw exception if not of a certain size
  end

  def name(code_point)
    if @unicode_data.has_key?(code_point)
      @unicode_data[code_point][NAME_IDX]
    else
      NOT_FOUND
    end
  end

  def unprintable?(code_point)
    general_cat = @unicode_data[code_point][GENERAL_CATEGORY_IDX]

    not general_cat or general_cat[0] == "C"
  end

  def right_to_left?(code_point)
    @unicode_data[code_point][BIDI_CLASS_IDX] == "R"
  end

  def download(path)
    if not system("curl #{UNICODE_DATA_URL} 2> /dev/null > #{path}")
      raise "failed to download #{UNICODE_DATA_URL}"
    end
  end
end

class ByteStream

  attr_reader :offset

  def initialize(input_stream, options)
    @input_stream = input_stream
    @offset = 0
  end

  def next
    s = _next
    @offset += 1
    if RUBY_VERSION.match(/^1\.8/)
      s ? s[0] : nil
    else
      s ? s.ord : nil
    end
  end
end

class IOByteStream < ByteStream
  def _next
    @input_stream.read(1)
  end
end

class ArrayByteStream < ByteStream

  def check_byte(byte)
    if byte < ZEROS_BYTE or byte > ONES_BYTE
      raise "not a byte: #{byte}"
    end
  end

  def arg_to_byte(arg)
    case arg
    when /^0x[0-9a-f]+$/i
      arg.to_i(16)
    when /^0b[01]+$/i
      arg.to_i(2)
    when /^0[0-7]+$/
      arg.to_i(8)
    when /^[1-9][0-9]*$/
      arg.to_i
    else
      raise "invalid arg: #{arg}: must be binary, octal, decimal, or hex"
    end
  end

  def _next
    s = @input_stream.shift
    s ? arg_to_byte(s) : s
  end
end

class CharFormatter

  def initialize(output_stream, options)
    @output_stream = output_stream
    @options = options

    @byte_offsets = []
    @char_offsets = []
    @code_points = []
  end

  def unprintable?(code_point)
    if @options[:unicode_data]
      @options[:unicode_data].unprintable?(code_point)
    else
      code_point <= 0x1f or
        (code_point >= 0x7f and code_point <= 0x9f)
    end
  end

  def right_to_left?(code_point)
    if @options[:unicode_data]
      @options[:unicode_data].right_to_left?(code_point)
    else
      false
    end
  end

  def add_char(byte_offset, char_offset, code_point)
    @byte_offsets << byte_offset
    @char_offsets << char_offset
    @code_points << code_point
  end

  def render_code_point(code_point)
    if code_point == INVALID_CODE_POINT
      [@options[:invalid_char]].pack("U")
    elsif unprintable?(code_point)
      [@options[:unprintable_char]].pack("U")
    else
      [code_point].pack("U")
    end
  end

  def format_code_point(code_point)
    if code_point == INVALID_CODE_POINT
      INVALID_CODE_POINT_HEX
    else
      to_hex(code_point)
    end
  end

  def astral_point_to_surrogate_pair(code_point)
    x = code_point - 0x10000
    lead = x >> 10
    trail = x & 0b1111111111

    return lead, trail
  end

  def format_surrogate_pair(code_point)
    if code_point < 0x10000
      to_hex(code_point) + "/" + INVALID_CODE_POINT_HEX
    else
      lead, trail = astral_point_to_surrogate_pair(code_point)
      to_hex(lead) + "/" + to_hex(trail)
    end
  end

  def print_rendered_code_points(width)
    augmented = @code_points.dup
    if @code_points.size > width
      raise "code points exceed width"
    end
    augmented.concat([32] * (width - @code_points.size))
    print augmented.map { |cp| render_code_point(cp) }.join(COLUMN_SEP)
    print "  "
  end

  def print_line(width)
    if @code_points.size > 0

      if @options[:byte_offset]
        print "#{to_hex(@byte_offsets.first)}"
      end

      if @options[:char_offset]
        if @options[:byte_offset]
          print COLUMN_SEP
        end
        print "#{to_hex(@char_offsets.first)}"
      end

      if @options[:byte_offset] or @options[:char_offset]
        print OFFSET_SEP
        print SECTION_SEP
      end

      if @options[:render]
        print_rendered_code_points(width)
      end

      print @code_points.map { |cp| format_code_point(cp) }.join(COLUMN_SEP)

      if @options[:surrogate_pairs]
        print SECTION_SEP
        pairs = @code_points.map { |cp| format_surrogate_pair(cp) }
        print pairs.join(COLUMN_SEP)
      end

      if @options[:name_lookup]
        print SECTION_SEP
        print @options[:unicode_data].name(@code_points[0])
      end

      puts

      @byte_offsets = []
      @char_offsets = []
      @code_points = []
    end
  end
end

def to_hex(cp)
  if cp == INVALID_CODE_POINT
    INVALID_CODE_POINT_HEX
  else
    sprintf("%04X", cp)
  end
end

def code_point(bytes)
  prefix_masks = PREFIX_MASK[bytes.size]
  shifts = SHIFTS[bytes.size]

  code_point = 0

  bytes.each_with_index do |byte, i|
    code_point += ((prefix_masks[i] ^ ONES_BYTE) & byte) << shifts[i]
  end

  code_point
end

def classify_byte(byte)
  if byte & MASK1 == PREFIX[1][0]
    return :first_of_one
  elsif byte & MASK3 == PREFIX[2][0]
    return :first_of_two
  elsif byte & MASK4 == PREFIX[3][0]
    return :first_of_three
  elsif byte & MASK5 == PREFIX[4][0]
    return :first_of_four
  elsif byte & MASK2 == PREFIX[2][1]
    return :not_first
  else
    return :invalid
  end
end

def get_rest_of_bytes(byte_stream, n)

  bytes = []
  invalid_byte = false

  while (n > 0)
    byte = byte_stream.next
    return nil if byte.nil?
    if byte & MASK2 == PREFIX[2][1]
      bytes << byte
    else
      invalid_byte = true
    end
    n -= 1
  end

  invalid_byte ? nil : bytes
end


def utf8_stream_to_unicode(byte_stream, output_stream, options)

  char_formatter = CharFormatter.new(output_stream, options)
  invalid_char_cnt = 0
  char_offset = 0
  width = options[:width]

  while true

    byte_offset = byte_stream.offset
    byte = byte_stream.next
    break if byte.nil?

    invalid_byte = false

    case (classify_byte(byte))
    when :first_of_one
      bytes = [byte]
    when :first_of_two
      bytes = get_rest_of_bytes(byte_stream, 1)
      bytes.unshift(byte) unless bytes.nil?
    when :first_of_three
      bytes = get_rest_of_bytes(byte_stream, 2)
      bytes.unshift(byte) unless bytes.nil?
    when :first_of_four
      bytes = get_rest_of_bytes(byte_stream, 3)
      bytes.unshift(byte) unless bytes.nil?
    else
      bytes = nil
    end

    if bytes.nil?
      invalid_char_cnt += 1
      cp = INVALID_CODE_POINT
    else
      cp = code_point(bytes)
    end

    char_formatter.add_char(byte_offset, char_offset, cp)

    if char_offset % width == (width - 1)
      char_formatter.print_line(width)
    end

    char_offset += 1
  end

  char_formatter.print_line(width)

  invalid_char_cnt
end

def parse_options
  options = {
    :render => true,
    :width => DEFAULT_WIDTH,
    :invalid_char => INVALID_BYTES,
    :unprintable_char => UNPRINTABLE_CODE_POINT,
  }

  OptionParser.new do |opts|
    opts.banner =
      "usage: #{$0} [OPTIONS] [FILE]\n" +
      "       #{$0} -b [-n] BYTE ...\n"

    opts.on("-i", "--invalid-code-point HEX_CODE_POINT") do |arg|
      options[:invalid_bytes] = arg.to_i(16)
    end

    opts.on("-u", "--unprintable-code-point HEX_CODE_POINT") do |arg|
      options[:unprintable_char] = arg.to_i(16)
    end

    opts.on("-w", "--width NUM") do |arg|
      options[:width] = arg.to_i
      if options[:width] < 1
        raise "invalid width: #{options[:width]}"
      end
    end

    opts.on("-b", "--byte-offset") do
      options[:byte_offset] = true
    end

    opts.on("-c", "--char-offset") do
      options[:char_offset] = true
    end

    opts.on("--no-render") do
      options[:render] = false
    end

    opts.on("-a", "--arg") do
      options[:arg] = true
    end

    opts.on("-n", "--name-lookup") do
      options[:name_lookup] = true
    end

    opts.on("-s", "--surrogate-pairs") do
      options[:surrogate_pairs] = true
    end

  end.parse!

  options
end

if $0 == __FILE__

  options = parse_options

  if options[:name_lookup]
    options[:unicode_data] = UnicodeData.new(UNICODE_DATA_CACHE)
    # FIXME: throw error if width was set
    options[:width] = 1
  end

  if options[:arg]
    if ARGV.size > 0
      byte_stream = ArrayByteStream.new(ARGV, options)
    end

  else
    if ARGV[0]
      input_stream = File.open(ARGV[0])
    else
      input_stream = $stdin
    end
    byte_stream = IOByteStream.new(input_stream, options)
  end

  invalid_chars = utf8_stream_to_unicode(byte_stream, $stdout, options)
  exit (invalid_chars > 0 ? 2 : 0)
end
