#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#define MSG_KEY 1234
#define BROADCASTER_MTYPE 1

struct msg_buffer {
    long mtype;
    pid_t sender_pid;
    char text[128];
};

int msgid;
pid_t my_pid;

void* receive_broadcasts(void* arg) {
    struct msg_buffer msg;
    while (1) {
        msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), my_pid, 0);
        printf("\n[Broadcast]: %s> ", msg.text);
        fflush(stdout);
    }
    return NULL;
}

int main() {
    my_pid = getpid();
    msgid = msgget((key_t)MSG_KEY, 0666);
    if (msgid == -1) {
        perror("Broadcaster is not running");
        return 1;
    }

    struct msg_buffer msg;
    msg.mtype = BROADCASTER_MTYPE;
    msg.sender_pid = my_pid;
    strcpy(msg.text, "REGISTER");
    msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0);

    pthread_t thread;
    pthread_create(&thread, NULL, receive_broadcasts, NULL);

    printf("Registered. Type to reply to broadcaster:\n> ");
    while (fgets(msg.text, sizeof(msg.text), stdin) != NULL) {
        msg.mtype = BROADCASTER_MTYPE;
        msg.sender_pid = my_pid;
        msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0);
        printf("> ");
    }
    return 0;
}