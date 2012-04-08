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
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/cdefs.h>

#include "bstg.h"

__RCSID("$Id$");


/*
 * Returns 0 on success.
 * Return errno (non-zero) on failure.
 */
int
bstg_funcs_init(bstg_funcs_t *ps, int verbose, size_t length)
{
    int rc;

    ps->magic = 0;
    rc = bstg_fdstore_init(&ps->fdstore);

    ps->pattern.iov_base = mmap(NULL,
            ps->pattern.iov_len = length,
            PROT_READ|PROT_WRITE,
            MAP_ANON|MAP_SHARED,
            -1,
            0);
    if (MAP_FAILED == ps->pattern.iov_base) {
        rc = errno;
    } else {
        memset(ps->pattern.iov_base, 0x55, ps->pattern.iov_len);
        mprotect(ps->pattern.iov_base, ps->pattern.iov_len, PROT_READ);
    }

    ps->buffer.iov_base = mmap(NULL,
            ps->buffer.iov_len = length,
            PROT_READ|PROT_WRITE,
            MAP_ANON|MAP_SHARED,
            -1,
            0);
    if (MAP_FAILED == ps->buffer.iov_base) {
        rc = errno;
    }

    ps->magic = BSTG_FUNCS_MAGIC;
    ps->verbose = verbose;

    if (rc) {
        bstg_funcs_destroy(ps);
    }

    return rc;
}

/*
 * Returns 0 on success.
 * Return errno (non-zero) on failure.
 */
int
bstg_funcs_destroy(bstg_funcs_t *ps)
{
    int rc;

    if (ps->pattern.iov_base != MAP_FAILED) {
        munmap(ps->pattern.iov_base, ps->pattern.iov_len);
        ps->pattern.iov_base = MAP_FAILED;
    }

    if (ps->buffer.iov_base != MAP_FAILED) {
        munmap(ps->buffer.iov_base, ps->buffer.iov_len);
        ps->buffer.iov_base = MAP_FAILED;
    }

    if ((rc = bstg_fdstore_destroy(&ps->fdstore))) {
        return rc;
    }
    assert(ps->magic == BSTG_FUNCS_MAGIC);
    ps->magic = ~BSTG_FUNCS_MAGIC;
    return 0;
}

