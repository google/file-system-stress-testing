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

-include ../inc/debug.mk

CFLAGS+=-Wall

ifndef RM
RM=rm
endif

ifndef PAX
PAX=pax
endif

ifndef GZCAT
GZCAT=gzcat
endif

ifndef CHMOD
CHMOD=chmod
endif

ifndef TOUCH
TOUCH=touch
endif

ifndef PWD_CMD
PWD_CMD=pwd
endif

ifndef GREP
GREP=grep
endif

ifndef FALSE
FALSE=false
endif

ifndef CP
CP=cp
endif

ifndef SETENV
SETENV=env
endif

ifndef MKDIR
MKDIR=mkdir
endif

ifndef KSH
KSH=/bin/ksh
endif

ifndef BASH
BASH=bash
endif

ifndef M4
M4=m4
endif

ifndef BASEDIR
BASEDIR=/mnt
endif

ifndef SUDO
SUDO=sudo
endif

ifndef INSTALL
INSTALL=install
endif

ifndef RANLIB
RANLIB=ranlib
endif
