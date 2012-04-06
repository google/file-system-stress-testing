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
    bstg_funcs_t funcs;

    plan_tests(13);

    ok(tcount == 0, "we expect 0 closes");
    ok(BSTG_FUNCS_MAGIC != -1, "magic is not -1");
    ok(BSTG_FUNCS_MAGIC != 0, "magic is not 0");

    ok(bstg_funcs_init(&funcs, 111, 4096) == 0, "simple init");
    ok(funcs.magic == BSTG_FUNCS_MAGIC, "magic was set");
    ok(funcs.verbose == 111, "verbose was set");
    ok(tcount == 0, "we expect 0 closes");

    ok(bstg_funcs_destroy(&funcs) == 0, "simple destroy");
    ok(funcs.magic != BSTG_FUNCS_MAGIC, "magic was unset");

    ok(bstg_funcs_init(&funcs, 0, 4096) == 0, "simple init");
    ok(funcs.magic == BSTG_FUNCS_MAGIC, "magic was set");
    ok(funcs.verbose == 0, "verbose is zero");
    ok(tcount == 0, "we expect 0 closes");

    return 0;
}
