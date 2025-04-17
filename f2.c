#include <stdio.h>

typedef struct {
    int pid;
    int burstTime;
    int arrivalTime;
    int remainingTime;
    int waitingTime;
    int turnAroundTime;
} Process;

int findNextProcess(Process processes[], int n, int time) {
    int idx = -1;
    int shortestTime = 9999;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime <= time && processes[i].remainingTime > 0 && processes[i].remainingTime < shortestTime) {
            shortestTime = processes[i].remainingTime;
            idx = i;
        }
    }

    return idx;
}

void calculateTimes(Process processes[], int n) {
    int time = 0;
    int completed = 0;

    while (completed < n) {
        int idx = findNextProcess(processes, n, time);

        if (idx != -1) {
            time++;
            processes[idx].remainingTime--;

            if (processes[idx].remainingTime == 0) {
                processes[idx].turnAroundTime = time - processes[idx].arrivalTime;
                processes[idx].waitingTime = processes[idx].turnAroundTime - processes[idx].burstTime;
                completed++;
            }
        } else {
            time++;
        }
    }
}

void printResults(Process processes[], int n) {
    printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burstTime,
               processes[i].arrivalTime, processes[i].waitingTime, processes[i].turnAroundTime);
    }
}

int main() {
    int n = 4;  // Number of processes
    Process processes[] = {{1, 6, 0, 6, 0, 0}, {2, 2, 2, 2, 0, 0}, {3, 8, 4, 8, 0, 0}, {4, 3, 5, 3, 0, 0}};

    calculateTimes(processes, n);
    printResults(processes, n);

    return 0;
}
