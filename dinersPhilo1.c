#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/queue.h>

#define N 5  // Number of philosophers

// Semaphore structure
struct Semaphore {
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

// Semaphore wait operation (P)
void P(struct Semaphore *s, struct process *p) {
    pthread_mutex_lock(&s->mutex);
    while (s->value <= 0) {
        pthread_cond_wait(&s->cond, &s->mutex);
    }
    s->value--;
    pthread_mutex_unlock(&s->mutex);
}

// Semaphore signal operation (V)
void V(struct Semaphore *s) {
    pthread_mutex_lock(&s->mutex);
    s->value++;
    pthread_cond_signal(&s->cond);
    pthread_mutex_unlock(&s->mutex);
}

// Process structure (philosopher)
struct process {
    int pid;
    STAILQ_ENTRY(process) processes;
};

// Semaphore for each chopstick
struct Semaphore chopstick[N];

// Philosopher function
void *philosopher(void *param) {
    struct process *p = (struct process *)param;
    int left = p->pid;
    int right = (p->pid + 1) % N;

    while (1) {
        printf("Philosopher %d is thinking.\n", p->pid);
        sleep(1);  // Simulate thinking

        // Pick up chopsticks
        P(&chopstick[left], p);
        P(&chopstick[right], p);

        printf("Philosopher %d is eating.\n", p->pid);
        sleep(1);  // Simulate eating

        // Put down chopsticks
        V(&chopstick[right]);
        V(&chopstick[left]);

        printf("Philosopher %d finished eating and is thinking again.\n", p->pid);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t phil[N];
    struct process *philosophers[N];

    // Initialize semaphores for each chopstick
    for (int i = 0; i < N; i++) {
        chopstick[i].value = 1;
        pthread_mutex_init(&chopstick[i].mutex, NULL);
        pthread_cond_init(&chopstick[i].cond, NULL);
    }

    // Create philosopher processes (simulated)
    for (int i = 0; i < N; i++) {
        philosophers[i] = (struct process *)malloc(sizeof(struct process));
        philosophers[i]->pid = i;
        pthread_create(&phil[i], NULL, philosopher, (void *)philosophers[i]);
    }

    // Wait for the threads to complete (infinite loop in this case)
    for (int i = 0; i < N; i++) {
        pthread_join(phil[i], NULL);
    }

    return 0;
}
