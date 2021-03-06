# Using Clodagh to reproduce FreeBSD bug kern/159971

## FreeBSD bug [kern/159971](http://www.freebsd.org/cgi/query-pr.cgi?pr=159971)

### Introduction

The example test
[Clodagh](https://github.com/google/file-system-stress-testing/tree/master/src/clodagh)
was used to find a filesystem bug with FreeBSD 9.0.  We were able to reduce the
number of operations required to reproduce the crash to only four operations.
The test code from the bug report --
[bstg0003.c](http://people.freebsd.org/~pho/stress/issues/suj23.sh),
used these operations from the framework library:

* [mkhashbang2.c](https://github.com/google/file-system-stress-testing/blob/master/src/funcs/special/mkhashbang2.c)
* [gcore.c](https://github.com/google/file-system-stress-testing/blob/master/src/funcs/special/gcore.c)
* [link.c](https://github.com/google/file-system-stress-testing/blob/master/src/funcs/src/link/link.c)
* [unlink.c](https://github.com/google/file-system-stress-testing/blob/master/src/funcs/src/unlink/unlink.c)


Here are the optimized instructions to reproduce
[kern/159971]([http://www.freebsd.org/cgi/query-pr.cgi?pr=159971),
using [Clodagh](https://github.com/google/file-system-stress-testing/tree/master/src/clodagh):
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
LD_LIBRARY_PATH=${DIR?}/lib ./mkpax -c -S "95 2 12 79" -f 159971.tgz

# now execute our list of four operations
LD_LIBRARY_PATH=${DIR?}/lib ./clodagh 159971.tgz

# within a few minutes, we get a panic
panic: ino 0xc54bcb00(0x3C8209) 284170, 378888 != 284183
```

### Step One -- create a champion archive

We want to setup a competition between different subsets of file system
operations.  We will create two archives of file system operations -- each
operation will only appear in one archive.  The plan is to execute
[Clodagh](https://github.com/google/file-system-stress-testing/tree/master/src/clodagh)
for each archive -- the archive that can crash the kernel the fastest is the
winner.  We will want to repeat this step multiple times.  Ideally you will
find an archive that will core the kernel in a few seconds.

````
cd ${CLODAGH?}

# randomly divide the operations into two seperate lists
LD_LIBRARY_PATH=${DIR?}/lib ./mkpax -c -J 2
# The two archives 0.tar.gz and 50.tar.gz will be created.

# now execute the first half
LD_LIBRARY_PATH=${DIR?}/lib ./clodagh 0.tar.gz

# now execute the remaining half
LD_LIBRARY_PATH=${DIR?}/lib ./clodagh 50.tar.gz
```


### Step two -- reduce the champion archive

Stage a second competition between different subsets of file system operations.
The only operations that can participate are the operations in the champion
archive -- half of the file system operations will be excluded from this second
competition. The archive that can crash the kernel the fastest is the winner.
We will want to repeat this step multiple times.  Ideally you will find an
archive that will core the kernel in a few seconds.  It is possible the winning
archive will be the original champion archive.

```
cd ${CLODAGH?}

# determine the list of eligible operations
LIST=$(LD_LIBRARY_PATH=${DIR?}/lib ./mkpax -r -f big.tgz | sort -n | uniq)

# randomly divide the remaining operations into two seperate lists
LD_LIBRARY_PATH=${DIR?}/lib ./mkpax -c -S ${LIST?} -J 2

# The two archives 0.tar.gz and 25.tar.gz will be created.

# now execute the first half
LD_LIBRARY_PATH=${DIR?}/lib ./clodagh 0.tar.gz

# now execute the remaining half
LD_LIBRARY_PATH=${DIR?}/lib ./clodagh 25.tar.gz

```

### Step three -- remove dead operations

We will stage another competition.  We will create one new archive for every
file system operation in the champion archive.  Every new archive will have one
operation missing. If the new archive can still crash the kernel, we know that
missing operation is not required and we will drop it from the champion
archive.  If the new archive cannot crash the kernel, we know that the missing
operation is a required operation and it has to remain in the champion archive.

### Step four -- file the bug report

For the
[kern/159971](http://www.freebsd.org/cgi/query-pr.cgi?pr=159971)
bug, the champion archive only had four unique operations. 
If your organization uses
[Clodagh](https://github.com/google/file-system-stress-testing/tree/master/src/clodagh):
* You could file a bug report with only the archive or the maybe just the list of operations.
* You would create a regression test suite of champion archives.  We would also add this new archive to this test suite.

For this FreeBSD bug, we just took the four operations, wrote a quick test
harness and submitted
[this code](http://people.freebsd.org/~pho/stress/issues/suj23.sh)
with the bug report.
