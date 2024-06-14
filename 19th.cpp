#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

sem_t rw_mutex;  // Semaphore for writer access
sem_t mutex;     // Semaphore for reader count access
int read_count = 0; // Number of readers currently reading

void* reader(void* arg) {
    int id = ((int)arg);

    while(1) {
        // Reader tries to enter the critical section
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&rw_mutex); // First reader locks the writer access
        }
        sem_post(&mutex);

        // Reading section
        printf("Reader %d is reading\n", id);
        sleep(rand() % 3 + 1); // Simulate reading time

        // Reader leaves the critical section
        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&rw_mutex); // Last reader unlocks the writer access
        }
        sem_post(&mutex);

        sleep(rand() % 3 + 1); // Simulate time between readings
    }

    return NULL;
}

void* writer(void* arg) {
    int id = ((int)arg);

    while(1) {
        // Writer tries to enter the critical section
        sem_wait(&rw_mutex);

        // Writing section
        printf("Writer %d is writing\n", id);
        sleep(rand() % 3 + 1); // Simulate writing time

        // Writer leaves the critical section
        sem_post(&rw_mutex);

        sleep(rand() % 3 + 1); // Simulate time between writings
    }

    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize the semaphores
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        if (pthread_create(&readers[i], NULL, reader, &reader_ids[i]) != 0) {
            perror("Failed to create reader thread");
        }
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        if (pthread_create(&writers[i], NULL, writer, &writer_ids[i]) != 0) {
            perror("Failed to create writer thread");
        }
    }

    // Join threads (this program will run indefinitely)
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy the semaphores
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}
