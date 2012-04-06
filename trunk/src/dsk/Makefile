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

DIR111=$(BASEDIR)/111
ONEMG=1048576

DSK=rd51.dsk ra81.dsk floppy.dsk
RAWDSK=$(addsuffix  ,$(basename $(DSK)))

.PHONY: all clean install

all: true $(DSK:%=%) $(DSK:%=%.gz)

true.c:
	printf "int main() { return 0; }\n" > $@

true.sh:
	printf "#!%s\n" $(DIR111)/true > $@
	
true: true.c

$(DSK): % : %.Z
	$(GZCAT) < $< > $@

$(RAWDSK:%=%.dsk.gz): %.dsk.gz: %.dsk %.h
	gzip -1 < $< > $@

# TODO(k) cleanup the BASEDIR creation

$(RAWDSK:%=%.h): %.h: %.dsk true true.sh
	$(SETENV) GZCAT=$(GZCAT) SUDO=$(SUDO) MNT=$(BASEDIR) $(KSH) ./mkdsk.sh $^
	$(SUDO) chown $(USER) $(BASEDIR)
	$(MKDIR) $(DIR111)
	chmod 0777 $(DIR111)
	$(MKDIR) -m 0777 $(BASEDIR)/222
	$(MKDIR) -m 0777 $(BASEDIR)/333
	$(MKDIR) -m 0777 $(BASEDIR)/444
	$(MKDIR) -m 0777 $(BASEDIR)/555
	$(MKDIR) -m 0777 $(BASEDIR)/666
	$(MKDIR) -m 0777 $(BASEDIR)/777
	$(MKDIR) -m 0777 $(BASEDIR)/888
	$(MKDIR) -m 0777 $(BASEDIR)/999
	$(MKDIR) -m 0777 $(BASEDIR)/aaa
	$(MKDIR) -m 0777 $(BASEDIR)/bbb
	$(MKDIR) -m 0777 $(BASEDIR)/ccc
	$(MKDIR) -m 0777 $(BASEDIR)/ddd
	$(MKDIR) -m 0777 $(BASEDIR)/eee
	$(MKDIR) -m 0777 $(BASEDIR)/fff
	$(INSTALL) -c -s -f uchg -m 0777 true $(DIR111)/..
	$(INSTALL) -c -s -f uchg -m 0777 true $(DIR111)
	$(INSTALL) -c -s -m 0777 true $(DIR111)/true2
	$(INSTALL) -c -m 0777 true.sh $(DIR111)
	$(INSTALL) -c -m 0777 $(<).Z $(DIR111)
	$(MKDIR) $(DIR111)/adir
	chmod 0777 $(DIR111)/adir
	mkfifo -m 0777 $(DIR111)/afifo
	truncate -s $(ONEMG) $(DIR111)/ahole
	chmod 0777 $(DIR111)/ahole
	$(INSTALL) -c -s -m 0777 true $(DIR111)/true.truncate
	truncate -s 8 $(DIR111)/true.truncate
	truncate -s $(ONEMG) $(DIR111)/true.truncate
	$(INSTALL) -c -m 0777 true.sh $(DIR111)/true.sh.truncate
	truncate -s 8 $(DIR111)/true.sh.truncate
	truncate -s $(ONEMG) $(DIR111)/true.sh.truncate
	umask 0 ; ln -s "" $(DIR111)/symlinkempty
	umask 0 ; ln -s "a" $(DIR111)/b
	umask 0 ; ln -s "b" $(DIR111)/c
	umask 0 ; ln -s "c" $(DIR111)/a
	find $(DIR111)/* | xargs -n 1 printf "  \"%s\",\n" > $@
	$(SETENV) GZCAT=$(GZCAT) SUDO=$(SUDO) MNT=$(BASEDIR) $(KSH) ./umdsk.sh

clean:
	$(RM) true true.c true.sh md.txt
	$(RM) $(RAWDSK:%=%.h) $(DSK:%=%.gz) $(DSK)

