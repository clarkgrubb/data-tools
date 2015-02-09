MAKEFLAGS += --warn-undefined-variables
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

scripts_url := http://unicode.org/Public/UNIDATA/Scripts.txt

Scripts.txt:
	wget $(scripts_url)

utf8_script.c: Scripts.txt utf8_script.c.erb
	./generate.rb $^ > $@

utf8-script: utf8_script.c
	gcc -std=c11 -o $@ $<

.PHONY: all
all: utf8-script

output:
	mkdir $@

output/%.tsv: test/input/%.csv | output
	./utf8-script < $< > $@
	diff test/expected.output/$*.tsv $@

tests := one two
test_files := $(patsubst %,output/%.tsv,$(tests))

.PHONY: test
test: $(test_files)

rubocop:
	find . -name '*.rb' | xargs rubocop -D

clean:
	rm -rf utf8_script.c

clobber: clean
	rm utf8-script
