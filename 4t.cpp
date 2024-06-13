#include <stdio.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int remaining_time;
    int executed;
};

void calculateTimes(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // Initialize remaining_time and executed flags
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].executed = 0;
    }

    int current_time = 0;
    int completed = 0;

    while (completed < n) {
        int min_index = -1;
        int min_burst = 99999; // Some large initial value

        // Find the process with the smallest remaining time among the waiting processes
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].executed == 0 &&
                processes[i].remaining_time < min_burst) {
                min_burst = processes[i].remaining_time;
                min_index = i;
            }
        }

        if (min_index == -1) {
            current_time++; // No process to execute, move to the next time unit
        } else {
            // Execute the selected process
            processes[min_index].remaining_time--;
            current_time++;

            if (processes[min_index].remaining_time == 0) {
                // Process completed
                completed++;
                processes[min_index].completion_time = current_time;
                processes[min_index].turnaround_time = processes[min_index].completion_time - processes[min_index].arrival_time;
                processes[min_index].waiting_time = processes[min_index].turnaround_time - processes[min_index].burst_time;
                processes[min_index].executed = 1;

                total_turnaround_time += processes[min_index].turnaround_time;
                total_waiting_time += processes[min_index].waiting_time;
            }
        }
    }

    // Print process details
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time,
               processes[i].waiting_time);
    }

    // Print average turnaround time and waiting time
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].process_id = i + 1;
    }

    // Calculate completion time, turnaround time, and waiting time for each process
    calculateTimes(processes, n);

    return 0;
}

