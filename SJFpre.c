#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

void calculateTimes(Process processes[], int n) {
    int time = 0, completed = 0, min_index;
    int min_remaining_time = 1e9;

    while (completed != n) {
        min_index = -1;
        min_remaining_time = 1e9;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 && processes[i].remaining_time < min_remaining_time) {
                min_remaining_time = processes[i].remaining_time;
                min_index = i;
            }
        }

        if (min_index == -1) {
            time++;
            continue;
        }

        processes[min_index].remaining_time--;
        time++;

        if (processes[min_index].remaining_time == 0) {
            processes[min_index].completion_time = time;
            processes[min_index].turnaround_time = processes[min_index].completion_time - processes[min_index].arrival_time;
            processes[min_index].waiting_time = processes[min_index].turnaround_time - processes[min_index].burst_time;
            completed++;
        }
    }
}

void printProcesses(Process processes[], int n) {
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    calculateTimes(processes, n);
    printProcesses(processes, n);

    return 0;
}