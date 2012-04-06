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

#ifdef _POSIX_SPAWN
int status;
pid_t child;
char *token[] = { NULL, NULL };

token[0] = bstg_pathstore_get();
if ((child = fork()) > 0) {
    waitpid(child, &status, 0);
} else if (child == 0) {
    extern char **environ;

    posix_spawn(NULL, token[0], NULL, NULL, token, environ);
    while(wait(&status) > 0);
    _exit(0);
}
#endif

__RCSID("$Id$");
