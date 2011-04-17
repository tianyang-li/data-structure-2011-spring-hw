CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : hospital

hospital : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o hospital
	
hospital-pg : $(OBJ)
	$(CC) $(CFLAGS) -pg $(OBJ) -o hospital

main.o : main.cc adj_list_graph.h
	$(CC) $(CFLAGS) -c main.cc

adj_list_graph.h : circ_list.h list_queue.h
	touch adj_list_graph.h

circ_list.h : list_node.h
	touch circ_list.h

list_queue.h : list_node.h
	touch list_queue.h
	
.PHONY : clean
clean :
	rm *.o
	