#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

int turn;                // Variable to hold whose turn it is
bool flag[2];            // Flag array for the two processes

// Shared resource
int shared_var = 0;

// Process 0 (Function executed by thread 1)
void *process_0() {
    for (int i = 0; i < 5; i++) {
        // Entry section for process 0
        flag[0] = true;       // Indicate that process 0 wants to enter critical section
        turn = 1;             // Give turn to process 1
        while (flag[1] && turn == 1);  // Wait until process 1 finishes its critical section

        // Critical section
        printf("Process 0 in critical section. Shared variable before increment: %d\n", shared_var);
        shared_var++;
        printf("Process 0 incremented shared variable to: %d\n", shared_var);

        // Exit section for process 0
        flag[0] = false;      // Indicate that process 0 is leaving critical section

        // Remainder section
        sleep(1);             // Simulate some work done in remainder section
    }

    return NULL;
}

// Process 1 (Function executed by thread 2)
void *process_1() {
    for (int i = 0; i < 5; i++) {
        // Entry section for process 1
        flag[1] = true;       // Indicate that process 1 wants to enter critical section
        turn = 0;             // Give turn to process 0
        while (flag[0] && turn == 0);  // Wait until process 0 finishes its critical section

        // Critical section
        printf("Process 1 in critical section. Shared variable before increment: %d\n", shared_var);
        shared_var++;
        printf("Process 1 incremented shared variable to: %d\n", shared_var);

        // Exit section for process 1
        flag[1] = false;      // Indicate that process 1 is leaving critical section

        // Remainder section
        sleep(1);             // Simulate some work done in remainder section
    }

    return NULL;
}

int main() {
    // Initialize the flags and turn
    flag[0] = flag[1] = false;
    turn = 0;

    pthread_t thread1, thread2;

    // Create two threads representing process 0 and process 1
    pthread_create(&thread1, NULL, process_0, NULL);
    pthread_create(&thread2, NULL, process_1, NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final value of shared variable: %d\n", shared_var);

    return 0;
}
