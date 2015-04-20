/* Esta estrutura contem a 
 * informação do nó e dois 
 * apontadores para os filhos 
 * do nó
 */
typedef struct nodo* AVL;

AVL inserir(char s[], AVL t);
int tamanho_AVL(AVL t);
int altura(AVL t);
int procurar(char *s,AVL t);
int max(int a,int b);
int validarLinha(char *linha,AVL AVLClientes,AVL AVLProdutos);
void imprimir(AVL t);
void displayCodigos(AVL t);
void imprimirLetra(AVL t, char s, int *i,int *q);
void imprimirClientes(AVL clientes, char s, int *i);

char *getData(AVL a);
int getAltura(AVL a);
AVL getEsq(AVL a);
AVL getDir(AVL a);
