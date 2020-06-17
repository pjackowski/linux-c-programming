#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define KEY 0x1111
#define INTERVAL 1

union semun {
    int value;
    struct semid_ds *buf;
    unsigned short *array;
};

// SEM_UNDO flag allows processes' semaphore be undone on process termination,
// otherwise other processes might be blocked if semaphone remains in incorrect state
struct sembuf p = { 0, -1, SEM_UNDO}; // semwait, down, acquire
struct sembuf v = { 0, +1, SEM_UNDO}; // semsignal, up, release

// some more reading on these structures realated to semaphores:
// sodocumentation.net/c/topic/10564/interprocess-communication--ipc-
// en.wikipedia.org/wiki/Semaphore_(programming)#Operation_names

int main(int argc, char *argv[]) {
    int sid = semget(KEY, 1, 0666 | IPC_CREAT);
    int res;

    if(sid < 0) {
        perror("Error when getting key for semaphore");
        exit(1);
    }

    union semun su;
    su.value = 1;

    res = semctl(sid, 0, SETVAL, su);

    if(res < 0) {
        perror("semctl error");
        exit(1);
    }

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
    
    int pid;
    pid = fork();

    if(pid < 0) {
        perror("fork error");
        exit(1);
    } else if(pid) {
    
        // parent
        
        char *se = "abcdefghijklmnop";
        int l = strlen(se);
        
        for(int i = 0; i < l; i++) {
        
            if(semop(sid, &p, 1) < 0) {
                perror("semop error #p");
                exit(1);
            }

            putchar(se[i]);
            fflush(stdout);
            
            sleep(INTERVAL);
            
            putchar(se[i]);
            fflush(stdout);

            if(semop(sid, &v, 1) < 0) {
                perror("semop error #v");
                exit(1);
            }

            sleep(INTERVAL);

        }
    
    } else {
        
        // child
        
        char *se = "ABCDEFGHIJKLMOP";
        int l = strlen(se);
        
        for(int i = 0; i < l; i++) {
        
            if(semop(sid, &p, 1) < 0) {
                perror("semop error #p");
                exit(1);
            }

            putchar(se[i]);
            fflush(stdout);
            
            sleep(INTERVAL);
            
            putchar(se[i]);
            fflush(stdout);

            if(semop(sid, &v, 1) < 0) {
                perror("semop error #v");
                exit(1);
            }

            sleep(INTERVAL);

        }

    }

    return 0;
}