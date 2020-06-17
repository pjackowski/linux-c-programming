#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char argv[]) {
    struct flock flk = {F_WRLCK, SEEK_SET, 0, 0, 0};
    int fd, res;
    
    // simple locks of exclusive locks,
    // locks can be read or write or both,
    // lock whole file or any fragments, ex. single byte
    // exclusive lock prevents other process from locking file

    flk.l_pid = getpid();

    fd = open("locks.c", O_RDWR);

    if(fd < 0) {
        perror("open function error");
        exit(1);
    }

    printf("Press ENTER to lock file.\n");
    getchar();

    // with following line I can not get blocking action as
    // demonstrated in the video
    // flk.l_type = F_RDLCK;

    printf("Checking if we can lock file...\n");

    res = fcntl(fd, F_SETLKW, &flk);
    
    if(res < 0) {
        perror("fcntl function error");
        exit(1);
    }

    printf("File is locked!\n");

    printf("Press ENTER to unlock file.\n");

    getchar();
    flk.l_type = F_UNLCK;
    res = fcntl(fd, F_SETLK, &flk);

    if(res < 0) {
        perror("fcntl function error");
        exit(1);
    }

    close(fd);

    return 0;
}