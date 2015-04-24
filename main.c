#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Estruturas/avl.h"
#include "Estruturas/avlCompras.h"


/* guardarCodigos
 * A função vai ler o ficheiro dos códigos dos 
 * Clientes e dos Produtos armazenando os códigos
 * numa Catalogo
 */
Catalogo guardarCodigos(FILE *fp,Catalogo t){
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
 * um array de 26 Catalogo, cada uma correspondendo a uma
 * letra do alfabeto, sendo cada compra armazenda na Catalogo 
 * correspondente á primeira letra do código do produto.
 */
void guardarCodigosCompras(FILE *fp,Compras array[],Catalogo Clientes,Catalogo Produtos){
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

void imprimirAux(char **s, int c , int l,int t, int pa) {
  	int j; /*j vai ate ao numero de colunas*/
 	int p; /*scanf da pagina a ler*/
 	int i=0;
 	int y=0;
 	char **aux = s;
 	char **atual;

 	printf("-------------------------Página %d--------------------------\n",pa+1);
	for (i=0;i<l && aux[y+1];i++){   
   		for (j=0;j<c && aux[y];j++,y++){
    		printf("%s\t", aux[y]);
   		}
	putchar('\n');
	}
   	printf("------------------------------------------------------------\n");
 	printf("Existem %d páginas. Página a verificar? (-1 para sair) ",t);	
    scanf(" %d",&p);
 	if (p==-1 || p > t || p==0)
 		printf("Exit!\n");
 	else{
 		atual=s+(p-1)*l*c-(pa*c*l);
 	    imprimirAux (atual,c,l,t,p-1);   
 	}
}

void imprimirLista(char **s,int c,int l) {
  int i = 0;
  int numpags;

  while (s[i]!='\0'){ /*calcula o numero de elems em s*/
    i++;
  } 

  numpags= i/(c*l);	 /*calcula o numero de paginas*/

  imprimirAux(s,c,l,numpags,0);
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
char** produtosCompradosAux(Compras c, char* cliente, char** lista, int *i) {
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
char** produtosComprados(Compras c[], char* cliente) {
	int k=0;
	int i;

	char** s = malloc(sizeof(char*)*200000);
	for(i=0;i<26;i++)
		s=produtosCompradosAux(c[i],cliente,s,&k);

	return s;
}

/*query 10 - MUITO LENTO!!*/
int comprouTodosMeses(int *lista){
	int i;
	int m1=0,m2=0,m3=0,m4=0,m5=0,m6=0,m7=0,m8=0,m9=0,m10=0,m11=0,m12=0;

	for(i=0;lista[i];i++){
		if(lista[i]==1) m1=1;
		if(lista[i]==2) m2=1;
		if(lista[i]==3) m3=1;
		if(lista[i]==4) m4=1;
		if(lista[i]==5) m5=1;
		if(lista[i]==6) m6=1;
		if(lista[i]==7) m7=1;
		if(lista[i]==8) m8=1;
		if(lista[i]==9) m9=1;
		if(lista[i]==10) m10=1;
		if(lista[i]==11) m11=1;
		if(lista[i]==12) m12=1;
	}
	return (m1 && m2 && m3 && m4 && m5 && m6 && m7 && m8 && m9 && m10 && m11 && m12);
}

int procurarLista(char cliente[], char** lista){
	int i;
	int valor=0;

	if(!lista || !cliente) return 0;

	for(i=0;lista[i];i++)
		if(strcmp(cliente,lista[i])==0){
			valor=1;
			break;
		}

	return valor;
}

int* mesesComprouAux(Compras c, char* cliente, int* lista, int *i) {
	if (c){
		mesesComprouAux(getEsqCompras(c),cliente,lista,i);
		if (strcmp(cliente,getClientes(c))==0) {  
			lista[(*i)]=getMes(c);				
			(*i)++;							
		}
		mesesComprouAux(getDirCompras(c),cliente,lista,i);
	}
	return lista;
}

char** mesComprou(Compras array[],char *cliente,char **lista,int *i){
	int indice;
	int k=0;
	int *temp=malloc(sizeof(int)*10000);

	if(cliente){
		for(indice=0;indice<26;indice++){
			if(!procurarLista(cliente,lista) && comprouTodosMeses(mesesComprouAux(array[indice],cliente,temp,&k))){
				lista[(*i)]=cliente;
				(*i)++;
			}
		}
	}	
	return lista;
}

char** exec(Compras array[],Catalogo t, char **lista,int *i){
	if(t){ 
		exec(array,getEsq(t),lista,i);
		mesComprou(array,getData(t),lista,i);
		exec(array,getDir(t),lista,i);
	}
	return lista;
}

/*QUERY 12 MT LENTO :(((( */
float getTotalQuantidadeAux(Compras avl,char *codigo){
	Compras t = avl;
	if(t){
		if(strcmp(getProd(avl),codigo)==0 && !strcmp(getProd(avl),codigo)>0){
			return getQuantidade(avl)+getTotalQuantidadeAux(getEsqCompras(t),codigo)+getTotalQuantidadeAux(getDirCompras(t),codigo);
		}
		return getTotalQuantidadeAux(getEsqCompras(t),codigo)+getTotalQuantidadeAux(getDirCompras(t),codigo);
	}
	return 0;
}

int getTotalQuantidade(Compras array[],char *codigo){
	int i;
	int totalCompras=0;
	i=codigo[0]-'A';

	totalCompras+=getTotalQuantidadeAux(array[i],codigo);
	
	return totalCompras;
}

/*int getTotalClientes(Compras c, char *produto,int *total){
	if(c){
		getTotalClientes(getEsqCompras(c),produto,total);
		if(c){
			if(strcmp(getProd(c),produto)==0){
				(*total)++;
			}
		}
		getTotalClientes(getDirCompras(c),produto,total);
	}
	return *total;
}*/


char** toStringProdutos(Catalogo produtos, char **dest, int*i){
	if(produtos){
		toStringProdutos(getEsq(produtos),dest,i);
		if(produtos){
			dest[(*i)]=getData(produtos);
			(*i)++;
		}
		toStringProdutos(getDir(produtos),dest,i);
	}
	return dest;
}

char** nMaisVendidos(Compras array[],Catalogo produtos){
	int i=0;
	int k;
	char **s=malloc(sizeof(char*)*200000);
	int *val=malloc(sizeof(int)*200000);

	toStringProdutos(produtos,s,&i);

	for(k=0;s[k];k++){
		val[k]=getTotalQuantidade(array,s[k]);
	}

	printf("Sucesso\n");

	return s;
}

/* Query 13 */
/* quais os 3 produtos mais comprados (por um cliente) durante o ano, neste momento apenas temos a imprimir 
*os produtos comprados por um cliente nesse ano (desculpa Octávio)*/
char** codMaisComprouAno (Compras avl[], char codigo[]){
	int k=0;
	int i=0;
	int mes;
	char **tmp= malloc(sizeof(char*)*100000);
	
	for(i=0;i<26;i++){
		for(mes=1;mes<=12;mes++){
			tmp = prodCompradoporClienteAux(avl[i],codigo,tmp,&k,mes);
		}
	}
	return tmp;
}

/*------------------*/
void query2(Catalogo produtos){
	int i=0;
	char ch;
	char decisao;
	char** s = malloc(sizeof(char*)*200000);
	printf("Introduza o caracter que pretende pesquisar: ");
	scanf(" %c",&ch);
	s=imprimirProdutos(produtos,ch,&i,s);

	printf("Sucesso! Deseja imprimir os resultados? (y/n) ");
	scanf(" %c",&decisao);
	if(decisao=='y')
		imprimirLista(s,5,4); /*5 colunas x 4 linhas*/
}

/*query 3*/
void query3(Compras array[]){
	char codigo[10];
	int mes;
	int indice;
	float totalN=0;
	float totalP=0;
	printf("Introduza o codigo de produto: ");
	scanf("%s",codigo);
	printf("Introduza o mês a pretendido: ");
	scanf("%d",&mes);

	indice=codigo[0]-'A';
	totalN=getTotalN(array[indice],codigo,mes);
	totalP=getTotalP(array[indice],codigo,mes);
	
	printf("Total faturado em modo N: %.2f\n",totalN);
	printf("Total faturado em modo P: %.2f\n",totalP);
	printf("Total faturado: %.2f\n",totalN+totalP);
}

int query4(Compras array[],Catalogo produtos){
	int i=0;
	int tamanho=0;
	char decisao;
	char** s = malloc(sizeof(char*)*200000);
	s=naoComprou(array,produtos,&i,s);

	for(i=0;s[i];i++)
		tamanho++;   
	
	printf("Sucesso! Exitem %d codigos que ninguem comprou.\n",tamanho);
	printf("Deseja imprimir os resultados? (y/n) ");
	scanf(" %c",&decisao);
	if(decisao=='y')
		imprimirLista(s,5,4); /*5 colunas x 4 linhas*/
	
	return tamanho;
}

void query5(Compras array[]){
	int i;
	char codigo[10];
	char** s = NULL;

	printf("Introduza o codigo de cliente: ");
	scanf("%s",codigo);
	s=produtosComprados(array,codigo);

	for(i=0;s[i]!=NULL;i++) 
		printf("produto/mes: %s\n",s[i]);
}


void query6(Catalogo clientes){
	int i=0;
	char ch;
	char decisao;
	char** s = malloc(sizeof(char*)*200000);
	printf("Introduza o caracter que pretende pesquisar: ");
	scanf(" %c",&ch);
	s=imprimirClientes(clientes,ch,&i,s);

	printf("Sucesso! Deseja imprimir os resultados? (y/n) ");
	scanf(" %c",&decisao);
	if(decisao=='y')
		imprimirLista(s,5,4); /*5 colunas x 4 linhas*/
}

void query7(Compras array[]){
	int min;
	int max;
	printf("Introduza o mês inicial da pesquisa: ");
	scanf(" %d",&min);
	printf("Introduza o mês final da pesquisa: ");
	scanf(" %d",&max);

	printf("Lucro: %f\n",totalLucroIntervalo(array,min,max)); 
	printf("Numero compras: %d\n",totalComprasIntervalo(array,min,max));
}

void query8(Compras array[]){
	int i;
	char codigo[10];
	char** s= NULL;

	printf("Introduza o codigo de produto: ");
	scanf("%s",codigo);
	s=procurarComprasCliente(array,codigo);

	for(i=0;s[i]!=NULL;i++) 
		printf("Cliente/tipo de compra: %s\n",s[i]);
}

void query9(Compras array[]){
	char** s= malloc(sizeof(char*)*200000);
	char** tmp = malloc(sizeof(char*)*200000);
	int* q=malloc(sizeof(int)*10000);
	char codigo[10];
	int mes;
	int i;
	int j=0;

	printf("Introduza o codigo de cliente: ");
	scanf("%s",codigo);
	printf("Introduza o mês a pesquisar: ");
	scanf("%d",&mes);

	q=codMaisComprouMes(array,codigo,mes,s);

	/*ELIMINA OS REPETIDOS*/
	for(i=0;s[i]!=NULL;i++){
		if(s[i]!=s[i+1]){
			tmp[j]=s[i];
			j++;
		}
	}

	ordena(tmp,q,j);

}

void query10(Compras array[],Catalogo clientes){
	int i=0;
	char** tmp = malloc(sizeof(char*)*200000);

	exec(array,clientes,tmp,&i);
	imprimirLista(tmp,1,10);
}

void query11(Compras array[],Catalogo clientes){
	int i;

	for(i=1;i<=12;i++)
		printf("Mês %d Numero de compras %d Numero de clientes %d\n",i,totalComprasIntervalo(array,i,i),totalClientesIntervalo(array,i,i));
}

void query12(Compras array[],Catalogo produtos){
	char **s=nMaisVendidos(array,produtos);


}

void query13(Compras array[]){
	char** tmp = malloc(sizeof(char*)*200000);
	char** s= malloc(sizeof(char*)*200000);
	int *quantidades=malloc(sizeof(int*)*10000);
	int quantidade=1;
	int i;
	int j=0;
	char codigo[10];

	printf("Introduza o codigo de cliente: ");
	scanf("%s",codigo);

	s=codMaisComprouAno(array,codigo);

	for(i=0;s[i]!=NULL;i++){
		if(s[i]==s[i+1]){
			quantidade++;
		}
		if(s[i]!=s[i+1]){
			quantidades[j]=quantidade;
			tmp[j]=s[i];
			j++;
			quantidade=1;
		}
	}

	j=0; /*reinicia o contador para apagar os repetidos*/
	/*ELIMINA OS REPETIDOS*/
	for(i=0;s[i]!=NULL;i++){
		if(s[i]!=s[i+1]){
			tmp[j]=s[i];
			j++;
		}
	}

	ordenaAno(tmp,quantidades,j);
}

void query14(Compras array[],Catalogo produtos,Catalogo clientes){
	int i=0;
	int tamanho=0;
	char** s = malloc(sizeof(char*)*200000);
	s=clienteNaoComprou(array,clientes,&i,s);

	for(i=0;s[i];i++)
		tamanho++;    
	
	printf("Numero de clientes que não compraram: %d\n",tamanho);
	printf("Numero de produtos que ninguem comprou: %d\n",query4(array,produtos));
}

void printIntro(){
	puts("\t #####  #######  #####  ####### #     # ### ######  ####### ###### ");
    puts("\t#     # #       #     #    #    #     #  #  #     # #       #     # ");
	puts("\t#       #       #          #    #     #  #  #     # #       #     # ");
	puts("\t#  #### #####    #####     #    #######  #  ######  #####   ######  ");
	puts("\t#     # #             #    #    #     #  #  #       #       #   # ");
	puts("\t#     # #       #     #    #    #     #  #  #       #       #    #   ");
	puts("\t #####  #######  #####     #    #     # ### #       ####### #     #" );
}

int main(){
	Compras array[26];
	FILE *fprodutos = fopen("Ficheiros/FichProdutos.txt","r");
	FILE *fclientes = fopen("Ficheiros/FichClientes.txt","r");
	FILE *fcompras  = fopen("Ficheiros/Compras.txt","r");
	Catalogo produtos = NULL;
	Catalogo clientes = NULL;

	printIntro();

	produtos = guardarCodigos(fprodutos,produtos);
	clientes = guardarCodigos(fclientes,clientes);
	guardarCodigosCompras(fcompras,array,clientes,produtos);
	puts("Tudo guardado e validado!");

	/*
	query2(produtos);
	query3(array);
	query4(array,produtos);
	query5(array); INCOMPLETA
	query6(clientes);
	query7(array);
	query8(array);
	query9(array);
	query13(array);
	query14(array,produtos,clientes);
	*/

	/*query10(array,clientes); MERDA DE FUNCAO*/

	/*query11(array,clientes); +- bem*/
	query12(array,produtos);

	return 0;
}