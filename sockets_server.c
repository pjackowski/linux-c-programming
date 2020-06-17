#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8080

int main(int argc, char argv[]) {
    int serv_fd, n_socket, v_read, rv;
    struct sockaddr_in address;

    int opt = 1;
    int addr_length = sizeof(address);
    char buffer[255] = {0};

    char *key = "I am the server.";
    serv_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(serv_fd < 0) {
        perror("socket function error");
        exit(1);
    }

    rv = setsockopt(serv_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    if(rv < 0) {
        perror("setsockopt function error");
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    rv = bind(serv_fd, (struct sockaddr *) &address, sizeof(address));
    if(rv < 0) {
        perror("bind funcion error");
        exit(1);
    }

    rv = listen(serv_fd, 3);
    if(rv < 0) {
        perror("listen function error");
        exit(1);
    }

    n_socket = accept(serv_fd, (struct sockaddr *) &address, (socklen_t *) &addr_length);
    if(n_socket < 0) {
        perror("accept function error");
        exit(1);
    }

    v_read = read(n_socket, buffer, 1024);

    printf("Content of the buffer:\n");
    printf("%s\n", buffer);

    send(n_socket, key, strlen(key), 0);

    printf("Message sent!\n");

    return 0;
}
