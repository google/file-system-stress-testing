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

#ifndef BSTG_BASEDIR
#error You need to define the mount point used during your test execution.
#endif

#include "fembot.h"
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/cdefs.h>

__RCSID("$Id$");

#define NPATHS ((sizeof(bstg_pathstore)/sizeof(bstg_pathstore[0])))
#define NFUNCS ((unsigned long)((sizeof(bstg_fembot_funcs)/sizeof(bstg_fembot_funcs[0]))))

const char *const bstg_pathstore[] = {
#include "pathstore.h"
};

int bstg_pathstore_count = 0;

char *
bstg_pathstore_get()
{
    return (char *)bstg_pathstore[bstg_pathstore_count % NPATHS];
}

#include "fembotfuncs.h"

void
usage(void)
{
    fprintf(stderr, "usage: aibreann [-n]\n");
    fprintf(stderr, "usage: aibreann [-f 0-%lu]\n", NFUNCS);
    exit(1);
}


int
main(int argc, char *argv[])
{
    int ch, nflag, farg;
    static bstg_funcs_t bfs;

    nflag = 0;
    farg = -1;
    while ((ch = getopt(argc, argv, "f:n")) != -1) {
        char *p;

        switch (ch) {
            case 'f':
                farg = strtol(optarg, &p, 10);
                if (*p != 0) {
                    usage();
                }
                break;
            case 'n':
                nflag = 1;
                break;
            case '?':
            default:
                usage();
        }
    }

    if (nflag) {
        printf("%lu\n", NFUNCS);
        return 0;
    }

    if (farg < 0 || farg >= NFUNCS) {
        usage();
    }

    if (bstg_funcs_init(&bfs, 1, 1048576)) {
        errx(1, "cannot init bfs");
    }

    for (bstg_pathstore_count = 0; bstg_pathstore_count < NPATHS;
            bstg_pathstore_count++) {

        if (bstg_fembot_funcs[farg] != src_close_closeall_bstg_funcs) {
            (*bstg_fembot_funcs[farg]) (&bfs);
        }

        if (bstg_fdstore_closeall(&bfs.fdstore)) {
            errx(1, "cannot fdstore closeall");
        }
    }

    if (bstg_funcs_destroy(&bfs)) {
        errx(1, "cannot bfs destroy");
    }
    return 0;
}
