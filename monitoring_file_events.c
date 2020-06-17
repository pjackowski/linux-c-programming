#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>

#define EVENT_SIZE (sizeof (struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))

int main(int argc, char *argv[]) {
    int length, i = 0;
    int fd, wd;
    char buffer[BUF_LEN];
    char path_to_monitor[] = "/home/badsector/public-html/linux-c-programming";

    printf("Setting up file system monitors on directory:\n");
    printf("%s\n\n", path_to_monitor);
    
    fd = inotify_init();
    if(fd < 0) {
        perror("Error: inotify_init error\n");
    }

    wd = inotify_add_watch(fd, path_to_monitor, IN_CREATE | IN_MODIFY | IN_DELETE);
    
    length = read(fd, buffer, BUF_LEN);
    if(length < 0) {
        perror("Error: read error\n");
    }

    while(i < length) {
        struct inotify_event *event = (struct inotify_event *) &buffer[i];

        if(event->mask &IN_CREATE) {
            printf("The file %s has been created\n", event->name);
        }

        if(event->mask &IN_MODIFY) {
            printf("The file %s has been modified\n", event->name);
        }

        if(event->mask &IN_DELETE) {
            printf("The file %s has been deleted\n", event->name);
        }

        i += EVENT_SIZE + event->len;
    }

    (void) inotify_rm_watch(fd, wd);
    (void) close(fd);

    return 0;
}