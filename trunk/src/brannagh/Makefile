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
#rd51 causes too many panics
DSK=ra81

.PHONY: all clean install

all: brannagh ../dsk/$(DSK).dsk.gz

pathstore.h: ../dsk/$(DSK).h
	$(CP) -f $< pathstore.h
	sed 's/111/222/g' < $< >> pathstore.h
	sed 's/111/333/g' < $< >> pathstore.h
	sed 's/111/444/g' < $< >> pathstore.h
	sed 's/111/555/g' < $< >> pathstore.h
	sed 's/111/666/g' < $< >> pathstore.h
	sed 's/111/777/g' < $< >> pathstore.h
	sed 's/111/888/g' < $< >> pathstore.h
	sed 's/111/999/g' < $< >> pathstore.h
	sed 's/111/aaa/g' < $< >> pathstore.h
	sed 's/111/bbb/g' < $< >> pathstore.h
	sed 's/111/ccc/g' < $< >> pathstore.h
	sed 's/111/ddd/g' < $< >> pathstore.h
	sed 's/111/eee/g' < $< >> pathstore.h
	sed 's/111/fff/g' < $< >> pathstore.h

brannagh: brannagh.c pathstore.h
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

install:

check:
	$(SETENV) GZCAT=$(GZCAT) SUDO=$(SUDO) MNT=$(BASEDIR) $(KSH) ./check.sh ../dsk/$(DSK).dsk.gz

clean:
	$(RM) brannagh pathstore.h $(RSK).dsk brannagh.core
