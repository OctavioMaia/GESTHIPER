#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avl.h"
#include "avlCompras.h"

typedef struct nodoCompras{
	char clientes[10];
	char produtos[10];
	char tipo_compra;
	int mes;
	float lucro;
	int quantidade;
	struct nodoCompras* esq;
	struct nodoCompras* dir;
	int altura;
}nodoCompras;

/* gets*/
char *getClientes (AVLCompras a) {
	return a -> clientes; 
}

char *getProd (AVLCompras a) {
	return a -> produtos;
}

char getTipo (AVLCompras a) {
	return a -> tipo_compra;
}

int getMes (AVLCompras a) {
	return a -> mes;
}

float getLucro (AVLCompras a) {
	return a -> lucro;
}

int getQuantidade (AVLCompras a) {
	return a -> quantidade;
}

int getAlturaCompras(AVLCompras a) {
	return a -> altura; 
}

AVLCompras getEsqCompras(AVLCompras a) {
	return a -> esq;
}

AVLCompras getDirCompras(AVLCompras a) {
	return a -> dir;
}

/* tamanho_AVLCompras
 * Esta função calcula o número de nodos
 * de uma AVL
 */
int tamanho_AVLCompras(AVLCompras t){
    if(t)
    	return 1 + (tamanho_AVLCompras(t->esq)+tamanho_AVLCompras(t->dir)); 
    else
        return 0;
}

/* alturaCompras
 * Esta função calcula a altura
 * de uma AVL
 */
int alturaCompras(AVLCompras t){
	return (t==NULL) ? 0 : t->altura;
}

/* procurarCompras
 * Esta função procura se um produto existe numa AVL
 */
int procurarProdutos(char s[], AVLCompras t){
	if(t==NULL)
		return 0;
	if(strcmp(s,t->produtos)<0) /*string menor, procura na esq*/
		return procurarProdutos(s,t->esq);
	else if(strcmp(s,t->produtos)>0) /*string maior procura na dir*/
		return procurarProdutos(s,t->dir);
	else	/*encontrou, ou seja strcmp(s,t->produtos)==0*/
		return 1; 
}

/* procurarClientes
 * Esta função verifica se um cliente existe numa AVL
 */

int procurarClientes(char s[], AVLCompras t){
	if(t==NULL)
		return 0;
	if(strcmp(s,getClientes(t))<0) /*string menor, procura na esq*/
		return procurarClientes(s,getEsqCompras(t));
	else if(strcmp(s,getClientes(t))>0) /*string maior procura na dir*/
		return procurarClientes(s,getDirCompras(t));
	else	/*encontrou, ou seja strcmp(s,getClientes(t))==0*/
		return 1; 
}


/* Max
 * Esta função calcula o máximo
 * entre dois numeros.
 */
int Max(int a,int b){
	return a>b ? a:b;
}


/* rodarESqUmaCompras
 * Rotação esquerda em um nó. Utilizada para
 * manter a arvore balenceada durante a inserção 
 * de um nodo.
 */ 
AVLCompras rodarEsqUmaCompras(AVLCompras t){
	AVLCompras aux = NULL;

	aux = t->esq;
    t->esq = aux->dir;
    aux->dir = t;
 
    t->altura = Max( alturaCompras( t->esq ), alturaCompras( t->dir ) ) + 1;
    aux->altura = Max( alturaCompras( aux->esq ), t->altura ) + 1;
    return aux; /*nova raiz*/
}

/* rodarDirUmaCompras
 * Rotação direita de um nó. Utilizada para
 * manter a arvore balenceada durante a inserção de um nodo.
 */
AVLCompras rodarDirUmaCompras(AVLCompras t){
	AVLCompras aux;

	aux = t->dir;
    t->dir = aux->esq;
    aux->esq = t;
 
    t->altura = Max( alturaCompras(t->esq),alturaCompras(t->dir) ) + 1;
    aux->altura = Max( alturaCompras(aux->dir),t->altura) + 1;
    return aux; /*nova raiz*/
}

/* rodarEsqDuploCompras
 * Uma rotação dupla para a esquerda é uma rotação
 * para direita no filho da direita seguida de uma 
 * rotação para a esquerda no nodo passado como parametro
 */
AVLCompras rodarEsqDuploCompras(AVLCompras t){
	t->esq = rodarDirUmaCompras(t->esq);

	return rodarEsqUmaCompras(t);
}

/* rodarDirDuploCompras
 * Uma rotação dupla para a direita é uma rotação 
 * para a esquerda no filho da esquerda seguida de 
 * uma rotação para a direita no nodo passado como parametro
 */
AVLCompras rodarDirDuploCompras(AVLCompras t){
	t->dir = rodarEsqUmaCompras(t->dir);

	return rodarDirUmaCompras(t);
}

/* inserirCompras
 * Função que insere um nodo numa arvore AVL 
 * garantido o balenceamento da arvore
*/
AVLCompras inserirCompras(char s[], AVLCompras t){
	char produto[10];
	float preco;
	int unidades_compradas;
	char tipo;
	char cliente[10];
	int Mes;

	if( t == NULL ){
        t = (AVLCompras)malloc(sizeof(struct nodoCompras));
        if( t == NULL ){
            /*Não conseguimos alocar memoria! ERRO*/
            exit(1);
        }else{
        	sscanf(s,"%s %f %d %c %s %d",produto,&preco,&unidades_compradas,&tipo,cliente,&Mes);
            strcpy(t->produtos,produto);
            strcpy(t->clientes,cliente);
            t->lucro = (preco*unidades_compradas);
            t->quantidade=unidades_compradas;
            t->mes=Mes;
            t->tipo_compra=tipo;
            t->altura = 0;
            t->esq = t->dir = NULL;
        }
    }
	else if(strcmp(s,t->produtos)<0){ 				/*metemos na esq*/
		t->esq = inserirCompras(s,t->esq);
		if(alturaCompras(t->esq)-alturaCompras(t->dir) == 2){ /*duplamente pesado, invocar dupla rotacao!*/
			if(strcmp(s,t->esq->produtos)<0) 		/*metemos na esq*/
				t=rodarEsqUmaCompras(t);
			else 						
				t=rodarEsqDuploCompras(t);
		}
	}
	else if(strcmp(s,t->produtos)>0){ 				/*metemos na dir*/
		t->dir = inserirCompras(s,t->dir);
		if(alturaCompras(t->dir)-alturaCompras(t->esq) == 2){ /*duplamente pesado, invocar dupla rotacao!*/
			if(strcmp(s,t->dir->produtos)>0) 		/* metemos na dir*/
				t=rodarDirUmaCompras(t);
			else
				t=rodarDirDuploCompras(t); 	
		}
	}
	t->altura = Max(alturaCompras(t->esq),alturaCompras(t->dir)) +1;
	return t;
}

void imprimirCompras(AVLCompras t){
	AVLCompras temp = t;

	if(temp){
		imprimirCompras(temp->esq);
		printf("Produto: %s\n",temp->produtos);
		printf("Cliente: %s\n",temp->clientes);
		printf("Tipo compra: %c\n",temp->tipo_compra);
		printf("Mês: %d\n",temp->mes);
		printf("Lucro: %f\n",temp->lucro);
		printf("Quantidade: %d\n",temp->quantidade);
		printf("-----------------\n");
		imprimirCompras(temp->dir);
	}
}
