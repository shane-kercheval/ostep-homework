#include <stdio.h>
#include "common_threads.h"

int balance = 0;

void* worker(void* arg) {
    for (int i = 0; i < 100000; i++) {
        balance++; // unprotected access 
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    for (int i = 0; i < 100000; i++) {
        balance++; // unprotected access
    }
    printf("balance: %d\n", balance);
    Pthread_join(p, NULL);
    return 0;
}
