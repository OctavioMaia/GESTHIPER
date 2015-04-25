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
char *getData(Catalogo a) {
	return a -> data;
}

int getAltura(Catalogo a) {
	return a -> altura; 
}

Catalogo getEsq(Catalogo a) {
	return a -> esq;
}

Catalogo getDir(Catalogo a) {
	return a -> dir;
}


int tamanho_AVL(Catalogo t){
    if(t)
    	return 1 + (tamanho_AVL(t->esq)+tamanho_AVL(t->dir)); 
    else
        return 0;
}


int altura(Catalogo t){
	return (t==NULL) ? 0 : t->altura;
}


int procurar(char s[], Catalogo t){
	if(t==NULL)
		return 0;
	if(strcmp(s,t->data)<0) /*string menor, procura na esq*/
		return procurar(s,t->esq);
	else if(strcmp(s,t->data)>0) /*string maior procura na dir*/
		return procurar(s,t->dir);
	else	/*encontrou, ou seja strcmp(s,t->data)==0*/
		return 1; 
}


int max(int a,int b){
	return a>b ? a:b;
}



Catalogo rodarEsqUma(Catalogo t){
	Catalogo aux = NULL;

	aux = t->esq;
    t->esq = aux->dir;
    aux->dir = t;
 
    t->altura = max( altura( t->esq ), altura( t->dir ) ) + 1;
    aux->altura = max( altura( aux->esq ), t->altura ) + 1;
    return aux; /*nova raiz*/
}


Catalogo rodarDirUma(Catalogo t){
	Catalogo aux;

	aux = t->dir;
    t->dir = aux->esq;
    aux->esq = t;
 
    t->altura = max( altura(t->esq),altura(t->dir) ) + 1;
    aux->altura = max( altura(aux->dir),t->altura) + 1;
    return aux; /*nova raiz*/
}


Catalogo rodarEsqDuplo(Catalogo t){
	t->esq = rodarDirUma(t->esq);

	return rodarEsqUma(t);
}

Catalogo rodarDirDuplo(Catalogo t){
	t->dir = rodarEsqUma(t->dir);

	return rodarDirUma(t);
}


Catalogo inserir(char s[], Catalogo t){

	if( t == NULL ){
        t = (Catalogo)malloc(sizeof(struct nodo));
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
