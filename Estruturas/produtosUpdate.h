/* ProdutosUpdate
 * Esta estrutura contém o nome do produto,
 * a quantidade total vendida.
 */
typedef struct nodoUpdate* ProdutosUpdate;


/* getProduto
 * Recebe uma estrutura do tipo ProdutosUpdate e
 * devolve o código de produto.
 */
char *getProduto(ProdutosUpdate a) ;


/* getQuantidadeTotal
 * Recebe uma estrutura do tipo ProdutosUpdate e
 * devolve a quantidade total comprada de um produto.
 */
int getQuantidadeTotal(ProdutosUpdate a) ;


/* getEsquerda
 * Recebe uma estrutura do tipo ProdutosUpdate e
 * devolve o nodo a esquerda.
 */
ProdutosUpdate getEsquerda(ProdutosUpdate a);


/* getDireita
 * Recebe uma estrutura do tipo ProdutosUpdate e
 * devolve o nodo a direita.
 */
ProdutosUpdate getDireita(ProdutosUpdate a);

/* Altura
 * Calcula a Altura de uma ProdutosUpdate
 */
int Altura(ProdutosUpdate t);

/* Procurar
 * Esta função procura se uma string
 * existe numa ProdutosUpdate
 */
int Procurar(char s[], ProdutosUpdate t);

/* MAX
 * Esta função calcula o máximo
 * entre dois numeros.
 */
int MAX(int a,int b);
int update(ProdutosUpdate t, char *s,int q);
void setQuantidadeTotal(ProdutosUpdate a,int n);

/* rodarESqUma
 * Rotação esquerda em um nó. Utilizada para
 * manter a arvore balenceada durante a inserção 
 * de um nodo.
 */ 
ProdutosUpdate rodarEsqUmaProdutos(ProdutosUpdate t);

/* rodarDirUma
 * Rotação direita de um nó. Utilizada para
 * manter a arvore balenceada durante a inserção de um nodo.
 */
ProdutosUpdate rodarDirUmaProdutos(ProdutosUpdate t);

/* rodarEsqDuplo 
 * Uma rotação dupla para a esquerda é uma rotação
 * para direita no filho da direita seguida de uma 
 * rotação para a esquerda no nodo passado como parametro
 */
ProdutosUpdate rodarEsqDuploProdutos(ProdutosUpdate t);

/* rodarDirDuplo
 * Uma rotação dupla para a direita é uma rotação 
 * para a esquerda no filho da esquerda seguida de 
 * uma rotação para a direita no nodo passado como parametro
 */
ProdutosUpdate rodarDirDuploProdutos(ProdutosUpdate t);

/* inserirProdutos
 * Função que insere um nodo numa arvore ProdutosUpdate 
 * garantido o balenceamento da arvore
 */
ProdutosUpdate inserirProdutos(char s[], ProdutosUpdate t);

