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

tests := one two three four
test_files := $(patsubst %,output/%.tab,$(tests))

state.png: state.dot
	dot -Tpng < $< > $@

.PHONY: test
test: $(test_files)

.PHONY: cppcheck
cppcheck:
	cppcheck --enable=all csv_to_tab.c

clean:
	rm -rf output

clobber: clean
	rm csv-to-tab
