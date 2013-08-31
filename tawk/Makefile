MAKEFLAGS += --warn-undefined-variables
SHELL := /bin/bash
.SHELLFLAGS := -o pipefail
.DEFAULT_GOAL := all
.DELETE_ON_ERROR:
.SUFFIXES:

repo := mawk-1.3.4-20130803
tarball := $(repo).tgz
url := ftp://invisible-island.net/mawk/$(tarball)

.PHONY: tarball repo patch build clean clobber install all
.SECONDARY:

$(tarball):
	curl $(url) > $@

tarball: $(tarball)

$(repo): $(tarball)
	tar xf $<

repo: $(repo)

# tawk.patch was created by copying the repo to REPO.patched, making
# the changes to REPO.patched, and running this command:
#
#  diff -rupN mawk-1.3.4-20130803 mawk-1.3.4-20130803.patched > tawk.patch

tawk: $(repo)
	patch -p0 < tawk.patch
	(cd $(repo); \
	./configure; \
	make)
	cp $(repo)/mawk $@

clean:
	-rm -rf $(repo) tawk output.tab

clobber: clean
	-rm -f $(tarball)

install:
	(cd $(repo); make install)

all: tawk

check: tawk
	./tawk '{print $$3}' test/input.tab > output.tab
	diff output.tab test/expected.output.tab
