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


int
main()
{
    int count = 0;
    int x;
    bstg_flist_t flist;

    plan_tests(38);

    ok(BSTG_FLIST_MAGIC != -1, "magic is not -1");
    ok(BSTG_FLIST_MAGIC != 0, "magic is not 0");

    ok(bstg_flist_init(&flist, 10) == 0, "simple init");
    ok(flist.magic == BSTG_FLIST_MAGIC, "magic was set");
    ok(flist.number == 10, "verbose was set");
    ok(flist.pindex[0] == 0, "zero index");

    ok(bstg_flist_set(&flist, 6, 5) == 1, "range error");
    ok(bstg_flist_set(&flist, 1, 11) == 1, "another range error");

    ok(bstg_flist_get(&flist, 0) == 0, "zero");
    ok(bstg_flist_get(&flist, 1) == 1, "one");
    ok(bstg_flist_get(&flist, 5) == 5, "five");
    ok(bstg_flist_get(&flist, 99) == 9, "nine");
    ok(bstg_flist_set(&flist, 0, 10) == 0, "nop");
    ok(bstg_flist_get(&flist, 1) == 1, "one");
    ok(bstg_flist_get(&flist, 5) == 5, "five");
    ok(bstg_flist_get(&flist, 99) == 9, "nine");

    ok(bstg_flist_set(&flist, 1, 10) == 0, "nop");
    ok(bstg_flist_get(&flist, 0) == 1, "zero moved");
    ok(bstg_flist_get(&flist, 1) == 2, "one moved");
    ok(bstg_flist_get(&flist, 89) == 9, "now nine");
    ok(bstg_flist_set(&flist, 1, 9) == 0, "nop");
    ok(bstg_flist_get(&flist, 0) == 1, "zero moved");
    ok(bstg_flist_get(&flist, 1) == 2, "one moved");
    ok(bstg_flist_get(&flist, 87) == 8, "now eight");

    ok(bstg_flist_set(&flist, 0, 10) == 0, "nop");
    ok(bstg_flist_shuffle(&flist) == 0, "shuffle");
    for (x = 0; x < 10; x++) {
        if (flist.pindex[0] != x) {
            count++;
        }
    }
    ok(count > 8, "shuffled");

    ok(bstg_flist_import(&flist, "1, 12,33") == 0, "import");
    ok(flist.pindex[0] == 1, "1");
    ok(flist.pindex[1] == 12, "12");
    ok(flist.pindex[2] == 33, "33");
    ok(bstg_flist_get(&flist, 0) == 1, "1");
    ok(bstg_flist_get(&flist, 1) == 12, "12");
    ok(bstg_flist_get(&flist, 2) == 33, "33");
    ok(bstg_flist_get(&flist, 3) == 1, "now 1");
    ok(bstg_flist_import(&flist, "abc") == 1, "bad import");

    ok(bstg_flist_destroy(&flist) == 0, "simple destroy");
    ok(flist.magic != BSTG_FLIST_MAGIC, "magic was unset");

    return 0;
}
