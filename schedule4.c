#include <stdio.h>
#include <limits.h>

//Priority Pre
// Define the Process structure
struct Process {
    int pid;  // Process ID
    int bt;   // Burst Time
    int art;  // Arrival Time
    int pri;  // Priority
};

// Function to find the waiting time for all processes
void findWaitingTime(struct Process proc[], int n, int wt[]) {
    int rt[n]; // Remaining burst time of all processes
    int complete = 0, t = 0, min_pri = INT_MAX;
    int shortest = 0, finish_time;
    int check = 0;

    // Initialize the remaining time array with burst times
    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;

    // Process until all processes get completed
    while (complete != n) {
        // Find process with the highest priority at the current time
        for (int j = 0; j < n; j++) {
            if ((proc[j].art <= t) && (proc[j].pri < min_pri) && rt[j] > 0) {
                min_pri = proc[j].pri;
                shortest = j;
                check = 1;
            }
        }

        if (check == 0) {
            t++;
            continue;
        }

        // Reduce remaining burst time by 1
        rt[shortest]--;

        // Update the minimum priority
        min_pri = proc[shortest].pri;

        // If a process gets completely executed
        if (rt[shortest] == 0) {
            complete++;
            check = 0;

            finish_time = t + 1;

            // Calculate waiting time
            wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].art;

            if (wt[shortest] < 0)
                wt[shortest] = 0;

            // Reset the minimum priority
            min_pri = INT_MAX;
        }

        // Increment time
        t++;
    }
}

// Function to calculate turn around time
void findTurnAroundTime(struct Process proc[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}

// Function to calculate average time and print results
void findAvgTime(struct Process proc[], int n) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // Function to find waiting time of all processes
    findWaitingTime(proc, n, wt);

    // Function to find turn around time for all processes
    findTurnAroundTime(proc, n, wt, tat);

    // Display processes along with all details
    printf("Processes  Burst Time  Arrival Time  Priority  Waiting Time  Turnaround Time\n");

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("  %d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].bt, proc[i].art, proc[i].pri, wt[i], tat[i]);
    }

    printf("\nAverage waiting time = %.2f", (float)total_wt / n);
    printf("\nAverage turnaround time = %.2f\n", (float)total_tat / n);
}

// Driver code
int main() {
    int n;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter burst time, arrival time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &proc[i].bt, &proc[i].art, &proc[i].pri);
    }

    // Function to calculate average waiting and turnaround time
    findAvgTime(proc, n);

    return 0;
}
