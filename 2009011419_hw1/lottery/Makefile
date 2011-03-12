CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : lottery

lottery : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o lottery

main.o : main.cc bin_search.h quick_sort.h
	$(CC) $(CFLGAS) -c main.cc
	
bin_search.o : bin_search.h bin_search.cc
	$(CC) $(CFLAGS) -c bin_search.cc
	
quick_sort.o : quick_sort.h quick_sort.cc
	$(CC) $(CFLAGS) -c quick_sort.cc

.PHONY : clean
clean :
	rm *.o 
