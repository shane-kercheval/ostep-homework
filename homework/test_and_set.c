#include <stdio.h>
#include <pthread.h>

int balance = 0;
// pthread_mutex_t lock;

int test_and_set(int *current_ptr, int new) {
    // each statement is atomic
    int current = *current_ptr;  // get current value from pointer (lock->flag)
    // What if a context switch happens here after `old` is assigned but before `old_ptr` is set. Seems like there would be a race condition leading to two threads acquiring the lock.
    // For example:
    // - Thread 0 executes and `old` is set to 0; then context switch happens before `*old_ptr = new`
    // - Now Thead 1 executes and `old` is also set to 0, `current_ptr` is set to 1; and 0 is returned; the lock is acquired by Thread 1.
    // - Sometime later (before Thread 1 releases the lock) Thread 0 resumes. `old` is still 0 from before the context swich, and that value is returned. Now the lock is also aquired by Thread 0
    // ——
    // I misunderstood. The authors are just showing what the operation would look like in C. But they specifically mention that the test and set operations are atomic and this an instruction supported at the hardware level. So I’m correct, that if those two operations (setting old and setting old_prt) weren’t atomic there would be a race condition. But that wasn’t what the authors were trying to suggest.
    // So this would be more likey to fail with many threads, and could still fail with 1, but is less likely.
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
