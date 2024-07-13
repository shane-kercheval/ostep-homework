NUM_LOOPS=1000000

compile:
	gcc -o counter_no_lock locks_counter_no_lock.c
	gcc -o counter_v1 locks_counter_v1.c

run: compile
	@bash -c 'for i in {1..10}; do \
		./counter_no_lock 0 $(NUM_LOOPS); \
		./counter_v1 0 $(NUM_LOOPS); \
		./counter_no_lock 1 $(NUM_LOOPS); \
		./counter_v1 1 $(NUM_LOOPS); \
		./counter_no_lock 2 $(NUM_LOOPS); \
		./counter_v1 2 $(NUM_LOOPS); \
		./counter_no_lock 4 $(NUM_LOOPS); \
		./counter_v1 4 $(NUM_LOOPS); \
	done'
