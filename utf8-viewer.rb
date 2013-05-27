#!/usr/bin/env ruby

UNIDATA_URL = 'ftp://ftp.unicode.org/Public/UNIDATA/UnicodeData.txt'

ZEROS_BYTE = 0
ONES_BYTE = 2**8 - 1

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

# http://en.wikipedia.org/wiki/UTF-8#Description
#

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

def to_hex(cp)
  sprintf("%04X", cp)
end

def lookup_code_point(code_point)
  unidata = `curl #{UNIDATA_URL} 2> /dev/null | grep '^#{to_hex(code_point)};'`
  unidata.split(';')[1]
end

def check_prefixes(bytes)
  raise "too many bytes" if bytes.size > 4
  raise "no bytes" if bytes.size == 0

  prefix_masks = PREFIX_MASK[bytes.size]
  prefixes = PREFIX[bytes.size]

  bytes.each_with_index do |byte, i|
    if prefix_masks[i] & byte != prefixes[i]
      raise "arg #{i} is not a valid unicode byte: #{byte}"
    end
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

def check_bytes(bytes)
  bytes.each_with_index do |byte, i|
    if byte < ZEROS_BYTE or byte > ONES_BYTE
      raise "arg #{i} is not a byte: #{byte}"
    end
  end
end

def args_to_bytes(args)
  args.map do |arg|
    case arg
    when /^0[xX]/
      arg.to_i(16)
    when /^0[bB]/
      arg.to_i(2)
    when /^0/
      arg.to_i(8)
    else
      arg.to_i
    end
  end
end

if $0 == __FILE__

  lookup_name = false

  if ARGV[0] == '-n' or ARGV[0] == '--name'
    lookup_name = true
    ARGV.shift
  end

  if ARGV.size == 0
    puts
    puts "USAGE: utf8-to-unicode.rb [-n|--name] BYTE ..."
    puts
    puts "   format of BYTEs can be binary, octal, decimal, or hex"
    puts
    puts "   use 0b, 0, <none>, and 0x prefixes, respectively"
    puts
    puts "   with -n|--name flag, look up Unicode character name."
    puts "   This requires internet access."
    puts

    exit 1
  end

  bytes = args_to_bytes(ARGV)
  check_bytes(bytes)
  check_prefixes(bytes)

  cp = code_point(bytes)
  puts "U+" + to_hex(cp)
  if lookup_name
    puts lookup_code_point(cp)
  end
end
