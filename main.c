#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Estruturas/avl.h"
#include "Estruturas/avlCompras.h"


/* guardarCodigos
 * A função vai ler o ficheiro dos códigos dos 
 * Clientes e dos Produtos armazenando os códigos
 * numa AVL
 */
AVL guardarCodigos(FILE *fp,AVL t){
	char buf[10];
	char *buf2;

	while(fgets(buf,10,fp)){
		buf2=strtok(buf,"\r\n");
		t = inserir(buf2,t); 
	}
	return t;
}

/* guardarCodigosCompras
 * A função vai ler o ficheiro de compras e vai criar 
 * um array de 26 AVL, cada uma correspondendo a uma
 * letra do alfabeto, sendo cada compra armazenda na AVL 
 * correspondente á primeira letra do código do produto.
 */
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


/*----------query 5--------*/
/* tostring
 * Esta função converte um inteiro numa string
 */
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

/* produtosCompradosAux
 * Esta função calcula a lista dos produtos comprados
 * por um cliente passado como parametro. 
 * Cada elemento da lista contem o código do produto e 
 * o mes em que foi comprado.
 */
char** produtosCompradosAux(AVLCompras c, char* cliente, char** lista, int *i) {
	char *aux = malloc(sizeof(char)*10);
	char *mes = malloc(sizeof(char)*3); 	/*guarda o mes e o \0*/

	if (c){
		produtosCompradosAux(getEsqCompras(c),cliente,lista,i);
		if (strcmp(cliente,getClientes(c))==0) {
			aux = getProd(c);				/*recebo o codigo produtos*/
			aux[6]=' ';						/*meto um espaço na ultima posicao*/
			aux[7]=tostring(mes,getMes(c));	/*na pos a seguir meto o mes em que o prod foi comprado*/
			aux[8]='\0';					/*termino a string com o \0*/

			lista[(*i)]=aux;				/*copio a string final*/
			(*i)++;							/*passo um indice a frente na string*/
		}
		produtosCompradosAux(getDirCompras(c),cliente,lista,i);
	}
	return lista;
}

/* produtosComprados
 * Esta função calcula a lista de todos os produtos
 * comprados mes a mes por um determinado cliente, 
 * passado como parametro.
 */
char** produtosComprados(AVLCompras c[], char* cliente) {
	int k=0;
	int i;

	char** s = malloc(sizeof(char*)*200000);
	for(i=0;i<26;i++)
		s=produtosCompradosAux(c[i],cliente,s,&k);

	return s;
}


/*query 9 - alterar output para compras inexistentes, ex mês>12*/
/*supostamente isto cria uma lista dos codigos de produtos que o dado cliente comprou e a quantidade para depois pegarmos nesta lista, juntarmos as quantidades dos mesmos produtos e ordernar mos
por ordem descendente (+ para -)*/

char** prodCompradoporClienteAux (AVLCompras c, char* cliente, char** lista, int *i,int m) {
	char *aux = malloc(sizeof(char)*11);
    char *quantidade = malloc(sizeof(int)*4); /*isto é para o caso de a quantidade apenas ter 3 caracteres!! e o \0*/
	if (c){
		prodCompradoporClienteAux(getEsqCompras(c),cliente,lista,i,m);
		if (strcmp(cliente,getClientes(c))==0 && getMes(c)==m) {   /*ATENÇÃO!! temos de somar as quantidades antes de fazer tostring da quantidade*/
			aux = getProd(c);				/*recebo o codigo produtos*/
			aux[6]=' ';						/*meto um espaço na ultima posicao*/
			aux[7]=tostring(quantidade, getQuantidade(c));	/*na pos a seguir meto a quantidade que o cliente comprou desse produto*/
			aux[8]='\0';					/*termino a string com o \0*/

			lista[(*i)]=aux;				/*copio a string final*/
			(*i)++;							/*passo um indice a frente na string*/
		}
		prodCompradoporClienteAux(getDirCompras(c),cliente,lista,i,m);
	}
	return lista;
}



char** codMaisComprouMes (AVLCompras avl[] ,char cod_clientes[], int m){
	int i=0;
	int indice;
	char **tmp= malloc(sizeof(char*)*100000);
	
	for(indice=0;indice<26;indice++)
		tmp= prodCompradoporClienteAux(avl[indice],cod_clientes,tmp,&i,m);
	
	return tmp;
}

/* Query 13 */
/* quais os 3 produtos mais comprados (por um cliente) durante o ano, neste momento apenas temos a imprimir 
*os produtos comprados por um cliente nesse ano (desculpa Octávio)*/

char** codMaisComprouAnoAux(AVLCompras c, char* cliente, char** lista, int *i) {
	char *aux = malloc(sizeof(char)*11);
	char *quantidade = malloc(sizeof(int)*4);
	if (c){
		codMaisComprouAnoAux(getEsqCompras(c),cliente,lista,i);
		if (strcmp(cliente, getClientes(c))==0) {  
			aux = getProd(c);				/*recebo o codigo produtos*/
			aux[6]=' ';
			aux[7]=tostring(quantidade,getQuantidade(c));
			aux[8]='\0';

			lista[(*i)]=aux;				/*copio a string final*/
			(*i)++;							/*passo um indice a frente na string*/
		}
		codMaisComprouAnoAux(getDirCompras(c),cliente,lista,i);
	}
	return lista;
}

char** codMaisComprouAno (AVLCompras avl[], char cod_clientes[]){
	int i=0;
	int indice;
	char **tmp= malloc(sizeof(char*)*10000);
	for(indice=0;indice<26; indice++)
		tmp = codMaisComprouAnoAux(avl[indice], cod_clientes, tmp,&i);

	return tmp;
}

/*maisComprado (char cod_clientes, int quantidade)*/
/*estava a pensar que se recebermos o produto e a quantidade numa lista, apenas tinhamos de 
* ver se havia produtos repetidos (para juntar as quantidades) e depois armazenar as 3 maiores quantidades
* enfim, pensamentos do alfredo*/


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

/*------------------*/

int query4(AVLCompras array[],AVL produtos){
	int i=0;
	int tamanho=0;
	char** s = malloc(sizeof(char*)*200000);
	naoComprou(array,produtos,&i,s);

	for(i=0;s[i];i++){
		/*printf(" %s\t",s[i]);*/
		tamanho++;   
	}
	return tamanho;
}

void query5(AVLCompras array[]){
	int i;
	char codigo[10];
	char** s = NULL;

	printf("Introduza o codigo de cliente: ");
	scanf("%s",codigo);
	s=produtosComprados(array,codigo);

	for(i=0;s[i]!=NULL;i++) 
		printf("produto/mes: %s\n",s[i]);
}

void query6(AVLCompras array[],AVL clientes){
	int i=0;
	char ch;
	printf("Introduza o caracter que pretende pesquisar: ");
	scanf(" %c",&ch);
	imprimirClientes(clientes,ch,&i);
	printf("\n");
}

void query7(AVLCompras array[]){
	int min;
	int max;
	printf("Introduza o mês inicial da pesquisa: ");
	scanf(" %d",&min);
	printf("Introduza o mês final da pesquisa: ");
	scanf(" %d",&max);

	printf("Lucro: %f\n",totalLucroIntervalo(array,min,max)); 
	printf("Numero compras: %d\n",totalComprasIntervalo(array,min,max));
}

void query8(AVLCompras array[]){
	int i;
	char codigo[10];
	char** s= NULL;

	printf("Introduza o codigo de produto: ");
	scanf("%s",codigo);
	s=procurarComprasCliente(array,codigo);

	for(i=0;s[i]!=NULL;i++) 
		printf("Cliente/tipo de compra: %s\n",s[i]);
}

void query9(AVLCompras array[]){
	char** s= NULL;
	int i;
	char codigo[10];
	printf("Introduza o codigo de cliente: ");
	scanf("%s",codigo);

	s=codMaisComprouAno(array,codigo);
	for(i=0;s[i]!=NULL;i++) 
		printf("Produto/quantidade: %s\n",s[i]);
}

void query14(AVLCompras array[],AVL produtos,AVL clientes){
	int i=0;
	int tamanho=0;
	char** s = malloc(sizeof(char*)*200000);
	s=clienteNaoComprou(array,clientes,&i,s);

	for(i=0;s[i];i++)
		tamanho++;    
	
	printf("Numero de clientes que não compraram: %d\n",tamanho);
	printf("Numero de produtos que ninguem comprou: %d\n",query4(array,produtos));
}


int main(){
	AVLCompras array[26];
	FILE *fprodutos = fopen("Ficheiros/FichProdutos.txt","r");
	FILE *fclientes = fopen("Ficheiros/FichClientes.txt","r");
	FILE *fcompras  = fopen("Ficheiros/Compras.txt","r");
	AVL produtos = NULL;
	AVL clientes = NULL;

	produtos = guardarCodigos(fprodutos,produtos);
	clientes = guardarCodigos(fclientes,clientes);
	guardarCodigosCompras(fcompras,array,clientes,produtos);
	puts("Feito validacao e inserção");

	/*query4(array,produtos)*/
	/*query5(array);*/
	/*query6(array,clientes);*/
	/*query7(array);*/
	/*query8(array);*/
	/*query9(array);*/
	
	/*query14(array,produtos,clientes);*/

	return 0;
}