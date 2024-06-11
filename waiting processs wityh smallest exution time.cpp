#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int id;
    int execution_time;
};

int main() {
    // Define an array of processes
    struct Process processes[MAX_PROCESSES];

    int num_processes;

    // Get the number of processes from the user
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    // Input process details
    printf("Enter process id and execution time for each process:\n");
    for (int i = 0; i < num_processes; ++i) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].id, &processes[i].execution_time);
    }

    // Find the process with the smallest execution time
    int smallest_execution_time = processes[0].execution_time;
    int smallest_execution_time_index = 0;
    for (int i = 1; i < num_processes; ++i) {
        if (processes[i].execution_time < smallest_execution_time) {
            smallest_execution_time = processes[i].execution_time;
            smallest_execution_time_index = i;
        }
    }

    // Execute the process with the smallest execution time
    printf("\nExecuting process %d with execution time %d\n", processes[smallest_execution_time_index].id, smallest_execution_time);

    return 0;
}

