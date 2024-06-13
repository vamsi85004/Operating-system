#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid, parent_pid;

    // Fork a new process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process created.\n");

        // Get child process ID
        pid = getpid();
        printf("Child process ID: %d\n", pid);

        // Get parent process ID
        parent_pid = getppid();
        printf("Parent process ID: %d\n", parent_pid);
    } else {
        // Parent process
        printf("Parent process created with child PID: %d\n", pid);

        // Get parent process ID
        parent_pid = getpid();
        printf("Parent process ID: %d\n", parent_pid);

        // Get child process ID
        pid = getppid();
        printf("Child process ID: %d\n", pid);
    }

    return 0;
}

