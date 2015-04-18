FICHEIRO = main.c Estruturas/avlBase.c Estruturas/avlComprasBase.c Estruturas/avl.h Estruturas/avlCompras.h catalogos.c contabilidade.c
OUTPUT = avl

build: $(FICHEIRO)
	gcc -Wall -ansi -pedantic -o2 -o $(OUTPUT) $(FICHEIRO)

clean:
	rm -f *.o 
	rm -f $(OUTPUT)

rebuild:
	clean build
