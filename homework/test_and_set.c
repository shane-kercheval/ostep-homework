#include <stdio.h>
#include <pthread.h>

int balance = 0;
// pthread_mutex_t lock;

int test_and_set(int *current_ptr, int new) {
    // each statement is atomic
    int current = *current_ptr;  // get current value from pointer (lock->flag)
    *current_ptr = new; // assign new value into pointer (lock->flag)
    return current; // return the current value
}

typedef struct __lock_t {
    int flag;
} lock_t;

lock_t lock_var;


void init(lock_t *lock) {
    // 0: lock is available, 1: lock is held
    lock->flag = 0;
}

void lock(lock_t *lock, int id) {
    printf("\nlock requested - %d\n", id);
    // Thread 0 requests lock (flag is set to 0)
    //   current flag is 0
    //   flag is set to 1
    //   0 is returned
    //   while loop immediately exits
    // Thread 1 requests lock (flag is still set to 1 from current lock)
    //   current flag is 1
    //   flag is set to 1
    //   1 is returned
    //   while loop continues to run; and thread 1 continues to set flag to 1
    // Thread 0 releases the lock and sets flag to 0
    // Thread 1 calls test_and_set this time
    //   however, now the current flag is set to 0
    //   flag is set to 1
    //   0 is returned
    //   Thread 1 breaks from while
    while (test_and_set(&lock->flag, 1) == 1) printf("|%d|", id);  // spin until test_and_set returns 1
    printf("\nlock acquired - %d\n", id);
}

void unlock(lock_t *lock, int id) {
    printf("\nunlocking - %d\n", id);
    lock->flag = 0;
    printf("\nunlocked - %d\n", id);
}

void *worker(void *arg) {
    lock(&lock_var, 1);
    // pthread_mutex_lock(&lock);
    // critical section
    for (int i = 0; i < 1000; i++) {
        printf("++1++");
        balance++;
    }
    // pthread_mutex_unlock(&lock);
    unlock(&lock_var, 1);
    return NULL;
}

int main() {
    pthread_t t_1;

    init(&lock_var);
    // pthread_mutex_init(&lock, NULL);
    pthread_create(&t_1, NULL, worker, NULL);
    

    lock(&lock_var, 0);
    // pthread_mutex_lock(&lock);
    // critical section
    for (int i = 0; i < 1000; i++) {
        printf("++0++");
        balance++;
    }
    // pthread_mutex_unlock(&lock);
    unlock(&lock_var, 0);

    pthread_join(t_1, NULL);
    // pthread_mutex_destroy(&lock);

    printf("balance: %d\n", balance);

    return 0;
}
