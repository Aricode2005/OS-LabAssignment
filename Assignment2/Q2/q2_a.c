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

    pid_t pid_X = fork();
    if (pid_X == 0) {
        srand(time(NULL) ^ getpid()); 

        for (int i = 0; i < N; i++) {
            printf("Process X (PID: %d) - Iteration %d starting\n", getpid(), i);
            
            int sleep_time = (rand() % 3) + 1;
            sleep(sleep_time); 
            
            printf("Process X (PID: %d) - Iteration %d finished\n", getpid(), i);
        }
        exit(0);
    }

    pid_t pid_Y = fork();
    if (pid_Y == 0) {
        srand(time(NULL) ^ getpid());

        for (int i = 0; i < N; i++) {
            printf("Process Y (PID: %d) - Iteration %d starting\n", getpid(), i);
            
            int sleep_time = (rand() % 3) + 1;
            sleep(sleep_time); 
            
            printf("Process Y (PID: %d) - Iteration %d finished\n", getpid(), i);
        }
        exit(0);
    }

    
    wait(NULL);
    wait(NULL);
    
    printf("Parent Process (PID: %d): Both X and Y have finished.\n", getpid());
    return 0;
}