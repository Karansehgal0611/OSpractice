#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/queue.h>

// Define a structure for processes (for demonstration)
struct process {
    int pid; // process ID
    STAILQ_ENTRY(process) processes; // Queue entry
};

// Semaphore structure
struct semaphore {
    STAILQ_HEAD(queue_head, process) q; // Queue of processes
    int value;
};

// P (Wait) operation
void P(struct semaphore *s, struct process *p) {
    if (s->value == 1) {
        s->value = 0; // Enter critical section
    } else {
        // Add process to the waiting queue
        STAILQ_INSERT_TAIL(&s->q, p, processes);
        printf("Process %d is going to sleep.\n", p->pid);
        sleep(1); // Simulate sleep
    }
}

// V (Signal) operation
void V(struct semaphore *s) {
    if (STAILQ_EMPTY(&s->q)) {
        s->value = 1; // Exit critical section
    } else {
        // Get the first process from the waiting queue
        struct process *p = STAILQ_FIRST(&s->q);
        STAILQ_REMOVE_HEAD(&s->q, processes);
        printf("Waking up process %d.\n", p->pid);
        free(p); // Simulate waking up the process
    }
}

int main() {
    // Initialize the semaphore
    struct semaphore s;
    s.value = 1; // Semaphore is initially available
    STAILQ_INIT(&s.q); // Initialize the queue

    // Create a process
    struct process *p1 = (struct process *)malloc(sizeof(struct process));
    p1->pid = 1;

    struct process *p2 = (struct process *)malloc(sizeof(struct process));
    p2->pid = 2;

    // Perform the P (wait) operation
    P(&s, p1); // Process 1 enters critical section
    P(&s, p2); // Process 2 goes to waiting

    // Perform the V (signal) operation
    V(&s); // Process 1 exits, wakes up process 2

    V(&s); // Process 2 exits

    printf("All processes completed!\n");

    return 0;
}

