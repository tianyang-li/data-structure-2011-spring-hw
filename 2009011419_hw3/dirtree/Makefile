CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : dirtree

dirtree : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o dirtree
	
main.o : main.cc
	$(CC) $(CFLAGS) -c main.cc	

.PHONY : clean
clean :
	rm *.o

