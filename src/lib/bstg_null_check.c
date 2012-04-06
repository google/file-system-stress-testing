/*
 * Copyright 2012 Google Inc.
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

#include <err.h>
#include <stdlib.h>
#include <sys/cdefs.h>

__RCSID("$Id$");

void *
bstg_null_check(void *ptr, const char *filename, int line)
{
    if (ptr == NULL) {
        errx(1, "NULL found : file=%s line=%d\n", filename, line);
    }
    return ptr;
}

