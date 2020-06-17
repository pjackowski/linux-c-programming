#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t cpid;

    if(fork() == 0) {
        exit(0);
    } else {
        cpid = wait(NULL);
    }

    printf("Parent process id: %d\n", getpid());
    printf("Child Process id : %d\n", cpid);

}