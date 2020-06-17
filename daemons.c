#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

static void structure_daemon(void) {
    pid_t pid;
    pid = fork();

    // #1
    if(pid < 0) {
        perror("Error when fork #1 call\n");
        exit(EXIT_FAILURE);
    }

    if(pid > 0){
        exit(EXIT_SUCCESS);
    }

    // #2
    if(setsid() < 0) {
        exit(EXIT_FAILURE);
    }

    // #3
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    // #4
    pid = fork();

    if(pid < 0) {
        perror("Error when fork #2 call\n");
        exit(EXIT_FAILURE);
    }

    if(pid > 0){
        exit(EXIT_SUCCESS);
    }

    // #5
    chdir("/");

    // #6
    umask(0);

    // #7
    int i = 0;
    for(i = sysconf(_SC_OPEN_MAX); i >= 0; i--) {
        close(i);
    }

    //#8
    openlog("my_daemon", LOG_PID, LOG_DAEMON);

}

int main(int argc, char *argv[]) {
    // steps to become good daemon
    // 1. fork to have child process working in the background
    // 2. setsid, new session id, so process is detached from controlling terminal
    // 3. catch or ignore signals
    // 4. fork again, let the parent process terminate to get rid of session leader process,
    //    only session leaders have TTY (control oveer terminal)
    // 5. chdir to change working directory of the daemon
    // 6. umask to change file mode mask according to the daemon's need
    // 7. close all file descriptors
    // 8. open log file

    structure_daemon();

    for(;;) {
        syslog(LOG_NOTICE, "Daemon has started\n");
        sleep(20);
        break;
    }

    syslog(LOG_NOTICE, "Daemon has completed\n");
    closelog();

    // captured syslog logs with command: journalctl -r
    // Jun 15 01:06:39 localhost.localdomain my_daemon[11319]: Daemon has completed
    // Jun 15 01:06:19 localhost.localdomain my_daemon[11319]: Daemon has started

    // ps output: ps -fxj | grep daemon
    // 2183 11868 11867 11867 ?           -1 S     1000   0:00  \_ ./daemons

    return EXIT_SUCCESS;
}