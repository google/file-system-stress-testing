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
 */

#include "fembot.h"

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/cdefs.h>

#include "bstg.h"

__RCSID("$Id$");


/*
 * An internal function to reset max, count and the fdset
 * to default values.
 *
 * Returns 0 on success.
 */
static inline int
bstg_fdstore_reset(bstg_fdstore_t *ps)
{
    ps->max = -1;
    ps->count = 0;
    FD_ZERO(&ps->fds);
    return 0;
}

/*
 * We initialize this collection of fds.
 * Caller provides memory storage.
 *
 * Returns 0 on success.
 * Return errno (non-zero) on failure.
 */
int
bstg_fdstore_init(bstg_fdstore_t *ps)
{
    ps->magic = BSTG_FDSTORE_MAGIC;
    return bstg_fdstore_reset(ps);
}


/*
 * Close all the fds in the set.
 *
 * Return 0 on success.
 */
int
bstg_fdstore_closeall(bstg_fdstore_t * ps)
{
    int curr;

    if (ps->magic != BSTG_FDSTORE_MAGIC) {
        return EINVAL;
    }

    for (curr = 0; curr <= ps->max; curr++) {
        if (FD_ISSET(curr, &ps->fds)) {
            bstg_fdstore_close(curr);
        }
    }

    return bstg_fdstore_reset(ps);
}


/*
 * We are finished with this collection of fds. Free all resources.
 * Remember caller provided storage for bstg_fdstore_t.
 *
 * Returns 0 on success.
 * Return errno (non-zero) on failure.
 */
int
bstg_fdstore_destroy(bstg_fdstore_t *ps)
{
    int rc;

    if ((rc = bstg_fdstore_closeall(ps))) {
        return rc;
    }
    assert(ps->magic == BSTG_FDSTORE_MAGIC);
    ps->magic = ~BSTG_FDSTORE_MAGIC;
    return 0;
}


/*
 * Get an fd from the set.
 *
 * Returns an fd on success.
 * Returns -1 on error.
 */
static int
bstg_fdstore_getraw(bstg_fdstore_t *ps)
{
    int tries, fd;

    assert(ps->magic == BSTG_FDSTORE_MAGIC);

    /* make ps->max+1 attempts to find an fd */
    for (tries = 0; tries <= ps->max; tries++) {
        /*
         * Start where we left off and then loop around
         * to the start when we reach the maximum fd.
         */
        fd = ps->count++ % (ps->max + 1);
        if (FD_ISSET(fd, &ps->fds)) {
            return fd;
        }
    }

    return -1;
}


/*
 * Added the fd to the set.
 *
 * Returns the given fd.
 */
int
bstg_fdstore_set(bstg_fdstore_t *ps, int fd)
{
    assert(ps->magic == BSTG_FDSTORE_MAGIC);

    /* replace an fd if there are too many open already */
    if (ps->max > 10) {
        int newd;

        if ((newd = bstg_fdstore_getraw(ps)) > 0) {
            if (dup2(fd, newd) != -1) {
                return newd;
            }
        }
    }

    if (fd > 0) {
        /* keep track of highest fd number */
        if (fd > ps->max) {
            ps->max = fd;
        }
        FD_SET(fd, &ps->fds);
    }
    return fd;
}


/*
 * Get an fd from the set.
 *
 * Returns an fd on success.
 * Returns -1 on error.
 */
int
bstg_fdstore_get2(bstg_fdstore_t *ps, int flags)
{
    int fd, x;
    static int omodes[4] = { O_RDWR, O_WRONLY, O_RDONLY, O_NOACCESS };
    enum { number_of_modes = sizeof(omodes)/sizeof(omodes[0]) } ;

    if ((fd = bstg_fdstore_getraw(ps)) > 0) {
        return fd;
    }

    /*
     * There are no valid fds in the set. Try to create a valid fd.
     */
    for (x = 0; x < number_of_modes; x++) {
        if ((fd = open(bstg_pathstore_get(),
            omodes[x] | O_NONBLOCK | O_NOCTTY | flags, 0777)) > 0) {
            return bstg_fdstore_set(ps, fd);
        }
    }

    return -1;
}


/*
 * Get an fd from the set.
 *
 * Returns an fd on success.
 * Returns -1 on error.
 */
int
bstg_fdstore_get(bstg_fdstore_t *ps)
{
    return bstg_fdstore_get2(ps, O_CREAT);
}

void
bstg_preexec(bstg_fdstore_t *ps)
{
    struct rlimit crl;

    bstg_fdstore_closeall(ps);
    close(0);
    close(1);
    close(2);

    crl.rlim_cur = crl.rlim_max = 0;
    setrlimit(RLIMIT_CORE, &crl);

    crl.rlim_cur = crl.rlim_max = 1;
    setrlimit(RLIMIT_CPU, &crl);
}

