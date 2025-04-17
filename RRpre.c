#include <stdio.h>

struct Process {
    int pid; // Process ID
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void calculateTimes(struct Process proc[], int n, int time_quantum) {
    int time = 0, completed = 0;
    int i, flag;
    
    // Initialize remaining time for each process
    for (i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
    }

    while (completed != n) {
        flag = 0; // Indicates if a process was processed in this cycle
        
        for (i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0 && proc[i].arrival_time <= time) {
                flag = 1;

                if (proc[i].remaining_time <= time_quantum) {
                    time += proc[i].remaining_time;
                    proc[i].remaining_time = 0;
                    proc[i].completion_time = time;
                    completed++;

                    // Calculate TAT and WT
                    proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
                    proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
                } else {
                    time += time_quantum;
                    proc[i].remaining_time -= time_quantum;
                }
            }
        }

        // If no process could run in this cycle, increment time
        if (!flag) {
            time++;
        }
    }
}

void printResults(struct Process proc[], int n) {
    int total_tat = 0, total_wt = 0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        total_tat += proc[i].turnaround_time;
        total_wt += proc[i].waiting_time;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].arrival_time,
               proc[i].burst_time, proc[i].completion_time,
               proc[i].turnaround_time, proc[i].waiting_time);
    }

    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
}

int main() {
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
    }

    calculateTimes(proc, n, time_quantum);
    printResults(proc, n);

    return 0;
}
