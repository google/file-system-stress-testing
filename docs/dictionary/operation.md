## Operation

When you execute a monkey test, this is consider one test -- the test find a
failure of this monkey test finds a new kernel crash or a diagnostic check
(fsck) fails.  The monkey test try to exercise the API of the software under
test in many random ways -- each exercise attempt will be defined as an
operation.  Operations will be stored in a pool.  A list of operations is a
subset of operations from the pool.
