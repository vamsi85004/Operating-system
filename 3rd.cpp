#include <stdio.h>

void calculateTimes(int burst_times[], int n) {
    int waiting_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time;
        int turnaround_time = waiting_time + burst_times[i];
        total_turnaround_time += turnaround_time;

        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, burst_times[i], waiting_time, turnaround_time);

        waiting_time += burst_times[i];
    }

    // Calculate average times
    double avg_waiting_time = (double)total_waiting_time / n;
    double avg_turnaround_time = (double)total_turnaround_time / n;
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_times[n];

    // Input burst times for each process
    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Burst time for Process %d: ", i + 1);
        scanf("%d", &burst_times[i]);
    }

    // Calculate waiting time and turnaround time
    calculateTimes(burst_times, n);

    return 0;
}
