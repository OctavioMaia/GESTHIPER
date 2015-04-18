#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estruturas/avl.h"

/* validarlinha
 * Esta função verifica se uma linha de compras é valida.
 * Ou seja, verifica se o código de produto é valido, o número de unidades
 * compradas é maior que zero, o tipo de compra é 'P' (compra em promoção)
 * ou 'N' (compra normal), o código do cliente é válido e o mês da compra
 * é válido.
 */

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
/* imprimir
 * Esta função imprime uma AVL.
 * Ou seja, vai receber como parametro uma AVL com 
 * os códigos dos produtos ou dos clientes e vai imprimir  
 * esses códigos para ser serem apresentados ao utilizador.
 */
void imprimir(AVL t){
	AVL temp = t;

	if(temp){
		imprimir(temp->esq);
		printf("%s\n",temp->data);
		imprimir(temp->dir);
	}
}

/* imprimirLetra
 * Esta função vai imprimir os códigos de todos
 * os produtos iniciados por uma determinada letra
 * passada como parametro.
 * Estes códigos irão ser impressos numa tabela, 
 * com dimensões passadas como parametros da função.
 * 
 */
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

/* displayCodigos
 * Esta função vai imprimir os códigos dos 
 * produtos iniciados por uma letra.
 */
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
