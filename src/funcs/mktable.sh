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
printf "void (*bstg_fembot_funcs[])(bstg_funcs_t *) = {\n"

let acount=0
for pname in ${@}
do
	FUNC="$(echo ${pname} | sed 's/\//_/g' | sed 's/[.]c//g')"
	printf "  %s, /* %d */\n" ${FUNC} ${acount}
    let acount=acount+1
done

printf "};\n"

