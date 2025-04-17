#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int completion_time;
} Process;


void sort_by_arrival_time(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}


void priority_scheduling(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int min_priority;
    int shortest;

    while (completed != n) {
        min_priority = 9999;
        shortest = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && processes[i].priority < min_priority) {
                min_priority = processes[i].priority;
                shortest = i;
            }
        }

        if (shortest == -1) {
            current_time++;
            continue;
        }

        processes[shortest].remaining_time--;
        current_time++;

        if (processes[shortest].remaining_time == 0) {
            processes[shortest].completion_time = current_time;
            completed++;
        }
    }
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time, burst time and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
    }

    sort_by_arrival_time(processes, n);
    priority_scheduling(processes, n);

    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].priority, processes[i].completion_time);
    }

    return 0;
}





