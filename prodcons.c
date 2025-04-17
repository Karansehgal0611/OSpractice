#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int count = 0;

sem_t empty, full, mutex;

void *producer(void *arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&empty); // Decrease empty slots
        sem_wait(&mutex); // Enter critical section
        buffer[count++] = i;
        printf("Produced: %d\n", i);
        sem_post(&mutex); // Exit critical section
        sem_post(&full); // Increase full slots
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&full); // Decrease full slots
        sem_wait(&mutex); // Enter critical section
        int item = buffer[--count];
        printf("Consumed: %d\n", item);
        sem_post(&mutex); // Exit critical section
        sem_post(&empty); // Increase empty slots
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;
    sem_init(&empty, 0, BUFFER_SIZE); // Initialize empty slots
    sem_init(&full, 0, 0);            // Initialize full slots
    sem_init(&mutex, 0, 1);           // Binary semaphore for critical section

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    return 0;
}

