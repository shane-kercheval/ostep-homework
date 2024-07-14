NUM_LOOPS=1000000

compile:
	gcc -o counter_no_lock locks_counter_no_lock.c
	gcc -o counter_v1 locks_counter_v1.c
	gcc -o counter_v2 locks_counter_v2_approximate_counter.c

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
	done'

run_approx: compile
	@bash -c 'for i in {1..20}; do \
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
	done'
