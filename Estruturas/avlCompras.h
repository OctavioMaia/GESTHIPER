typedef struct nodoCompras *Compras;
typedef struct nodo *CatalogoAux; /*declaro isto pois nao posso usar o nome Catalogo, pois ja foi declarado!!*/
Compras array[26];

int tamanho_AVLCompras(Compras a);
int comparar(const void *a, const void *b);
Compras inserirCompras(char s[], Compras a);
int procurarProdutos(char s[], Compras a);
int procurarClientes(char s[], Compras a);
void imprimirCompras(Compras a);

char *getClientes (Compras a);
char *getProd (Compras a);
char getTipo (Compras a);
int getMes (Compras a);
float getLucro (Compras a);
int getQuantidade (Compras a);
int getAlturaCompras(Compras a);
Compras getEsqCompras(Compras a);
Compras getDirCompras(Compras a);