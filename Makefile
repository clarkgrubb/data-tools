MAKEFLAGS += --warn-undefined-variables
SHELL := /bin/bash
.SHELLFLAGS := -o pipefail
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

man1_source := $(wildcard doc/*.1.md)
man1_targets := $(patsubst doc/%.md,man/%,$(man1_source))
LOCAL_INSTALL_DIR ?= $(shell if [ -d ~/Bin ]; then echo ~/Bin; else echo /usr/local/bin; fi)
LOCAL_MAN_DIR ?= $(shell if [ -d ~/Man ]; then echo ~/Man; else echo /usr/local/share/man; fi)
LOCAL_MAN1_DIR := $(LOCAL_MAN_DIR)/man1
pwd := $(shell pwd)
harnesses_base := csv_to_json csv_to_tsv dom_awk highlight join_tsv json_awk
harnesses_base += reservoir_sample trim_tsv tsv_to_csv tsv_to_json utf8_viewer
harnesses_base += xlsx_to_csv
harnesses := $(patsubst %,harness.%,$(harnesses_base))
hexedit := hexedit/hexedit
gem_pkgs := json nokogiri
pip_pkgs := xlrd
tawk := tawk/tawk
VPATH = test

.PHONY: all build build-hexedit build-tawk TAGS check clean test man install-hexedit install-tawk install install-build install-man install-script
.SECONDARY:

setup.ruby:
	gem install $(gem_pkgs)

setup.python:
	pip install $(pip_pkgs)

setup: setup.ruby setup.python

$(hexedit):
	(cd hexedit; make)

$(tawk):
	(cd tawk; make tawk)

build-hexedit: $(hexedit)

build-tawk: $(tawk)

build: install-hexedit install-tawk

install-hexedit: $(hexedit)
	ln -sf $(pwd)/hexedit/hexedit/hexedit $(LOCAL_INSTALL_DIR)/hexedit

install-tawk: $(tawk)
	ln -sf $(pwd)/tawk/tawk $(LOCAL_INSTALL_DIR)/tawk

install-build: install-hexedit install-tawk

install-script:
	ln -sf $(pwd)/csv_to_json.py $(LOCAL_INSTALL_DIR)/csv-to-json
	ln -sf $(pwd)/csv_to_tsv.py $(LOCAL_INSTALL_DIR)/csv-to-tsv
	ln -sf $(pwd)/date_seq.py $(LOCAL_INSTALL_DIR)/date-seq
	ln -sf $(pwd)/dom-awk.rb $(LOCAL_INSTALL_DIR)/dom-awk
	ln -sf $(pwd)/header-sort.sh $(LOCAL_INSTALL_DIR)/header-sort
	ln -sf $(pwd)/highlight.py $(LOCAL_INSTALL_DIR)/highlight
	ln -sf $(pwd)/join_tsv.py $(LOCAL_INSTALL_DIR)/join-tsv
	ln -sf $(pwd)/json-awk.rb $(LOCAL_INSTALL_DIR)/json-awk
	ln -sf $(pwd)/reservoir_sample.py $(LOCAL_INSTALL_DIR)/reservoir-sample
	ln -sf $(pwd)/set-diff.sh $(LOCAL_INSTALL_DIR)/set-diff
	ln -sf $(pwd)/set-intersect.sh $(LOCAL_INSTALL_DIR)/set-intersect
	ln -sf $(pwd)/trim_tsv.py $(LOCAL_INSTALL_DIR)/trim-tsv
	ln -sf $(pwd)/tsv_to_csv.py $(LOCAL_INSTALL_DIR)/tsv-to-csv
	ln -sf $(pwd)/tsv_to_json.py $(LOCAL_INSTALL_DIR)/tsv-to-json
	ln -sf $(pwd)/utf8-viewer.rb $(LOCAL_INSTALL_DIR)/utf8-viewer
	ln -sf $(pwd)/xlsx_to_csv.py $(LOCAL_INSTALL_DIR)/xls-to-csv
	ln -sf $(pwd)/xlsx_to_csv.py $(LOCAL_INSTALL_DIR)/xlsx-to-csv

# To generate the man pages `pandoc` must be installed.  On Mac go to
#
#    http://johnmacfarlane.net/pandoc/installing.html
#
#  and download the installer.  On Ubuntu there is a package:
#
#    $ sudo apt-get install pandoc
#
# An uninstalled man page can be viewed with the man command:
#
#    $ man doc/foo.1
#
man/%.1: doc/%.1.md
	pandoc -s -s -w man $< -o $@

man_targets: $(man1_targets)

$(LOCAL_MAN1_DIR):
	mkdir -p $@

install-man: $(LOCAL_MAN1_DIR)
	if [ ! -d $(LOCAL_MAN_DIR)/man1 ]; then \
	echo directory does not exist: $(LOCAL_MAN_DIR)/man1; \
	false; \
	fi
	for target in $(man1_targets); \
	do \
	cp $$target $(LOCAL_MAN_DIR)/man1; \
	done

install: install-build install-script install-man

all: build
	@echo
	@echo 'To install Ruby gems and Python packages:'
	@echo
	@echo '   $$ sudo make setup'
	@echo
	@echo 'To install data tools and man pages:'
	@echo
	@echo '   $$ make install'
	@echo

output output/csv_to_json output/csv_to_tsv output/dom_awk output/highlight:
	mkdir -p $@

output/join_tsv output/json_awk output/reservoir_sample output/trim_tsv:
	mkdir -p $@

output/tsv_to_csv output/tsv_to_json output/utf8_viewer output/xlsx_to_csv:
	mkdir -p $@

harness.csv_to_json: csv_to_json/test.csv | output/csv_to_json
	./csv_to_json.py $< > output/csv_to_json/test.csv_to_json.json
	echo $$'λ,two\nthree,four' | ./csv_to_json.py > output/csv_to_json/unicode.json
	echo $$'λ,two\nthree,four' | \
	./csv_to_json.py --header=first,second > output/csv_to_json/unicode2.json

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

harness.join_tsv: | output/join_tsv
	./join_tsv.py --column=url \
	test/join_tsv/input1.tsv \
	test/join_tsv/input2.tsv \
	> output/join_tsv/output.tsv
	diff test/join_tsv/expected.output.tsv output/join_tsv/output.tsv
	#
	./join_tsv.py --column=url \
	test/join_tsv/input1.null.tsv \
	test/join_tsv/input2.null.tsv \
	> output/join_tsv/output.null.tsv
	diff test/join_tsv/expected.output.tsv output/join_tsv/output.null.tsv
	#
	./join_tsv.py --column=url --left \
	test/join_tsv/input1.left.tsv \
	test/join_tsv/input2.left.tsv \
	> output/join_tsv/output.left.tsv
	diff test/join_tsv/expected.output.left.tsv output/join_tsv/output.left.tsv
	#
	./join_tsv.py --column=url --right \
	test/join_tsv/input2.left.tsv \
	test/join_tsv/input1.left.tsv \
	> output/join_tsv/output.right.tsv
	diff test/join_tsv/expected.output.right.tsv output/join_tsv/output.right.tsv
	#
	./join_tsv.py --column=url --null=NULL \
	test/join_tsv/input1.NULL_VALUE.tsv \
	test/join_tsv/input2.NULL_VALUE.tsv \
	> output/join_tsv/output.NULL_VALUE.tsv
	diff test/join_tsv/expected.output.NULL_VALUE.tsv output/join_tsv/output.NULL_VALUE.tsv
	#
	./join_tsv.py --left-column=url1 --right-column=url2 \
	test/join_tsv/input1.diff.tsv \
	test/join_tsv/input2.diff.tsv \
	> output/join_tsv/output.diff.tsv
	diff test/join_tsv/expected.output.diff.tsv output/join_tsv/output.diff.tsv


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

# doesn't pass with Ruby 1.8:
#
harness.utf8_viewer: | output/utf8_viewer
	-ruby -e '(0..255).each { |i| print i.chr }' \
	| ./utf8-viewer.rb -bc \
	> output/utf8_viewer/bytes.bcr.out
	diff test/utf8_viewer/expected.bytes.bcr.out output/utf8_viewer/bytes.bcr.out
	#
	./utf8-viewer.rb -a 33 34 35 > output/utf8_viewer/arg.decimal.out
	diff test/utf8_viewer/expected.arg.out output/utf8_viewer/arg.decimal.out
	#
	./utf8-viewer.rb -a 041 042 043 > output/utf8_viewer/arg.octal.out
	diff test/utf8_viewer/expected.arg.out output/utf8_viewer/arg.octal.out

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

pep8:
	pep8 *.py

TAGS:
	find . -name '*.py' | xargs etags

clean:
	-find . -name '*.pyc' | xargs rm
	-find doc -name '*.[0-9]' | xargs rm
	-find . -name '*.html' | xargs rm
	-rm TAGS
	-rm -rf output
	$(MAKE) -C tawk $@
	$(MAKE) -C hexedit $@
