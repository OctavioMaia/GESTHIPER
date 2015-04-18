#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estruturas/avl.h"

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