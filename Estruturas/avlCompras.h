/* Esta estrutura é para as compras.
 * Cada nó possui o código do cliente,
 * o código do produto, o tipo de compra,
 * o mes da compra, o lucro resultante da 
 * compra (quantidade*lucro), a quantidade
 * da compra, e dois apontadores para os
 * filhos do nó.
 */

typedef struct nodoCompras *Compras;
typedef struct nodo *CatalogoAux;
 
int tamanho_AVLCompras(Compras t);
Compras inserirCompras(char s[], Compras t);
int procurarProdutos(char s[], Compras t);
int procurarClientes(char s[], Compras t);
void imprimirCompras(Compras t);
float getTotal(Compras avl[],char codigo[], int m);
float getTotalN(Compras avl,char codigo[], int m);
float getTotalP(Compras avl,char codigo[], int m);
float getTot(Compras avl, int m);
float totalLucroIntervalo(Compras array[],int mesMin, int mesMax);
int totalComprasIntervalo(Compras array[],int mesMin, int mesMax);
char** procurarComprasClienteAux(Compras c, char* produto, char** clientes, int *i);
char** procurarComprasCliente(Compras c[], char* produto);

char** naoComprou(Compras array[],CatalogoAux produtos,int *i,char** destino);
char** clienteNaoComprouAux(Compras t,CatalogoAux clientes,int *i,char** destino);
char** clienteNaoComprou(Compras array[],CatalogoAux clientes,int *i,char** destino);

char *getClientes (Compras a);
char *getProd (Compras a);
char getTipo (Compras a);
int getMes (Compras a);
float getLucro (Compras a);
int getQuantidade (Compras a);
int getAlturaCompras(Compras a);
Compras getEsqCompras(Compras a);
Compras getDirCompras(Compras a);
