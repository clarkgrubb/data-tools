% DOM-AWK(1)
% Clark Grubb
% February 17, 2013


# NAME

dom-awk - read HTML or XML into a DOM object and process it with a Ruby script.

# SYNOPSIS

dom-awk [-x|-h] (-f SCRIPT\_PATH) | RUBY\_SCRIPT) [XML\_OR\_HTML_FILE]

# DESCRIPTION

Read an HTML or XML document from a command line path or standard input and process it with a Ruby script.  The Ruby script can be specified on the command line like `awk`, or the Ruby code can be in a file whose path is provided with the `-f` option.

The HTML/XML document is parsed using the Ruby Nokogiri library and made available to the Ruby script which is provided as a command line argument.  The Ruby DOM object is put in the global accumulator variable $_.

A Nokogiri DOM object is a hierarchical tree of Nodes.  Here are some of the most useful Node methods:

    []           treat Node as Hash of its attributes
    children()   return NodeSet of children
    content()
    css()        return NodeSet which matches CSS rule
    document()
    parent()
    to_s()
    xpath()      return NodeSet 

Some useful NodeSet methods.

    []
    each()
    filter()
    include?()
    length()

A summary of XPath and CSS selectior syntax:

                         xpath                css             dom
                         -------------------  --------------  -----------------------------
    by id                //*[@id="foo"]       #foo            getElementById("foo")
    by class             //*[@class="foo"]    .foo            getElementsByClassName("foo")
    by tag               //div                div             getElementsByTagName("div")
    by attribute         //*[@title]          [title]
    by attribute value   //*[@title="foo"]    [title="foo"]
    union                //h1 | //h2          h1, h2
    child                [@class="foo"]/li    .foo > li
    descendant           [@class="foo"]//td   .foo td


# EXAMPLES

    curl www.google.com | dom-awk  '$_.xpath("//a").each {|o| puts o["href"] }'

    echo '<xml><foo>bar</foo></xml>' | dom-awk '$_.xpath("//foo").each { |o| puts o.content }'

# OPTIONS

-f SCRIPT\_PATH, \--file=SCRIPT\_PATH
: Use Ruby code in SCRIPT\_PATH to process input.

-h, \--html
: Used to indicate input is HTML.

-x, \--xml
: Used to indicate input is XML.

# SEE ALSO

`curl` (1), `w3m` (1)

http://nokogiri.org/Nokogiri/XML/Node.html
