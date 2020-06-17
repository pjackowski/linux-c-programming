#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    long path_size;
    char *path_ptr = NULL;
    char *buff = NULL;
    int res;

    //
    // get current path
    printf("\n#1 Read current path\n");

    // getcwd requires buffer size, so first check max path size
    // allowed on the machine to avoid overflows
    path_size = pathconf(".", _PC_PATH_MAX);
    printf("_PC_PATH_MAX: %ld\n", path_size);

    // allocate memory
    buff = (char *) malloc((size_t) path_size);

    if(buff != NULL) {
         path_ptr = getcwd(buff, (size_t) path_size);
    }

    printf("Current path: %s\n", path_ptr);

    //
    // create a new directory
    printf("\n#2 Create a new directory\n");
    res = mkdir("./testdir", 0600);

    if(res == 0) {
        printf("Directory created\n");
    } else {
        printf("Directory creation failed, error: %d\n", res);
    }

    return 0;
}