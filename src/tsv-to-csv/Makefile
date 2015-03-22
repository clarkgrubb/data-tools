MAKEFLAGS += --warn-undefined-variables
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

tsv-to-csv: tsv_to_csv.c
	gcc -o $@ $<

.PHONY: all
all: tsv-to-csv

output:
	mkdir $@

output/%.tsv: test/input/%.tsv | output
	./tsv-to-csv < $< > $@
	diff test/expected.output/$*.csv $@

tests := one two
test_files := $(patsubst %,output/%.tsv,$(tests))

.PHONY: test
test: $(test_files)

clean:
	rm -rf output

clobber: clean
	rm tsv-to-csv
