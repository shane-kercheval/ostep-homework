#include <stdio.h>
#include <unistd.h>
// #include <stdlib.h>
// #include <stdbool.h>
#include <assert.h>
#include "utils.h"

int main(int argc, char *argv[]) {
    // printf("Num args: %d\n", argc);
    // for (int i = 0; i < argc; i++) {
    //     printf("Arg %d: %s\n", i, argv[i]);
    // }
    printf("hello\n");
    struct timeval start, end;
    gettimeofday(&start, NULL);
    sleep(1);
    gettimeofday(&end, NULL);
    long elapsed = duration(start, end);
    printf("Elapsed time: %ld microseconds\n", elapsed);
    printf("goodbye\n");

    return 0;
}
