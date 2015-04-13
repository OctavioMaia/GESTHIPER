#include <stdio.h>
#include <string.h>
#include "avl.h"

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


AVL guardarValidar(FILE *fp,AVL Compras, AVL Produtos,AVL Clientes){
	char buf[40];
	char *buf2;
	int inseridos=0;
	int validos=0,invalidos=0;

	while(fgets(buf,40,fp)){
		buf2=strtok(buf,"\r\n");
		Compras = inserir(buf2,Compras); 
		
		if(validarLinha(buf2,Clientes,Produtos)) 
			validos++;
		else 
			invalidos++;

		inseridos++;
	}
	return Compras;
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
	char decisao;

	printf("Deseja procurar códigos? (y/n): ");
	scanf(" %c", &decisao);

	if(decisao=='y'){
		printf("Introduza a letra a pesquisar (em maiuscula): ");
		scanf(" %c",&letra);
		imprimirLetra(t,letra,&i,&q);
		printf("\n");
	}
}

int main(){
	FILE *fprodutos = fopen("FichProdutos.txt","r");
	FILE *fclientes = fopen("FichClientes.txt","r");
	FILE *fcompras  = fopen("Compras.txt","r");
	AVL produtos = NULL;
	AVL clientes = NULL;
	AVL compras  = NULL;

	produtos = guardarCodigos(fprodutos,produtos);
	clientes = guardarCodigos(fclientes,clientes);
	compras  = guardarValidar(fcompras,compras,produtos,clientes);
	
	printf("Tudo guardado e validado!\n");
	displayCodigos(produtos);
	return 0;
}