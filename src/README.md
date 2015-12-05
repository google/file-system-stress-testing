# How to install and compile the test framework.

The execution of these file system stress tests will find bugs in the FreeBSD
kernel.  You want to run these tests on a test/scratch machine that contains no
data of value.  We assume you have a root account on this test machine.

## Installation to FreeBSD 9.0

```
DIR=${HOME}/fsstf

# install required packages
pkg_add -r wget
pkg_add -r subversion
pkg_add -r gmake
pkg_add -r pdksh

# get the source for fsstf
cd ${DIR?}
svn checkout http://file-system-stress-testing-framework.googlecode.com/svn/trunk/ file-system-stress-testing-framework-read-only

# port and install proplib to freebsd
cd ${DIR?}/etc
wget http://portableproplib.googlecode.com/files/proplib-0.6.0.tar.xz
cd ${DIR?}
tar xf etc/proplib-0.6.0.tar.xz
cd ${DIR?}/proplib-0.6.0/src
patch < ../../file-system-stress-testing-framework-read-only/contrib/freebsd9_proplib-0.6.0.patch
cd ${DIR?}/proplib-0.6.0
sh ./configure --prefix=${DIR?}
make CFLAGS=-D__GNUC_PREREQ=__GNUC_PREREQ__
make install

# port fsstf to freebsd
cd ${DIR?}/file-system-stress-testing-framework-read-only
printf "CFLAGS:=-Wall -Werror -O0 -g2 -I${DIR?}/include\n" > src/inc/debug.mk
printf "LDFLAGS:=-L${DIR?}/lib\n" >> src/inc/debug.mk
printf "BSTG_TAP_CFLAGS=-I../etc\n" >> src/inc/debug.mk
printf "BSTG_TAP_LDFLAGS=-L.\n" >> src/inc/debug.mk
printf "PROVE=../etc/prove\n" >> src/inc/debug.mk
printf "SUDO=env\n" >> src/inc/debug.mk
printf "KSH=/usr/local/bin/ksh\n" >> src/inc/debug.mk

# compile fsstf and example tests
cd ${DIR?}/file-system-stress-testing-framework-read-only/src
gmake
```

## Installation to Linux

The early project development used FreeBSD instead of Linux.  If you have an
interest porting to Linux, please contact the project maintainers -- we are
interested in supporting Linux as a future goal.
