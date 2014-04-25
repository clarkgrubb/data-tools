MAKEFLAGS += --warn-undefined-variables
SHELL := /bin/bash
.SHELLFLAGS := -o pipefail
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

.PHONY: all clean clobber install patch
.SECONDARY:

# hexedit_url := http://rigaux.org/hexedit-1.2.13.src.tgz
#
# hexedit-1.2.13.src.tgz:
# 	curl $(hexedit_url) > $@

hexedit: hexedit-1.2.13.src.tgz
	tar xf $<

# patch_url := http://www.volkerschatz.com/unix/patches/hexedit-search2a.diff.gz
#
# hexedit-search2a.diff:
#	curl $(patch_url) > $@.gz
#	gunzip $@.gz

patch: hexedit-search2a.diff hexedit
	patch -p0 < $<

cygwin.patch: patch
	patch hexedit/hexedit.h < hexedit.h.diff

build: clean patch
	(cd hexedit; \
	./configure; \
	make)

cygwin.build: cygwin.patch
	(cd hexedit; \
	./configure; \
	make)

all: build

clean:
	-rm -rf hexedit

clobber: clean
	-rm -rf hexedit-1.2.13.src.tgz hexedit-search2a.diff

install:
	(cd hexedit; make install)
