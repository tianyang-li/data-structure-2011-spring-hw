CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : duplicity

duplicity : $(OBJ)
	$(CC) $(CFLGAS) $(OBJ) -o duplicity
	
main.o : main.cc
	$(CC) $(CFLAGS) -c main.cc
	
.PHONY : clean
clean :
	rm *.o