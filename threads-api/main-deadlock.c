#include <stdio.h>
#include <unistd.h>
#include "common_threads.h"

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;

void* worker(void* arg) {
    if ((long long) arg == 0) {
        printf("Thread 0: trying to acquire lock m1\n");
        Pthread_mutex_lock(&m1);
        printf("Thread 0: acquired lock m1 \n");
        // sleep 1 second
        sleep(1);
        printf("Thread 0: trying to acquire lock m2\n");
        Pthread_mutex_lock(&m2);
        printf("Thread 0: acquired lock m2\n");
    } else {
        printf("Thread 1: trying to acquire lock m2\n");
        Pthread_mutex_lock(&m2);
        printf("Thread 1: acquired lock m2\n");
        // sleep 1 second
        sleep(1);
        printf("Thread 1: trying to acquire lock m1\n");
        Pthread_mutex_lock(&m1);
        printf("Thread 1: acquired lock m1\n");
    }
    Pthread_mutex_unlock(&m1);
    Pthread_mutex_unlock(&m2);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2;
    Pthread_create(&p1, NULL, worker, (void *) (long long) 0);
    Pthread_create(&p2, NULL, worker, (void *) (long long) 1);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    return 0;
}
