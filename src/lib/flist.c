/*
 * vim:ts=4:sw=4:expandtab
 *
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
#include <err.h>
#include <stdlib.h>
#include <string.h>
#include <sys/cdefs.h>

#include "bstg.h"

__RCSID("$Id$");


int
bstg_flist_init(bstg_flist_t *ps, u_int32_t number)
{
    u_int32_t x;

    ps->saved = ps->upper = ps->number = number;
    if ((ps->pindex =
        calloc(ps->upper = ps->number = number, sizeof(*ps->pindex)))) {
        ps->magic = BSTG_FLIST_MAGIC;
        for (x = 0; x < number; x++) {
            ps->pindex[x] = x;
        }
        return ps->lower = 0;
    }
    return 1;
}

int
bstg_flist_destroy(bstg_flist_t *ps)
{
    assert(ps->magic == BSTG_FLIST_MAGIC);
    assert(ps->pindex != NULL);
    free(ps->pindex);
    ps->pindex = NULL;
    ps->magic = ~BSTG_FLIST_MAGIC;

    return 0;
}

int
bstg_flist_shuffle(bstg_flist_t *ps)
{
    u_int32_t len, swapindex;
    u_int32_t temp;

    assert(ps->magic == BSTG_FLIST_MAGIC);
    len = ps->number;
    while (len > 1) {
        swapindex = arc4random() % len--;
        temp = ps->pindex[len];
        ps->pindex[len] = ps->pindex[swapindex];
        ps->pindex[swapindex] = temp;
    }

    return 0;
}

int
bstg_flist_set(bstg_flist_t *ps, u_int32_t lower, u_int32_t upper)
{
    if (lower >= upper) {
        return 1;
    }
    if (upper > ps->number) {
        return 1;
    }
    ps->lower = lower;
    ps->upper = upper;

    return 0;
}

int
bstg_flist_get(bstg_flist_t *ps, u_int32_t index)
{
    u_int32_t range;

    range = ps->upper - ps->lower;
    return ps->pindex[(index % range) + ps->lower];
}

int
bstg_flist_import(bstg_flist_t *ps, char *options)
{
    char *curr, *p;
    unsigned number;
    size_t index;
    u_int32_t count;
    int rc;

    assert(ps->magic == BSTG_FLIST_MAGIC);
    rc = 0;
    ps->number = ps->saved;
    ps->lower = 0;
    count = 0;
    curr = options;
    while (*curr) {
        /* skip white space */
        index = strspn(curr, " ,:\t\n");
        curr = &curr[index];

        /* if number exists, add it to our list */
        number = strtoul(curr, &p, 10);
        if (p == curr) {
            break;
        }
        ps->pindex[count++] = number;

        if (count > ps->number) {
            rc = 1;
            warnx("too many numbers: count=%d ps.number=%d number=%d curr=%s",
                count, ps->number, number, curr);
            break;
        }

        /* skip this number */
        index = strspn(curr, "0123456789");
        curr = &curr[index];
    }

    if (count == 0) {
        rc = 1;
        warnx("no digits at all: count=%d", count);
    }

    ps->upper = ps->number = count;
    return rc;
}
