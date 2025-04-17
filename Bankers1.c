#include <stdio.h>
#include <stdbool.h>

void calculateNeed(int need[][100], int max[][100], int alloc[][100], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

bool isSafe(int processes[], int avail[], int max[][100], int alloc[][100], int n, int m) {
    int need[n][100];
    calculateNeed(need, max, alloc, n, m);

    bool finish[n];
    for (int i = 0; i < n; i++) finish[i] = false;

    int safeSeq[n];
    int work[m];

    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }

                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        work[k] += alloc[p][k];
                    }

                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }


        if (!found) {
            printf("The system is not in a safe state\n");
            return false;
        }
    }

    printf("The system is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", safeSeq[i]);
    }
    printf("\n");
    return true;
}

int main() {
    int n, m;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int processes[n];
    for (int i = 0; i < n; i++) {
        processes[i] = i;
    }

    int avail[m];
    printf("Enter the available resources (space-separated): ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    int max[n][100], alloc[n][100];

    printf("Enter the maximum resource matrix (each row as space-separated values):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter the allocation matrix (each row as space-separated values):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }
    isSafe(processes, avail, max, alloc, n, m);

    return 0;}