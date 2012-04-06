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

int pfd[2];

if (pipe(pfd) != -1) {
    int x, val;

    for (x = 0; x < 2; x++) {
        if ((val = fcntl(pfd[x], F_GETFL, 0)) >= 0) {
            val |= O_NONBLOCK;
            fcntl(pfd[x], F_SETFL, val);
        }
        bstg_fdstore_set(ps, pfd[x]);
    }
}

__RCSID("$Id$");
