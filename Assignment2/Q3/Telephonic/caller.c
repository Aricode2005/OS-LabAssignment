#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_C2R "/tmp/fifo_caller_to_receiver"
#define FIFO_R2C "/tmp/fifo_receiver_to_caller"

int main() {
    mkfifo(FIFO_C2R, 0666);
    mkfifo(FIFO_R2C, 0666);

    printf("Waiting for Receiver to connect...\n");
    int fd_write = open(FIFO_C2R, O_WRONLY);
    int fd_read = open(FIFO_R2C, O_RDONLY);
    printf("Connected! Start typing...\n");

    if (fork() == 0) {
        char buffer[256];
        while (read(fd_read, buffer, sizeof(buffer)) > 0) {
            printf("\r[Receiver]: %s", buffer);
        }
        exit(0);
    } else {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            write(fd_write, buffer, strlen(buffer) + 1);
        }
    }
    return 0;
}