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

.PHONY: test.unescape
test.unescape: tab-to-csv
	./tab-to-csv -u < test/input/newline.tab > output/newline.unescape.csv
	diff test/expected.output/newline.unescape.csv output/newline.unescape.csv
	./tab-to-csv -u < test/input/cr.tab > output/cr.unescape.csv
	diff test/expected.output/cr.unescape.csv output/cr.unescape.csv
	./tab-to-csv -u < test/input/tab.tab > output/tab.unescape.csv
	diff test/expected.output/tab.unescape.csv output/tab.unescape.csv
	./tab-to-csv -u < test/input/backslash.tab > output/backslash.unescape.csv
	diff test/expected.output/backslash.unescape.csv output/backslash.unescape.csv

.PHONY: test.default
test.default: tab-to-csv
	./tab-to-csv < test/input/newline.tab > output/newline.default.csv
	diff test/expected.output/newline.default.csv output/newline.default.csv
	./tab-to-csv < test/input/cr.tab > output/cr.default.csv
	diff test/expected.output/cr.default.csv output/cr.default.csv
	./tab-to-csv < test/input/tab.tab > output/tab.default.csv
	diff test/expected.output/tab.default.csv output/tab.default.csv
	./tab-to-csv < test/input/backslash.tab > output/backslash.default.csv
	diff test/expected.output/backslash.default.csv output/backslash.default.csv

.PHONY: test
test: $(test_files) test.unescape test.default

.PHONY: cppcheck
cppcheck:
	cppcheck --enable=all tab_to_csv.c

.PHONY: check
check: cppcheck test

.PHONY: clean.build
clean.build:
	rm tab-to-csv

.PHONY: clean.test
clean.test:
	rm -rf output

.PHONY: clean
clean: clean.test
