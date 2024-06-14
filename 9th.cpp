#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024  // Size of shared memory segment

int main() {
    pid_t pid;
    int shmid;
    char *shm_ptr;

    // Create shared memory segment
    if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory segment
    if ((shm_ptr = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Fork a child process
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    // Parent process
    if (pid > 0) {
        printf("Parent process writing to shared memory...\n");
        sprintf(shm_ptr, "Hello from parent!");

        // Wait for child process to complete
        wait(NULL);

        printf("Parent read from shared memory: %s\n", shm_ptr);

        // Detach shared memory segment
        if (shmdt(shm_ptr) == -1) {
            perror("shmdt");
            exit(1);
        }

        // Remove shared memory segment
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }
    } 
    // Child process
    else {
        printf("Child process reading from shared memory...\n");
        printf("Child read from shared memory: %s\n", shm_ptr);
        sprintf(shm_ptr, "Hello from child!");

        // Detach shared memory segment
        if (shmdt(shm_ptr) == -1) {
            perror("shmdt");
            exit(1);
        }

        exit(0);
    }

    return 0;
}

