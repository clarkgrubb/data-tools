MAKEFLAGS += --warn-undefined-variables
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

csv-to-tsv: csv_to_tsv.c
	gcc -O2 -o $@ $<

.PHONY: all
all: csv-to-tsv

output:
	mkdir $@

output/%.tsv: test/input/%.csv | output
	./csv-to-tsv < $< > $@
	diff test/expected.output/$*.tsv $@

tests := one two
test_files := $(patsubst %,output/%.tsv,$(tests))

state.png: state.dot
	dot -Tpng < $< > $@

.PHONY: test
test: $(test_files)

clean:
	rm -rf output

clobber: clean
	rm csv-to-tsv
