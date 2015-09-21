MAKEFLAGS += --warn-undefined-variables
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

json-array-to-stream: json_array_to_stream.c
	gcc -o $@ $<

.PHONY: all
all: json-array-to-stream

output:
	mkdir $@

output/%.json: test/input/%.json | output
	./json-array-to-stream < $< > $@
	diff test/expected.output/$*.json $@

tests := sample
test_files := $(patsubst %,output/%.json,$(tests))

.PHONY: test
test: $(test_files)

clean:
	rm -rf output
