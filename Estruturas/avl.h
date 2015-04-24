typedef struct nodo* Catalogo;

Catalogo inserir(char s[], Catalogo t);
int tamanho_AVL(Catalogo t);
int altura(Catalogo t);
int procurar(char *s,Catalogo t);
int max(int a,int b);
int validarLinha(char *linha,Catalogo AVLClientes,Catalogo AVLProdutos);
void imprimir(Catalogo t);
void displayCodigos(Catalogo t);
void imprimirLetra(Catalogo t, char s, int *i,int *q);
char** imprimirClientes(Catalogo clientes, char s, int *i,char **destino);
char** imprimirProdutos(Catalogo clientes, char s, int *i,char **destino);

char *getData(Catalogo a);
int getAltura(Catalogo a);
Catalogo getEsq(Catalogo a);
Catalogo getDir(Catalogo a);
