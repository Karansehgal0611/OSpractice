#include <stdio.h>
#include <limits.h>

// Structure to represent a process
struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time of the process
    int burst;      // Burst time of the process
    int priority;   // Priority of the process (lower value indicates higher priority)
    int completion; // Completion time of the process
    int turnaround; // Turnaround time of the process
    int waiting;    // Waiting time of the process
};

// Function to sort processes by arrival time and priority
void sortByArrivalAndPriority(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrival > proc[j + 1].arrival ||
               (proc[j].arrival == proc[j + 1].arrival && proc[j].priority > proc[j + 1].priority)) {
                // Swap processes
                temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

// Function to implement non-preemptive priority scheduling
void priorityScheduling(struct Process proc[], int n, int gantt_processes[], int gantt_times[], int *gantt_idx) {
    int currentTime = 0, completed = 0;
    int isCompleted[n];

    // Initialize isCompleted array
    for (int i = 0; i < n; i++)
        isCompleted[i] = 0;

    // Main loop iterates until all processes are completed
    while (completed != n) {
        int highestPriority = INT_MAX;
        int selectedIndex = -1;

        // Find the process with the highest priority that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival <= currentTime && !isCompleted[i] && proc[i].priority < highestPriority) {
                highestPriority = proc[i].priority;
                selectedIndex = i;
            }
        }

        // If a process is found, execute it
        if (selectedIndex != -1) {
            proc[selectedIndex].completion = currentTime + proc[selectedIndex].burst;
            proc[selectedIndex].turnaround = proc[selectedIndex].completion - proc[selectedIndex].arrival;
            proc[selectedIndex].waiting = proc[selectedIndex].turnaround - proc[selectedIndex].burst;

            // Update the Gantt chart arrays
            gantt_processes[*gantt_idx] = proc[selectedIndex].pid;
            gantt_times[*gantt_idx + 1] = proc[selectedIndex].completion;
            (*gantt_idx)++;

            // Mark the process as completed
            isCompleted[selectedIndex] = 1;
            completed++;

            // Advance the current time
            currentTime += proc[selectedIndex].burst;
        } else {
            // If no process is found, increment the current time
            currentTime++;
        }
    }

    // Display the results
    printf("\nProcesses  Arrival Time  Burst Time  Priority  Completion Time  Turnaround Time  Waiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("  %d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            proc[i].pid, proc[i].arrival, proc[i].burst, proc[i].priority,
            proc[i].completion, proc[i].turnaround, proc[i].waiting);
    }

    // Calculate and display average turnaround time and average waiting time
    double totalTurnaround = 0, totalWaiting = 0;
    for (int i = 0; i < n; i++) {
        totalTurnaround += proc[i].turnaround;
        totalWaiting += proc[i].waiting;
    }
    printf("\nAverage Turnaround Time: %.2f", totalTurnaround / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWaiting / n);
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

    // Print process ID in the middle
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
        if (gantt_times[i + 1] > 9) printf("\b"); // remove 1 space if necessary
        printf("%d", gantt_times[i + 1]);
    }
    printf("\n");
}

// Main function
int main() {
    int n;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    int gantt_processes[n]; // To store process execution sequence
    int gantt_times[n + 1]; // To store times of process switching
    int gantt_idx = 0;

    // Input process details
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &proc[i].arrival, &proc[i].burst, &proc[i].priority);
    }

    // Initialize the first Gantt time to 0
    gantt_times[0] = 0;

    // Sort processes by arrival time and priority
    sortByArrivalAndPriority(proc, n);

    // Perform priority scheduling
    priorityScheduling(proc, n, gantt_processes, gantt_times, &gantt_idx);

    // Print Gantt chart
    printGanttChart(gantt_processes, gantt_times, gantt_idx);

    return 0;
}
