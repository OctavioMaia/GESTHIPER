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

/* Query 2
 * Esta função vai imprimir os códigos de todos
 * os produtos iniciados por uma determinada letra
 * passada como parametro.
 * Estes códigos irão ser impressos numa tabela, 
 * com dimensões passadas como parametros da função.
 * 
 */
char** imprimirProdutos(AVL clientes, char s, int *i,char **destino){
	AVL t = clientes;
	char *aux;

	if(t){ 
		imprimirProdutos(getEsq(t),s,i,destino);
		aux=getData(t);
		if(aux[0]==s){
			destino[(*i)]=malloc(sizeof(char)*7);
			destino[(*i)]=getData(t);
			(*i)++;
		}
	imprimirProdutos(getDir(t),s,i,destino);
	}
	return destino;
}