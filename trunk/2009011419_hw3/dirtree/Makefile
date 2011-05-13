CC = g++
CFLAGS = -Wall -ggdb
OBJ = main.o

all : dirtree trie

dirtree : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o dirtree
	
main.o : main.cc red-black-tree.h
	$(CC) $(CFLAGS) -c main.cc	
	
trie : trie.cc
	$(CC) $(CFLAGS) -D TRIE trie.cc -o trie	

.PHONY : clean
clean :
	rm *.o

