CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : subway

subway : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o subway

main.o : main.cc circ_list.h list_node.h	
	$(CC) $(CFLAGS) -c main.cc
	
circ_list.o : circ_list.h circ_list.cc
	$(CC) $(CFLAGS) -c circ_list.cc
	
list_node.o : list_node.h list_node.cc
	$(CC) $(CFLAGS) -c list_node.cc

.PHONY : clean
clean:
	rm *.o

