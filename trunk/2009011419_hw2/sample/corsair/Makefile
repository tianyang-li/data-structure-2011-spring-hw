CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : corsair

corsair : $(OBJ)
	$(CC) $(CFLAGS) -o corsair

main.o : main.cc
	$(CC) $(CFLGAS) -c main.cc

.PHONY : clean
clean :
	rm *.o
