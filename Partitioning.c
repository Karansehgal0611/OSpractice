#include <stdio.h>
#include <stdbool.h>

#define MAX_PARTITIONS 10
#define MAX_PROCESSES 10

void firstFit(int blockSize[], int m, int processSize[], int n);
void bestFit(int blockSize[], int m, int processSize[], int n);
void worstFit(int blockSize[], int m, int processSize[], int n);

int main() {
    int blockSize[MAX_PARTITIONS], processSize[MAX_PROCESSES];
    int m, n, i;

    printf("Enter number of blocks: ");
    scanf("%d", &m);

    printf("Enter the size of each block:\n");
    for (i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter the size of each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    printf("\nFirst Fit Allocation:\n");
    firstFit(blockSize, m, processSize, n);

    printf("\nBest Fit Allocation:\n");
    bestFit(blockSize, m, processSize, n);

    printf("\nWorst Fit Allocation:\n");
    worstFit(blockSize, m, processSize, n);

    return 0;
}

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    bool allocated[m]; // Tracks if a block is occupied

    // Initialize allocations and block status
    for (int i = 0; i < n; i++) {
        allocation[i] = -1; // No process allocated initially
    }
    for (int i = 0; i < m; i++) {
        allocated[i] = false; // All blocks are initially free
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!allocated[j] && blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                allocated[j] = true; // Mark the block as allocated
                break;
            }
        }
    }

    printf("Process\tSize\tBlock\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("%d\t%d\t%d\n", i + 1, processSize[i], allocation[i] + 1);
        } else {
            printf("%d\t%d\tNot Allocated\n", i + 1, processSize[i]);
        }
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    bool allocated[m]; // Tracks if a block is occupied

    // Initialize allocations and block status
    for (int i = 0; i < n; i++) {
        allocation[i] = -1; // No process allocated initially
    }
    for (int i = 0; i < m; i++) {
        allocated[i] = false; // All blocks are initially free
    }

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (!allocated[j] && blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            allocated[bestIdx] = true; // Mark the block as allocated
        }
    }

    printf("Process\tSize\tBlock\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("%d\t%d\t%d\n", i + 1, processSize[i], allocation[i] + 1);
        } else {
            printf("%d\t%d\tNot Allocated\n", i + 1, processSize[i]);
        }
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    bool allocated[m]; // Tracks if a block is occupied

    // Initialize allocations and block status
    for (int i = 0; i < n; i++) {
        allocation[i] = -1; // No process allocated initially
    }
    for (int i = 0; i < m; i++) {
        allocated[i] = false; // All blocks are initially free
    }

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (!allocated[j] && blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            allocated[worstIdx] = true; // Mark the block as allocated
        }
    }

    printf("Process\tSize\tBlock\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("%d\t%d\t%d\n", i + 1, processSize[i], allocation[i] + 1);
        } else {
            printf("%d\t%d\tNot Allocated\n", i + 1, processSize[i]);
        }
    }
}