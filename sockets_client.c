#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

int main(int argc, char argv[]) {
    int n_socket, v_read, rv;
    struct sockaddr_in address;

    char buffer[255] = {0};

    char *key = "I am the client.";
    n_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(n_socket < 0) {
        perror("socket function error");
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    rv = inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
    if(rv <= 0) {
        perror("Invalid IP address");
        exit(1);
    }

    rv = connect(n_socket, (struct sockaddr *) &address, sizeof(address));
    if(rv < 0) {
        perror("connect function failure");
        exit(1);
    }

    send(n_socket, key, strlen(key), 0);
    printf("Message sent!\n");

    v_read = read(n_socket, buffer, 1024);
    printf("Content of the buffer:\n");
    printf("%s\n", buffer);

    return 0;
}
