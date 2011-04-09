CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : hospital

hospital : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o hospital

main.o : main.cc adj_list_graph.h
	$(CC) $(CFLAGS) -c main.cc

adj_list_graph.h : circ_list.h

circ_list.h : list_node.h
	
.PHONY : clean
clean :
	rm *.o
	