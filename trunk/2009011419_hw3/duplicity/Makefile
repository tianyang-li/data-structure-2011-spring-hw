CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : duplicity

duplicity : $(OBJ)
	$(CC) $(CFLGAS) $(OBJ) -o duplicity
	
main.o : main.cc
	$(CC) $(CFLAGS) -c main.cc
	
main.cc : hash1.h hash1.cc
	touch main.cc	
	$(CC) $(CFLAGS) -c hash1.cc
	
.PHONY : clean
clean :
	rm *.o