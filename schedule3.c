#include <stdio.h>
#include <limits.h>

// RR pre
// Define the Process structure
struct Process {
    int pid; // Process ID
    int bt;  // Burst Time
    int art; // Arrival Time
};

// Function to find the waiting time for all processes and record the Gantt chart
void findWaitingTime(struct Process proc[], int n, int wt[], int quantum, int gantt_processes[], int gantt_times[], int *gantt_idx) {
    int rem_bt[n]; // Remaining burst times
    int t = 0; // Current time
    int completed = 0; // Number of completed processes

    // Initialize remaining burst times
    for (int i = 0; i < n; i++) {
        rem_bt[i] = proc[i].bt;
    }

    // Traverse processes in round-robin manner
    while (completed != n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0 && proc[i].art <= t) {
                done = 0;

                // Record the start time of the current process in Gantt chart
                if (*gantt_idx == 0 || gantt_processes[*gantt_idx - 1] != proc[i].pid) {
                    gantt_processes[*gantt_idx] = proc[i].pid;
                    gantt_times[*gantt_idx] = t;
                    (*gantt_idx)++;
                }

                // Process execution
                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t += rem_bt[i];
                    wt[i] = t - proc[i].bt - proc[i].art;
                    rem_bt[i] = 0;
                    completed++;
                }
            }
        }

        if (done) {
            t++;
        }
    }

    // Record the end time for the last process
    gantt_times[*gantt_idx] = t;
}

// Function to calculate turnaround time
void findTurnAroundTime(struct Process proc[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = proc[i].bt + wt[i];
    }
}

// Function to calculate average time and print results
void findAvgTime(struct Process proc[], int n, int quantum) {
    int wt[n], tat[n];
    int gantt_processes[100], gantt_times[100]; // Arrays to store Gantt chart
    int gantt_idx = 0;

    // Find waiting time and record Gantt chart
    findWaitingTime(proc, n, wt, quantum, gantt_processes, gantt_times, &gantt_idx);

    // Find turnaround time
    findTurnAroundTime(proc, n, wt, tat);

    // Display process details
    printf("PN\tAT\tBT\tWT\tTAT\n");
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].art, proc[i].bt, wt[i], tat[i]);
    }

    printf("\nAverage waiting time = %.2f", (float)total_wt / n);
    printf("\nAverage turn around time = %.2f\n", (float)total_tat / n);

    // Print Gantt chart
    printf("\nGantt Chart:\n");
    printGanttChart(gantt_processes, gantt_times, gantt_idx);
}

// Function to print the Gantt chart
void printGanttChart(int gantt_processes[], int gantt_times[], int gantt_idx) {
    int i, j;

    // Print top bar
    printf(" ");
    for (i = 0; i < gantt_idx; i++) {
        for (j = 0; j < (gantt_times[i + 1] - gantt_times[i]); j++) printf("--");
        printf(" ");
    }
    printf("\n|");

    // Print process IDs
    for (i = 0; i < gantt_idx; i++) {
        int burst = gantt_times[i + 1] - gantt_times[i];
        for (j = 0; j < burst / 2; j++) printf(" ");
        printf("P%d", gantt_processes[i]);
        for (j = 0; j < burst / 2; j++) printf(" ");
        printf("|");
    }
    printf("\n ");

    // Print bottom bar
    for (i = 0; i < gantt_idx; i++) {
        for (j = 0; j < (gantt_times[i + 1] - gantt_times[i]); j++) printf("--");
        printf(" ");
    }
    printf("\n");

    // Print timeline
    printf("0");
    for (i = 0; i < gantt_idx; i++) {
        for (j = 0; j < (gantt_times[i + 1] - gantt_times[i]); j++) printf("  ");
        if (gantt_times[i + 1] > 9) printf("\b"); // Remove 1 space if necessary
        printf("%d", gantt_times[i + 1]);
    }
    printf("\n");
}

// Driver code
int main() {
    int n, quantum;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1; // Assign Process IDs starting from 1
        printf("Enter burst time and arrival time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].bt, &proc[i].art);
    }

    // Input quantum time
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Calculate and display average times and Gantt chart
    findAvgTime(proc, n, quantum);

    return 0;
}
