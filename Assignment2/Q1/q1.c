#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int fd_XY[2];
    int fd_YX[2];

    if (pipe(fd_XY) == -1 || pipe(fd_YX) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
      
        close(fd_XY[0]);
        close(fd_YX[1]);

        int x = 100;
        int yr;

        printf("Process X: Writing x = %d\n", x);
        write(fd_XY[1], &x, sizeof(x)); 

        read(fd_YX[0], &yr, sizeof(yr)); 
        printf("Process X: Read y = %d from Y\n", yr);

        close(fd_XY[1]);
        close(fd_YX[0]);
        exit(0);
    } 
    else if (pid > 0) {
       
        close(fd_YX[0]); 
        close(fd_XY[1]); 

        int y = 200;
        int xr;

        printf("Process Y: Writing y = %d\n", y);
        write(fd_YX[1], &y, sizeof(y)); 
        
        read(fd_XY[0], &xr, sizeof(xr)); 
        printf("Process Y: Read x = %d from X\n", xr);

        close(fd_YX[1]);
        close(fd_XY[0]);
        
        wait(NULL); 
    }

    return 0;
}