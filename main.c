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
	printf("Inseridos %d codigos válidos\n",inseridos );
}

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
	/*imprimirCompras(array[0]);*/

	printf("%f\n",getTotal(array,"UI1819",5));
	return 0;
}