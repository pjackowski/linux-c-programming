#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int ctrl_c_counter = 0;

void sighandler(int);
int main(int argc, char *argv[]) {
    
    signal(SIGINT, sighandler);

    for(;;) {
        printf("Sleeping...\n");
        sleep(3);
    }

    return 0;
}

void sighandler(int signum) {
    printf("\nCaught signal %d", signum);

    if(signum == 2) {
        printf("\nCareful now, ctrl+c is powerful signal...\n");
        ctrl_c_counter++;

        if(ctrl_c_counter >= 5) {
            printf("Alright, alright, exiting now...\n");
            exit(1);
        }
        
    }
}