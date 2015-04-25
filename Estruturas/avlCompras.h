typedef struct nodoCompras *Compras;
typedef struct nodo *CatalogoAux; /*declaro isto pois nao posso usar o nome Catalogo, pois ja foi declarado!!*/
Compras array[26];

char *getClientes (Compras a);
char *getProd (Compras a);
char getTipo (Compras a);
int getMes (Compras a);
float getLucro (Compras a);
int getQuantidade (Compras a);
int getAlturaCompras(Compras a);
Compras getEsqCompras(Compras a);
Compras getDirCompras(Compras a);

/* tamanho_AVLCompras
 * Esta função calcula o número de nodos
 * de uma AVL
 */
int tamanho_AVLCompras(Compras a);

/* alturaCompras
 * Esta função calcula a altura
 * de uma AVL
 */
int alturaCompras(Compras t);

/* procurarProdutos
 * Esta função procura se um produto existe numa AVL
 */
int procurarProdutos(char s[], Compras a);

/* procurarClientes
 * Esta função verifica se um cliente existe numa AVL
 */
int procurarClientes(char s[], Compras a);

/* Max
 * Esta função calcula o máximo
 * entre dois numeros.
 */
int Max(int a,int b);

/* rodarESqUmaCompras
 * Rotação esquerda em um nó. Utilizada para
 * manter a arvore balenceada durante a inserção 
 * de um nodo.
 */ 
Compras rodarEsqUmaCompras(Compras t);

/* rodarDirUmaCompras
 * Rotação direita de um nó. Utilizada para
 * manter a arvore balenceada durante a inserção de um nodo.
 */
Compras rodarDirUmaCompras(Compras t);

/* rodarEsqDuploCompras
 * Uma rotação dupla para a esquerda é uma rotação
 * para direita no filho da direita seguida de uma 
 * rotação para a esquerda no nodo passado como parametro
 */
Compras rodarEsqDuploCompras(Compras t);

/* rodarDirDuploCompras
 * Uma rotação dupla para a direita é uma rotação 
 * para a esquerda no filho da esquerda seguida de 
 * uma rotação para a direita no nodo passado como parametro
 */
Compras rodarDirDuploCompras(Compras t);

/* inserirCompras
 * Função que insere um nodo numa arvore AVL 
 * garantido o balenceamento da arvore
*/
Compras inserirCompras(char s[], Compras t);

/*
*
*/
void imprimirCompras(Compras a);
