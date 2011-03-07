CC = g++
CFLAGS = -Wall
OBJ = main.o circ_list.o

all : interview

interview : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o interview

main.o : main.cc
	$(CC) $(CFLAGS) -c main.cc
	
circ_list.o: circ_list.h circ_list.cc
	$(CC) $(CFLAGS) -c circ_list.cc
	
.PHONY : clean
clean:
	rm *.o