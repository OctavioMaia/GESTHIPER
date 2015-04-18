#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Estruturas/avl.h"
#include "Estruturas/avlCompras.h"

/*--- query 3----*/ 
float getTotal(AVLCompras avl[],char codigo[], int m){
	int indice = codigo[0] - 'A';
	return (getTotalP(avl[indice],codigo,m)+getTotalN(avl[indice],codigo,m));
}

float getTotalP(AVLCompras avl,char codigo[], int m){
	AVLCompras t = avl;
	if(t){
		if(t->tipo_compra=='P' && (t->mes)==m && (strcmp(codigo,t->produtos)==0)){
			return t->lucro+getTotalP(t->esq,codigo,m)+getTotalP(t->dir,codigo,m);
		}
		return getTotalP(t->esq,codigo,m)+getTotalP(t->dir,codigo,m);
	}
	return 0;
}

float getTotalN(AVLCompras avl,char codigo[], int m){
	AVLCompras t = avl;
	if(t){
		if(t->tipo_compra=='N' && (t->mes)==m && (strcmp(codigo,t->produtos)==0)){
			return t->lucro+getTotalN(t->esq,codigo,m)+getTotalN(t->dir,codigo,m);
		}
		return getTotalN(t->esq,codigo,m)+getTotalN(t->dir,codigo,m);
	}
	return 0;
}

/*------------QUERY 4---------*/
void naoComprou(AVLCompras array[],AVL produtos,int *i,char** destino){
	int indice;

	if(produtos){
		naoComprou(array,produtos->esq,i,destino);
		
		indice = produtos->data[0]-'A';
		if(array[indice])
			if(procurarProdutos(produtos->data,array[indice])==0){
				destino[(*i)] = malloc(sizeof(char)*6);
				destino[(*i)] = produtos->data;
				(*i)++;
			}

		naoComprou(array,produtos->dir,i,destino);
	}
}

/*-----------query6------------*/
void imprimirClientes(AVL clientes, char s, int *i){
	AVL t = clientes;
	if(islower(s))
		s=toupper(s);

	if(*i==8){ /*8 elementos por coluna*/
		printf("\n");;
		*i=0;
	}
	if(t){ 
		imprimirClientes(t->esq,s,i);
		if(t->data[0]==s){
			printf("%s ",t->data);
			(*i)++;
		}
	imprimirClientes(t->dir,s,i);
	}
}

/*--------------query7-----------*/

float getTot(AVLCompras avl, int m){
	AVLCompras t = avl;
	if(t){
		if((t->mes)==m){
			return t->lucro+getTot(t->esq,m)+getTot(t->dir,m);
		}
		return getTot(t->esq,m)+getTot(t->dir,m);
	}
	return 0;
}

float totalLucroIntervalo(AVLCompras array[],int mesMin, int mesMax){
	int i,m;
	float totalLucro=0;

	for(i=0;i<26;i++){
		for(m=mesMin;m<=mesMax;m++){
			totalLucro+=getTot(array[i],m);	
		}
	}
	return totalLucro;
}

int totalComprasIntervalo(AVLCompras array[],int mesMin, int mesMax){
	int i;
	int totalCompras=0;

	for(i=mesMin;i<=mesMax;i++){
		totalCompras+=tamanho_AVLCompras(array[i]);
	}
	return totalCompras;
}

/*--------------query 8------ */

char** procurarComprasClienteAux(AVLCompras c, char* produto, char** clientes, int *i) {
	char *aux = malloc(sizeof(char)*10);
	char buf[3];

	if (c){
		procurarComprasClienteAux(c->esq,produto,clientes,i);
		if (strcmp(produto,c->produtos)==0) {
			buf[0]=' ';
			buf[1]=c->tipo_compra;
			buf[2]='\0';
			aux = strcat(c->clientes,buf);
			clientes[(*i)]=aux;
			(*i)++;
		}
		procurarComprasClienteAux(c->dir,produto,clientes,i);
	}
	return clientes;
}


char** procurarComprasCliente(AVLCompras c[], char* produto) {
	int k=0;
	int indice = produto[0] - 'A';

	char** s = malloc(sizeof(char*)*200000);
	s=procurarComprasClienteAux(c[indice],produto,s,&k);
	return s;
}
