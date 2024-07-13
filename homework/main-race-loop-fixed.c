#include <stdio.h>
#include "common_threads.h"

int balance = 0;
pthread_mutex_t lock;

// NOTE: This code doesn't check the value returned by pthread_mutex_lock
void *worker(void *arg) {
    pthread_mutex_lock(&lock);
    // critical section
    for (int i = 0; i < 100000; i++) {
        balance++;
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t t_1;

    pthread_mutex_init(&lock, NULL);
    pthread_create(&t_1, NULL, worker, NULL);
    

    pthread_mutex_lock(&lock);
    // critical section
    for (int i = 0; i < 100000; i++) {
        balance++;
    }
    pthread_mutex_unlock(&lock);

    pthread_join(t_1, NULL);
    pthread_mutex_destroy(&lock);

    printf("balance: %d\n", balance);

    return 0;
}
