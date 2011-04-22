CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : battle

battle : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o battle
	
main.o : main.cc
	$(CC) $(CFLAGS) -c main.cc

.PHONY : clean
clean :
	rm *.o