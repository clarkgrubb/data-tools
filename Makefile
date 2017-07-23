MAKEFLAGS += --warn-undefined-variables
SHELL := bash
.SHELLFLAGS := -e -o pipefail -c
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

LOCAL_INSTALL_DIR ?= $(shell if [ -d ~/Local/bin ]; then echo ~/Local/bin; else echo /usr/local/bin; fi)
LOCAL_MAN_DIR ?= $(shell if [ -d ~/Local/man ]; then echo ~/Local/man; else echo /usr/local/share/man; fi)

local_man1_dir := $(LOCAL_MAN_DIR)/man1
man1_source := $(wildcard doc/*.1.md)
man1_targets := $(patsubst doc/%.md,man/%,$(man1_source))
pwd := $(shell pwd)
src := $(pwd)/src
pip_pkgs := openpyxl xlrd PyYAML pylint pep8
VPATH = test

.PHONY: setup.python
setup.python:
	pip3 install -r requirements.txt

bin:
	mkdir $@
	LOCAL_INSTALL_DIR=$(shell pwd)/bin make install-script install-c

.PHONY: setup
setup: ve bin setup.python

ve := . ve/bin/activate

ve:
	python3 -m venv ve
	. ve/bin/activate && pip install -r requirements.txt

.PHONY: utf8-script
utf8-script:
	(cd data_tools/$@; make)

.PHONY: csv-to-tab
csv-to-tab:
	(cd data_tools/$@; make)

.PHONY: json-pluck
json-pluck:
	(cd data_tools/$@; make)

.PHONY: tab-to-csv
tab-to-csv:
	(cd data_tools/$@; make)

.PHONY: build
build: utf8-script csv-to-tab tab-to-csv json-pluck

.PHONY: install-c
install-c: build
	ln -sf $(pwd)/data_tools/utf8-script/utf8-script $(LOCAL_INSTALL_DIR)/utf8-script
	ln -sf $(pwd)/data_tools/utf8-script/utf8-category $(LOCAL_INSTALL_DIR)/utf8-category
	ln -sf $(pwd)/data_tools/csv-to-tab/csv-to-tab $(LOCAL_INSTALL_DIR)/csv-to-tab
	ln -sf $(pwd)/data_tools/tab-to-csv/tab-to-csv $(LOCAL_INSTALL_DIR)/tab-to-csv
	ln -sf $(pwd)/data_tools/json-pluck/json-pluck $(LOCAL_INSTALL_DIR)/json-pluck

.PHONY: install-script
install-script:
	ln -sf $(src)/check-tsv.sh $(LOCAL_INSTALL_DIR)/check-tsv
	ln -sf $(src)/convert_date.py $(LOCAL_INSTALL_DIR)/convert-date
	ln -sf $(src)/counting_sort.py $(LOCAL_INSTALL_DIR)/counting-sort
	ln -sf $(src)/csv_to_json.py $(LOCAL_INSTALL_DIR)/csv-to-json
	ln -sf $(src)/csv-to-postgres.sh $(LOCAL_INSTALL_DIR)/csv-to-postgres
	ln -sf $(src)/csv_to_xlsx.py $(LOCAL_INSTALL_DIR)/csv-to-xlsx
	ln -sf $(src)/date_fill.py $(LOCAL_INSTALL_DIR)/date-fill
	ln -sf $(src)/date_seq.py $(LOCAL_INSTALL_DIR)/date-seq
	ln -sf $(src)/header-sort.sh $(LOCAL_INSTALL_DIR)/header-sort
	ln -sf $(src)/highlight.py $(LOCAL_INSTALL_DIR)/highlight
	ln -sf $(src)/html_table_to_csv.py $(LOCAL_INSTALL_DIR)/html-table-to-csv
	ln -sf $(src)/join_tsv.py $(LOCAL_INSTALL_DIR)/join-tsv
	ln -sf $(src)/json-diff.sh $(LOCAL_INSTALL_DIR)/json-diff
	ln -sf $(src)/normalize_utf8.py $(LOCAL_INSTALL_DIR)/normalize-utf8
	ln -sf $(src)/postgres-to-csv.sh $(LOCAL_INSTALL_DIR)/postgres-to-csv
	ln -sf $(src)/reservoir_sample.py $(LOCAL_INSTALL_DIR)/reservoir-sample
	ln -sf $(src)/set-diff.sh $(LOCAL_INSTALL_DIR)/set-diff
	ln -sf $(src)/set-intersect.sh $(LOCAL_INSTALL_DIR)/set-intersect
	ln -sf $(src)/tokenize.sh $(LOCAL_INSTALL_DIR)/tokenize
	ln -sf $(src)/trim_tsv.py $(LOCAL_INSTALL_DIR)/trim-tsv
	ln -sf $(src)/tsv-header.sh $(LOCAL_INSTALL_DIR)/tsv-header
	ln -sf $(src)/tsv_to_json.py $(LOCAL_INSTALL_DIR)/tsv-to-json
	ln -sf $(src)/xlsx_to_csv.py $(LOCAL_INSTALL_DIR)/xls-to-csv
	ln -sf $(src)/xlsx_to_csv.py $(LOCAL_INSTALL_DIR)/xlsx-to-csv
	ln -sf $(src)/yaml_to_json.py $(LOCAL_INSTALL_DIR)/yaml-to-json

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

.PHONY: man_targets
man_targets: $(man1_targets)

$(local_man1_dir):
	mkdir -p $@

.PHONY: install-man
install-man: $(local_man1_dir)
	if [ ! -d $(LOCAL_MAN_DIR)/man1 ]; then \
	echo directory does not exist: $(LOCAL_MAN_DIR)/man1; \
	false; \
	fi
	for target in $(man1_targets); \
	do \
	cp $$target $(LOCAL_MAN_DIR)/man1; \
	done

.PHONY: install
install: install-c install-script install-man

.PHONY: all
all: build
	@echo
	@echo 'To install Python packages:'
	@echo
	@echo '   $$ sudo make setup'
	@echo
	@echo 'To install data tools and man pages:'
	@echo
	@echo '   $$ make install'
	@echo

output:
	mkdir -p $@

output/%:
	mkdir -p $@

.PHONY: test.check_tsv
test.check_tsv:
	./data_tools/check-tsv.sh test/check_tsv/input.good.tsv
	! ./data_tools/check-tsv.sh test/check_tsv/input.bad.tsv

.PHONY: test.convert_date
test.convert_date:
	$(ve) && cat test/convert_date/input.txt | ./data_tools/convert_date.py -i %s \
	| ./data_tools/convert_date.py -i %Y-%m-%dT%H:%M:%S -o %s \
	| diff - test/convert_date/input.txt
	$(ve) && cat test/convert_date/input.txt | ./data_tools/convert_date.py -i %s \
	| ./data_tools/convert_date.py -o %s \
	| diff - test/convert_date/input.txt

.PHONY: test.counting_sort
test.counting_sort: counting_sort/input.txt | output/counting_sort
	$(ve) && ./data_tools/counting_sort.py $< > output/counting_sort/output.txt
	sort $< > output/counting_sort/expected.output.txt
	diff output/counting_sort/output.txt output/counting_sort/expected.output.txt

.PHONY: test.csv_to_json
test.csv_to_json: csv_to_json/test.csv | output/csv_to_json
	$(ve) && ./data_tools/csv_to_json.py $< > output/csv_to_json/test.csv_to_json.json
	$(ve) && echo $$'λ,two\nthree,four' | ./data_tools/csv_to_json.py > output/csv_to_json/unicode.json
	$(ve) && echo $$'λ,two\nthree,four' \
	  | ./data_tools/csv_to_json.py --header=first,second > output/csv_to_json/unicode2.json

.PHONY: test.csv_to_tab
test.csv_to_tab: | csv-to-tab output/csv_to_tab
	echo -n $$'one,two\nthree,four' | ./data_tools/csv-to-tab/csv-to-tab > output/csv_to_tab/test.csv_to_tab.tab
	diff test/csv_to_tab/expected.tab output/csv_to_tab/test.csv_to_tab.tab
	echo $$'λ,two\nthree,four' | ./data_tools/csv-to-tab/csv-to-tab > output/csv_to_tab/unicode.tab
	diff test/csv_to_tab/expected.unicode.tab output/csv_to_tab/unicode.tab
	echo -n $$'one,two\ttwo\nthree,four' | ./data_tools/csv-to-tab/csv-to-tab --escape > output/csv_to_tab/test.csv_to_tab.escape.tab
	diff test/csv_to_tab/expected.escape.tab output/csv_to_tab/test.csv_to_tab.escape.tab


.PHONY: test.sv_to_xlsx
test.csv_to_xlsx: | output/csv_to_xlsx
	$(ve) && ./data_tools/csv_to_xlsx.py -o output/csv_to_xlsx/output.xlsx \
	test/csv_files/no-header.csv \
	test/csv_files/unicode.csv

.PHONY: test.date_fill
test.date_fill: | output/date_fill
	$(ve) && ./data_tools/date_fill.py --date-column=0 --format=%Y-%m-%dT%H -i test/date_fill/input.tsv \
	> output/date_fill/output.tsv
	diff output/date_fill/output.tsv test/date_fill/expected.output.tsv

.PHONY: test.highlight
test.highlight: highlight/input.txt | output/highlight
	$(ve) && ./data_tools/highlight.py control < $< > output/highlight/output1.txt
	diff test/highlight/expected.output.txt output/highlight/output1.txt
	$(ve) && ./data_tools/highlight.py control $< > output/highlight/output2.txt
	diff test/highlight/expected.output.txt output/highlight/output2.txt
	$(ve) && ./data_tools/highlight.py -r control < $< > output/highlight/output3.txt
	diff test/highlight/expected.output.txt output/highlight/output3.txt
	$(ve) && ./data_tools/highlight.py -r control $< > output/highlight/output4.txt
	diff test/highlight/expected.output.txt output/highlight/output4.txt

.PHONY: test.html_table_to_csv
test.html_table_to_csv: | output/html_table_to_csv
	$(ve) && ./data_tools/html_table_to_csv.py \
	  < test/html_table_to_csv/test.html \
	  > output/html_table_to_csv/output.test.csv
	diff output/html_table_to_csv/output.test.csv test/html_table_to_csv/expected.test.csv

.PHONY: test.join_tsv
test.join_tsv: | output/join_tsv
	$(ve) && ./data_tools/join_tsv.py --column=url \
	test/join_tsv/input1.tsv \
	test/join_tsv/input2.tsv \
	> output/join_tsv/output.tsv
	diff test/join_tsv/expected.output.tsv output/join_tsv/output.tsv
	#
	$(ve) && ./data_tools/join_tsv.py --column=url \
	test/join_tsv/input1.null.tsv \
	test/join_tsv/input2.null.tsv \
	> output/join_tsv/output.null.tsv
	diff test/join_tsv/expected.output.tsv output/join_tsv/output.null.tsv
	#
	$(ve) && ./data_tools/join_tsv.py --column=url --left \
	test/join_tsv/input1.left.tsv \
	test/join_tsv/input2.left.tsv \
	> output/join_tsv/output.left.tsv
	diff test/join_tsv/expected.output.left.tsv output/join_tsv/output.left.tsv
	#
	$(ve) && ./data_tools/join_tsv.py --column=url --left \
	test/join_tsv/input2.left.tsv \
	test/join_tsv/input1.left.tsv \
	> output/join_tsv/output.left.tsv
	diff test/join_tsv/expected.output.left2.tsv output/join_tsv/output.left.tsv
	#
	$(ve) && ./data_tools/join_tsv.py --column=url --right \
	test/join_tsv/input2.left.tsv \
	test/join_tsv/input1.left.tsv \
	> output/join_tsv/output.right.tsv
	diff test/join_tsv/expected.output.right.tsv output/join_tsv/output.right.tsv
	#
	$(ve) && ./data_tools/join_tsv.py --column=url --null=NULL \
	test/join_tsv/input1.NULL_VALUE.tsv \
	test/join_tsv/input2.NULL_VALUE.tsv \
	> output/join_tsv/output.NULL_VALUE.tsv
	diff test/join_tsv/expected.output.NULL_VALUE.tsv output/join_tsv/output.NULL_VALUE.tsv
	#
	$(ve) && ./data_tools/join_tsv.py --left-column=url1 --right-column=url2 \
	test/join_tsv/input1.diff.tsv \
	test/join_tsv/input2.diff.tsv \
	> output/join_tsv/output.diff.tsv
	diff test/join_tsv/expected.output.diff.tsv output/join_tsv/output.diff.tsv

.PHONY: test.json_diff
test.json_diff: | output/json_diff
	-./data_tools/json-diff.sh test/json_diff/1a.json test/json_diff/1b.json > output/json_diff/output1.txt
	diff -w test/json_diff/expected.output1.txt output/json_diff/output1.txt
	-./data_tools/json-diff.sh test/json_diff/2a.json test/json_diff/2b.json > output/json_diff/output2.txt
	diff -w test/json_diff/expected.output2.txt output/json_diff/output2.txt

.PHONY: test.normalize_utf8
test.normalize_utf8: normalize_utf8/input.txt | output/normalize_utf8
	$(ve) && ./data_tools/normalize_utf8.py < $< > output/normalize_utf8/output.nfc.txt
	diff test/normalize_utf8/expected.output.nfc.txt output/normalize_utf8/output.nfc.txt
	$(ve) && ./data_tools/normalize_utf8.py $< > output/normalize_utf8/output.nfc.2.txt
	diff test/normalize_utf8/expected.output.nfc.txt output/normalize_utf8/output.nfc.2.txt
	$(ve) && ./data_tools/normalize_utf8.py --nfd < $< > output/normalize_utf8/output.nfd.txt
	diff test/normalize_utf8/expected.output.nfd.txt output/normalize_utf8/output.nfd.txt

.PHONY: test.reservoir_sample
test.reservoir_sample: reservoir_sample/input.txt | output/reservoir_sample
	$(ve) && ./data_tools/reservoir_sample.py -r 17 -s 3 < $< > output/reservoir_sample/output.txt
	diff test/reservoir_sample/expected.output.txt output/reservoir_sample/output.txt

.PHONY: test.tsv_header
test.tsv_header: | output/tsv_header
	./data_tools/tsv-header.sh test/tsv_header/input.tsv > output/tsv_header/output.txt
	diff test/tsv_header/expected.output.txt output/tsv_header/output.txt

.PHONY: test.trim_tsv
test.trim_tsv: | output/trim_tsv
	$(ve) && echo -n $$' one \t two \n three \t four' \
	  | ./data_tools/trim_tsv.py > output/trim_tsv/trim_tsv.tsv
	diff test/trim_tsv/expected.trim_tsv.tsv output/trim_tsv/trim_tsv.tsv
	$(ve) && ./data_tools/trim_tsv.py test/trim_tsv/input.tsv > output/trim_tsv/output2.tsv
	diff test/trim_tsv/expected.trim_tsv.tsv output/trim_tsv/output2.tsv

#.PHONY: test.tab_to_csv
#test.tab_to_csv: tab_to_csv/escapes.tsv | tab-to-csv csv-to-tab output/tab_to_csv
#	./data_tools/tab-to-csv/tab-to-csv -u $< | ./data_tools/csv-to-tab/csv-to-tab -e > output/tab_to_csv/escape.tsv
#	diff $< output/tab_to_csv/escape.tsv

.PHONY: test.tsv_to_json
test.tsv_to_json: tsv_to_json/test.tsv | output/tsv_to_json
	$(ve) && ./data_tools/tsv_to_json.py $< > output/tsv_to_json/test.tsv_to_json.json

.PHONY: test.xlsx_to_csv
test.xlsx_to_csv: xlsx_to_csv/test.xlsx | output/xlsx_to_csv
	$(ve) && ./data_tools/xlsx_to_csv.py --list $< > output/xlsx_to_csv/list.out
	$(ve) && ./data_tools/xlsx_to_csv.py --sheet=three_rows_three_cols $< output/xlsx_to_csv/3r3c.csv
	$(ve) && ./data_tools/xlsx_to_csv.py --sheet=unicode $< output/xlsx_to_csv/unicode.csv
	$(ve) && ./data_tools/xlsx_to_csv.py --sheet=spaces $< output/xlsx_to_csv/spaces.csv
	$(ve) && ./data_tools/xlsx_to_csv.py --sheet=dates $< output/xlsx_to_csv/dates.csv
	diff output/xlsx_to_csv/list.out test/xlsx_to_csv/expected.list.out
	diff output/xlsx_to_csv/3r3c.csv test/xlsx_to_csv/expected.3r3c.csv
	diff output/xlsx_to_csv/unicode.csv test/xlsx_to_csv/expected.unicode.csv
	diff output/xlsx_to_csv/spaces.csv test/xlsx_to_csv/expected.spaces.csv
	diff output/xlsx_to_csv/dates.csv test/xlsx_to_csv/expected.dates.csv

.PHONY: test.yaml_to_json
test.yaml_to_json: yaml_to_json/input.yaml | output/yaml_to_json
	$(ve) && ./data_tools/yaml_to_json.py $< > output/yaml_to_json/ouptut1.json
	$(ve) && ./data_tools/yaml_to_json.py < $< > output/yaml_to_json/output2.json

python_base := convert_date counting_sort csv_to_json csv_to_tab
python_base += csv_to_xlsx date_fill highlight html_table_to_csv join_tsv
python_base += normalize_utf8 reservoir_sample trim_tsv tsv_to_json
python_base += xlsx_to_csv yaml_to_json
python_harnesses := $(patsubst %,test.%,$(python_base))

.PHONY: python.harness
python.harness: $(python_harnesses)

shell.harness: test.check_tsv test.json_diff test.tsv_header

.PHONY: test.harness
test.harness: python.harness shell.harness

.PHONY: pep8
pep8: ve
	. ./ve/bin/activate && find data_tools -name '*.py' \
	  | xargs pep8 --max-line-length=100

.PHONY: pylint
pylint: ve
	. ./ve/bin/activate && find data_tools -name '*.py' \
	  | xargs pylint --rcfile .pylintrc --disable=missing-docstring

.PHONY: shellcheck
shellcheck:
	find data_tools -name '*.sh' | xargs shellcheck

# TODO: no shellcheck
.PHONY: check
check: pylint pep8 test.harness

.PHONY: clean
clean:
	-find . -name '*.pyc' | xargs rm
	-find doc -name '*.[0-9]' | xargs rm
	-find . -name '*.html' | xargs rm
	-rm -rf output
