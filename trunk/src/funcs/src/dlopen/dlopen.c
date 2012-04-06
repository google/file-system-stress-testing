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

char *mypath;
pid_t child;

mypath = bstg_pathstore_get();

if ((child = fork()) > 0) {
    int status;

    /* parent should busywait for the child to terminate */
    bstg_waitpid(child, &status, 30);
} else if (child == 0) {
    void *handle;

    signal(SIGBUS, bstg_signalx);
    signal(SIGSEGV, bstg_signalx);
    if ((handle = dlopen(mypath, RTLD_LAZY)) != NULL) {
        dlclose(handle);
    }
    signal(SIGBUS, SIG_DFL);
    signal(SIGSEGV, SIG_DFL);

    _exit(1);
}

__RCSID("$Id$");
