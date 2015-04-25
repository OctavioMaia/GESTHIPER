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
char *getClientes (Compras a) {
	return a -> clientes; 
}

char *getProd (Compras a) {
	return a -> produtos;
}

char getTipo (Compras a) {
	return a -> tipo_compra;
}

int getMes (Compras a) {
	return a -> mes;
}

float getLucro (Compras a) {
	return a -> lucro;
}

int getQuantidade (Compras a) {
	return a -> quantidade;
}

int getAlturaCompras(Compras a) {
	return a -> altura; 
}

Compras getEsqCompras(Compras a) {
	return a -> esq;
}

Compras getDirCompras(Compras a) {
	return a -> dir;
}


int tamanho_AVLCompras(Compras t){
    if(t)
    	return 1 + (tamanho_AVLCompras(t->esq)+tamanho_AVLCompras(t->dir)); 
    else
        return 0;
}


int alturaCompras(Compras t){
	return (t==NULL) ? 0 : t->altura;
}


int procurarProdutos(char s[], Compras t){
	if(t==NULL)
		return 0;
	if(strcmp(s,t->produtos)<0) /*string menor, procura na esq*/
		return procurarProdutos(s,t->esq);
	else if(strcmp(s,t->produtos)>0) /*string maior procura na dir*/
		return procurarProdutos(s,t->dir);
	else	/*encontrou, ou seja strcmp(s,t->produtos)==0*/
		return 1; 
}


int procurarClientes(char s[], Compras t){
	if(t==NULL)
		return 0;
	if(strcmp(s,getClientes(t))<0) /*string menor, procura na esq*/
		return procurarClientes(s,getEsqCompras(t));
	else if(strcmp(s,getClientes(t))>0) /*string maior procura na dir*/
		return procurarClientes(s,getDirCompras(t));
	else	/*encontrou, ou seja strcmp(s,getClientes(t))==0*/
		return 1; 
}



int Max(int a,int b){
	return a>b ? a:b;
}


Compras rodarEsqUmaCompras(Compras t){
	Compras aux = NULL;

	aux = t->esq;
    t->esq = aux->dir;
    aux->dir = t;
 
    t->altura = Max( alturaCompras( t->esq ), alturaCompras( t->dir ) ) + 1;
    aux->altura = Max( alturaCompras( aux->esq ), t->altura ) + 1;
    return aux; /*nova raiz*/
}


Compras rodarDirUmaCompras(Compras t){
	Compras aux;

	aux = t->dir;
    t->dir = aux->esq;
    aux->esq = t;
 
    t->altura = Max( alturaCompras(t->esq),alturaCompras(t->dir) ) + 1;
    aux->altura = Max( alturaCompras(aux->dir),t->altura) + 1;
    return aux; /*nova raiz*/
}


Compras rodarEsqDuploCompras(Compras t){
	t->esq = rodarDirUmaCompras(t->esq);

	return rodarEsqUmaCompras(t);
}


Compras rodarDirDuploCompras(Compras t){
	t->dir = rodarEsqUmaCompras(t->dir);

	return rodarDirUmaCompras(t);
}

Compras inserirCompras(char s[], Compras t){
	char produto[10];
	float preco;
	int unidades_compradas;
	char tipo;
	char cliente[10];
	int Mes;

	if( t == NULL ){
        t = (Compras)malloc(sizeof(struct nodoCompras));
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