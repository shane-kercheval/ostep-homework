NUM_LOOPS=10000000

compile:
	gcc -o counter_no_lock locks_counter_no_lock.c locks_utils.c
	gcc -o counter_v1 locks_counter_v1.c locks_utils.c
	gcc -o counter_v2 locks_counter_v2_approximate_counter.c locks_utils.c
	gcc -o counter_v3 locks_counter_v3_approximate_counter.c locks_utils.c
	gcc -o counter_v4 locks_counter_v4_approximate_counter.c locks_utils.c

valgrind: compile
	valgrind --leak-check=full ./counter_v2


# no errors because single thread
helgrind_no_lock_0: compile
	valgrind --tool=helgrind ./counter_no_lock 0 $(NUM_LOOPS)

# errors because multiple threads
helgrind_no_lock_1: compile
	valgrind --tool=helgrind ./counter_no_lock 1 $(NUM_LOOPS)

# no errors because multiple threads but uses locks; lower num loops because valgrind is slow
helgrind_counter_v1_20: compile
	valgrind --tool=helgrind ./counter_v1 20 100000 1000

# no errors because multiple threads but uses global/local locks; lower num loops because valgrind is slow
helgrind_counter_v2_20: compile
	valgrind --tool=helgrind ./counter_v2 20 100000 1000

# has errors because doesn't use local locks; so if num threads greater than num cpus then there will be contention
helgrind_counter_v3_20: compile
	valgrind --tool=helgrind ./counter_v3 20 100000 1000

# no errors because doesn't use local locks; so if num threads greater than num cpus then there will be contention
helgrind_counter_v3_10: compile
	valgrind --tool=helgrind ./counter_v3 10 100000 1000

# no errors because doesn't use local locks; but each thread has its own counter and global counter is still locked
helgrind_counter_v4_20: compile
	valgrind --tool=helgrind ./counter_v4 20 100000 1000


run: compile
	@bash -c 'for i in {1..20}; do \
		./counter_no_lock 0 $(NUM_LOOPS); \
		./counter_no_lock 1 $(NUM_LOOPS); \
		./counter_no_lock 2 $(NUM_LOOPS); \
		./counter_no_lock 4 $(NUM_LOOPS); \
		./counter_no_lock 10 $(NUM_LOOPS); \
		./counter_no_lock 20 $(NUM_LOOPS); \
		./counter_v1 0 $(NUM_LOOPS); \
		./counter_v1 1 $(NUM_LOOPS); \
		./counter_v1 2 $(NUM_LOOPS); \
		./counter_v1 4 $(NUM_LOOPS); \
		./counter_v1 10 $(NUM_LOOPS); \
		./counter_v1 20 $(NUM_LOOPS); \
		./counter_v2 0 $(NUM_LOOPS) 100; \
		./counter_v2 1 $(NUM_LOOPS) 100; \
		./counter_v2 2 $(NUM_LOOPS) 100; \
		./counter_v2 4 $(NUM_LOOPS) 100; \
		./counter_v2 10 $(NUM_LOOPS) 100; \
		./counter_v2 20 $(NUM_LOOPS) 100; \
		./counter_v2 0 $(NUM_LOOPS) 10000; \
		./counter_v2 1 $(NUM_LOOPS) 10000; \
		./counter_v2 2 $(NUM_LOOPS) 10000; \
		./counter_v2 4 $(NUM_LOOPS) 10000; \
		./counter_v2 10 $(NUM_LOOPS) 10000; \
		./counter_v2 20 $(NUM_LOOPS) 10000; \
		./counter_v2 0 $(NUM_LOOPS) 1000000; \
		./counter_v2 1 $(NUM_LOOPS) 1000000; \
		./counter_v2 2 $(NUM_LOOPS) 1000000; \
		./counter_v2 4 $(NUM_LOOPS) 1000000; \
		./counter_v2 10 $(NUM_LOOPS) 1000000; \
		./counter_v2 20 $(NUM_LOOPS) 1000000; \
		./counter_v3 0 $(NUM_LOOPS) 100; \
		./counter_v3 1 $(NUM_LOOPS) 100; \
		./counter_v3 2 $(NUM_LOOPS) 100; \
		./counter_v3 4 $(NUM_LOOPS) 100; \
		./counter_v3 10 $(NUM_LOOPS) 100; \
		./counter_v3 20 $(NUM_LOOPS) 100; \
		./counter_v3 0 $(NUM_LOOPS) 10000; \
		./counter_v3 1 $(NUM_LOOPS) 10000; \
		./counter_v3 2 $(NUM_LOOPS) 10000; \
		./counter_v3 4 $(NUM_LOOPS) 10000; \
		./counter_v3 10 $(NUM_LOOPS) 10000; \
		./counter_v3 20 $(NUM_LOOPS) 10000; \
		./counter_v3 0 $(NUM_LOOPS) 1000000; \
		./counter_v3 1 $(NUM_LOOPS) 1000000; \
		./counter_v3 2 $(NUM_LOOPS) 1000000; \
		./counter_v3 4 $(NUM_LOOPS) 1000000; \
		./counter_v3 10 $(NUM_LOOPS) 1000000; \
		./counter_v3 20 $(NUM_LOOPS) 1000000; \
		./counter_v4 0 $(NUM_LOOPS) 100; \
		./counter_v4 1 $(NUM_LOOPS) 100; \
		./counter_v4 2 $(NUM_LOOPS) 100; \
		./counter_v4 4 $(NUM_LOOPS) 100; \
		./counter_v4 10 $(NUM_LOOPS) 100; \
		./counter_v4 20 $(NUM_LOOPS) 100; \
		./counter_v4 0 $(NUM_LOOPS) 10000; \
		./counter_v4 1 $(NUM_LOOPS) 10000; \
		./counter_v4 2 $(NUM_LOOPS) 10000; \
		./counter_v4 4 $(NUM_LOOPS) 10000; \
		./counter_v4 10 $(NUM_LOOPS) 10000; \
		./counter_v4 20 $(NUM_LOOPS) 10000; \
		./counter_v4 0 $(NUM_LOOPS) 1000000; \
		./counter_v4 1 $(NUM_LOOPS) 1000000; \
		./counter_v4 2 $(NUM_LOOPS) 1000000; \
		./counter_v4 4 $(NUM_LOOPS) 1000000; \
		./counter_v4 10 $(NUM_LOOPS) 1000000; \
		./counter_v4 20 $(NUM_LOOPS) 1000000; \
	done'

run_v4: compile
	@bash -c 'for i in {1..20}; do \
		./counter_v4 0 $(NUM_LOOPS) 100; \
		./counter_v4 1 $(NUM_LOOPS) 100; \
		./counter_v4 2 $(NUM_LOOPS) 100; \
		./counter_v4 4 $(NUM_LOOPS) 100; \
		./counter_v4 10 $(NUM_LOOPS) 100; \
		./counter_v4 20 $(NUM_LOOPS) 100; \
		./counter_v4 0 $(NUM_LOOPS) 10000; \
		./counter_v4 1 $(NUM_LOOPS) 10000; \
		./counter_v4 2 $(NUM_LOOPS) 10000; \
		./counter_v4 4 $(NUM_LOOPS) 10000; \
		./counter_v4 10 $(NUM_LOOPS) 10000; \
		./counter_v4 20 $(NUM_LOOPS) 10000; \
		./counter_v4 0 $(NUM_LOOPS) 1000000; \
		./counter_v4 1 $(NUM_LOOPS) 1000000; \
		./counter_v4 2 $(NUM_LOOPS) 1000000; \
		./counter_v4 4 $(NUM_LOOPS) 1000000; \
		./counter_v4 10 $(NUM_LOOPS) 1000000; \
		./counter_v4 20 $(NUM_LOOPS) 1000000; \
		done'
