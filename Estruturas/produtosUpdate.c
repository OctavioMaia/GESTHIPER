#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "produtosUpdate.h"

typedef struct nodo{
	char data[10];
	int qtotal;
	int Altura;
	struct nodo *esq;
	struct nodo *dir;
}nodo;

char *getProduto(ProdutosUpdate a) {
	return a -> data;
}

int getQuantidadeTotal(ProdutosUpdate a) {
	return a -> qtotal; 
}

void setQuantidadeTotal(ProdutosUpdate a,int n) {
	a -> qtotal = n;
}

ProdutosUpdate getEsquerda(ProdutosUpdate a){
	return a->esq;
}

ProdutosUpdate getDireita(ProdutosUpdate a){
	return a->dir;
}

/* Altura
 * Esta função calcula a Altura
 * de uma ProdutosUpdate
 */
int Altura(ProdutosUpdate t){
	return (t==NULL) ? 0 : t->Altura;
}

/* Procurar
 * Esta função procura se uma string
 * existe numa ProdutosUpdate
 */
int Procurar(char s[], ProdutosUpdate t){
	if(t==NULL)
		return 0;
	if(strcmp(s,t->data)<0) /*string menor, procura na esq*/
		return Procurar(s,t->esq);
	else if(strcmp(s,t->data)>0) /*string maior procura na dir*/
		return Procurar(s,t->dir);
	else	/*encontrou, ou seja strcmp(s,t->data)==0*/
		return 1; 
}

/* MAX
 * Esta função calcula o máximo
 * entre dois numeros.
 */
int MAX(int a,int b){
	return a>b ? a:b;
}


/* rodarESqUma
 * Rotação esquerda em um nó. Utilizada para
 * manter a arvore balenceada durante a inserção 
 * de um nodo.
 */ 
ProdutosUpdate rodarEsqUmaProdutos(ProdutosUpdate t){
	ProdutosUpdate aux = NULL;

	aux = t->esq;
    t->esq = aux->dir;
    aux->dir = t;
 
    t->Altura = MAX( Altura( t->esq ), Altura( t->dir ) ) + 1;
    aux->Altura = MAX( Altura( aux->esq ), t->Altura ) + 1;
    return aux; /*nova raiz*/
}

/* rodarDirUma
 * Rotação direita de um nó. Utilizada para
 * manter a arvore balenceada durante a inserção de um nodo.
 */
ProdutosUpdate rodarDirUmaProdutos(ProdutosUpdate t){
	ProdutosUpdate aux;

	aux = t->dir;
    t->dir = aux->esq;
    aux->esq = t;
 
    t->Altura = MAX( Altura(t->esq),Altura(t->dir) ) + 1;
    aux->Altura = MAX( Altura(aux->dir),t->Altura) + 1;
    return aux; /*nova raiz*/
}

/* rodarEsqDuplo 
 * Uma rotação dupla para a esquerda é uma rotação
 * para direita no filho da direita seguida de uma 
 * rotação para a esquerda no nodo passado como parametro
 */
ProdutosUpdate rodarEsqDuploProdutos(ProdutosUpdate t){
	t->esq = rodarDirUmaProdutos(t->esq);

	return rodarEsqUmaProdutos(t);
}

/* rodarDirDuplo
 * Uma rotação dupla para a direita é uma rotação 
 * para a esquerda no filho da esquerda seguida de 
 * uma rotação para a direita no nodo passado como parametro
 */
ProdutosUpdate rodarDirDuploProdutos(ProdutosUpdate t){
	t->dir = rodarEsqUmaProdutos(t->dir);

	return rodarDirUmaProdutos(t);
}

int update(ProdutosUpdate t, char *s,int q){
	if(t==NULL)
		return 0;
	if(strcmp(s,t->data)<0) 
		return update(t->esq,s,q);
	else if(strcmp(s,t->data)>0)
		return update(t->dir,s,q);
	else
		return t->qtotal=(t->qtotal+q);
}

/* inserirProdutos
 * Função que insere um nodo numa arvore ProdutosUpdate 
 * garantido o balenceamento da arvore
 */

ProdutosUpdate inserirProdutos(char s[], ProdutosUpdate t){
	char produto[10];
	float preco;
	int unidades_compradas;
	char tipo;
	char cliente[10];
	int Mes;

	if( t == NULL ){
        t = (ProdutosUpdate)malloc(sizeof(struct nodo));
        if( t == NULL ){
            /*Não conseguimos alocar memoria! ERRO*/
            exit(1);
        }else{
        	sscanf(s,"%s %f %d %c %s %d",produto,&preco,&unidades_compradas,&tipo,cliente,&Mes);
            strcpy(t->data,produto);
            t->qtotal=update(t,produto,unidades_compradas);
            t->Altura = 0;
            t->esq = t->dir = NULL;
        }
    }
	else if(strcmp(s,t->data)<0){ 				/*metemos na esq*/
		t->esq = inserirProdutos(s,t->esq);
		if(Altura(t->esq)-Altura(t->dir) == 2){ /*duplamente pesado, invocar dupla rotacao!*/
			if(strcmp(s,t->esq->data)<0) 		/*metemos na esq*/
				t=rodarEsqUmaProdutos(t);
			else 						
				t=rodarEsqDuploProdutos(t);
		}
	}
	else if(strcmp(s,t->data)>0){ 				/*metemos na dir*/
		t->dir = inserirProdutos(s,t->dir);
		if(Altura(t->dir)-Altura(t->esq) == 2){ /*duplamente pesado, invocar dupla rotacao!*/
			if(strcmp(s,t->dir->data)>0) 		/* metemos na dir*/
				t=rodarDirUmaProdutos(t);
			else
				t=rodarDirDuploProdutos(t); 	
		}
	}
	t->Altura = MAX(Altura(t->esq),Altura(t->dir)) +1;
	return t;
}