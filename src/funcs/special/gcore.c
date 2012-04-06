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

pid_t sleepchild, gcorechild;

/* create a child for the gcore target */
if ((sleepchild = fork()) == 0) {
    sleep(30);
    _exit(1);
} else if (sleepchild > 0) {
    char *token[] = { NULL, NULL, NULL, NULL, NULL };
    char buf[128];
    int status;

    /* use the first process as the target */
    snprintf(buf, sizeof(buf), "%d", sleepchild);
    token[0] = "gcore";
    token[1] = "-c";
    token[2] = bstg_pathstore_get();
    token[3] = buf;

    if ((gcorechild = fork()) > 0) {
        /* parent should busywait for the gcorechild to terminate */
        bstg_waitpid(gcorechild, &status, 60);
    } else if (gcorechild == 0) {
        extern char **environ;

        bstg_preexec(ps);
        /* TODO(krussell) document or fix harded gcore path */
        execve("/usr/bin/gcore", token, environ);
        _exit(1);
    }

    kill(sleepchild, SIGKILL);
    waitpid(sleepchild, &status, 0);
}

__RCSID("$Id$");
