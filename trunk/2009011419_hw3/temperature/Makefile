CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : temperature

temperature : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o temperature

main.o : main.cc
	$(CC) $(CFLAGS) -c main.cc

.PHONY : clean
clean :
	rm *.o
	