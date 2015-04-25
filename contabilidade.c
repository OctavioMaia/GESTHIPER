#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estruturas/avl.h"
#include "Estruturas/avlCompras.h"
#include "catalogos.h"
#include "contabilidade.h"

/*--- query 3----*/ 
/* getTotal
 * Esta função dado um mês e um código de produto determina 
 * o total faturado com esse produto nesse mês.
 * Além do código do produto e dos mês, a função recebe 
 * a AVL com todos os códigos iniciados pela letra do 
 * produto desejado.
 */ 

float getTotal(Compras avl[],char codigo[], int m){
	int indice = codigo[0] - 'A';
	return (getTotalP(avl[indice],codigo,m)+getTotalN(avl[indice],codigo,m));
}

/* getTotalP
 * Esta função dado um mês e um código de produto determina 
 * o total faturado com esse produto em compras em promoção 
 * ou seja do tipo 'P' nesse mês.
 */ 
float getTotalP(Compras avl,char codigo[], int m){
	Compras t = avl;
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
float getTotalN(Compras avl,char codigo[], int m){
	Compras t = avl;
	if(t){
		if(getTipo(t)=='N' && (getMes(t))==m && (strcmp(codigo,getProd(t))==0)){
			return getLucro(t)+getTotalN(getEsqCompras(t),codigo,m)+getTotalN(getDirCompras(t),codigo,m);
		}
		return getTotalN(getEsqCompras(t),codigo,m)+getTotalN(getDirCompras(t),codigo,m);
	}
	return 0;
}

/*----------query 5--------*/
/* produtosCompradosAux
 * Esta função calcula a lista dos produtos comprados
 * por um cliente passado como parametro. 
 * Cada elemento da lista contem o código do produto e 
 * o mes em que foi comprado.
 */
int* produtosCompradosAux(Compras c, char* cliente, char** lista, int* quantidades,int *mes, int *i) {
	if (c){
		produtosCompradosAux(getEsqCompras(c),cliente,lista,quantidades,mes,i);
		if (strcmp(cliente,getClientes(c))==0 ) {
			lista[(*i)]=getProd(c);
			quantidades[(*i)]=getQuantidade(c);
			mes[(*i)]=getMes(c);
			(*i)++;	
		}
		produtosCompradosAux(getDirCompras(c),cliente,lista,quantidades,mes,i);
	}
	return quantidades;
}

/* produtosComprados
 * Esta função calcula a lista de todos os produtos
 * comprados mes a mes por um determinado cliente, 
 * passado como parametro.
 */

int calculaTotal(int *q,int *mes,int m){
	int i;
	int total=0;

	for(i=0;q[i]>0;i++){
		if(mes[i]==m){
			total+=q[i];
		}
	}
	return total;
}

int produtosComprados(Compras c[], char* cliente,int m) {
	int k=0;
	int i;
	int *q=malloc(sizeof(int)*10000);
	int *mes=malloc(sizeof(int)*10000);
	char** s = malloc(sizeof(char*)*200000);

	for(i=0;i<26;i++)
		produtosCompradosAux(c[i],cliente,s,q,mes,&k);
 	
	return calculaTotal(q,mes,m);
}

/*--------------query7-----------*/
/* getTot
 * Esta função determina o lucro total das compras de
 * um determinado mês passado como parametro.
 */
float getTot(Compras avl, int m){
	Compras t = avl;
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
float totalLucroIntervalo(Compras array[],int mesMin, int mesMax){
	int i,m;
	float totalLucro=0;

	for(i=0;i<26;i++){
		for(m=mesMin;m<=mesMax;m++){
			totalLucro+=getTot(array[i],m);	
		}
	}
	return totalLucro;
}

/*get compras*/
float getTotCompras(Compras avl, int m){
	Compras t = avl;
	if(t){
		if((getMes(t))==m){
			return 1+getTotCompras(getEsqCompras(t),m)+getTotCompras(getDirCompras(t),m);
		}
		return getTotCompras(getEsqCompras(t),m)+getTotCompras(getDirCompras(t),m);
	}
	return 0;
}

/* totalComprasIntervalo
 * Função que determina o total das compras
 * dado um intervalo fechado de meses.
 */
int totalComprasIntervalo(Compras array[],int mesMin, int mesMax){
	int i;
	int m;
	int totalCompras=0;

	for(i=0;i<26;i++){
		for(m=mesMin;m<=mesMax;m++){
			totalCompras+=getTotCompras(array[i],m);
		}
	}
	return totalCompras;
}

/*QUERY 9*/
/* calculaMx
 * Esta função calcula o máximo de uma função, devolvendo o indice
 * em que o máximo se encontra.
 */
int calculaMax(int *q,int n){
	int i;
	int max=0;

	for(i=1;i<n;i++){
		if(q[i]>q[max]){
			max=i;
		}
	}
	return max; /*devolve indice*/
}

/* ordena 
 * Esta função vai determinar qual o maior elemento no array e coloca esse 
 * valor a -1.
 */
void ordena(char** s, int *q,int n){
	int imax;

	while(imax=calculaMax(q,n),q[imax]!=-1){
		printf("Código: %s Quantidade: %d\n",s[imax],q[imax]);
		q[imax]=-1;
	}
}

/* comparar
 * compara duas strings
 */
int comparar(const void *a, const void *b) { 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;

    return strcmp(*ia, *ib);
}

/* codMaisComprouMes
 * Determina a lista dos produtos que um cliente mais comprou.
 */
int* codMaisComprouMes(Compras avl[] ,char cod_clientes[], int m,char** tmp){
	int i=0;
	int j=0;
	int indice;
	int len;
	int quantidade=1;
	int *quantidades=malloc(sizeof(int*)*10000);
	char **final=malloc(sizeof(char*)*100000);

	for(indice=0;indice<26;indice++)
		tmp= prodCompradoporClienteAux(avl[indice],cod_clientes,tmp,&i,m);
	
	len = sizeof(tmp) / sizeof(char *);
	qsort(tmp,len,sizeof(char*),comparar);

	for(i=0;tmp[i]!=NULL;i++){
		if(tmp[i]==tmp[i+1]){
			quantidade++;
		}
		if(tmp[i]!=tmp[i+1]){
			quantidades[j]=quantidade;
			final[j]=tmp[i];
			j++;
			quantidade=1;
		}
	}

	return quantidades;
}

/*query 11*/
/* totalClientesIntervalo
  * Calcula o numero de clientes que realizaram compras num intervalo de meses
  */
int totalClientesIntervalo(Compras array[],int mesMin, int mesMax){
	int i;
	int m;
	int k=0;
	int j=0;
	int len=0;
	char **s=malloc(sizeof(char*)*200000);
	char **tmp=malloc(sizeof(char*)*200000);

	for(i=0;i<26;i++){
		for(m=mesMin;m<=mesMax;m++){
			getTotClientes(array[i],m,s,&k);
		}
	}

	for(i=0;s[i];i++,len++);
	qsort(s,len,sizeof(char*),comparar);

	for(i=0;s[i];i++){
		if(procurarLista(s[i],tmp)==0){
			tmp[j]=s[i];
			j++;
		}
	}
	return j;
}

/*Query 13*/
void ordenaAno(char** s, int *q,int n){
	int imax;
	int conta=0;

	while(imax=calculaMax(q,n),q[imax]!=-1){
		if(conta<3){
			printf("Código: %s Quantidade: %d\n",s[imax],q[imax]);
			q[imax]=-1;
			conta++;
		}
		else
			break;
	}
}