#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/queue.h>

// Define a process structure (simulating a Process Control Block - PCB)
struct process {
    int pid; // Process ID
    STAILQ_ENTRY(process) processes; // Singly-linked tail queue entry
};

// Define the semaphore structure
struct Semaphore {
    int value; // Semaphore value
    STAILQ_HEAD(queue_head, process) q; // Queue of processes waiting on the semaphore
};

// P (wait) operation
void P(struct Semaphore *s, struct process *p) {
    s->value--;
    if (s->value < 0) {
        printf("Process %d is blocked.\n", p->pid);
        STAILQ_INSERT_TAIL(&s->q, p, processes); // Add process to the semaphore's waiting queue
        sleep(1); // Simulate blocking (sleep is just for demonstration)
    }
}

// V (signal) operation
void V(struct Semaphore *s) {
    s->value++;
    if (s->value <= 0) {
        // Wake up the first process from the queue
        struct process *p = STAILQ_FIRST(&s->q);
        if (p != NULL) {
            STAILQ_REMOVE_HEAD(&s->q, processes);
            printf("Waking up process %d.\n", p->pid);
            free(p); // Simulate process waking up and removing it from the queue
        }
    }
}

int main() {
    // Initialize semaphore
    struct Semaphore s;
    s.value = 1; // Initially available
    STAILQ_INIT(&s.q); // Initialize the process queue

    // Simulate processes
    struct process *p1 = (struct process *)malloc(sizeof(struct process));
    p1->pid = 1;
    struct process *p2 = (struct process *)malloc(sizeof(struct process));
    p2->pid = 2;

    // Perform P (wait) and V (signal) operations
    P(&s, p1); // Process 1 performs P
    P(&s, p2); // Process 2 performs P and gets blocked

    V(&s); // Process 1 performs V, waking up process 2
    V(&s); // Process 2 performs V

    printf("All processes completed!\n");

    // Clean up
    free(p1);
    return 0;
}

