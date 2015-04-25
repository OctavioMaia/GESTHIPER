/* Compras
 * Esta estrutura contem toda a informação 
 * necessária para processar as compras
 */
typedef struct nodoCompras *Compras;

/* CatalogoAux
 * Esta estrutura contém toda a informação
 * necessária para guardar os codigos de 
 * produtos e clientes
 */
typedef struct nodo *CatalogoAux;

/* array
 * Trata-se de um array de AVL's para minimizar
 * os tempos de pesquisa
 */
Compras array[26];

/* getClientes
 * Recebe uma estrutura do tipo Compras e
 * devolve os codigos dos clientes.
 */
char *getClientes (Compras a);


/* getProd
 * Recebe uma estrutura do tipo Compras e
 * devolve os codigos dos produtos.
 */
char *getProd (Compras a);


/* getTipo
 * Recebe uma estrutura do tipo Compras e
 * devolve o tipo da compra (N ou P).
 */
char getTipo (Compras a);


/* getClientes
 * Recebe uma estrutura do tipo Compras e
 * devolve o mês.
 */
int getMes (Compras a);


/* getLucro
 * Recebe uma estrutura do tipo Compras e
 * devolve o Lucro.
 */
float getLucro (Compras a);


/* getQuantidade
 * Recebe uma estrutura do tipo Compras e
 * devolve a quantidade comprada.
 */
int getQuantidade (Compras a);


/* getAlturaCompras
 * Recebe uma estrutura do tipo Compras e
 * devolve a altura da AVL das Compras.
 */
int getAlturaCompras(Compras a);


/* getEsqCompras
 * Recebe uma estrutura do tipo Compras e
 * devolve o nodo esquerdo.
 */
Compras getEsqCompras(Compras a);


/* getDirCompras
 * Recebe uma estrutura do tipo Compras e
 * devolve o nodo a direita.
 */
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