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

#include <setjmp.h>
#include <signal.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/cdefs.h>

__RCSID("$Id$");

volatile sig_atomic_t count;


int
main()
{
    char *area;

    plan_tests(1);

    count = 0;
    area = mmap(0, 4096, PROT_READ|PROT_WRITE, MAP_ANON, -1, 0);
    if (area != MAP_FAILED) {
        munmap(area, 4096);
    }

    signal(SIGBUS, bstg_signalj);
    signal(SIGSEGV, bstg_signalj);

    if (!sigsetjmp(bstg_jmpbuf, 1)) {
        memset(area, 0xff, 4096);
    } else {
        count++;
    }

    signal(SIGBUS, SIG_DFL);
    signal(SIGSEGV, SIG_DFL);

    ok(count == 1, "we did fault");

    return 0;
}
