#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *argv2[] = {"ls", NULL};
    execvp(argv2[0], argv2);

    return 0;
}