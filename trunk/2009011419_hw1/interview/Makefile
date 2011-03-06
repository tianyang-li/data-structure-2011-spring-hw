CC = g++
CFLAGS = -Wall
OBJ = main.o line_list.o

all : interview

interview : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o interview

main.o : main.cc
	$(CC) $(CFLAGS) -c main.cc
	
line_list.o: line_list.h line_list.cc
	$(CC) $(CFLAGS) -c line_list.cc
	
.PHONY : clean
clean:
	rm *.o