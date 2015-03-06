MAKEFLAGS += --warn-undefined-variables
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

scripts_url := http://unicode.org/Public/UNIDATA/Scripts.txt
unicode_data_url := ftp://ftp.unicode.org/Public/UNIDATA/UnicodeData.txt

Scripts.txt:
	wget $(scripts_url)

UnicodeData.txt:
	wget $(unicode_data_url)

utf8_script.c: Scripts.txt utf8_script.c.erb
	./generate_script.rb $^ > $@

utf8-script: utf8_script.c
	gcc -O2 -o $@ $<

utf8_category.c: UnicodeData.txt utf8_category.c.erb
	./generate_category.rb $^ > $@

utf8-category: utf8_category.c
	gcc -O2 -o $@ $<


.PHONY: all
all: utf8-script utf8-category

output:
	mkdir $@

output/%: test/input/% | output
	./utf8-script < $< > $@
	diff test/expected.output/$* $@

tests := one two three
test_files := $(patsubst %,output/%.txt,$(tests))

.PHONY: test
test: $(test_files)

rubocop:
	find . -name '*.rb' | xargs rubocop -D

clean:
	rm -rf utf8_script.c

clobber: clean
	rm utf8-script
