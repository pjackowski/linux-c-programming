#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <seccomp.h>
#include <errno.h>

void call_child(void) {
    scmp_filter_ctx ctx;
    int rc;

    // initialize seccomp context 
    
    // whitelist, error by default
    ctx = seccomp_init(SCMP_ACT_ERRNO(EPERM));

    // blacklist, allow by default
    // ctx = seccomp_init(SCMP_ACT_ALLOW);

    // adding seccomp rule #1 (write)
    // syscall: write, sys_write, fs/read_write.c
    rc = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0);
    if(rc < 0) {
        fprintf(stderr, "rule %d add failed\n", rc);
        goto out;
    }

    // adding seccomp rule #2 (exit)
    // syscall: exit, sys_exit, kernel/exit.c
    rc = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0);
    if(rc < 0) {
        fprintf(stderr, "rule %d add failed\n", rc);
        goto out;
    }

    // additional error handling to see if rules loaded
    rc = seccomp_load(ctx);
    if(rc < 0) {
        fprintf(stderr, "context load failed %d\n", rc);
        goto out;
    }

    // calling an array after declaring seccomp rules
    // it works for me, but doesn't on the presentation,
    // looks like seccomp isn't enabled/enforced in Fedora
    fprintf(stdout, "hello world\n");

out:
    seccomp_release(ctx);
}

int main(int argc, char *argv[]) {
    pid_t cpid;
    
    fprintf(stdout, "main\n");
    
    // do not init seccomp here, unless you wont to grant
    // access to fork or clone syscall; glibc is likely actually
    // using the system call clone instead of fork, see man fork;
    // you can verify this by having a look at strace ./a.out
    
    cpid = fork();

    // check for failed fork process
    if(cpid < 0) {
        fprintf(stdout, "fork failed\n");
        exit(-1);
    }

    // only when forking succeeded
    if(cpid == 0) {
        fprintf(stdout, "child\n");
        call_child();
    } else {
        fprintf(stdout, "parent\n");
    }

}
