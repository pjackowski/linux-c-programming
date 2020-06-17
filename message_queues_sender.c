#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>

struct msg_buffer {
    long msg_type;
    char msg_txt[500];
} message;

int main(int argc, char *argv[]) {
    key_t key;
    int msg_id;

    key = ftok("progfile", 65);
    msg_id = msgget(key, 0666 | IPC_CREAT);
    message.msg_type = 1;

    printf("Please input data to send:\n");
    fgets(message.msg_txt, sizeof(message.msg_txt), stdin);
    
    msgsnd(msg_id, &message, sizeof(message), 0);

    printf("Data sent.\n");

    return 0;
}