MAKEFLAGS += --warn-undefined-variables
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

tab-to-csv: tab_to_csv.c
	gcc -O2 -o $@ $<

.PHONY: all
all: tab-to-csv

output:
	mkdir $@

output/%.csv: test/input/%.tab | output
	./tab-to-csv < $< > $@
	diff test/expected.output/$*.csv $@

tests := one
test_files := $(patsubst %,output/%.csv,$(tests))

.PHONY: test
test: $(test_files)

clean:
	rm -rf output

clobber: clean
	rm tab-to-csv
