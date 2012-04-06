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

struct stat sbuf;
int fd;
char * base;

/* TODO(krussell): document /true is expected to be permanent */

base = MAP_FAILED;
fd = open(BSTG_BASEDIR"/true", O_RDONLY|O_NONBLOCK|O_NOCTTY);
if ((fd > 0) && (fstat(fd, &sbuf) == 0)) {
    base = mmap(NULL, sbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
}
close(fd);

if (base != MAP_FAILED) {
    fd = bstg_fdstore_get2(ps, 0);
    posix_madvise(base, sbuf.st_size, POSIX_MADV_SEQUENTIAL);
    ftruncate(fd, 0);
    pwrite(fd, base, sbuf.st_size, 0);
    munmap(base, sbuf.st_size);
}

__RCSID("$Id$");
