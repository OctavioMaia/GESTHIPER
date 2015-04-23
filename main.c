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


/*query 9 */
int comparar(const void *a, const void *b) { 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;

    return strcmp(*ia, *ib);
}

char** prodCompradoporClienteAux (Compras c, char* cliente, char** lista, int *i,int m) {
	int quantidade; 
	if (c){
		prodCompradoporClienteAux(getEsqCompras(c),cliente,lista,i,m);
		if (strcmp(cliente,getClientes(c))==0 && getMes(c)==m) {   /*ATENÇÃO!! temos de somar as quantidades antes de fazer tostring da quantidade*/
			quantidade=getQuantidade(c);
			while(quantidade>0){
				lista[(*i)]=getProd(c);				/*copio a string final*/
				(*i)++;							/*passo um indice a frente na string*/
				quantidade--;
			}
		}
		prodCompradoporClienteAux(getDirCompras(c),cliente,lista,i,m);
	}
	return lista;
}

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

void ordena(char** s, int *q,int n){
	int imax;

	while(imax=calculaMax(q,n),q[imax]!=-1){
		printf("Código: %s Quantidade: %d\n",s[imax],q[imax]);
		q[imax]=-1;
	}

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

	/*query2(produtos);
	query3(array);
	query4(array,produtos);
	query5(array);
	query6(clientes);
	query7(array);
	query8(array);

	query9(array);
	query13(array);

	query14(array,produtos,clientes);*/

	return 0;
}