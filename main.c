#include <stdio.h>
#include <string.h>
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


AVL guardarValidar(FILE *fp,AVL Compras, AVL Produtos,AVL Clientes){ /*alterar para usar as novas AVLs*/
	char buf[40];
	char *buf2;
	/*int validos=0,invalidos=0;*/

	while(fgets(buf,40,fp)){
		buf2=strtok(buf,"\r\n");
		
		if(validarLinha(buf2,Clientes,Produtos)){ 
			/*Compras = inserir(buf2,Compras); inserir so apos ter a avl para compras
			validos++;*/
		}
		/*else 
			invalidos++;*/
	}
	return Compras;
}

AVLCompras guardarCodigosCompras(FILE *fp,AVLCompras t,AVL Clientes,AVL Produtos){
	char buf[40];
	char *buf2;
	int inseridos=0;

	while(fgets(buf,40,fp)){
		buf2=strtok(buf,"\r\n");
		if(validarLinha(buf2,Clientes,Produtos)){
			t = inserirCompras(buf2,t); 
			inseridos++;
		}
	}
	printf("Inserir %d codigos válidos\n",inseridos );
	return t;
}


void getTotal(AVLCompras t,char codigo[], int m){
	if(t){
		getTotal(t->esq,codigo,m);
		if(t->tipo_compra=='N' && (strcmp(codigo,t->produtos)==0) ){
			printf("N: %f\n",t->lucro);
		}
		if(t->tipo_compra=='P' && (strcmp(codigo,t->produtos)==0) ){
			printf("P: %f\n",t->lucro);
		}
		getTotal(t->dir,codigo,m);
	}
}

int main(){
	FILE *fprodutos = fopen("FichProdutos.txt","r");
	FILE *fclientes = fopen("FichClientes.txt","r");
	FILE *fcompras  = fopen("Compras.txt","r");
	AVL produtos = NULL;
	AVL clientes = NULL;
	AVLCompras compras  = NULL;

	produtos = guardarCodigos(fprodutos,produtos);
	clientes = guardarCodigos(fclientes,clientes);
	compras  = guardarCodigosCompras(fcompras,compras,clientes,produtos);
	
	getTotal(compras,"HF2710",1);

	/*printf("Tudo guardado e validado!\n");

	printf("Deseja procurar códigos? (y/n): ");
	scanf(" %c", &decisao);
	if(decisao=='y') displayCodigos(produtos);
	*/
	return 0;
}