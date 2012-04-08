#ifndef __FEMBOTFUNCS_H
#define __FEMBOTFUNCS_H

/*
 * Copyright 2011 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *
 * $Id$
 */

#include "topfuncs.h"

#define BSTG_PATH_MAX (1024)

#include <unistd.h>

#include <dirent.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <libgen.h>
#include <signal.h>
#ifdef _POSIX_SPAWN
#include <spawn.h>
#endif
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/mount.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/uio.h>
#include <termios.h>

#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif

#ifdef __NetBSD__
#ifdef _POSIX_SPAWN
#error _POSIX_SPAWN defined.  This was not expected.
#endif
#define eaccess access
#include <sys/mount.h>
#define fdopendir(___fd)	((NULL))
#endif

#ifdef linux
#include <bsd/stdlib.h>

#define lpathconf pathconf

#ifndef __RCSID
#define __RCSID(__not_used) struct rcsid_not_defined
#endif

#endif


#endif
