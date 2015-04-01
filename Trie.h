#define TAMANHO 36 /*26 letras do alfabeto + 10 digitos para*/

typedef struct nodo{
	int data;
	char ch;
	struct nodo* filhos[TAMANHO]; /*Cada um nos 26 nodos é uma letra do alfabeto e 10 digitos*/
}*Trie;