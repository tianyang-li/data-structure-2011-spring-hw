CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : dirtree

dirtree : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o dirtree
	
main.o : main.cc dict-tree.h
	$(CC) $(CFLAGS) -c main.cc	

dict-tree.h : red-black-tree.h
	touch dict-tree.h

.PHONY : clean
clean :
	rm *.o

