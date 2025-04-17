#include <stdio.h>
#include <limits.h>

// Define the Process structure
struct Process {
    int pid; // Process ID
    int bt;  // Burst Time
    int art; // Arrival Time
};

// Function to find the waiting time for all processes
void findWaitingTime(struct Process proc[], int n, int wt[], int gantt_processes[], int gantt_times[], int *gantt_idx) {
    int rt[n]; // Remaining burst time
    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    int check = 0;

    // Initialize remaining time with the burst time
    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;

    // Process until all processes are completed
    while (complete != n) {
        // Find process with minimum remaining time at current time
        for (int j = 0; j < n; j++) {
            if ((proc[j].art <= t) && (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = 1;
            }
        }

        if (check == 0) {
            t++;
            continue;
        }

        // Record the process in Gantt chart
        if (*gantt_idx == 0 || gantt_processes[*gantt_idx - 1] != proc[shortest].pid) {
            gantt_processes[*gantt_idx] = proc[shortest].pid;
            gantt_times[*gantt_idx] = t;
            (*gantt_idx)++;
        }

        // Reduce remaining time by one
        rt[shortest]--;

        // Update minimum
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        // If a process gets completed
        if (rt[shortest] == 0) {
            complete++;
            check = 0;
            finish_time = t + 1;
            wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].art;
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }

        // Increment time
        t++;
    }

    // Record the end time for the last process
    gantt_times[*gantt_idx] = t;
}

// Function to calculate turnaround time
void findTurnAroundTime(struct Process proc[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}

// Function to calculate average time
void findAvgTime(struct Process proc[], int n) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    int gantt_processes[100], gantt_times[100]; // Arrays to store Gantt chart
    int gantt_idx = 0;

    // Find waiting times and record Gantt chart
    findWaitingTime(proc, n, wt, gantt_processes, gantt_times, &gantt_idx);

    // Find turnaround times
    findTurnAroundTime(proc, n, wt, tat);

    // Display process details
    printf(" P\t\tBT\t\tWT\t\tTAT\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf(" %d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].bt, wt[i], tat[i]);
    }

    printf("\nAverage waiting time = %.2f", (float)total_wt / (float)n);
    printf("\nAverage turn around time = %.2f\n", (float)total_tat / (float)n);

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
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1; // Assign Process IDs starting from 1
        printf("Enter burst time and arrival time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].bt, &proc[i].art);
    }

    // Calculate and display average times and Gantt chart
    findAvgTime(proc, n);
    return 0;
}
