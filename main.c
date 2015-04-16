#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avl.h"
#include "avlCompras.h"

AVL guardarCodigos(FILE *fp,AVL t){
	char buf[10];
	char *buf2;
	int inseridos=0;

	while(fgets(buf,10,fp)){
		buf2=strtok(buf,"\r\n");
		t = inserir(buf2,t); 
		inseridos++;
	}
	return t;
}

void guardarCodigosCompras(FILE *fp,AVLCompras array[],AVL Clientes,AVL Produtos){
	char buf[40];
	char *buf2;
	int inseridos=0;
	int indice;
	int i;

	for(i=0;i<26;i++){
		array[i]=NULL;
	}

	while(fgets(buf,40,fp)){
		buf2=strtok(buf,"\r\n");
		if(validarLinha(buf2,Clientes,Produtos)){
			indice = buf2[0] - 'A';
			array[indice] = inserirCompras(buf2,array[indice]); 
			inseridos++;
		}
	}
	/*printf("Inseridos %d codigos válidos\n",inseridos );*/
}

/*------------QUERY 4---------*/
int naoComprouAux(AVLCompras t, char codigo[], int *i){
	if(t){
		naoComprouAux(t->esq,codigo,i);

		if(strcmp(t->produtos,codigo)==0) /*encontrei*/
			(*i)++;

		naoComprouAux(t->dir,codigo,i);
	}
	return *i;
}

void naoComprou(AVLCompras array[],AVL produtos, int *conta){
	int indice;
	char aux[10];
	int balde=0;

	if(produtos){
		naoComprou(array,produtos->esq);
		
		strcpy(aux,produtos->data);
		indice = aux[0]-'A';
		if(array[indice])
			if(naoComprouAux(array[indice],aux,&balde)==0)
				printf("%d\n",*conta++);

		naoComprou(array,produtos->dir);
	}
}

/*------------------*/

int main(){
	AVLCompras array[26];
	FILE *fprodutos = fopen("FichProdutos.txt","r");
	FILE *fclientes = fopen("FichClientes.txt","r");
	FILE *fcompras  = fopen("Compras.txt","r");
	AVL produtos = NULL;
	AVL clientes = NULL;

	produtos = guardarCodigos(fprodutos,produtos);
	clientes = guardarCodigos(fclientes,clientes);
	guardarCodigosCompras(fcompras,array,clientes,produtos);
	puts("Feito validacao e inserção");
	/*------------------QUERY 6 ----------------*/
	/*int i=0*/
	/*imprimirCompras(array[0]);*/
	/*imprimirClientes(clientes,'b',&i); */
	
	/*------------------QUERY 7 ----------------*/
	/*printf("Lucro: %f\n",totalLucroIntervalo(array,1,12)); */
	/*printf("Numero compras: %d\n",totalComprasIntervalo(array,1,12));*/


	/*-------------QUERY 8-----------*/
	/*int i;
	char** s= NULL;

	s=procurarComprasCliente(array,"PQ6219");
	for(i=0;s[i]!=NULL;i++) printf("Cliente/tipo de compra: %s\n",s[i]);
	*/

	/*---------query 4----------*/
		int conta=0;
	naoComprou(array,produtos,&conta);

	return 0;
}