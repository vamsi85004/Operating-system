#include <stdio.h>
#include <stdlib.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int findHighestPriorityProcess(struct Process processes[], int n, int current_time) {
    int highest_priority_index = -1;
    int highest_priority = 99999; // Some large initial value

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 &&
            processes[i].priority < highest_priority) {
            highest_priority = processes[i].priority;
            highest_priority_index = i;
        }
    }

    return highest_priority_index;
}

void calculateTimes(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    int current_time = 0;
    int completed = 0;

    while (completed < n) {
        int highest_priority_index = findHighestPriorityProcess(processes, n, current_time);

        if (highest_priority_index == -1) {
            current_time++; // No process to execute, move to the next time unit
        } else {
            processes[highest_priority_index].remaining_time--;
            current_time++;

            if (processes[highest_priority_index].remaining_time == 0) {
                completed++;

                processes[highest_priority_index].completion_time = current_time;
                processes[highest_priority_index].turnaround_time = processes[highest_priority_index].completion_time - processes[highest_priority_index].arrival_time;
                processes[highest_priority_index].waiting_time = processes[highest_priority_index].turnaround_time - processes[highest_priority_index].burst_time;

                total_turnaround_time += processes[highest_priority_index].turnaround_time;
                total_waiting_time += processes[highest_priority_index].waiting_time;
            }
        }
    }

    // Print process details
    printf("Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].priority, processes[i].completion_time,
               processes[i].turnaround_time, processes[i].waiting_time);
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
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].process_id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Calculate completion time, turnaround time, and waiting time for each process
    calculateTimes(processes, n);

    return 0;
}

