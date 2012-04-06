#
# Copyright 2011 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

include ../inc/default.mk
include ../inc/tap.mk

.PHONY: all clean check

CFLAGS+=-I. -I ../lib -DBSTG_BASEDIR=\"$(BASEDIR)\"
LDFLAGS+=-L../funcs -lfembotfuncs -L../lib -lfembot

RAWSRCS:=$(shell cat list.txt)
RAW:=$(addsuffix  ,$(basename $(RAWSRCS)))
TSTS=fembotfuncs

all: libfembotfuncs.a fembotfuncs.h

fembotfuncs.h: $(RAW:%=%_bstg_funcs.c)
	$(RM) $@
	printf "#ifndef __FEMBOTFUNCS_H\n" > $@
	printf "#define __FEMBOTFUNCS_H\n" >> $@
	cat topfuncs.h >> $@
	././mkproto.sh $^ >> $@
	././mktable.sh $^ >> $@
	printf "\n#endif\n" >> $@

libfembotfuncs.a: $(RAW:%=%_bstg_funcs.o)
	$(AR) $(ARFLAGS) $@ $^
	$(RANLIB) $@

$(RAW:%=%_bstg_funcs.c): %_bstg_funcs.c: %.c mkfuncs.sh
	./mkfuncs.sh $< $@ > $@

clean:
	$(RM) libfembotfuncs.a fembotfuncs.h
	$(RM) $(RAW:%=%_bstg_funcs.c)
	$(RM) $(RAW:%=%_bstg_funcs.o)
	$(RM) $(TSTS:%=%_test.t) $(TSTS:%=%_test)

$(TSTS:%=%_test): %_test: %_test.c
	$(CC) $(CFLAGS) $(BSTG_TAP_CFLAGS) $^ $(LDFLAGS) $(BSTG_TAP_LDFLAGS) -o $@

$(TSTS:%=%_test.t): %_test.t: %_test
	printf "#!/bin/sh\nexec ./%s\nexit 1" $< > $@
	chmod a+x $@

check: $(TSTS:%=%_test.t)
	$(PROVE) ./$^

