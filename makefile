FICHEIRO = main.c Estruturas/avl.c Estruturas/avlCompras.c Estruturas/avl.h Estruturas/avlCompras.h catalogos.c catalogos.h contabilidade.c contabilidade.h
OUTPUT = gesthiper

build: $(FICHEIRO)
	gcc -Wall -ansi -pedantic -o2 -o $(OUTPUT) $(FICHEIRO)

clean:
	rm -f *.o 
	rm -f $(OUTPUT)

rebuild:
	clean build
