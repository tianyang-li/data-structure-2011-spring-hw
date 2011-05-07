CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : temperature

temperature : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o temperature

main.o : main.cc range-tree.h
	$(CC) $(CFLAGS) -c main.cc
	
range-tree.h : quick-sort.h
	touch range-tree.h	

.PHONY : clean
clean :
	rm *.o
	