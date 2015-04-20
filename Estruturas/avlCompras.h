/* Esta estrutura é para as compras.
 * Cada nó possui o código do cliente,
 * o código do produto, o tipo de compra,
 * o mes da compra, o lucro resultante da 
 * compra (quantidade*lucro), a quantidade
 * da compra, e dois apontadores para os
 * filhos do nó.
 */

typedef struct nodoCompras *AVLCompras;
 
 
int tamanho_AVLCompras(AVLCompras t);
AVLCompras inserirCompras(char s[], AVLCompras t);
int procurarProdutos(char s[], AVLCompras t);
void imprimirCompras(AVLCompras t);
float getTotal(AVLCompras avl[],char codigo[], int m);
float getTotalN(AVLCompras avl,char codigo[], int m);
float getTotalP(AVLCompras avl,char codigo[], int m);
float getTot(AVLCompras avl, int m);
float totalLucroIntervalo(AVLCompras array[],int mesMin, int mesMax);
int totalComprasIntervalo(AVLCompras array[],int mesMin, int mesMax);
char** procurarComprasClienteAux(AVLCompras c, char* produto, char** clientes, int *i);
char** procurarComprasCliente(AVLCompras c[], char* produto);

char *getClientes (AVLCompras a);
char *getProd (AVLCompras a);
char getTipo (AVLCompras a);
int getMes (AVLCompras a);
float getLucro (AVLCompras a);
int getQuantidade (AVLCompras a);
int getAlturaCompras(AVLCompras a);
AVLCompras getEsqCompras(AVLCompras a);
AVLCompras getDirCompras(AVLCompras a);
