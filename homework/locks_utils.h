#include <sys/time.h>

#ifndef STATS_RECORDER_H
#define STATS_RECORDER_H

long duration(struct timeval start, struct timeval end);
int record_stats(const char* type, int num_threads, int num_loops, long micro_seconds, int update_frequency, char *matches);

#endif // STATS_RECORDER_H
