CC = g++
CFLAGS = -Wall -ggdb

all : scheduler heap-test

scheduler : main.cc priority-queue.h
	$(CC) $(CFLAGS) main.cc -o scheduler
	
heap-test : heap-test.cc priority-queue.h
	$(CC) $(CFLAGS) -D HEAP_TEST heap-test.cc -o heap-test
