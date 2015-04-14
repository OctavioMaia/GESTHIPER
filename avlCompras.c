#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avlCompras.h"
#include "avl.h"

int tamanho_AVLCompras(AVLCompras t){
    if(t)
    	return 1 + (tamanho_AVLCompras(t->esq)+tamanho_AVLCompras(t->dir)); 
    else
        return 0;
}

int alturaCompras(AVLCompras t){
	return (t==NULL) ? 0 : t->altura;
}

int procurarCompras(char s[], AVLCompras t){
	if(t==NULL)
		return 0;
	if(strcmp(s,t->produtos)<0) /*string menor, procura na esq*/
		return procurarCompras(s,t->esq);
	else if(strcmp(s,t->produtos)>0) /*string maior procura na dir*/
		return procurarCompras(s,t->dir);
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
		printf("Cliente: %s\n",temp->clientes);
		printf("Produto: %s\n",temp->produtos);
		printf("Tipo compra: %c\n",temp->tipo_compra);
		printf("Mês: %d\n",temp->mes);
		printf("Lucro: %f\n",temp->lucro);
		printf("Quantidade: %d\n",temp->quantidade);
		printf("-----------------\n");
		imprimirCompras(temp->dir);
	}
}