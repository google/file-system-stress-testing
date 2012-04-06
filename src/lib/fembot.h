#ifndef __FEMBOT_H
#define __FEMBOT_H

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
 * $Id$
 */

#include <unistd.h>
#include <setjmp.h>
#include <sys/select.h>
#include <sys/uio.h>


/* magic value to determine if data has been initialized */
#ifndef BSTG_FDSTORE_MAGIC
#define BSTG_FDSTORE_MAGIC  ((unsigned)(~0xbeef1238))
#endif

#define BSTGNULLCHECK(__x)	(bstg_null_check(__x, __FILE__, __LINE__))

/*
 * A collection of fds.
 *  magic: a magic number for a simple sanity check
 *  max: largest fd in set
 *  fds: use select's fd_set
 *  count: used by bstg_fdstore_get()
 */
typedef struct bstg_fdstore_t {
    int max;
    unsigned magic;
    unsigned count;
    fd_set fds;
} bstg_fdstore_t;

/* initialize the fdstore */
int bstg_fdstore_init(bstg_fdstore_t *);

/* close every fd in the fdstore */
int bstg_fdstore_closeall(bstg_fdstore_t *);

/* we are done with the fdstore */
int bstg_fdstore_destroy(bstg_fdstore_t *);

/* cover function for close() */
int bstg_fdstore_close(int);

/* add an fd into the fdstore */
int bstg_fdstore_set(bstg_fdstore_t *, int);

/* return an fd from the fdstore */
int bstg_fdstore_get(bstg_fdstore_t *);

/* return an fd from the fdstore -- pass in open() oflags */
int bstg_fdstore_get2(bstg_fdstore_t *ps, int flags);

/* cleanup before an exec() */
void bstg_preexec(bstg_fdstore_t *);


/* magic value to determine if data has been initialized */
#ifndef BSTG_FUNCS_MAGIC
#define BSTG_FUNCS_MAGIC  ((unsigned)(~0xbeefabcd))
#endif

/*
 * Global data used by the load test.
 *  magic: a magic number for a simple sanity check
 *  verbose: a hint to print more debug output
 *  verbose: a hint to print more debug output
 *  pattern: readonly buffer of a known pattern
 *  buffer: used as a destination of read()
 *  fdstore: fds open()ed during the test run
 */
typedef struct bstg_funcs_t {
    unsigned magic;
    int verbose;

    struct iovec pattern;
    struct iovec buffer;

    bstg_fdstore_t fdstore;
} bstg_funcs_t;

/* initialize the globals */
int bstg_funcs_init(bstg_funcs_t *, int, size_t);

/* we are done with globals */
int bstg_funcs_destroy(bstg_funcs_t *);


/* magic value to determine if data has been initialized */
#ifndef BSTG_FLIST_MAGIC
#define BSTG_FLIST_MAGIC    ((unsigned)(~0xdead5555))
#endif

/*
 *
 */
typedef struct bstg_flist_t {
    u_int32_t magic;
    u_int32_t *pindex;
    u_int32_t number;
    u_int32_t lower;
    u_int32_t upper;
} bstg_flist_t;

/* initialize the list */
int bstg_flist_init(bstg_flist_t *, u_int32_t);

/* we are done with the list */
int bstg_flist_destroy(bstg_flist_t *);

/* shuffle the array of ints */
int bstg_flist_shuffle(bstg_flist_t *);

/* reset the range via the lower/upper values */
int bstg_flist_set(bstg_flist_t *, u_int32_t, u_int32_t);

/* return the index in the current range */
int bstg_flist_get(bstg_flist_t *, u_int32_t);

/* use a string of , separated numbers to init the list of ints */
int bstg_flist_import(bstg_flist_t *, char *);


/* waitpid() but with timeout (quarter seconds) */
pid_t bstg_waitpid(pid_t, int *, int);

/* return a path in filesystem under test */
char * bstg_pathstore_get();

/* signal handler that calls _exit(signo) */
void bstg_signalx(int);

/* signal handler that calls siglongjmp(bstg_jmpbuf, 1) */
extern sigjmp_buf bstg_jmpbuf;
void bstg_signalj(int);

/* Used to check the return ptr from malloc. */
/* We will exit() on NULL or just return the pointer. */
/* Use with BSTGNULLCHECK(), to get the file/line data. */
void * bstg_null_check(void *, const char *, int );

#endif
