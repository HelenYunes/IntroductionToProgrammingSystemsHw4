CC = gcc
FLAGS = -Wall -g
.PHONY: all clean

all: frequency

frequency: Trie.c
	$(CC) $(FLAGS) Trie.c -o frequency

clean:
	rm -f frequency