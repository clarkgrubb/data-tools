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
VPATH = test

ve := . ve/bin/activate

ve:
	python3 -m venv ve
	. ve/bin/activate && pip install -r requirements.txt

.PHONY: utf8-script
utf8-script:
	(cd src/$@; make)

.PHONY: csv-to-tab
csv-to-tab:
	(cd src/$@; make)

.PHONY: json-pluck
json-pluck:
	(cd src/$@; make)

.PHONY: tab-to-csv
tab-to-csv:
	(cd src/$@; make)

.PHONY: build.c
build.c: utf8-script csv-to-tab tab-to-csv json-pluck

.PHONY: build
build: ve build.c

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

.PHONY: install-script
install.script:
	./setup.py sdist

.PHONY: install-c
install.c: build.c
	cp src/csv-to-tab/csv-to-tab $(LOCAL_INSTALL_DIR)
	cp src/json-pluck/json-pluck $(LOCAL_INSTALL_DIR)
	cp src/tab-to-csv/tab-to-csv $(LOCAL_INSTALL_DIR)
	cp src/utf8-script/utf8-category $(LOCAL_INSTALL_DIR)
	cp src/utf8-script/utf8-script $(LOCAL_INSTALL_DIR)

.PHONY: install-man
install.man: $(local_man1_dir)
	if [ ! -d $(LOCAL_MAN_DIR)/man1 ]; then \
	echo directory does not exist: $(LOCAL_MAN_DIR)/man1; \
	false; \
	fi
	for target in $(man1_targets); \
	do \
	cp $$target $(LOCAL_MAN_DIR)/man1; \
	done

.PHONY: install
install:
	@echo
	@echo 'To install Python and Bash scripts:'
	@echo
	@echo '   $$ ./setup.py sdist'
	@echo '   $$ pip3 install dist/data-tools-0.1.0.tar.gz'
	@echo
	@echo 'To install C tools:'
	@echo
	@echo '   $$ make install.c'
	@echo
	@echo 'To install man pages:'
	@echo
	@echo '   $$ make install.man'
	@echo

.PHONY: all
all: install

output:
	mkdir -p $@

output/%:
	mkdir -p $@

.PHONY: test.check_tsv
test.check_tsv:
	./data_tools/check-tsv test/check_tsv/input.good.tsv
	! ./data_tools/check-tsv test/check_tsv/input.bad.tsv

.PHONY: test.convert_date
test.convert_date: ve
	$(ve) && cat test/convert_date/input.txt | ./data_tools/convert_date.py -i %s \
	| ./data_tools/convert_date.py -i %Y-%m-%dT%H:%M:%S -o %s \
	| diff - test/convert_date/input.txt
	$(ve) && cat test/convert_date/input.txt | ./data_tools/convert_date.py -i %s \
	| ./data_tools/convert_date.py -o %s \
	| diff - test/convert_date/input.txt

.PHONY: test.counting_sort
test.counting_sort: counting_sort/input.txt ve | output/counting_sort
	$(ve) && ./data_tools/counting_sort.py $< > output/counting_sort/output.txt
	sort $< > output/counting_sort/expected.output.txt
	diff output/counting_sort/output.txt output/counting_sort/expected.output.txt

.PHONY: test.csv_to_json
test.csv_to_json: csv_to_json/test.csv ve | output/csv_to_json
	$(ve) && ./data_tools/csv_to_json.py $< > output/csv_to_json/test.csv_to_json.json
	$(ve) && echo $$'λ,two\nthree,four' | ./data_tools/csv_to_json.py > output/csv_to_json/unicode.json
	$(ve) && echo $$'λ,two\nthree,four' \
	  | ./data_tools/csv_to_json.py --header=first,second > output/csv_to_json/unicode2.json

.PHONY: test.csv_to_tab
test.csv_to_tab: | csv-to-tab output/csv_to_tab
	echo -n $$'one,two\nthree,four' | ./src/csv-to-tab/csv-to-tab > output/csv_to_tab/test.csv_to_tab.tab
	diff test/csv_to_tab/expected.tab output/csv_to_tab/test.csv_to_tab.tab
	echo $$'λ,two\nthree,four' | ./src/csv-to-tab/csv-to-tab > output/csv_to_tab/unicode.tab
	diff test/csv_to_tab/expected.unicode.tab output/csv_to_tab/unicode.tab
	echo -n $$'one,two\ttwo\nthree,four' | ./src/csv-to-tab/csv-to-tab --escape > output/csv_to_tab/test.csv_to_tab.escape.tab
	diff test/csv_to_tab/expected.escape.tab output/csv_to_tab/test.csv_to_tab.escape.tab


.PHONY: test.sv_to_xlsx
test.csv_to_xlsx: ve | output/csv_to_xlsx
	$(ve) && ./data_tools/csv_to_xlsx.py -o output/csv_to_xlsx/output.xlsx \
	test/csv_files/no-header.csv \
	test/csv_files/unicode.csv

.PHONY: test.date_fill
test.date_fill: ve | output/date_fill
	$(ve) && ./data_tools/date_fill.py --date-column=0 --format=%Y-%m-%dT%H -i test/date_fill/input.tsv \
	> output/date_fill/output.tsv
	diff output/date_fill/output.tsv test/date_fill/expected.output.tsv

.PHONY: test.highlight
test.highlight: highlight/input.txt ve | output/highlight
	$(ve) && ./data_tools/highlight.py control < $< > output/highlight/output1.txt
	diff test/highlight/expected.output.txt output/highlight/output1.txt
	$(ve) && ./data_tools/highlight.py control $< > output/highlight/output2.txt
	diff test/highlight/expected.output.txt output/highlight/output2.txt
	$(ve) && ./data_tools/highlight.py -r control < $< > output/highlight/output3.txt
	diff test/highlight/expected.output.txt output/highlight/output3.txt
	$(ve) && ./data_tools/highlight.py -r control $< > output/highlight/output4.txt
	diff test/highlight/expected.output.txt output/highlight/output4.txt

.PHONY: test.html_table_to_csv
test.html_table_to_csv: ve | output/html_table_to_csv
	$(ve) && ./data_tools/html_table_to_csv.py \
	  < test/html_table_to_csv/test.html \
	  > output/html_table_to_csv/output.test.csv
	diff output/html_table_to_csv/output.test.csv test/html_table_to_csv/expected.test.csv

.PHONY: test.join_tsv
test.join_tsv: ve | output/join_tsv
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
	-./data_tools/json-diff test/json_diff/1a.json test/json_diff/1b.json > output/json_diff/output1.txt
	diff -w test/json_diff/expected.output1.txt output/json_diff/output1.txt
	-./data_tools/json-diff test/json_diff/2a.json test/json_diff/2b.json > output/json_diff/output2.txt
	diff -w test/json_diff/expected.output2.txt output/json_diff/output2.txt

.PHONY: test.normalize_utf8
test.normalize_utf8: normalize_utf8/input.txt ve | output/normalize_utf8
	$(ve) && ./data_tools/normalize_utf8.py < $< > output/normalize_utf8/output.nfc.txt
	diff test/normalize_utf8/expected.output.nfc.txt output/normalize_utf8/output.nfc.txt
	$(ve) && ./data_tools/normalize_utf8.py $< > output/normalize_utf8/output.nfc.2.txt
	diff test/normalize_utf8/expected.output.nfc.txt output/normalize_utf8/output.nfc.2.txt
	$(ve) && ./data_tools/normalize_utf8.py --nfd < $< > output/normalize_utf8/output.nfd.txt
	diff test/normalize_utf8/expected.output.nfd.txt output/normalize_utf8/output.nfd.txt

.PHONY: test.reservoir_sample
test.reservoir_sample: reservoir_sample/input.txt ve | output/reservoir_sample
	$(ve) && ./data_tools/reservoir_sample.py -r 17 -s 3 < $< > output/reservoir_sample/output.txt
	diff test/reservoir_sample/expected.output.txt output/reservoir_sample/output.txt

.PHONY: test.tsv_header
test.tsv_header: | output/tsv_header
	./data_tools/tsv-header test/tsv_header/input.tsv > output/tsv_header/output.txt
	diff test/tsv_header/expected.output.txt output/tsv_header/output.txt

.PHONY: test.trim_tsv
test.trim_tsv: ve | output/trim_tsv
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
test.tsv_to_json: tsv_to_json/test.tsv ve | output/tsv_to_json
	$(ve) && ./data_tools/tsv_to_json.py $< > output/tsv_to_json/test.tsv_to_json.json

.PHONY: test.xlsx_to_csv
test.xlsx_to_csv: xlsx_to_csv/test.xlsx ve | output/xlsx_to_csv
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
test.yaml_to_json: yaml_to_json/input.yaml ve | output/yaml_to_json
	$(ve) && ./data_tools/yaml_to_json.py $< > output/yaml_to_json/ouptut1.json
	$(ve) && ./data_tools/yaml_to_json.py < $< > output/yaml_to_json/output2.json

python_base := convert_date counting_sort csv_to_json csv_to_tab
python_base += csv_to_xlsx date_fill highlight html_table_to_csv join_tsv
python_base += normalize_utf8 reservoir_sample trim_tsv tsv_to_json
python_base += xlsx_to_csv yaml_to_json
python_tests := $(patsubst %,test.%,$(python_base))

.PHONY: test.c
test.c:
	cd src/csv-to-tab && make test
	cd src/json-pluck && make test
	cd src/tab-to-csv && make test
	cd src/utf8-script && make test

.PHONY: test.python
test.python: $(python_tests)

test.shell: test.check_tsv test.json_diff test.tsv_header

.PHONY: test
test: test.python test.shell

.PHONY: pep8
pep8: ve
	. ./ve/bin/activate && find data_tools -name '*.py' \
	  | xargs pep8 --max-line-length=100

.PHONY: pylint
pylint: ve
	. ./ve/bin/activate && find data_tools -name '*.py' \
	  | xargs pylint --rcfile .pylintrc --disable=missing-docstring

shell_scripts := $(shell grep -l '/usr/bin/env bash' data_tools/* 2> /dev/null)

.PHONY: shellcheck
shellcheck:
	echo $(shell_scripts) | xargs shellcheck

.PHONY: check.c
check.c:
	cd src/csv-to-tab && make check
	cd src/json-pluck && make check
	cd src/tab-to-csv && make check
	cd src/utf8-script && make check

.PHONY: check
check: pylint pep8 shellcheck check.c test

.PHONY: clean.test
clean.test:
	-rm -rf output
	cd src/csv-to-tab && make $@
	cd src/json-pluck && make $@
	cd src/tab-to-csv && make $@
	cd src/utf8-script && make $@

.PHONY: clean.build
clean.build:
	rm -rf ve
	-find . -name '*.pyc' | xargs rm
	cd src/csv-to-tab && make $@
	cd src/json-pluck && make $@
	cd src/tab-to-csv && make $@
	cd src/utf8-script && make $@

.PHONY: clean.generate
clean.generate:
	cd src/utf8-script && make $@

.PHONY: clean
clean: clean.test
