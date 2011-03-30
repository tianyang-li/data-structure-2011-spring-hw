CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : log

log : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o log

main.o : main.cc list_stack.h
	$(CC) $(CFLAGS) -c main.cc

list_stack.h : list_node.h
	
.PHONY : clean
clean :
	rm *.o 
	