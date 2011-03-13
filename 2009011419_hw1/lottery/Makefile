CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : lottery rand_gen qs_test

lottery : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o lottery

main.o : main.cc bin_search.h quick_sort.h
	$(CC) $(CFLAGS) -c main.cc
	
bin_search.o : bin_search.h bin_search.cc
	$(CC) $(CFLAGS) -c bin_search.cc
	
quick_sort.o : quick_sort.h quick_sort.cc
	$(CC) $(CFLAGS) -c quick_sort.cc
	
qs_test: qs_test.cc quick_sort.h
	$(CC) $(CFLAGS) qs_test.cc -o qs_test

rand_gen: rand_gen.cc
	$(CC) $(CFLAGS) rand_gen.cc -o rand_gen

.PHONY : clean
clean :
	rm *.o 
