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
#
# $Id$
#

include ../inc/default.mk
include ../inc/tap.mk

CFLAGS+=-I../lib -DBSTG_BASEDIR=\"$(BASEDIR)\"
LDFLAGS+=-L../lib -lfembot

.PHONY: all clean check

SRCS=fdstore bstg_fdstore_close bstg_waitpid \
    funcs flist bstg_signalx bstg_signalj bstg_null_check #pathstore

all: libfembot.a

libfembot.a: $(SRCS:%=%.o)
	$(AR) $(ARFLAGS) $@ $^
	$(RANLIB) $@

$(SRCS:%=%_test): %_test: %_test.c
	$(CC) $(CFLAGS) $(BSTG_TAP_CFLAGS) $^ $(LDFLAGS) $(BSTG_TAP_LDFLAGS) -o $@

$(SRCS:%=%_test.t): %_test.t: %_test
	printf "#!/bin/sh\nexec ./%s\nexit 1" $< > $@
	chmod a+x $@

check: $(SRCS:%=%_test.t)
	$(PROVE) ./$^

clean:
	$(RM) libfembot.a $(SRCS:%=%.o) $(SRCS:%=%_test) $(SRCS:%=%_test.t)

