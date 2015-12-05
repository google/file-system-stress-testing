# Aibreann

This is a smoke test to ensure the kernel is suitable for testing.  We have
created a small disk image with a collection of files, symlinks, directories
and fifos. We will run every operation, from our library, and target every file
object on the disk image.  We expect the kernel to not core.  And we expect the
file system images to fsck cleanly.

If the kernel does core, you should be able to remove functions from the
operational set to determine which kernel call is causing the problems.  This
example does not use any special test strategies to reduce the test code to the
minimum required to reproduce the kernel core.

Here are some example bugs that should be easy to reproduce with this smoke test:
* [kern/98064: Crash with FIFOs (named pipes) and truncate()](http://www.freebsd.org/cgi/query-pr.cgi?pr=98064)
* [kern/98116: Crash with sparse files and execve](http://www.freebsd.org/cgi/query-pr.cgi?pr=98116)


```
# you have already followed the installation instructions
DIR=${HOME}/fsstf

# run the smoke test
AIBREAN=${DIR?}/file-system-stress-testing-framework-read-only/src/aibreann
gmake -C ${AIBREAN?} check
```
