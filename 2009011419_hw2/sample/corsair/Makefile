CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : corsair

corsair : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o corsair

main.o : main.cc
	$(CC) $(CFLAGS) -c main.cc

.PHONY : clean
clean :
	rm *.o
