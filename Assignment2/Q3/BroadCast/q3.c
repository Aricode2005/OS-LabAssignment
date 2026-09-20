// broadcast_pipe.c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define NUM_LISTENERS 3

int main() {
    int pipes[NUM_LISTENERS][2];
    pid_t pids[NUM_LISTENERS];
    char *weather_update = "Weather Update: Sunny, 28°C, Humidity 60%";

    for (int i = 0; i < NUM_LISTENERS; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Pipe failed");
            return 1;
        }

        pids[i] = fork();

        if (pids[i] == 0) { 
            close(pipes[i][1]); 
            
            char buffer[128];
            read(pipes[i][0], buffer, sizeof(buffer));
            printf("[Listener %d - PID %d] Received: %s\n", i + 1, getpid(), buffer);
            
            close(pipes[i][0]);
            return 0; 
        }
    }

    printf("[Broadcaster - PID %d] Sending weather data...\n", getpid());
    for (int i = 0; i < NUM_LISTENERS; i++) {
        close(pipes[i][0]); 
        write(pipes[i][1], weather_update, strlen(weather_update) + 1);
        close(pipes[i][1]);
    }

    for (int i = 0; i < NUM_LISTENERS; i++) {
        wait(NULL);
    }

    return 0;
}