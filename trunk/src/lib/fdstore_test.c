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

#define NDEBUG
#include "fembot.h"
#include "tap.h"

#include <errno.h>
#include <sys/cdefs.h>

#include "bstg.h"

__RCSID("$Id$");


char *
bstg_pathstore_get()
{
    return "/this/file/does/not/exist";
}


/* mock up the close() -- just count invocations */
static int tcount = 0;
int
bstg_fdstore_close(int fd)
{
    tcount++;
    return 0;
}


int
main()
{
    bstg_fdstore_t store;

    plan_tests(28);

    ok(BSTG_FDSTORE_MAGIC != -1, "magic is not -1");
    store.magic = -1;
    ok(bstg_fdstore_destroy(&store) == EINVAL, "einval destroy");

    ok(bstg_fdstore_init(&store) == 0, "simple init");
    ok(store.magic == BSTG_FDSTORE_MAGIC, "magic was set");
    ok(bstg_fdstore_get(&store) == -1, "empty set");
    ok(bstg_fdstore_set(&store, 3) == 3, "add 3 to set");
    ok(store.max == 3, "3 is max");
    ok(FD_ISSET(3, &store.fds) != 0, "set has 3");
    ok(bstg_fdstore_get(&store) == 3, "set has one member");
    ok(bstg_fdstore_get(&store) == 3, "set has one member");
    ok(bstg_fdstore_get(&store) == 3, "set has one member");
    ok(bstg_fdstore_set(&store, 4) == 4, "add 4 to set");
    ok(bstg_fdstore_get(&store) == 3, "first 3");
    ok(bstg_fdstore_get(&store) == 4, "then 4");
    ok(bstg_fdstore_get(&store) == 3, "then 3 again");
    tcount = 0;
    ok(bstg_fdstore_closeall(&store) == 0, "close all fds");
    ok(tcount == 2, "we expect 2 closes");
    ok(store.magic == BSTG_FDSTORE_MAGIC, "magic was set");
    ok(bstg_fdstore_get(&store) == -1, "empty set");
    ok(bstg_fdstore_set(&store, 9) == 9, "add 9 to set");
    ok(bstg_fdstore_set(&store, 9) == 9, "add 9 to set");
    ok(bstg_fdstore_set(&store, 9) == 9, "add 9 to set");
    ok(bstg_fdstore_get(&store) == 9, "set has one member");
    ok(bstg_fdstore_get(&store) == 9, "set has one member");
    tcount = 0;
    ok(bstg_fdstore_destroy(&store) == 0, "close all fds");
    ok(tcount == 1, "we expect 2 closes");
    ok(store.magic != BSTG_FDSTORE_MAGIC, "magic not set");
    ok(bstg_fdstore_destroy(&store) == EINVAL, "einval destroy");

    return 0;
}
