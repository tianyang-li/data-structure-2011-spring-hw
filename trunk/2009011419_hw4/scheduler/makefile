CC = g++
CFLAGS = -Wall -ggdb

all : scheduler heap-test bf

scheduler : main.cc priority-queue.h
	$(CC) $(CFLAGS) main.cc -o scheduler
	
heap-test : heap-test.cc priority-queue.h
	$(CC) $(CFLAGS) -D HEAP_TEST heap-test.cc -o heap-test
	
bf : brute-force.cc
	$(CC) $(CFLAGS) -D BRUTE_FORCE brute-force.cc -o bf
