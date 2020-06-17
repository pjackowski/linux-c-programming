#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/utsname.h>

int main(int argc, char* argv[]) {
    struct utsname buff;

    errno = 0;

    if(uname(&buff) != 0) {
        perror("Error during uname\n");
        exit(EXIT_FAILURE);
    }

    printf("System  : %s\n", buff.sysname);
    printf("Node    : %s\n", buff.nodename);
    printf("Release : %s\n", buff.release);
    printf("Version : %s\n", buff.version);
    printf("Machine : %s\n", buff.machine);
    
    return 0;
}