FICHEIRO = Trie.c Trie.h
OUTPUT = Trie

build: $(FICHEIRO)
	gcc -Wall -ansi -pedantic -o2 -o $(OUTPUT) $(FICHEIRO)

clean:
	rm -f *.o 
	rm -f $(OUTPUT)

rebuild:
	clean build
