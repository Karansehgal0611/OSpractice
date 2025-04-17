#include <stdio.h>
#include <stdbool.h>
//SJF NON PREEMPTIVE

struct Process {
    int pid;      // Process ID
    int at;       // Arrival Time
    int bt;       // Burst Time
    int ct;       // Completion Time
    int tat;      // Turn Around Time
    int wt;       // Waiting Time
    bool is_completed; // Completion status
};

void sortByArrival(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void calculateTimes(struct Process p[], int n) {
    int current_time = 0;
    int completed = 0;

    while (completed != n) {
        int shortest = -1;
        int min_bt = 10000;  // Arbitrary large number

        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && !p[i].is_completed && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                shortest = i;
            }
        }

        if (shortest == -1) {
            current_time++;
        } else {
            current_time += p[shortest].bt;
            p[shortest].ct = current_time;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
            p[shortest].is_completed = true;
            completed++;
        }
    }
}

void printTable(struct Process p[], int n) {
    float total_tat = 0, total_wt = 0;
    printf("------------------------------------------------------------\n");
    printf("| Process | Arrival Time | Burst Time | Completion Time | TAT | Waiting Time |\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        total_tat += p[i].tat;
        total_wt += p[i].wt;
        printf("| P%d      |     %2d       |    %2d      |       %2d        |  %2d  |     %2d       |\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("------------------------------------------------------------\n");

    printf("Average Turn Around Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
}

void printGanttChart(struct Process p[], int n) {
    printf("\nGantt Chart:\n");

    // Print top bar
    for (int i = 0; i < n; i++) {
        printf("----------");
    }
    printf("\n");

    // Print process IDs
    for (int i = 0; i < n; i++) {
        printf("|   P%d    ", p[i].pid);
    }
    printf("|\n");

    // Print bottom bar
    for (int i = 0; i < n; i++) {
        printf("----------");
    }
    printf("\n");

    // Print completion times
    int current_time = p[0].at;
    printf("%d", current_time);
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].at) {
            current_time = p[i].at;
        }
        current_time += p[i].bt;
        printf("         %2d", current_time);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input Arrival Time and Burst Time for each process
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time for Process P%d: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time for Process P%d: ", p[i].pid);
        scanf("%d", &p[i].bt);
        p[i].is_completed = false;
    }

    // Sort processes by Arrival Time
    sortByArrival(p, n);

    // Calculate times using SJF
    calculateTimes(p, n);

    // Print table with calculated times
    printTable(p, n);

    // Print Gantt chart
    printGanttChart(p, n);

    return 0;
}
