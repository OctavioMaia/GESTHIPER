#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Estruturas/avl.h"
#include "Estruturas/avlCompras.h"

/*--- query 3----*/ 
/* getTotal
 * Esta função dado um mês e um código de produto determina 
 * o total faturado com esse produto nesse mês.
 * Além do código do produto e dos mês, a função recebe 
 * a AVL com todos os códigos iniciados pela letra do 
 * produto desejado.
 */ 

float getTotal(AVLCompras avl[],char codigo[], int m){
	int indice = codigo[0] - 'A';
	return (getTotalP(avl[indice],codigo,m)+getTotalN(avl[indice],codigo,m));
}

/* getTotalP
 * Esta função dado um mês e um código de produto determina 
 * o total faturado com esse produto em compras em promoção 
 * ou seja do tipo 'P' nesse mês.
 */ 
float getTotalP(AVLCompras avl,char codigo[], int m){
	AVLCompras t = avl;
	if(t){
		if(getTipo(t)=='P' && (getMes(t))==m && (strcmp(codigo,getProd(t))==0)){
			return getLucro(t)+getTotalP(getEsqCompras(t),codigo,m)+getTotalP(getDirCompras(t),codigo,m);
		}
		return getTotalP(getEsqCompras(t),codigo,m)+getTotalP(getDirCompras(t),codigo,m);
	}
	return 0;
}

/* getTotalN
 * Esta função dado um mês e um código de produto determina 
 * o total faturado com esse produto em compras em promoção 
 * ou seja do tipo 'N' nesse mês.
 */ 
float getTotalN(AVLCompras avl,char codigo[], int m){
	AVLCompras t = avl;
	if(t){
		if(getTipo(t)=='N' && (getMes(t))==m && (strcmp(codigo,getProd(t))==0)){
			return getLucro(t)+getTotalN(getEsqCompras(t),codigo,m)+getTotalN(getDirCompras(t),codigo,m);
		}
		return getTotalN(getEsqCompras(t),codigo,m)+getTotalN(getDirCompras(t),codigo,m);
	}
	return 0;
}

/*------------QUERY 4---------*/
/*naoComprou
 * Esta função determina a lista de códigos de produtos
 * que ninguem comprou.
 * A função procura se o código de um produto foi vendido, ou seja, 
 * verifica se existe o código de um produto na AVLCompras. Se não 
 * existir guarda o código do produto.
 */
char** naoComprou(AVLCompras array[],AVL produtos,int *i,char** destino){
	int indice;
    char *aux;
	if(produtos){
		naoComprou(array,getEsq(produtos),i,destino);  
		aux= getData(produtos);
		indice = aux[0]-'A';
		if(array[indice])
			if(procurarProdutos(getData(produtos),array[indice])==0){
				destino[(*i)] = malloc(sizeof(char)*7);
				destino[(*i)] = getData(produtos);
				(*i)++;
			}

		naoComprou(array,getDir(produtos),i,destino);
	}
	return destino;
}


/*-----------query6------------*/
/* imprimirClientes
 * Esta função imprime a lista do código de todos
 * os clientes que se inicie por uma letra dada 
 * como parametro.
 */
char** imprimirClientes(AVL clientes, char s, int *i,char **destino){
	AVL t = clientes;
	char *aux;
	if(islower(s)) s=toupper(s);

	if(t){ 
		imprimirClientes(getEsq(t),s,i,destino);
		aux=getData(t);
		if(aux[0]==s){
			destino[(*i)]=malloc(sizeof(char)*7);
			destino[(*i)]=aux;
			(*i)++;
		}
	imprimirClientes(getDir(t),s,i,destino);
	}
	return destino;
}

/*--------------query7-----------*/
/* getTot
 * Esta função determina o lucro total das compras de
 * um determinado mês passado como parametro.
 */
float getTot(AVLCompras avl, int m){
	AVLCompras t = avl;
	if(t){
		if((getMes(t))==m){
			return getLucro(t)+getTot(getEsqCompras(t),m)+getTot(getDirCompras(t),m);
		}
		return getTot(getEsqCompras(t),m)+getTot(getDirCompras(t),m);
	}
	return 0;
}

/* totalLucroIntervalo
 * Função que determina o lucro total das compras
 * dado um intervalo fechado de meses.
 * A função vai somando o lucro desde o primeiro 
 * mes do intervalo até ao ultimo, obtendo-se assim
 * o lucro total no intervalo.
 */
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

/* totalComprasIntervalo
 * Função que determina o total das compras
 * dado um intervalo fechado de meses.
 */
int totalComprasIntervalo(AVLCompras array[],int mesMin, int mesMax){
	int i;
	int totalCompras=0;

	for(i=mesMin;i<=mesMax;i++){
		totalCompras+=tamanho_AVLCompras(array[i]);
	}
	return totalCompras;
}

/*--------------query 8------ */
/* procurarComprasClienteAux
 * A função vai determinar os códigos dos clientes e a 
 * quantidade de clientes que compraram um determinado 
 * produto, diferenciado se a compra foi normal ('N') 
 * ou em promoção ('P').
 */
char** procurarComprasClienteAux(AVLCompras c, char* produto, char** clientes, int *i) {
	char *aux = malloc(sizeof(char)*10);
	char buf[3];

	if (c){
		procurarComprasClienteAux(getEsqCompras(c),produto,clientes,i);
		if (strcmp(produto,getProd(c))==0) {
			buf[0]=' ';
			buf[1]=getTipo(c);
			buf[2]='\0';
			aux = strcat(getClientes(c),buf);
			clientes[(*i)]=aux;
			(*i)++;
		}
		procurarComprasClienteAux(getDirCompras(c),produto,clientes,i);
	}
	return clientes;
}

/* procurarComprasCliente
 * A função vai determinar os códigos dos clientes e a 
 * quantidade de clientes que compraram um determinado 
 * produto, diferenciado se a compra foi normal ('N') 
 * ou em promoção ('P').
 */
char** procurarComprasCliente(AVLCompras c[], char* produto) {
	int k=0;
	int indice = produto[0] - 'A';

	char** s = malloc(sizeof(char*)*200000);
	s=procurarComprasClienteAux(c[indice],produto,s,&k);
	return s;
}

/*------------Query 14-------------------*
*- numero de clientes registados que não realizaram compras, não é complicado, é parecido com a 4 mas para
* clientes, descobre o erro e faz em 5 min, yes you can
*- numero de produtos que ninguem comprou (igual a query 4)*/
char** clienteNaoComprouAux(AVLCompras t,AVL clientes,int *i,char** destino){
    char *aux;
	if(clientes){
		aux=getData(clientes);
		clienteNaoComprouAux(t,getEsq(clientes),i,destino);  
		if(t){
			if(procurarProdutos(aux,t)){
				destino[(*i)] = malloc(sizeof(char)*7);
				destino[(*i)] = aux;
				(*i)++;
			}
		}
		clienteNaoComprouAux(t,getDir(clientes),i,destino);
	}
	return destino;
}

char** clienteNaoComprou(AVLCompras array[],AVL clientes,int *i,char** destino){
	int k=0;
	int indice;
	char **tmp= malloc(sizeof(char*)*1000000);

	for(indice=0;indice<26; indice++){
		tmp = clienteNaoComprouAux(array[indice],clientes,&k,destino);
	}
	return tmp;
}
