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
 *
 * $Id$
 */

#include <stdio.h>

int
plan_tests(int count)
{
  printf("1..%d\n", count);
  return count;
}

int
ok(int rc, const char * message)
{
  static int count = 0;

  count++;
  if (rc) {
    printf("ok %d - %s\n", count, message);
  } else {
    printf("not ok %d - %s\n", count, message);
  }

  return rc;
}


