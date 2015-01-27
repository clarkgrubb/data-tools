MAKEFLAGS += --warn-undefined-variables
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

fast-csv-to-tsv: fast_csv_to_tsv.c
	gcc -std=c11 -o $@ $<

.PHONY: all
all: fast-csv-to-tsv

output:
	mkdir $@

output/%.tsv: test/input/%.csv | output
	./fast-csv-to-tsv < $< > $@
	diff test/expected.output/$*.tsv $@

tests := one two
test_files := $(patsubst %,output/%.tsv,$(tests))

.PHONY: test
test: $(test_files)

clean:
	rm -rf output

clobber: clean
	rm fast-csv-to-tsv
