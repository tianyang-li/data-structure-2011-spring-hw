CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : hospital
	$(CC) $(CFLAGS) $(OBJ) -o hospital

main.o : main.cc
	$(CC) $(CFLAGS) -c main.cc
	
.PHONY : clean
clean :
	rm *.o
	