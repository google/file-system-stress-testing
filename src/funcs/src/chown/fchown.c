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

int groupids, fd;
gid_t *newids, newid;
struct stat sbuf;

fd = bstg_fdstore_get(ps);
fstat(fd, &sbuf);

/* get the current supplementary group list */
newids = NULL;
if ((groupids = getgroups(0, NULL)) > 0) {
    newids = calloc(groupids, sizeof(gid_t));
}

newid = -1;
if (newids != NULL) {
    int x;

    /* find the first group id that is different than the file */
    for (x = 0; x < groupids; x++) {
        if (newids[x] != sbuf.st_gid) {
            newid = newids[x];
            break;
        }
    }
}

fchown(fd, -1, newid);
free(newids);

__RCSID("$Id$");
