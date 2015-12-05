## Clodagh

This is the first example test to use a special test strategy reduce the test
code to the minimum required to reproduce the kernel core.

```
# you have already followed the installation instructions
DIR=${HOME}/fsstf

# setup /mnt to be your filesystem under test
cd /mnt
mkdir 111 222 333 444 555 666 777 888 999 aaa bbb ccc ddd eee fff
install  -c -s -f uchg -m 0777 /usr/bin/true true
install  -c -s -f uchg -m 0777 /usr/bin/true 111/true

CLODAGH=${DIR?}/file-system-stress-testing-framework-read-only/src/clodagh
cd ${CLODAGH?}

# create a list of operations to execute
LD_LIBRARY_PATH=${DIR?}/lib ./mkpax -c -f big.tgz

# now execute our list of operations
LD_LIBRARY_PATH=${DIR?}/lib ./clodagh big.tgz

```

To start with, the test executation is similar to Brannagh.  But this time, we
used `mkpax` to generate a list of operations.  And `clodagh` is just an
execution engine -- it will only execute the operations in the order found in
the archive.  Now we can
[create strategies](https://code.google.com/p/file-system-stress-testing-framework/wiki/FreeBSDKern159971)
to reduce the archive to a minimal number of operations require to reproduce
the kernel core.
