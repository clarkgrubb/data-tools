require 'test/unit'
require './utf8-to-unicode'

class TestUTF8toUnicode < Test::Unit::TestCase

  def test_args_to_bytes

    bytes = args_to_bytes(['127'])

    assert_equal(1, bytes.size)
    assert_equal(127, bytes[0])

    bytes = args_to_bytes(['10', '20', '30'])
    assert_equal(3, bytes.size)
    assert_equal(10, bytes[0])
    assert_equal(20, bytes[1])
    assert_equal(30, bytes[2])

    bytes = args_to_bytes(['0200', '0377'])
    assert_equal(2, bytes.size)
    assert_equal(128, bytes[0])
    assert_equal(255, bytes[1])

    bytes = args_to_bytes(['0b1111'])
    assert_equal(1, bytes.size)
    assert_equal(15, bytes[0])

    bytes = args_to_bytes(['0x3bb'])
    assert_equal(1, bytes.size)
    assert_equal(955, bytes[0])

  end

  def test_check_bytes

    # valid bytes should not raise an exception
    #
    check_bytes((0...256).to_a)

    assert_raises(RuntimeError) do
      check_bytes([-1])
    end

    assert_raises(RuntimeError) do
      check_bytes([256])
    end
  end

  def test_code_point

    (0...128).each do |byte|
      assert_equal(byte, code_point([byte]))
    end

    bytes = args_to_bytes(['0304', '0200'])
    check_prefixes(bytes)
    assert_equal(0x100, code_point(bytes))

    bytes = args_to_bytes(['0342', '0200', '0250'])
    check_prefixes(bytes)
    assert_equal(0x2028, code_point(bytes))

  end

end
