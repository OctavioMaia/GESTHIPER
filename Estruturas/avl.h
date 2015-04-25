/* Catalogo
 * Esta estrutura contém o codigo, a altura
 * da estrutura.
 */
typedef struct nodo* Catalogo;

/* getData
 * Recebe uma estrutura do tipo Catalogo e
 * devolve o código.
 */
char *getData(Catalogo a);

/* getAltura
 * Recebe uma estrutura do tipo Catalogo e
 * devolve a altura da mesma.
 */
int getAltura(Catalogo a);

/* getEsq
 * Recebe uma estrutura do tipo Catalogo e
 * devolve o nodo a esquerda.
 */
Catalogo getEsq(Catalogo a);

/* getData
 * Recebe uma estrutura do tipo Catalogo e
 * devolve o nodo à direita.
 */
Catalogo getDir(Catalogo a);

/* inserir
 * Função que insere um nodo numa arvore Catalogo 
 * garantido o balenceamento da arvore
 */
Catalogo inserir(char s[], Catalogo t);

/* tamanho_AVL
 * Esta função calcula o número de nodos
 * de uma Catalogo
 */
int tamanho_AVL(Catalogo t);

/* altura
 * Esta função calcula a altura
 * de uma Catalogo
 */
int altura(Catalogo t);

/* procurar
 * Esta função procura se uma string
 * existe numa Catalogo
 */
int procurar(char *s,Catalogo t);

/* max
 * Esta função calcula o máximo
 * entre dois numeros.
 */
int max(int a,int b);

/* rodarESqUma
 * Rotação esquerda em um nó. Utilizada para
 * manter a arvore balenceada durante a inserção 
 * de um nodo.
 */
Catalogo rodarEsqUma(Catalogo t);

/* rodarDirUma
 * Rotação direita de um nó. Utilizada para
 * manter a arvore balenceada durante a inserção de um nodo.
 */
Catalogo rodarDirUma(Catalogo t);

/* rodarEsqDuplo 
 * Uma rotação dupla para a esquerda é uma rotação
 * para direita no filho da direita seguida de uma 
 * rotação para a esquerda no nodo passado como parametro
 */
Catalogo rodarEsqDuplo(Catalogo t);


/* rodarDirDuplo
 * Uma rotação dupla para a direita é uma rotação 
 * para a esquerda no filho da esquerda seguida de 
 * uma rotação para a direita no nodo passado como parametro
 */
Catalogo rodarDirDuplo(Catalogo t);

char *getData(Catalogo a);
int getAltura(Catalogo a);
Catalogo getEsq(Catalogo a);
Catalogo getDir(Catalogo a);
