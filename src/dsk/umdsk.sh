#!/bin/ksh
. ../shlib/bsd.lib

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

#
# umount filesystem
#
aibreann_umount()
{
  typeset md
  typeset dsk

  # config file to be a md(4) disk
  md="$(cat md.txt)"
  if [ -z "${md}" ] ; then
    return 1
  fi

  # mount this new filesystem
  ${SUDO} umount ${MNT}
  if [ ${?} -ne 0 ] ; then
    return 1
  fi

  bstg_undskvnconfig ${md}
  if [ ${?} -ne 0 ] ; then
    return 1
  fi

  return 0
}

aibreann_umount "${1}"
exit
