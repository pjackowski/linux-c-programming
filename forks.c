#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc, char *argv[]) {

    //the way forks work:

    // requires no argument
    // fork()

    // fork returns process id to the parent
    //int pid = fork()

    // after creation parent and child start execution
    // from the next instruction after the fork (next line)

    // return values:
    // fork() > 0, means success
    // fork() < 0, means error, ex. system is out of memory
    // fork() = 0, child process have pid value 0 in the program (?)

    // difference in the exit funtions
    // exit  - performs some cleaning for the process before termination,
    //         buffer flushes, closes network connections, etc.
    // _exit - terminates process without any cleanup tasks

    fork();
    fork();
    printf("Hello Linux!\n");
    printf("Bye Linux!\n");
    exit(0);

}
