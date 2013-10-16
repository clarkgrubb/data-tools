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
harnesses_base := csv_to_json csv_to_tsv dom_awk highlight json_awk
harnesses_base += reservoir_sample trim_tsv tsv_to_csv tsv_to_json utf8_viewer
harnesses_base += xlsx_to_csv
harnesses := $(patsubst %,harness.%,$(harnesses_base))
gem_pkgs := json nokogiri
pip_pkgs := xlrd
VPATH = test

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
	ln -sf $(pwd)/reservoir_sample.py $(LOCAL_INSTALL_DIR)/reservoir-sample
	ln -sf $(pwd)/set-diff.sh $(LOCAL_INSTALL_DIR)/set-diff
	ln -sf $(pwd)/set-intersect.sh $(LOCAL_INSTALL_DIR)/set-intersect
	ln -sf $(pwd)/trim_tsv.py $(LOCAL_INSTALL_DIR)/trim-tsv
	ln -sf $(pwd)/tawk/tawk $(LOCAL_INSTALL_DIR)/tawk
	ln -sf $(pwd)/tsv_to_csv.py $(LOCAL_INSTALL_DIR)/tsv-to-csv
	ln -sf $(pwd)/tsv_to_json.py $(LOCAL_INSTALL_DIR)/tsv-to-json
	ln -sf $(pwd)/utf8-viewer.rb $(LOCAL_INSTALL_DIR)/utf8-viewer
	ln -sf $(pwd)/xlsx_to_csv.py $(LOCAL_INSTALL_DIR)/xls-to-csv
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

all:
	@echo
	@echo 'To install data-tools:'
	@echo
	@echo '   $$ sudo make setup'
	@echo
	@echo '   $$ make install'
	@echo

output output/csv_to_json output/csv_to_tsv output/dom_awk output/highlight:
	mkdir -p $@

output/json_awk output/reservoir_sample output/trim_tsv output/tsv_to_csv:
	mkdir -p $@

output/tsv_to_json output/utf8_viewer output/xlsx_to_csv:
	mkdir -p $@

harness.csv_to_json: csv_to_json/test.csv | output/csv_to_json
	./csv_to_json.py $< > output/csv_to_json/test.csv_to_json.json
	#diff output/csv_to_json/test.csv_to_json.json test/expected.test.csv_to_json.json

harness.csv_to_tsv: | output/csv_to_tsv
	echo -n $$'one,two\nthree,four' | ./csv_to_tsv.py > output/csv_to_tsv/test.csv_to_tsv.tsv
	diff test/csv_to_tsv/expected.tsv output/csv_to_tsv/test.csv_to_tsv.tsv
	echo $$'λ,two\nthree,four' | ./csv_to_tsv.py > output/csv_to_tsv/unicode.tsv
	diff test/csv_to_tsv/expected.unicode.tsv output/csv_to_tsv/unicode.tsv

harness.dom_awk: dom_awk/input.txt | output/dom_awk
	./dom-awk.rb '$$_.xpath("//a").each { |o| puts o["href"] }' $< \
	> output/dom_awk/output.txt
	diff test/dom_awk/expected.output.txt output/dom_awk/output.txt

harness.highlight: highlight/input.txt | output/highlight
	./highlight.py control < $< > output/highlight/output1.txt
	diff test/highlight/expected.output.txt output/highlight/output1.txt
	./highlight.py control $< > output/highlight/output2.txt
	diff test/highlight/expected.output.txt output/highlight/output2.txt
	./highlight.py -r control < $< > output/highlight/output3.txt
	diff test/highlight/expected.output.txt output/highlight/output3.txt
	./highlight.py -r control $< > output/highlight/output4.txt
	diff test/highlight/expected.output.txt output/highlight/output4.txt

harness.json_awk: json_awk/input.json | output/json_awk
	./json-awk.rb 'puts $$_["foo"]' $< > output/json_awk/output1.txt
	diff test/json_awk/expected.output.txt output/json_awk/output1.txt
	./json-awk.rb 'puts $$_["foo"]' < $< > output/json_awk/output2.txt
	diff test/json_awk/expected.output.txt output/json_awk/output2.txt

harness.reservoir_sample: reservoir_sample/input.txt | output/reservoir_sample
	./reservoir_sample.py -r 17 -s 3 < $< > output/reservoir_sample/output.txt
	diff test/reservoir_sample/expected.output.txt output/reservoir_sample/output.txt

harness.trim_tsv: | output/trim_tsv
	echo -n $$' one \t two \n three \t four' | ./trim_tsv.py > output/trim_tsv/trim_tsv.tsv
	diff test/trim_tsv/expected.trim_tsv.tsv output/trim_tsv/trim_tsv.tsv
	./trim_tsv.py test/trim_tsv/input.tsv > output/trim_tsv/output2.tsv
	diff test/trim_tsv/expected.trim_tsv.tsv output/trim_tsv/output2.tsv

harness.tsv_to_csv: tsv_to_csv/escapes.tsv | output/tsv_to_csv
	./tsv_to_csv.py -u $< | ./csv_to_tsv.py -e > output/tsv_to_csv/escape.tsv
	diff $< output/tsv_to_csv/escape.tsv

harness.tsv_to_json: tsv_to_json/test.tsv | output/tsv_to_json
	./tsv_to_json.py $< > output/tsv_to_json/test.tsv_to_json.json

harness.utf8_viewer: | output/utf8_viewer
	-ruby -e '(0..255).each { |i| print i.chr }' \
	| ./utf8-viewer.rb -bc \
	> output/utf8_viewer/bytes.bcr.out
	diff test/utf8_viewer/expected.bytes.bcr.out output/utf8_viewer/bytes.bcr.out

harness.xlsx_to_csv: xlsx_to_csv/test.xlsx | output/xlsx_to_csv
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

test.python:
	find . -name 'test*.py' | xargs python

test.ruby:
	find . -name 'test*.rb' | xargs ruby

test: test.python test.ruby

check: test harness

clean:
	-find . -name '*.pyc' | xargs rm
	-find doc -name '*.[0-9]' | xargs rm
	-find . -name '*.html' | xargs rm
	-rm TAGS
	-rm -rf output
