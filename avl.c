#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

int tamanho_AVL(AVL t){
    if(t)
    	return 1 + (tamanho_AVL(t->esq)+tamanho_AVL(t->dir)); 
    else
        return 0;
}

int altura(AVL t){
	return (t==NULL) ? 0 : t->altura;
}

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

int max(int a,int b){
	return a>b ? a:b;
}

AVL rodarEsqUma(AVL t){
	AVL aux = NULL;

	aux = t->esq;
    t->esq = aux->dir;
    aux->dir = t;
 
    t->altura = max( altura( t->esq ), altura( t->dir ) ) + 1;
    aux->altura = max( altura( aux->esq ), t->altura ) + 1;
    return aux; /*nova raiz*/
}

AVL rodarDirUma(AVL t){
	AVL aux;

	aux = t->dir;
    t->dir = aux->esq;
    aux->esq = t;
 
    t->altura = max( altura(t->esq),altura(t->dir) ) + 1;
    aux->altura = max( altura(aux->dir),t->altura) + 1;
    return aux; /*nova raiz*/
}

AVL rodarEsqDuplo(AVL t){
	t->esq = rodarDirUma(t->esq);

	return rodarEsqUma(t);
}

AVL rodarDirDuplo(AVL t){
	t->dir = rodarEsqUma(t->dir);

	return rodarDirUma(t);
}

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

int validarLinha(char *linha,AVL AVLClientes,AVL AVLProdutos){
	char produto[10];
	float preco;
	int unidades_compradas;
	char tipo_compra;
	char cliente[10];
	int mes;

	sscanf(linha,"%s %f %d %c %s %d",produto,&preco,&unidades_compradas,&tipo_compra,cliente,&mes);

	if(!procurar(produto,AVLProdutos) || preco<0 || unidades_compradas<0 || (tipo_compra!='N' && tipo_compra!='P') || !procurar(cliente,AVLClientes) || (mes<1 || mes>12)) return 0;
	
	return 1;
}

/*ALTERAR ESTA CENA PARA NAO TER PRINTFS*/

void imprimir(AVL t){
	AVL temp = t;

	if(temp){
		imprimir(temp->esq);
		printf("%s\n",temp->data);
		imprimir(temp->dir);
	}
}

void imprimirLetra(AVL t, char s, int *i,int *q){
	char decisao;

	if(*q==20){
		printf("\n-----------------------------");
		printf("\nDeseja imprimir mais 20 codigos? (y/n) :");
		scanf(" %c",&decisao);
		if(decisao=='y'){
			*q=0;
			printf("-----------------------------\n");
		}
		else
			(*q)++; /*dou o valor 21 pois o programa so funciona para <=20, logo para*/	
	}

	if(*i==5){ /*5 elementos por coluna*/
		putchar('\n');
		*i=0;
	}
	if(t){ 
		imprimirLetra(t->esq,s,i,q);
		if(t->data[0]==s && *q<20){
			printf("%s ",t->data);
			(*q)++;
			(*i)++;
		}
	imprimirLetra(t->dir,s,i,q);
	}
}

void displayCodigos(AVL t){
	int i=0;
	int q=0;
	char letra;

	printf("Introduza a letra a pesquisar (em maiuscula): ");
	scanf(" %c",&letra);
	imprimirLetra(t,letra,&i,&q);
	printf("\n");
}

/*FIM DA CENA PRA ALTERAR*/