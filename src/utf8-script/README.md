# Overview

This utility takes UTF-8 encoded input and tallies the characters
by Unicode script.  For example:

    $ echo αλφα βετα foo bar | utf8-script
    4	Common
    8	Greek
    6	Latin


# Unicode Scripts

Each Unicode character belongs to a Unicode script.  Examples of
Unicode scripts are Latin, Greek, Cyrillic, Hebrew, Arabic,
Devanagari, Hangul, Hiragana, Katakana, and Han.

Some Unicode characters are classified as belonging to the Common,
Inherited, or Unknown scripts.

The Common characters include symbols which are shared by the scripts.
This includes most punctuation.  The Inherited characters are
combining marks  The Unknown characters are Unicode points to
which the Unicode standard has left undefined.

The mapping from Unicode point to script is described in
[Scripts.txt][1].

# Character Ranges

Unicode 7.0 defines 126 scripts including Unknown.  The characters in
a script often don't have contiguous points; in Scripts.txt they are
described by 1808 ranges.  However, we can reduce the number to 806
ranges, or 1404 ranges if we include ranges for gaps of Unknown
characters.

# Implementation Notes

A simple implementation would for each character check each of the
1404 ranges.  This would mean up to 2808 comparisons would be
performed for each character.  We can exit early when we find the
correct range.  Most characters, at least in the USA, are ASCII
characters, so if we perform the low point comparisons first, the
script might be reasonably fast on most inputs.

It seems better, however, to implement a decision tree which
implements some sort of bisection algorithm.  An optimal solution
might take into account the likelihood of the scripts or the
characters.  Not having such data, we will assume each range is
equally likely.  In some ways this is a bad assumption, but at least
it should minimize the maximum depth of our tree.  At each node of the
tree we compare the character `ch` against a new value `x`.

    [low, x)  [x, high)
    
Initially `low` is 0 and `high` is 0x120000.

If we want to test whether `[left, right]` intersects `[start,
ending)`, it is easier to check whether they are disjoint, which
happens when

    left >= ending || right < start

# Choosing Where to Divide the Interval 

If there is more than one range intersecting the current interval, we
divide it so as to maximize the information gain:

    H([low, high)) - H([low, x)) + H([x, high))

The information entropy `H` is

    H([a, b)) = - P([a, b)) log P([a, b)
    
We compute `P([a, b))` by assuming each range is equally likely:

    P([a, b)) = <# of ranges intersecting [a, b)> / 1404

# An Optimization for ASCII

Although most decision points are computed in the above manner, we
perform the first comparision at x = 128.  This keeps the path taken through
the decision tree short for ASCII characters.

[1]: http://unicode.org/Public/UNIDATA/Scripts.txt
[2]: http://www.unicode.org/reports/tr44/#General_Category_Values
