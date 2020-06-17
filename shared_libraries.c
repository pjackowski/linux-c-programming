#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // shared and static libraries
    
    // create static library:
    // ar -rc libstatic.a LIST_OF_LIBRARIES_TO_LINK

    // compile source with use of static library:
    // gcc -g -o prog prog.o libprogstatic.a

    // compile shared library:
    // gcc -g -fPIC -Wall -Werror -Wextra -pedantic *.c -shared -o libshared.so

    return 0;
}