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

output/%.tab: test/input/%.csv csv-to-tab | output
	./csv-to-tab < $< > $@
	diff test/expected.output/$*.tab $@

tests := one two three four
test_files := $(patsubst %,output/%.tab,$(tests))

.PHONY: test.default
test.default: csv-to-tab
	./csv-to-tab -x < test/input/backslash.csv > output/backslash.default.tab
	diff test/expected.output/backslash.default.tab output/backslash.default.tab


.PHONY: test.escape
test.escape: csv-to-tab
	./csv-to-tab -e < test/input/tab.csv > output/tab.escape.tab
	diff test/expected.output/tab.escape.tab output/tab.escape.tab
	./csv-to-tab -e < test/input/cr.csv > output/cr.escape.tab
	diff test/expected.output/cr.escape.tab output/cr.escape.tab
	./csv-to-tab -e < test/input/newline.csv > output/newline.escape.tab
	diff test/expected.output/newline.escape.tab output/newline.escape.tab
	./csv-to-tab -e < test/input/backslash.csv > output/backslash.escape.tab
	diff test/expected.output/backslash.escape.tab output/backslash.escape.tab

.PHONY: test.replace
test.replace: csv-to-tab
	./csv-to-tab -r < test/input/tab.csv > output/tab.replace.tab
	diff test/expected.output/tab.replace.tab output/tab.replace.tab
	./csv-to-tab -r < test/input/cr.csv > output/cr.replace.tab
	diff test/expected.output/cr.replace.tab output/cr.replace.tab
	./csv-to-tab -r < test/input/newline.csv > output/newline.replace.tab
	diff test/expected.output/newline.replace.tab output/newline.replace.tab
	./csv-to-tab -r < test/input/backslash.csv > output/backslash.replace.tab
	diff test/expected.output/backslash.replace.tab output/backslash.replace.tab


.PHONY: test.strip
test.strip: csv-to-tab
	./csv-to-tab -x < test/input/tab.csv > output/tab.strip.tab
	diff test/expected.output/tab.strip.tab output/tab.strip.tab
	./csv-to-tab -x < test/input/cr.csv > output/cr.strip.tab
	diff test/expected.output/cr.strip.tab output/cr.strip.tab
	./csv-to-tab -x < test/input/newline.csv > output/newline.strip.tab
	diff test/expected.output/newline.strip.tab output/newline.strip.tab
	./csv-to-tab -x < test/input/backslash.csv > output/backslash.strip.tab
	diff test/expected.output/backslash.strip.tab output/backslash.strip.tab

.PHONY: test
test: $(test_files) test.default test.escape test.replace test.strip

.PHONY: cppcheck
cppcheck:
	cppcheck --enable=all csv_to_tab.c

.PHONY: check
check: cppcheck test

state.png: state.dot
	dot -Tpng < $< > $@

.PHONY: clean.build
clean.build:
	rm csv-to-tab

.PHONY: clean.test
clean.test:
	rm -rf output

.PHONY: clean
clean: clean.test
