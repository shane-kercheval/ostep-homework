#include "locks_utils.h"
#include <stdio.h>
#include <sys/time.h>

#define MICRO_SECONDS_IN_SECOND 1000000

long duration(struct timeval start, struct timeval end) {
    return ((end.tv_sec - start.tv_sec) * MICRO_SECONDS_IN_SECOND) + (end.tv_usec - start.tv_usec);
}

int record_stats(const char* type, int num_threads, int num_loops, long micro_seconds, int update_frequency, char *matches) {
    // as a reminder, `const` means that the value of the variable `type` will not be modified
    // it leads to better safety and optimization by the compiler
    FILE *file = fopen("lock_results.csv", "a+");
    if (file == NULL) {
        fprintf(stderr, "Failed to open results.csv\n");
        return 1;
    }
    // Check to see if the file is empty
    fseek(file, 0, SEEK_END); // moves file pointer to the end of the file
    long current_position = ftell(file); // get the current file pointer's position
    if (current_position == 0) {  // if the position is 0, the file is empty; write headers
        fprintf(file, "Type,# Threads,# Loops,Microseconds,Update Frequency,Matches\n");
    }
    fseek(file, 0, SEEK_END);  // move the the pointer to the end of the file to append data
    fprintf(file, "%s,%d,%d,%ld,%d,%s\n", type, num_threads, num_loops, micro_seconds, update_frequency, matches);
    fclose(file);
}
