typedef struct nodo{
	char data[40];
	struct nodo* esq;
	struct nodo* dir;
	int altura;
}*AVL;
	
int tamanho_AVL(AVL t);
int altura(AVL t);
int procurar(char *s,AVL t);
int max(int a,int b);
AVL rodarEsqUma(AVL t);
AVL rodarDirUma(AVL t);
AVL rodarEsqDuplo(AVL t);
AVL rodarDirDuplo(AVL t);
AVL inserir(char s[], AVL t);
void imprimir(AVL t);
int validarLinha(char *linha,AVL AVLClientes,AVL AVLProdutos);