MAN1_SOURCE = $(wildcard doc/*.1.md)

MAN1_TARGETS = $(patsubst %.md,%,$(MAN1_SOURCE))

LOCAL_INSTALL_DIR = /usr/local/bin

LOCAL_MAN_DIR = /usr/local/share/man

PWD := $(shell pwd)


.PHONY: all TAGS check clean test man install install-man

all: man

TAGS:
	find . -name '*.py' | xargs etags

check_python:
	find . -name 'test*.py' | xargs python

check_ruby:
	find . -name 'test*.rb' | xargs ruby

check: check_python check_ruby

clean:
	-find . -name '*.pyc' | xargs rm
	-find doc -name '*.[0-9]' | xargs rm
	-find . -name '*.html' | xargs rm
	-rm TAGS

setup.ruby:
	gem install nokogiri

# On Mac OS X, might have to replace 'cpan' with 'cpan5.12':
#
setup.perl:
	cpan -i Text::CSV
	cpan -i Text::Iconv
	cpan -i Spreadsheet::XLSX

setup: setup.ruby setup.perl

install: install-man
	ln -sf $(PWD)/csv_to_tsv.py $(LOCAL_INSTALL_DIR)/csv-to-tsv
	ln -sf $(PWD)/tsv_to_csv.py $(LOCAL_INSTALL_DIR)/tsv-to-csv
	ln -sf $(PWD)/json-awk.rb $(LOCAL_INSTALL_DIR)/json-awk
	ln -sf $(PWD)/dom-awk.rb $(LOCAL_INSTALL_DIR)/dom-awk
	ln -sf $(PWD)/utf8-viewer.rb $(LOCAL_INSTALL_DIR)/utf8-viewer
	ln -sf $(PWD)/xlsx-to-csv.pl $(LOCAL_INSTALL_DIR)/xlsx-to-csv
	ln -sf $(PWD)/set-diff.sh $(LOCAL_INSTALL_DIR)/set-diff
	ln -sf $(PWD)/set-intersect.sh $(LOCAL_INSTALL_DIR)/set-intersect
	ln -sf $(PWD)/weekdays.sh $(LOCAL_INSTALL_DIR)/weekdays
	ln -sf $(PWD)/csv_to_json.py $(LOCAL_INSTALL_DIR)/csv-to-json
	ln -sf $(PWD)/tsv_to_json.py $(LOCAL_INSTALL_DIR)/tsv-to-json
	ln -sf $(PWD)/header-sort.sh $(LOCAL_INSTALL_DIR)/header-sort

install-man: man
	if [ ! -d $(LOCAL_MAN_DIR)/man1 ]; then \
	echo directory does not exist: $(LOCAL_MAN_DIR)/man1; \
	return 1; \
	fi
	for target in $(MAN1_TARGETS); \
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
man: $(MAN1_TARGETS)

doc/%.1: doc/%.1.md
	pandoc -s -s -w man $< -o $@

test: check
