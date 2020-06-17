#include<stdio.h>
#include<stdlib.h>
#include<sys/statvfs.h>

int main(int argc, char* argv[]) {
    struct statvfs buff;

    if(statvfs(".", &buff) == -1) {
        perror("Error reading statvfs\n");
        exit(1);
    } else {
        printf("Each file system block has size of %ld\n", buff.f_frsize);
        printf("There are %ld blocks available out of %ld\n", buff.f_bavail, buff.f_blocks);
    }

    return 0;
}