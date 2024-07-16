#ifndef UTILS_H
#define UTILS_H

#include <sys/time.h>

#define MICRO_SECONDS_IN_SECOND 1000000

/*
 * Calculate the duration between two timevals in microseconds.
 * For example:
 *   #include <sys/time.h>
 *   #include <stdio.h>
 *   #include "utils.h"
 *   struct timeval start, end;
 *   gettimeofday(&start, NULL);
 *   // do something
 *   gettimeofday(&end, NULL);
 *   long elapsed = duration(start, end);
 *   printf("Elapsed time: %ld microseconds\n", elapsed);
*/
long duration(struct timeval start, struct timeval end);


#endif // UTILS_H
