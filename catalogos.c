#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Estruturas/avl.h"
#include "Estruturas/avlCompras.h"
#include "contabilidade.h"
#include "catalogos.h"

/* validarlinha
 * Esta função verifica se uma linha de compras é valida.
 * Ou seja, verifica se o código de produto é valido, o número de unidades
 * compradas é maior que zero, o tipo de compra é 'P' (compra em promoção)
 * ou 'N' (compra normal), o código do cliente é válido e o mês da compra
 * é válido.
 */
int validarLinha(char *linha,Catalogo AVLClientes,Catalogo AVLProdutos){
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
 * os produtos iniciados por uma determinada letra MAISCULA
 * passada como parametro.
 * Estes códigos irão ser impressos numa tabela
 */
char** imprimirProdutos(Catalogo produtos,char s,int *i,char **destino){
	Catalogo t = produtos;
	char *aux;

	if(t){ 
		imprimirProdutos(getEsq(t),s,i,destino);
		aux=getData(t);
		if(aux[0]==s){
			destino[(*i)]=malloc(sizeof(char)*7);
			destino[(*i)]=aux;
			(*i)++;
		}
	imprimirProdutos(getDir(t),s,i,destino);
	}
	return destino;
}

/*------------QUERY 4---------*/
/*naoComprou
 * Esta função determina a lista de códigos de produtos
 * que ninguem comprou.
 * A função procura se o código de um produto foi vendido, ou seja, 
 * verifica se existe o código de um produto na Compras. Se não 
 * existir guarda o código do produto.
 */
char** naoComprou(Compras array[],Catalogo produtos,int *i,char** destino){
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
char** imprimirClientes(Catalogo clientes, char s, int *i,char **destino){
	Catalogo t = clientes;
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

/*--------------query 8------ */
/* procurarComprasClienteAux
 * A função vai determinar os códigos dos clientes e a 
 * quantidade de clientes que compraram um determinado 
 * produto, diferenciado se a compra foi normal ('N') 
 * ou em promoção ('P').
 */
char** procurarComprasClienteAux(Compras c, char* produto, char** clientes, int *i) {
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


/*QUERY 9*/
/* prodCompradoporClienteAux
 * Esta função copia para uma string o código de 
 * um produto, quantas vezes esse produto tiver 
 * sido comprado.
 */
char** prodCompradoporClienteAux (Compras c, char* cliente, char** lista, int *i,int m) {
	int quantidade; 
	if (c){
		prodCompradoporClienteAux(getEsqCompras(c),cliente,lista,i,m);
		if (strcmp(cliente,getClientes(c))==0 && getMes(c)==m) {   
			quantidade=getQuantidade(c);
			while(quantidade>0){
				lista[(*i)]=getProd(c);			
				(*i)++;							
				quantidade--;
			}
		}
		prodCompradoporClienteAux(getDirCompras(c),cliente,lista,i,m);
	}
	return lista;
}

/* procurarComprasCliente
 * A função vai determinar os códigos dos clientes e a 
 * quantidade de clientes que compraram um determinado 
 * produto, diferenciado se a compra foi normal ('N') 
 * ou em promoção ('P').
 */
char** procurarComprasCliente(Compras c[], char* produto) {
	int k=0;
	int indice = produto[0] - 'A';

	char** s = malloc(sizeof(char*)*200000);
	s=procurarComprasClienteAux(c[indice],produto,s,&k);
	return s;
}

/*query 11*/
/* getTotClientes
 * Esta função copia para uma string o código de um 
 * cliente se este tiver realizado alguma compra num
 * mes dado como parametro.
 */
char** getTotClientes(Compras c, int mes,char **dest,int *i) {
	if (c){
		getTotClientes(getEsqCompras(c),mes,dest,i);
		if (getMes(c)==mes){
			dest[(*i)]=getClientes(c);
			(*i)++;
		}	
		getTotClientes(getDirCompras(c),mes,dest,i);
	}
	return dest;
}

/*------------Query 14-------------------*/
/* clienteNaoComprou
 * Esta função verifica se um cliente realizou compras,
 * se não tiver realizado copia o código do cliente para
 * um array.
 */

char** clienteNaoComprouAux(Compras t,CatalogoAux clientes,int *i,char** destino){
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

char** clienteNaoComprou(Compras array[],CatalogoAux clientes,int *i,char** destino){
	int k=0;
	int indice;
	char **tmp= malloc(sizeof(char*)*1000000);

	for(indice=0;indice<26; indice++){
		tmp = clienteNaoComprouAux(array[indice],clientes,&k,destino);
	}
	return tmp;
}

/* imprimirLista
 * Esta função vai calcular o numero de paginas 
 * que existem, e invoca a função auxiliar  
 * imprimirAux de maneira a permitir ao utilizador 
 * um modo de navegação pelos resultados.
 */
void imprimirLista(char **s,int c,int l) {
  int i = 0;
  int numpags;

  while (s[i]!='\0'){ /*calcula o numero de elems em s*/
    i++;
  } 

  numpags= i/(c*l);	 /*calcula o numero de paginas*/

  imprimirAux(s,c,l,numpags,0);
}
