#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/time.h>

#define INTERVAL 1000

void signal_handler(int);
int main(int argc, char *argv[]) {
    struct itimerval it_val;

    if(signal(SIGALRM, (void (*)(int)) signal_handler) == SIG_ERR) {
        perror("Unable to catch signal\n");
        exit(1);
    }

    it_val.it_value.tv_sec = INTERVAL / 1000;
    it_val.it_value.tv_usec = (INTERVAL / 1000) % 1000000;
    it_val.it_interval = it_val.it_value;

    if(setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
        perror("Timer does not work properly\n");
    }

    for(;;) {
        pause();
    }
    
    return 0;
}

void signal_handler(int signum) {
    printf("Received timer alarm, interval %dms\n", INTERVAL);
}