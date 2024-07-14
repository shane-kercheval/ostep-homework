#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include "locks_utils.h"


typedef struct {
    int value;
} counter_t;
counter_t counter = {0};

typedef struct {
    int num_loops;
    int id;
} thread_args_t;

void init(counter_t *c) {
    c->value = 0;
}

void increment(counter_t *c) {
    c->value++;
}

void decrement(counter_t *c) {
    c->value--;
}

int get(counter_t *c) {
    return c->value;
}

void run_loops(int num_loops, int id) {
    printf("+starting thread %d\n", id);
    for (int i = 0; i < num_loops; i++) {
        increment(&counter);
        // decrement(&counter);
    }
    printf("-ending %d\n", id);
}

void *worker(void *arg) {
    thread_args_t *args = (thread_args_t *)arg;
    int num_loops = args->num_loops;
    int id = args->id;
    run_loops(num_loops, id);
}

int main(int argc, char *argv[]) {
    printf("COUNTER - NO LOCK\n");
    if (argc < 3) {
        printf("Enter the number of threads to create and the counter\n");
        return 1;
    }
    int num_threads = atoi(argv[1]);
    int num_loops = atoi(argv[2]);
    printf("Number of threads: %d\n", num_threads);
    printf("Number of loops: %d\n", num_loops);
    long num_cpu_cores = sysconf(_SC_NPROCESSORS_ONLN);  // # of "logical processors" that are "currently online"
    printf("Number of CPU cores available: %ld\n", num_cpu_cores);
    
    
    struct timeval start, end;
    printf("counter start: %d\n", counter.value);
    gettimeofday(&start, NULL);

    pthread_t threads[num_threads];
    thread_args_t args[num_threads];
    for (int i = 0; i < num_threads; i++) {
        printf("|creating thread %d\n", i);
        args[i].num_loops = num_loops;
        args[i].id = i;
        if (pthread_create(&threads[i], NULL, worker, (void*)&args[i])) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }
    run_loops(num_loops, -1);  // -1 represents main
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    gettimeofday(&end, NULL);
    printf("counter end: %d\n", counter.value);
    long micro_seconds = duration(start, end);
    printf("Execution time: %ld microseconds\n", micro_seconds);
    int expected_count = (num_threads + 1) * num_loops;
    printf("Final Count: %d\n", counter.value);
    printf("Expected count: %d\n", expected_count);
    char *matches = counter.value == expected_count ? "true" : "false";
    printf("Count matches expected value: %s\n", matches);
    printf("----\n\n");
    int status = record_stats("V0 - No Locking", num_threads, num_loops, micro_seconds, -1, matches);
    if (status != 0) {
        return status;
    }
    return 0;
}
