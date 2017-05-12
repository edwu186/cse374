all: autocomplete

autocomplete: main.o trie.o
	gcc main.o trie.o -o autocomplete -std=c11 -g -Wall

main.o: main.c trie.h
	gcc -c main.c -o main.o -std=c11 -g -Wall

trie.o: trie.c trie.h
	gcc -c trie.c -o trie.o -std=c11 -g -Wall

clean:
	rm -f *.o autocomplete
