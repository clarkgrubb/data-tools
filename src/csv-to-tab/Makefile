MAKEFLAGS += --warn-undefined-variables
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

csv-to-tab: csv_to_tab.c
	gcc -O2 -o $@ $<

.PHONY: all
all: csv-to-tab

output:
	mkdir $@

output/%.tab: test/input/%.csv | output
	./csv-to-tab < $< > $@
	diff test/expected.output/$*.tab $@

tests := one two three
test_files := $(patsubst %,output/%.tab,$(tests))

state.png: state.dot
	dot -Tpng < $< > $@

.PHONY: test
test: $(test_files)

clean:
	rm -rf output

clobber: clean
	rm csv-to-tab
