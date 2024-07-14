/*
* This version changes the number of values/locks to be the number of threads instead of the number of CPUs.
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include "locks_utils.h"


typedef struct {
    int global_value;
    pthread_mutex_t global_lock;
    int *local_values;
    // pthread_mutex_t *local_locks;
    int update_frequency;
} counter_t;
counter_t counter;


typedef struct {
    int num_loops;
    int thread_id;
} thread_args_t;


void lock(pthread_mutex_t *mutex) {
    int status = pthread_mutex_lock(mutex);
    if (status != 0) {
        fprintf(stderr, "Error locking mutex\n");
        exit(1);
    }
}

void unlock(pthread_mutex_t *mutex) {
    int status = pthread_mutex_unlock(mutex);
    if (status != 0) {
        fprintf(stderr, "Error unlocking the mutex\n");
        exit(1);
    }
}

void init(counter_t *c, int num_threads, int update_frequency) {
    c->global_value = 0;
    if (pthread_mutex_init(&c->global_lock, NULL) != 0) {
        fprintf(stderr, "Error initializing the mutex\n");
        exit(1);
    }
    c->local_values = (int *)malloc(num_threads * sizeof(int));
    // c->local_locks = (pthread_mutex_t *)malloc(num_threads * sizeof(pthread_mutex_t));
    // for (long i = 0; i < num_threads; i++) {
    //     c->local_values[i] = 0;
    //     if (pthread_mutex_init(&c->local_locks[i], NULL) != 0) {
    //         fprintf(stderr, "Error initializing the mutex\n");
    //         exit(1);
    //     }
    // }
    c->update_frequency = update_frequency;
}

void increment(counter_t *c, int thread_id) {
    // from OSTEP:
    // lock(&c->local_locks[cpu]);
    c->local_values[thread_id]++;
    // if local value is greater than the update frequency, then update the global value
    if (c->local_values[thread_id] >= c->update_frequency) {
        // lock global lock
        lock(&c->global_lock);
        c->global_value += c->local_values[thread_id];
        unlock(&c->global_lock);
        c->local_values[thread_id] = 0;
    }
    // unlock(&c->local_locks[cpu]);
}

// void decrement(counter_t *c) {
//     lock(&c->lock);
//     c->value--;
//     unlock(&c->lock);
// }

// int get(counter_t *c) {
//     lock(&c->lock);
//     int value = c->value;
//     unlock(&c->lock);
//     return value;
// }

void run_loops(int num_loops, int thread_id) {
    printf("+starting thread %d\n", thread_id);
    for (int i = 0; i < num_loops; i++) {
        increment(&counter, thread_id);
        // decrement(&counter);
    }
    printf("-ending %d\n", thread_id);
}

void *worker(void *arg) {
    thread_args_t *args = (thread_args_t *)arg;
    run_loops(args->num_loops, args->thread_id);
}

int main(int argc, char *argv[]) {
    printf("COUNTER - V4\n");
    if (argc < 4) {
        printf("Enter the number of threads to create and the counter\n");
        return 1;
    }
    int num_threads = atoi(argv[1]);
    int num_loops = atoi(argv[2]);
    int update_frequency = atoi(argv[3]);
    printf("Number of threads: %d\n", num_threads);
    printf("Number of loops: %d\n", num_loops);
    printf("Update frequency: %d\n", update_frequency);
 
    init(&counter, num_threads, update_frequency);

    struct timeval start, end;
    printf("counter start: %d\n", counter.global_value);
    pthread_t threads[num_threads];
    thread_args_t args[num_threads];
    
    gettimeofday(&start, NULL);
    for (int i = 0; i < num_threads; i++) {
        printf("|creating thread %d\n", i);
        args[i].num_loops = num_loops;
        args[i].thread_id = i;
        if (pthread_create(&threads[i], NULL, worker, (void*)&args[i])) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }
    run_loops(num_loops, num_threads);  // e.g. 10 threads, ids are 0-9; main() id is 10
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    gettimeofday(&end, NULL);
    printf("counter end: %d\n", counter.global_value);
    long micro_seconds = duration(start, end);
    printf("Execution time: %ld microseconds\n", micro_seconds);
    int expected_count = (num_threads + 1) * num_loops;
    printf("Final Count: %d\n", counter.global_value);
    printf("Expected count: %d\n", expected_count);
    char *matches = counter.global_value == expected_count ? "true" : "false";
    printf("Count matches expected value: %s\n", matches);
    printf("----\n\n");
    int status = record_stats("V4 - Approx (thread counters)", num_threads, num_loops, micro_seconds, update_frequency, matches);

    //cleanup; destroy locks and free memory
    pthread_mutex_destroy(&counter.global_lock);
    // for (long i = 0; i < num_threads; i++) {
    //     pthread_mutex_destroy(&counter.local_locks[i]);
    // }
    // free(counter.local_locks);
    free(counter.local_values);

    if (status != 0) {
        return status;
    }
    return 0;
}
