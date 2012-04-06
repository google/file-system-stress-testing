#!/bin/ksh
#
# Copyright 2011 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
SSRC="${1}"
DEST="${2}"
FUNC="$(echo ${2} | sed 's/\//_/g' | sed 's/[.]c//g')"
printf "#include \"internalfuncs.h\"\n\n"
printf "void %s(bstg_funcs_t *pf)\n{\n" ${FUNC}
printf "  bstg_fdstore_t *ps;\n\n"
printf "  ps = &pf->fdstore;\n"
printf "  setproctitle(\"%%s\", __func__);\n"
printf "  if (pf->verbose) {\n"
printf "    write(2, __func__, sizeof(__func__));\n"
printf "    write(2, \"%cn\", 1);\n" "\\"
printf "    fsync(2);\n"
printf "    tcdrain(2);\n"
printf "    usleep(250);\n"
printf "  }\n"
printf "  #include \"%s\"\n}\n\n" ${SSRC}
