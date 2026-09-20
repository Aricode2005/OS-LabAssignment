#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
 
int main() {
    int N;
    printf("Enter number of iterations (N >= 10): ");
    scanf("%d", &N);
    if (N < 10) {
        printf("N must be at least 10. Setting N to 10.\n");
        N = 10; 
    }

    int sync_pipe[2];
    if (pipe(sync_pipe) == -1) {
        perror("Pipe failed");
        return 1;
    }
    
    pid_t pid_X = fork();
    if (pid_X == 0) {
        srand(time(NULL) ^ getpid()); 
        close(sync_pipe[0]); 
        for (int i = 0; i < N; i++) {
            printf("Process X (PID: %d) - Iteration %d starting\n", getpid(), i);
            
            sleep((rand() % 3) + 1); 
            
            printf("Process X (PID: %d) - Iteration %d finished\n", getpid(), i);
            
            char token = 'S';
            write(sync_pipe[1], &token, 1);
        }
        close(sync_pipe[1]);
        exit(0);
    }

    pid_t pid_Y = fork();
    if (pid_Y == 0) {
        srand(time(NULL) ^ getpid());
        close(sync_pipe[1]); 
        
        for (int i = 0; i < N; i++) {
            if (i > 0) {
                char token;
                read(sync_pipe[0], &token, 1); 
            }
            
            printf("Process Y (PID: %d) - Iteration %d starting\n", getpid(), i);
            
            sleep((rand() % 3) + 1);
            
            printf("Process Y (PID: %d) - Iteration %d finished\n", getpid(), i);
        }
        close(sync_pipe[0]);
        exit(0);
    }

    wait(NULL);
    wait(NULL);
    printf("Parent Process (PID: %d): Both X and Y have finished.\n", getpid());
    return 0;
}