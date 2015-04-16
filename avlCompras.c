#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avl.h"
#include "avlCompras.h"

int tamanho_AVLCompras(AVLCompras t){
    if(t)
    	return 1 + (tamanho_AVLCompras(t->esq)+tamanho_AVLCompras(t->dir)); 
    else
        return 0;
}

int alturaCompras(AVLCompras t){
	return (t==NULL) ? 0 : t->altura;
}

int procurarProdutos(char s[], AVLCompras t){
	if(t==NULL)
		return 0;
	if(strcmp(s,t->produtos)<0) /*string menor, procura na esq*/
		return procurarProdutos(s,t->esq);
	else if(strcmp(s,t->produtos)>0) /*string maior procura na dir*/
		return procurarProdutos(s,t->dir);
	else	/*encontrou, ou seja strcmp(s,t->produtos)==0*/
		return 1; 
}

int Max(int a,int b){
	return a>b ? a:b;
}

AVLCompras rodarEsqUmaCompras(AVLCompras t){
	AVLCompras aux = NULL;

	aux = t->esq;
    t->esq = aux->dir;
    aux->dir = t;
 
    t->altura = Max( alturaCompras( t->esq ), alturaCompras( t->dir ) ) + 1;
    aux->altura = Max( alturaCompras( aux->esq ), t->altura ) + 1;
    return aux; /*nova raiz*/
}

AVLCompras rodarDirUmaCompras(AVLCompras t){
	AVLCompras aux;

	aux = t->dir;
    t->dir = aux->esq;
    aux->esq = t;
 
    t->altura = Max( alturaCompras(t->esq),alturaCompras(t->dir) ) + 1;
    aux->altura = Max( alturaCompras(aux->dir),t->altura) + 1;
    return aux; /*nova raiz*/
}

AVLCompras rodarEsqDuploCompras(AVLCompras t){
	t->esq = rodarDirUmaCompras(t->esq);

	return rodarEsqUmaCompras(t);
}

AVLCompras rodarDirDuploCompras(AVLCompras t){
	t->dir = rodarEsqUmaCompras(t->dir);

	return rodarDirUmaCompras(t);
}

AVLCompras inserirCompras(char s[], AVLCompras t){
	char produto[10];
	float preco;
	int unidades_compradas;
	char tipo;
	char cliente[10];
	int Mes;

	if( t == NULL ){
        t = (AVLCompras)malloc(sizeof(struct nodoCompras));
        if( t == NULL ){
            /*Não conseguimos alocar memoria! ERRO*/
            exit(1);
        }else{
        	sscanf(s,"%s %f %d %c %s %d",produto,&preco,&unidades_compradas,&tipo,cliente,&Mes);
            strcpy(t->produtos,produto);
            strcpy(t->clientes,cliente);
            t->lucro = (preco*unidades_compradas);
            t->quantidade=unidades_compradas;
            t->mes=Mes;
            t->tipo_compra=tipo;
            t->altura = 0;
            t->esq = t->dir = NULL;
        }
    }
	else if(strcmp(s,t->produtos)<0){ 				/*metemos na esq*/
		t->esq = inserirCompras(s,t->esq);
		if(alturaCompras(t->esq)-alturaCompras(t->dir) == 2){ /*duplamente pesado, invocar dupla rotacao!*/
			if(strcmp(s,t->esq->produtos)<0) 		/*metemos na esq*/
				t=rodarEsqUmaCompras(t);
			else 						
				t=rodarEsqDuploCompras(t);
		}
	}
	else if(strcmp(s,t->produtos)>0){ 				/*metemos na dir*/
		t->dir = inserirCompras(s,t->dir);
		if(alturaCompras(t->dir)-alturaCompras(t->esq) == 2){ /*duplamente pesado, invocar dupla rotacao!*/
			if(strcmp(s,t->dir->produtos)>0) 		/* metemos na dir*/
				t=rodarDirUmaCompras(t);
			else
				t=rodarDirDuploCompras(t); 	
		}
	}
	t->altura = Max(alturaCompras(t->esq),alturaCompras(t->dir)) +1;
	return t;
}

void imprimirCompras(AVLCompras t){
	AVLCompras temp = t;

	if(temp){
		imprimirCompras(temp->esq);
		printf("Produto: %s\n",temp->produtos);
		printf("Cliente: %s\n",temp->clientes);
		printf("Tipo compra: %c\n",temp->tipo_compra);
		printf("Mês: %d\n",temp->mes);
		printf("Lucro: %f\n",temp->lucro);
		printf("Quantidade: %d\n",temp->quantidade);
		printf("-----------------\n");
		imprimirCompras(temp->dir);
	}
}

float getTotal(AVLCompras avl[],char codigo[], int m){
	int indice = codigo[0] - 'A';
	return (getTotalP(avl[indice],codigo,m)+getTotalN(avl[indice],codigo,m));
}

float getTotalP(AVLCompras avl,char codigo[], int m){
	AVLCompras t = avl;
	if(t){
		if(t->tipo_compra=='P' && (t->mes)==m && (strcmp(codigo,t->produtos)==0)){
			return t->lucro+getTotalP(t->esq,codigo,m)+getTotalP(t->dir,codigo,m);
		}
		return getTotalP(t->esq,codigo,m)+getTotalP(t->dir,codigo,m);
	}
	return 0;
}

float getTotalN(AVLCompras avl,char codigo[], int m){
	AVLCompras t = avl;
	if(t){
		if(t->tipo_compra=='N' && (t->mes)==m && (strcmp(codigo,t->produtos)==0)){
			return t->lucro+getTotalN(t->esq,codigo,m)+getTotalN(t->dir,codigo,m);
		}
		return getTotalN(t->esq,codigo,m)+getTotalN(t->dir,codigo,m);
	}
	return 0;
}

/*-----------query6------------*/
void imprimirClientes(AVL clientes, char s, int *i){
	AVL t = clientes;
	if(islower(s))
		s=toupper(s);

	if(*i==8){ /*8 elementos por coluna*/
		printf("\n");;
		*i=0;
	}
	if(t){ 
		imprimirClientes(t->esq,s,i);
		if(t->data[0]==s){
			printf("%s ",t->data);
			(*i)++;
		}
	imprimirClientes(t->dir,s,i);
	}
}

/*--------------query7-----------*/

float getTot(AVLCompras avl, int m){
	AVLCompras t = avl;
	if(t){
		if((t->mes)==m){
			return t->lucro+getTot(t->esq,m)+getTot(t->dir,m);
		}
		return getTot(t->esq,m)+getTot(t->dir,m);
	}
	return 0;
}

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

int totalComprasIntervalo(AVLCompras array[],int mesMin, int mesMax){
	int i;
	int totalCompras=0;

	for(i=mesMin;i<=mesMax;i++){
		totalCompras+=tamanho_AVLCompras(array[i]);
	}
	return totalCompras;
}

/*--------------query 8------ */

char** procurarComprasClienteAux(AVLCompras c, char* produto, char** clientes, int *i) {
	char *aux = malloc(sizeof(char)*10);
	char buf[3];

	if (c){
		procurarComprasClienteAux(c->esq,produto,clientes,i);
		if (strcmp(produto,c->produtos)==0) {
			buf[0]=' ';
			buf[1]=c->tipo_compra;
			buf[2]='\0';
			aux = strcat(c->clientes,buf);
			clientes[(*i)]=aux;
			(*i)++;
		}
		procurarComprasClienteAux(c->dir,produto,clientes,i);
	}
	return clientes;
}


char** procurarComprasCliente(AVLCompras c[], char* produto) {
	int k=0;
	int indice = produto[0] - 'A';

	char** s = malloc(sizeof(char*)*200000);
	s=procurarComprasClienteAux(c[indice],produto,s,&k);
	return s;
}

/*------------QUERY 4---------*/
void naoComprou(AVLCompras array[],AVL produtos,int *i,char** destino){
	int indice;

	if(produtos){
		naoComprou(array,produtos->esq,i,destino);
		
		indice = produtos->data[0]-'A';
		if(array[indice])
			if(procurarProdutos(produtos->data,array[indice])==0){
				destino[(*i)] = malloc(sizeof(char)*6);
				destino[(*i)] = produtos->data;
				(*i)++;
			}

		naoComprou(array,produtos->dir,i,destino);
	}
}