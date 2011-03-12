CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : scoreboard

scoreboard : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o scoreboard

main.o : main.cc
	$(CC) $(CFLAGS) -c main.cc
	
.PHONY : clean
clean:
	rm *.o
