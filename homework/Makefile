NUM_THREADS=0
NUM_LOOPS=1000000

run:
	gcc -o counter_no_lock locks_counter_no_lock.c
	gcc -o counter_v1 locks_counter_v1.c
	./counter_no_lock 0 $(NUM_LOOPS)
	./counter_v1 0 $(NUM_LOOPS)
	./counter_no_lock 1 $(NUM_LOOPS)
	./counter_v1 1 $(NUM_LOOPS)
	./counter_no_lock 2 $(NUM_LOOPS)
	./counter_v1 2 $(NUM_LOOPS)
	./counter_no_lock 4 $(NUM_LOOPS)
	./counter_v1 4 $(NUM_LOOPS)