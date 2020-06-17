#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *my_thread(void *vargp) {
    sleep(2);
    printf("Hello from the thread (2s delay)\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t tid;

    printf("Starting threading example\n");
    printf("Hello from the parent\n");
    pthread_create(&tid, NULL, my_thread, NULL);
    pthread_join(tid, NULL);
    printf("Threading example is complete\n");
    
    return 0;
}