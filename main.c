#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "avl.h"
#include "avlCompras.h"

AVL guardarCodigos(FILE *fp,AVL t){
	char buf[10];
	char *buf2;

	while(fgets(buf,10,fp)){
		buf2=strtok(buf,"\r\n");
		t = inserir(buf2,t); 
	}
	return t;
}

void guardarCodigosCompras(FILE *fp,AVLCompras array[],AVL Clientes,AVL Produtos){
	char buf[40];
	char *buf2;
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
			/*inseridos++;*/
		}
	}
	/*printf("Inseridos %d codigos válidos\n",inseridos );*/
}

/*----------query 4--------*/
void naoComprou(AVLCompras array[],AVL produtos,int *i,char** destino);


/*----------query 5--------*/
char tostring(char str[], int num){
    int i, resto, tamanho = 0, n=num; /*n=num, copia para usar no calculo do tamanho*/

    while (n != 0){		/*devolve o tamanho do numero, dividindo sempre por 10*/
        tamanho++;
        n /= 10;
    }

    for (i=0;i<tamanho;i++){
        resto = num % 10;
        num = num / 10; /*buscar o caracter a inserir, ex: 20, insere o 2*/
        str[tamanho - (i + 1)] = resto + '0'; /*converte de um int para char*/
    }
    str[tamanho] = '\0'; /*terminar a string*/
    return *str;
}

char** produtosCompradosAux(AVLCompras c, char* cliente, char** lista, int *i) {
	char *aux = malloc(sizeof(char)*10);
	char *mes = malloc(sizeof(char)*3); 	/*guarda o mes e o \0*/

	if (c){
		produtosCompradosAux(c->esq,cliente,lista,i);
		if (strcmp(cliente,c->clientes)==0) {
			aux = c->produtos;				/*recebo o codigo produtos*/
			aux[6]=' ';						/*meto um espaço na ultima posicao*/
			aux[7]=tostring(mes,c->mes);	/*na pos a seguir meto o mes em que o prod foi comprado*/
			aux[8]='\0';					/*termino a string com o \0*/

			lista[(*i)]=aux;				/*copio a string final*/
			(*i)++;							/*passo um indice a frente na string*/
		}
		produtosCompradosAux(c->dir,cliente,lista,i);
	}
	return lista;
}


char** produtosComprados(AVLCompras c[], char* cliente) {
	int k=0;
	int indice = cliente[0] - 'A';

	char** s = malloc(sizeof(char*)*200000);
	s=produtosCompradosAux(c[indice],cliente,s,&k);
	return s;
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
	/*
	int i=0;
	int tamanho=0;
	char** s = malloc(sizeof(char*)*200000);
	naoComprou(array,produtos,&i,s);

	for(i=0;s[i];i++){
		printf(" %s\t",s[i]);
		tamanho++;
	}
	printf("\nNumero de codigos que ninguem comprou: %d\n",tamanho);
	*/

	/*---------query 5----------*/
	int i;
	char** s= NULL;

	s=produtosComprados(array,"CQ626");

	for(i=0;s[i]!=NULL;i++) 
		printf("produto/mes: %s\n",s[i]);
	

	return 0;
}