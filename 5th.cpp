#include <stdio.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int executed;
};

void calculateTimes(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // Initialize executed flags
    for (int i = 0; i < n; i++) {
        processes[i].executed = 0;
    }

    int current_time = 0;
    int completed = 0;

    while (completed < n) {
        int highest_priority_index = -1;
        int highest_priority = -1;

        // Find the process with the highest priority among the waiting processes
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].executed == 0 &&
                processes[i].priority > highest_priority) {
                highest_priority = processes[i].priority;
                highest_priority_index = i;
            }
        }

        if (highest_priority_index == -1) {
            current_time++; // No process to execute, move to the next time unit
        } else {
            // Execute the selected process
            processes[highest_priority_index].burst_time--;
            current_time++;

            if (processes[highest_priority_index].burst_time == 0) {
                // Process completed
                completed++;
                processes[highest_priority_index].completion_time = current_time;
                processes[highest_priority_index].turnaround_time = processes[highest_priority_index].completion_time - processes[highest_priority_index].arrival_time;
                processes[highest_priority_index].waiting_time = processes[highest_priority_index].turnaround_time - processes[highest_priority_index].burst_time;
                processes[highest_priority_index].executed = 1;


