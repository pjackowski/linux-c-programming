#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

char fifo_path[] = "linux_programming.fifo";

void sighandler(int);
int main(int argc, char *argv[]) {
    char out[100] = "This is FIFO example on Linux";
    char in[100];
    int  fr, fw, res;

    //
    // create FIFO
    res = mkfifo(fifo_path, 0666);
    if(res != 0) {
        perror("Error creating FIFO");
        printf("Removing FIFO %s\n", fifo_path);
        unlink(fifo_path);
        exit(1);
    }

    printf("Created FIFO: %s\n", fifo_path);

    //
    // open FIFO for reading

    // The most important thing to know about FIFOs is that the open()
    // syscall blocks until someone attempts to open the same FIFO for
    // the other direction.

    // You cannot open a FIFO for writing, write something in it and
    // close it and later open it for reading and retrieve the data.
    // It has to be opened for reading and writing simultaneously,
    // because it's a named PIPE.

    fr = open(fifo_path, O_RDONLY | O_NONBLOCK);
    if(fr < 0) {
        perror("Error opening FIFO for read only");
        exit(1);
    }

    //
    // open FIFO for write only
    fw = open(fifo_path, O_WRONLY);

    if(fw < 0) {
        perror("Error opening FIFO for write only");
        exit(1);
    }

    //
    // write to FIFO
    res = write(fw, out, strlen(out) + 1);
    if(res < 0) {
        perror("Error writing to FIFO");
        exit(1);
    }

    //
    // read from FIFO
    res = read(fr, in, sizeof(in));
    if(res < 0) {
        perror("Error reading from FIFO");
        exit(1);
    }

    //
    // close FIFO
    close(fr);
    close(fw);

    //
    // print read result
    printf("Read '%s' from FIFO\n", in);
  
    //
    // remove FIFO from the file system
    printf("Removing FIFO %s\n", fifo_path);
    unlink(fifo_path);

    return 0;
}

void sighandler(int signum) {
    if(signum == 2) {
        printf("Removing FIFO %s\n", fifo_path);
        unlink(fifo_path);
        exit(1);
    }
}