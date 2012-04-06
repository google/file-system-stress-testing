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

CFLAGS+=-I. -I ../lib -I ../funcs -DBSTG_BASEDIR=\"$(BASEDIR)\"
LDFLAGS+=-L../funcs -lfembotfuncs -L../lib -lfembot
DSK=rd51

.PHONY: all clean install check

all: aibreann

aibreann: aibreann.c pathstore.h
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

pathstore.h: ../dsk/$(DSK).h
	$(CP) -f $< $@

install:

check: ../dsk/$(DSK).dsk.gz
	$(SETENV) GZCAT=$(GZCAT) SUDO=$(SUDO) MNT=$(BASEDIR) $(KSH) ./check.sh $<

clean:
	$(RM) aibreann pathstore.h $(DSK).dsk aibreann.core
