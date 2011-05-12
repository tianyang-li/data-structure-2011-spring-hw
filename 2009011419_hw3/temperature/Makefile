CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : temperature bf

temperature : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o temperature

main.o : main.cc range-tree.h
	$(CC) $(CFLAGS) -c main.cc
	
range-tree.h : quick-sort.h
	touch range-tree.h	
	
bf : bf.cc
	$(CC) -D BF $(CFLAGS) bf.cc -o bf

.PHONY : clean
clean :
	rm *.o
	