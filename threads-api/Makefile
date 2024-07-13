
FLAGS = -Wall -pthread -g

all: main-race main-deadlock main-deadlock-global main-signal main-signal-cv

clean:
	rm -f main-race main-deadlock main-deadlock-global main-signal main-signal-cv

main-race: main-race.c common_threads.h
	gcc -o main-race main-race.c $(FLAGS)

helgrind-main-race:
	valgrind --tool=helgrind ./main-race

main-race-loop: main-race-loop.c common_threads.h
	gcc -o main-race-loop main-race-loop.c $(FLAGS)

helgrind-main-race-loop:
	valgrind --tool=helgrind ./main-race-loop

main-race-loop-fixed: main-race-loop-fixed.c common_threads.h
	gcc -o main-race-loop-fixed main-race-loop-fixed.c $(FLAGS)

helgrind-main-race-loop-fixed:
	valgrind --tool=helgrind ./main-race-loop-fixed


main-deadlock: main-deadlock.c common_threads.h
	gcc -o main-deadlock main-deadlock.c $(FLAGS)

main-deadlock-global: main-deadlock-global.c common_threads.h
	gcc -o main-deadlock-global main-deadlock-global.c $(FLAGS)

main-signal: main-signal.c common_threads.h
	gcc -o main-signal main-signal.c $(FLAGS)

main-signal-cv: main-signal-cv.c common_threads.h
	gcc -o main-signal-cv main-signal-cv.c $(FLAGS)

