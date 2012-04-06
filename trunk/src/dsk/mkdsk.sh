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
# Create and initialize a new filesystem suitable for this test case.
#
aibreann_newfs()
{
  typeset md
  typeset dsk

  dsk=${1}
  # we expect this file to exist
  if [ ! -s ${dsk} ] ; then
    return 1
  fi

  # config file to be a md(4) disk
  md="$(bstg_dskvnconfig ${dsk})"
  if [ -z "${md}" ] ; then
    return 1
  fi

  # save for later
  printf "%s\n" ${md} > md.txt

  # format the filesystem 
  bstg_newfs ${md} ${dsk}
  if [ ${?} -ne 0 ] ; then
    bstg_undskvnconfig ${md}
    return 1
  fi

  # mount this new filesystem
  bstg_bsdmount /dev/${md} ${MNT} ${dsk}
  if [ ${?} -ne 0 ] ; then
    bstg_undskvnconfig ${md}
    return 1
  fi

  return 0
}

aibreann_newfs "${1}"
exit
