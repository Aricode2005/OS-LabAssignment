#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#define MAX_LISTENERS 10
#define MSG_KEY 1234
#define BROADCASTER_MTYPE 1

struct msg_buffer {
    long mtype;
    pid_t sender_pid;
    char text[128];
};

int msgid;
pid_t listeners[MAX_LISTENERS];
int listener_count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* receive_messages(void* arg) {
    struct msg_buffer msg;
    while (1) {
        msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), BROADCASTER_MTYPE, 0);
        
        if (strcmp(msg.text, "REGISTER") == 0) {
            pthread_mutex_lock(&lock);
            if (listener_count < MAX_LISTENERS) {
                listeners[listener_count++] = msg.sender_pid;
                printf("\n[System] Listener %d connected.\n> ", msg.sender_pid);
            }
            pthread_mutex_unlock(&lock);
        } else {
            printf("\n[Listener %d says]: %s> ", msg.sender_pid, msg.text);
        }
        fflush(stdout);
    }
    return NULL;
}

int main() {
    msgid = msgget((key_t)MSG_KEY, 0666 | IPC_CREAT);
    
    pthread_t thread;
    pthread_create(&thread, NULL, receive_messages, NULL);

    struct msg_buffer msg;
    printf("Broadcaster started. Type messages to broadcast:\n> ");
    while (fgets(msg.text, sizeof(msg.text), stdin) != NULL) {
        pthread_mutex_lock(&lock);
        for (int i = 0; i < listener_count; i++) {
            msg.mtype = listeners[i]; 
            msg.sender_pid = getpid();
            msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0);
        }
        pthread_mutex_unlock(&lock);
        printf("> ");
    }
    
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}