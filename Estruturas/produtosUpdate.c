#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "produtosUpdate.h"

typedef struct nodoUpdate{
	char data[10];
	int qtotal;
	int Altura;
	struct nodoUpdate *esq;
	struct nodoUpdate *dir;
}nodoUpdate;

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

int Altura(ProdutosUpdate t){
	return (t==NULL) ? 0 : t->Altura;
}


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


int MAX(int a,int b){
	return a>b ? a:b;
}



ProdutosUpdate rodarEsqUmaProdutos(ProdutosUpdate t){
	ProdutosUpdate aux = NULL;

	aux = t->esq;
    t->esq = aux->dir;
    aux->dir = t;
 
    t->Altura = MAX( Altura( t->esq ), Altura( t->dir ) ) + 1;
    aux->Altura = MAX( Altura( aux->esq ), t->Altura ) + 1;
    return aux; /*nova raiz*/
}


ProdutosUpdate rodarDirUmaProdutos(ProdutosUpdate t){
	ProdutosUpdate aux;

	aux = t->dir;
    t->dir = aux->esq;
    aux->esq = t;
 
    t->Altura = MAX( Altura(t->esq),Altura(t->dir) ) + 1;
    aux->Altura = MAX( Altura(aux->dir),t->Altura) + 1;
    return aux; /*nova raiz*/
}


ProdutosUpdate rodarEsqDuploProdutos(ProdutosUpdate t){
	t->esq = rodarDirUmaProdutos(t->esq);

	return rodarEsqUmaProdutos(t);
}


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



ProdutosUpdate inserirProdutos(char s[], ProdutosUpdate t){
	char produto[10];
	float preco;
	int unidades_compradas;
	char tipo;
	char cliente[10];
	int Mes;

	if( t == NULL ){
        t = (ProdutosUpdate)malloc(sizeof(struct nodoUpdate));
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