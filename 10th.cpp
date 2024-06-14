#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

// Define message structure
struct message {
    long mtype;
    char mtext[100];
};

int main() {
    key_t key;
    int msgid;
    struct message msg;

    // Generate a unique key for the message queue
    key = ftok("msgq_example", 65);

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process (receiver)
        printf("Child process (Receiver)\n");

        // Receive message from the queue
        if (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        printf("Received message: %s\n", msg.mtext);

    } else { // Parent process (sender)
        printf("Parent process (Sender)\n");

        // Construct the message
        msg.mtype = 1; // Message type
        strcpy(msg.mtext, "Hello from sender!");

        // Send the message
        if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }

        printf("Message sent\n");

        // Wait for the child process to finish
        wait(NULL);
    }

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}

