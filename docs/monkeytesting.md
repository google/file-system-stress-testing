# Monkey testing tool comparison.


## Monkey Testing

We can [categorize](http://www.testingeducation.org/k04/documents/bbst16_2004.ppt)
existing OS kernel monkey test strategies using these characteristics:

* type: Are the test case operations created dynamically during execution?  Do you use a pool of existing static test case operations?
* size: What is the size of the test case operational set?
* success criteria: crash/diagnostic vs oracle vs state machine
* dependence: Are the test case operations run serially or in parallel?

project | type | size | success criteria | dependence
------- | ---- | ---- | ---------------- | ----------
[crashme](http://people.delphiforums.com/gjc/crashme.html) | dynamically | huge | crash/diagnostic | serially
fsx | static | small | crash/diagnostic/oracle | serially
krt | static/dynamic | depends | crash/diagnostic | parallel
[Aibreann](https://github.com/google/file-system-stress-testing/tree/master/src/aibreann) | static | small | crash/diagnostic | serially
[Brannagh](https://github.com/google/file-system-stress-testing/tree/master/src/brannagh) | static | medium | crash/diagnostic | parallel
[Clodagh](https://github.com/google/file-system-stress-testing/tree/master/src/clodagh) | static | medium | crash/diagnostic | parallel


## fsx

* [fsx.c](http://codemonkey.org.uk/projects/fsx/)

Testing tools of this class quickly become a victim of the
[Pesticide Paradox](https://github.com/google/file-system-stress-testing/blob/master/docs/dictionary/pesticideparadox.md).
When you first use fsx.c to test a filesystem, you will find a set of new
bugs.  The operations are run serially, so bug reproduction is trivial. After
these bugs are fixed, fsx becomes a pure regression test because the tool is
ineffective in finding existing bugs.

To continue to find more bugs, the tool will have to:
* increase the size of the operational pool
* execute the operations in parallel

Making these changes to fsx, or this type of tool, might reduce the
effectiveness of the tool as a regression test because the tool could avoid
once travelled code paths, after the new changes.

## krt

* ["A Structured Framework for Designing Kernel Reliability Tests." 11th International Software Quality Conference (Quality Week), San Francisco, CA, May, 1998](http://www.employees.org/~kirk/doc/krt.ps.gz)

project | type | size | success criteria | dependence
------- | ---- | ---- | ---------------- | ----------
[krt](http://www.employees.org/~kirk/doc/krt.ps.gz) | static | small | crash/diagnostic | parallel

Tools of this class avoid the
[Pesticide Paradox](https://github.com/google/file-system-stress-testing/blob/master/docs/dictionary/pesticideparadox.md)
by making it easy to add new operations to the operational pool. Running these
operations in parallel continues to find new bugs in existing code.

The entropy used by these tools will often make root cause analysis
[difficult and time consuming](http://unix.derkeiler.com/Mailing-Lists/FreeBSD/arch/2009-01/msg00053.html).
The bug reports usually consist of running a 1000 line test program for 6-12
hours and eventually the kernel will core.  The odds of having a volunteer open
source kernel developer spending a week to fix this bug is not high.  If we
could some how reduce the test program to two/three kernel calls and the
execution time to 30 seconds, you will have a better change of getting kernel
developer resources to fix this bug.  


## References

* [Black Box Testing](http://www.testingeducation.org/k04/documents/bbst16_2004.ppt)
* ["A Structured Framework for Designing Kernel Reliability Tests." 11th International Software Quality Conference (Quality Week), San Francisco, CA, May, 1998](http://www.employees.org/~kirk/doc/krt.ps.gz)
* [The FreeBSD Kernel Stress Test Suite](http://people.freebsd.org/~pho/stress/index.html)
* [Monkey test, from Wikipedia](http://en.wikipedia.org/wiki/Monkey_test)
* [Differential Testing for Software](http://www.linux-mips.org/pub/linux/mips/people/macro/DEC/DTJ/DTJT08/DTJT08PF.PDF)
* [Fuzzing at scale](http://googleonlinesecurity.blogspot.com/2011/08/fuzzing-at-scale.html)
* [Software Testing](http://www.ece.cmu.edu/~koopman/des_s99/sw_testing)
* [An Empirical Study into the Security Exposure to Hosts of Hostile Virtualized Environments](http://taviso.decsystem.org/virtsec.pdf)
