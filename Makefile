MAKEFLAGS += --warn-undefined-variables
SHELL := /bin/bash
.SHELLFLAGS := -o pipefail
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

man1_source := $(wildcard doc/*.1.md)
man1_targets := $(patsubst %.md,%,$(man1_source))
LOCAL_INSTALL_DIR ?= $(shell if [ -d ~/Bin ]; then echo ~/Bin; else echo /usr/local/bin; fi)
LOCAL_MAN_DIR ?= $(shell if [ -d ~/Man ]; then echo ~/Man; else echo /usr/local/share/man; fi)
pwd := $(shell pwd)
harnesses_base := csv_to_json csv_to_tsv tsv_to_csv tsv_to_json xlsx_to_csv
harnesses := $(patsubst %,harness.%,$(harnesses_base))
gem_pkgs := nokogiri
pip_pkgs := xlrd

.PHONY: all TAGS check clean test man install install-man
.SECONDARY:

setup.ruby:
	gem install $(gem_pkgs)

setup.python:
	pip install $(pip_pkgs)

setup: setup.ruby setup.python

build:
	(cd tawk; make tawk)
	(cd hexedit; make)

install: build
	ln -sf $(pwd)/csv_to_json.py $(LOCAL_INSTALL_DIR)/csv-to-json
	ln -sf $(pwd)/csv_to_tsv.py $(LOCAL_INSTALL_DIR)/csv-to-tsv
	ln -sf $(pwd)/date_seq.py $(LOCAL_INSTALL_DIR)/date-seq
	ln -sf $(pwd)/dom-awk.rb $(LOCAL_INSTALL_DIR)/dom-awk
	ln -sf $(pwd)/header-sort.sh $(LOCAL_INSTALL_DIR)/header-sort
	ln -sf $(pwd)/hexedit/hexedit/hexedit $(LOCAL_INSTALL_DIR)/hexedit
	ln -sf $(pwd)/highlight.py $(LOCAL_INSTALL_DIR)/highlight
	ln -sf $(pwd)/json-awk.rb $(LOCAL_INSTALL_DIR)/json-awk
	ln -sf $(pwd)/set-diff.sh $(LOCAL_INSTALL_DIR)/set-diff
	ln -sf $(pwd)/set-intersect.sh $(LOCAL_INSTALL_DIR)/set-intersect
	ln -sf $(pwd)/strip_columns.py $(LOCAL_INSTALL_DIR)/strip-columns
	ln -sf $(pwd)/tawk/tawk $(LOCAL_INSTALL_DIR)/tawk
	ln -sf $(pwd)/tsv_to_csv.py $(LOCAL_INSTALL_DIR)/tsv-to-csv
	ln -sf $(pwd)/tsv_to_json.py $(LOCAL_INSTALL_DIR)/tsv-to-json
	ln -sf $(pwd)/utf8-viewer.rb $(LOCAL_INSTALL_DIR)/utf8-viewer
	ln -sf $(pwd)/xlsx_to_csv.py $(LOCAL_INSTALL_DIR)/xlsx-to-csv
	@echo Run 'make install-man' to install man pages.

install-man: man
	if [ ! -d $(LOCAL_MAN_DIR)/man1 ]; then \
	echo directory does not exist: $(LOCAL_MAN_DIR)/man1; \
	false; \
	fi
	for target in $(man1_targets); \
	do \
	cp $$target $(LOCAL_MAN_DIR)/man1; \
	done

data/UnicodeData.txt:
	curl ftp://ftp.unicode.org/Public/UNIDATA/UnicodeData.txt > $@

download: data/UnicodeData.txt

pep8:
	pep8 *.py

# An uninstalled man page can be viewed with the man command:
#
#   man doc/foo.1
#
man: $(man1_targets)

doc/%.1: doc/%.1.md
	pandoc -s -s -w man $< -o $@

TAGS:
	find . -name '*.py' | xargs etags

all: man

output output/xlsx_to_csv:
	mkdir -p $@

harness.tsv_to_csv.escape: test/escapes.tsv | output
	./tsv_to_csv.py -u $< | ./csv_to_tsv.py -e > output/escape.tsv
	diff $< output/escape.tsv

harness.csv_to_json: test/test.csv | output
	./csv_to_json.py $< > output/test.csv_to_json.json
	#diff output/test.csv_to_json.json test/expected.test.csv_to_json.json

harness.tsv_to_json: test/test.tsv | output
	./tsv_to_json.py $< > output/test.tsv_to_json.json

harness.tsv_to_csv: harness.tsv_to_csv.escape

harness.csv_to_tsv:
	echo -n $$'one,two\nthree,four' | csv-to-tsv > output/test.csv_to_tsv.tsv
	diff test/expected.csv_to_tsv.tsv output/test.csv_to_tsv.tsv

harness.xlsx_to_csv: test/xlsx_to_csv/test.xlsx | output/xlsx_to_csv
	./xlsx_to_csv.py --list $< > output/xlsx_to_csv/list.out
	./xlsx_to_csv.py --sheet=three_rows_three_cols $< output/xlsx_to_csv/3r3c.csv
	./xlsx_to_csv.py --sheet=unicode $< output/xlsx_to_csv/unicode.csv
	./xlsx_to_csv.py --sheet=spaces $< output/xlsx_to_csv/spaces.csv
	./xlsx_to_csv.py --sheet=dates $< output/xlsx_to_csv/dates.csv
	diff output/xlsx_to_csv/list.out test/xlsx_to_csv/expected.list.out
	diff output/xlsx_to_csv/3r3c.csv test/xlsx_to_csv/expected.3r3c.csv
	diff output/xlsx_to_csv/unicode.csv test/xlsx_to_csv/expected.unicode.csv
	diff output/xlsx_to_csv/spaces.csv test/xlsx_to_csv/expected.spaces.csv
	diff output/xlsx_to_csv/dates.csv test/xlsx_to_csv/expected.dates.csv

harness: $(harnesses)

check.python:
	find . -name 'test*.py' | xargs python

check.ruby:
	find . -name 'test*.rb' | xargs ruby

check: check.python check.ruby

test: check

clean:
	-find . -name '*.pyc' | xargs rm
	-find doc -name '*.[0-9]' | xargs rm
	-find . -name '*.html' | xargs rm
	-rm TAGS
	-rm -rf output
