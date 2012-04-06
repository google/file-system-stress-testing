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

int fd;
struct stat sbuf;
char *area;

sbuf.st_size = 512;
fstat(fd = bstg_fdstore_get(ps), &sbuf);
area = mmap(NULL, sbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);

if (!sigsetjmp(bstg_jmpbuf, 1)) {
    signal(SIGBUS, bstg_signalj);
    signal(SIGSEGV, bstg_signalj);
    memcpy(pf->buffer.iov_base, area, min(sbuf.st_size, pf->buffer.iov_len));
}
signal(SIGBUS, SIG_DFL);
signal(SIGSEGV, SIG_DFL);

munmap(area, sbuf.st_size);

__RCSID("$Id$");
