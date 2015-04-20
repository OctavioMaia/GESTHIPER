#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

typedef struct nodo{
	char data[10];
	struct nodo* esq;
	struct nodo* dir;
	int altura;
}nodo; 

/*gets */
char *getData(AVL a) {
	return a -> data;
}

int getAltura(AVL a) {
	return a -> altura; 
}

AVL getEsq(AVL a) {
	return a -> esq;
}

AVL getDir(AVL a) {
	return a -> dir;
}

/* tamanho_AVL
 * Esta função calcula o número de nodos
 * de uma AVL
 */
int tamanho_AVL(AVL t){
    if(t)
    	return 1 + (tamanho_AVL(t->esq)+tamanho_AVL(t->dir)); 
    else
        return 0;
}

/* altura
 * Esta função calcula a altura
 * de uma AVL
 */
int altura(AVL t){
	return (t==NULL) ? 0 : t->altura;
}

/* procurar
 * Esta função procura se uma string
 * existe numa AVL
 */
int procurar(char s[], AVL t){
	if(t==NULL)
		return 0;
	if(strcmp(s,t->data)<0) /*string menor, procura na esq*/
		return procurar(s,t->esq);
	else if(strcmp(s,t->data)>0) /*string maior procura na dir*/
		return procurar(s,t->dir);
	else	/*encontrou, ou seja strcmp(s,t->data)==0*/
		return 1; 
}

/* max
 * Esta função calcula o máximo
 * entre dois numeros.
 */
int max(int a,int b){
	return a>b ? a:b;
}


/* rodarESqUma
 * Rotação esquerda em um nó. Utilizada para
 * manter a arvore balenceada durante a inserção 
 * de um nodo.
 */ 
AVL rodarEsqUma(AVL t){
	AVL aux = NULL;

	aux = t->esq;
    t->esq = aux->dir;
    aux->dir = t;
 
    t->altura = max( altura( t->esq ), altura( t->dir ) ) + 1;
    aux->altura = max( altura( aux->esq ), t->altura ) + 1;
    return aux; /*nova raiz*/
}

/* rodarDirUma
 * Rotação direita de um nó. Utilizada para
 * manter a arvore balenceada durante a inserção de um nodo.
 */
AVL rodarDirUma(AVL t){
	AVL aux;

	aux = t->dir;
    t->dir = aux->esq;
    aux->esq = t;
 
    t->altura = max( altura(t->esq),altura(t->dir) ) + 1;
    aux->altura = max( altura(aux->dir),t->altura) + 1;
    return aux; /*nova raiz*/
}

/* rodarEsqDuplo 
 * Uma rotação dupla para a esquerda é uma rotação
 * para direita no filho da direita seguida de uma 
 * rotação para a esquerda no nodo passado como parametro
 */
AVL rodarEsqDuplo(AVL t){
	t->esq = rodarDirUma(t->esq);

	return rodarEsqUma(t);
}

/* rodarDirDuplo
 * Uma rotação dupla para a direita é uma rotação 
 * para a esquerda no filho da esquerda seguida de 
 * uma rotação para a direita no nodo passado como parametro
 */
AVL rodarDirDuplo(AVL t){
	t->dir = rodarEsqUma(t->dir);

	return rodarDirUma(t);
}

/* inserir
 * Função que insere um nodo numa arvore AVL 
 * garantido o balenceamento da arvore
 */
AVL inserir(char s[], AVL t){

	if( t == NULL ){
        t = (AVL)malloc(sizeof(struct nodo));
        if( t == NULL ){
            /*Não conseguimos alocar memoria! ERRO*/
            exit(1);
        }else{
            strcpy(t->data,s);
            t->altura = 0;
            t->esq = t->dir = NULL;
        }
    }
	else if(strcmp(s,t->data)<0){ 				/*metemos na esq*/
		t->esq = inserir(s,t->esq);
		if(altura(t->esq)-altura(t->dir) == 2){ /*duplamente pesado, invocar dupla rotacao!*/
			if(strcmp(s,t->esq->data)<0) 		/*metemos na esq*/
				t=rodarEsqUma(t);
			else 						
				t=rodarEsqDuplo(t);
		}
	}
	else if(strcmp(s,t->data)>0){ 				/*metemos na dir*/
		t->dir = inserir(s,t->dir);
		if(altura(t->dir)-altura(t->esq) == 2){ /*duplamente pesado, invocar dupla rotacao!*/
			if(strcmp(s,t->dir->data)>0) 		/* metemos na dir*/
				t=rodarDirUma(t);
			else
				t=rodarDirDuplo(t); 	
		}
	}
	t->altura = max(altura(t->esq),altura(t->dir)) +1;
	return t;
}
