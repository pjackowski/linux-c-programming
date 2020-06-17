#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
    int proc_id, parent_proc_id;

    proc_id = getpid();
    parent_proc_id = getppid();

    printf("PID : %d\n", proc_id);
    printf("PPID: %d\n", parent_proc_id);

    return 0;

}