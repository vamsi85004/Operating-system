#include <stdio.h>
#include <stdlib.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void calculateTimes(struct Process processes[], int n, int time_quantum) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int remaining_processes = n;

    int current_time = 0;

    // Initialize remaining time for each process
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }

    while (remaining_processes > 0) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time <= time_quantum) {
                    // Process completes within time quantum
                    current_time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                } else {
                    // Process needs more time
                    current_time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                }

                // Update completion time
                processes[i].completion_time = current_time;

                // Update turnaround time and waiting time
                processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

                // Update total turnaround time and waiting time
                total_turnaround_time += processes[i].turnaround_time;
                total_waiting_time += processes[i].waiting_time;

                // Decrement remaining_processes if the process has completed execution
                if (processes[i].remaining_time == 0) {
                    remaining_processes--;
                }
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
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].process_id = i + 1;
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    // Calculate completion time, turnaround time, and waiting time for each process
    calculateTimes(processes, n, time_quantum);

    return 0;
}

