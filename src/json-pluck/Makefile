MAKEFLAGS += --warn-undefined-variables
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

json-pluck: json_pluck.c
	gcc -O2 -o $@ $<

.PHONY: all
all: json-pluck

output:
	mkdir $@

output/%.json: test/input/%.json | output
	./json-pluck < $< > $@
	diff test/expected.output/$*.json $@

tests := sample sample2
test_files := $(patsubst %,output/%.json,$(tests))

.PHONY: test
test: $(test_files)

.PHONY: check
check: test

.PHONY: clean.test
clean.test:
	rm -rf output

.PHONY: clean.build
clean.build:
	rm json-pluck

.PHONY: clean
clean: clean.test
