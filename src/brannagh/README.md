# Brannagh

This is a classic kernel stress test. This example does not use any special
test strategies to reduce the test code to the minimum required to reproduce
the kernel core. We run every test operation randomly waiting for the kernel to
core.  This test may take hours to cause the core and we have no idea what
operations are critical to reproducing the kernel bug.

```
# you have already followed the installation instructions
DIR=${HOME}/fsstf

# run the classic stress test
BRANNAGH=${DIR?}/file-system-stress-testing-framework-read-only/src/brannagh
gmake -C ${BRANNAGH?} check
```
