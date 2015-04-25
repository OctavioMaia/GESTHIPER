#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
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

/* imprimirAux
 * Esta função auxilia a a função imprimirLista e permite 
 * imprimir no ecrã os resultados, em que pagina o 
 * utilizador se encontra, o numero de paginas total  
 * que existem e qual a decisão que quer tomar de seguida:
 * se pretende sair ou se pretende ir para outra pagina.
 */
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
			printf("%d\n", getQuantidade(avl));
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
		printf("%s %d\n",s[k],val[k]);
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
	clock_t begin, end; /*Contadores de tempo de execucao para query 2*/
	double time_spent;

	int i=0;
	char ch;
	char decisao;
	char** s = malloc(sizeof(char*)*200000);

	printf("Introduza o caracter que pretende pesquisar: ");
	scanf(" %c",&ch);

	begin = clock(); /*init contador*/
	s=imprimirProdutos(produtos,ch,&i,s);
	end = clock(); /*end contador*/
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 2*/

	printf("Sucesso, demoramos %fs! Deseja imprimir os resultados? (y/n) ",time_spent);
	scanf(" %c",&decisao);
	if(decisao=='y')
		imprimirLista(s,5,4); /*5 colunas x 4 linhas*/
}

/*query 3*/
void query3(Compras array[]){
	clock_t begin, end; /*Contadores de tempo de execucao para query 3*/
	double time_spent;

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

	begin = clock(); /*init contador*/
	totalN=getTotalN(array[indice],codigo,mes);
	totalP=getTotalP(array[indice],codigo,mes);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 3*/

	printf("Sucesso, demoramos %fs!\n",time_spent);
	printf("Total faturado em modo N: %.2f\n",totalN);
	printf("Total faturado em modo P: %.2f\n",totalP);
	printf("Total faturado: %.2f\n",totalN+totalP);
}

int query4(Compras array[],Catalogo produtos){
	clock_t begin, end; /*Contadores de tempo de execucao para query 4*/
	double time_spent;

	int i=0;
	int tamanho=0;
	char decisao;
	char** s = malloc(sizeof(char*)*200000);
	
	begin=clock();
	
	s=naoComprou(array,produtos,&i,s);
	
	end=clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 4*/

	for(i=0;s[i];i++)
		tamanho++;   

	printf("Sucesso, demoramos %fs! Exitem %d codigos que ninguem comprou.\n",time_spent,tamanho);
	printf("Deseja imprimir os resultados? (y/n) ");
	scanf(" %c",&decisao);
	if(decisao=='y')
		imprimirLista(s,5,4); /*5 colunas x 4 linhas*/
	
	return tamanho;
}

void query5(Compras array[]){
	clock_t begin, end; /*Contadores de tempo de execucao para query 5*/
	double time_spent;

	FILE *f;
	int i;
	char decisao;
	char codigo[10];
	int q[12];

	printf("Introduza o codigo de cliente: ");
	scanf("%s",codigo);

	begin=clock();
	for(i=0;i<12;i++)
		q[i]=produtosComprados(array,codigo,i+1);

	end=clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 5*/

	for(i=0;i<12;i++)
		printf("Mes %d Quantidade %d\n",i+1,q[i]);

	printf("\nSucesso, demoramos %fs! Deseja guardar para um ficheiro txt? (y/n) ",time_spent);
	scanf(" %c",&decisao);

	if(decisao=='y'){
		f = fopen("query5.txt", "w");
		for(i=0;i<12;i++)
			fprintf(f, "Mês: %d Quantidade: %d\n",i+1,q[i]);
	}
	printf("Sucesso!\n");
	fclose(f);
}


void query6(Catalogo clientes){
	clock_t begin, end; /*Contadores de tempo de execucao para query 6*/
	double time_spent;

	int i=0;
	char ch;
	char decisao;
	char** s = malloc(sizeof(char*)*200000);
	printf("Introduza o caracter que pretende pesquisar: ");
	scanf(" %c",&ch);

	begin=clock();
	s=imprimirClientes(clientes,ch,&i,s);
	
	end=clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 6*/

	printf("Sucesso, demoramos %fs! Deseja imprimir os resultados? (y/n) ",time_spent);
	scanf(" %c",&decisao);
	if(decisao=='y')
		imprimirLista(s,5,4); /*5 colunas x 4 linhas*/
}

void query7(Compras array[]){
	clock_t begin, end; /*Contadores de tempo de execucao para query 7*/
	double time_spent;

	int min;
	int max;
	printf("Introduza o mês inicial da pesquisa: ");
	scanf(" %d",&min);
	printf("Introduza o mês final da pesquisa: ");
	scanf(" %d",&max);

	begin=clock();
	printf("Lucro: %.2f\n",totalLucroIntervalo(array,min,max)); 
	printf("Numero compras: %d\n",totalComprasIntervalo(array,min,max));

	end=clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 7*/

	printf("Sucesso, demoramos %fs!\n",time_spent);
}

void query8(Compras array[]){
	clock_t begin, end; /*Contadores de tempo de execucao para query 8*/
	double time_spent;

	int i;
	char codigo[10];
	char** s= malloc(sizeof(char*)*10000);

	printf("Introduza o codigo de produto: ");
	scanf("%s",codigo);

	begin=clock();
	s=procurarComprasCliente(array,codigo);
	end=clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 8*/

	printf("Sucesso, demoramos %fs!\n",time_spent);

	for(i=0;s[i]!=NULL;i++) 
		printf("Cliente/tipo de compra: %s\n",s[i]);
}

void query9(Compras array[]){
	clock_t begin, end; /*Contadores de tempo de execucao para query 9*/
	double time_spent;

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

	begin=clock();
	q=codMaisComprouMes(array,codigo,mes,s);

	/*ELIMINA OS REPETIDOS*/
	for(i=0;s[i]!=NULL;i++){
		if(s[i]!=s[i+1]){
			tmp[j]=s[i];
			j++;
		}
	}
	ordena(tmp,q,j);
	end=clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 9*/

	printf("Sucesso, demoramos %fs!\n",time_spent);

}

void query10(Compras array[],Catalogo clientes){
	clock_t begin, end; /*Contadores de tempo de execucao para query 10*/
	double time_spent;

	int i=0;
	char** tmp = malloc(sizeof(char*)*200000);
	begin=clock();

	exec(array,clientes,tmp,&i);

	end=clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 10*/

	printf("Sucesso, demoramos %fs!\n",time_spent);

	imprimirLista(tmp,5,4);
}

void query11(Compras array[]){
	clock_t begin, end; /*Contadores de tempo de execucao para query 11*/
	double time_spent;

	FILE *f = fopen("query11.csv","w");
	int i;

	printf("Aguarde por favor...\n");

	begin=clock();
	fprintf(f,"Mês,#Compras,#Clientes\n");
	for(i=1;i<=12;i++)
			fprintf(f,"%d,%d,%d\n",i,totalComprasIntervalo(array,i,i),totalClientesIntervalo(array,i,i));

	end=clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 11*/

	printf("Sucesso, demoramos %fs!\n",time_spent);
	
	fclose(f);
}

void query12(Compras array[],Catalogo produtos){
	/*clock_t begin, end; Contadores de tempo de execucao para query 12
	double time_spent;

	int i;

	begin=clock();
	char **s=nMaisVendidos(array,produtos);

	end=clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC; tempo de exec query 12

	printf("Sucesso, demoramos %fs!\n",time_spent);
*/
}

void query13(Compras array[]){
	clock_t begin, end; /*Contadores de tempo de execucao para query 13*/
	double time_spent;

	char** tmp = malloc(sizeof(char*)*200000);
	char** s= malloc(sizeof(char*)*200000);
	int *quantidades=malloc(sizeof(int*)*10000);
	int quantidade=1;
	int i;
	int j=0;
	char codigo[10];

	printf("Introduza o codigo de cliente: ");
	scanf("%s",codigo);

	begin=clock();

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

	end=clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 13*/

	printf("Sucesso, demoramos %fs!\n",time_spent);

	ordenaAno(tmp,quantidades,j);
}

void query14(Compras array[],Catalogo produtos,Catalogo clientes){
	clock_t begin, end; /*Contadores de tempo de execucao para query 14*/
	double time_spent;

	int i=0;
	int k=0;
	int tamanho=0;
	int ninguemComprou=0;
	char** s = malloc(sizeof(char*)*200000);
	char** q4= malloc(sizeof(char*)*200000);

	begin=clock(); 
	s=clienteNaoComprou(array,clientes,&i,s);
	q4=naoComprou(array,produtos,&k,q4);

	for(i=0;s[i];i++)
		tamanho++;  

	for(i=0;q4[i];i++)
		ninguemComprou++;
	
	printf("Numero de clientes que não compraram: %d\n",tamanho);
	printf("Numero de produtos que ninguem comprou: %d\n",ninguemComprou);

	end=clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 14*/

	printf("Sucesso, demoramos %fs!\n",time_spent);
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

void execQueries(Compras array[],Catalogo produtos,Catalogo clientes){
	int i;
	printf("\nSelecione a query que pretende testar: (2-14) ");
    scanf(" %d", &i);
    switch (i){
     case 2  : query2(produtos);                 break;   	
     case 3  : query3(array);                    break;
     case 4  : query4(array, produtos);          break;
     case 5  : query5(array);                    break; 
     case 6  : query6(clientes);                 break;
     case 7  : query7(array);                    break;
     case 8  : query8(array);                    break;
     case 9  : query9(array);                    break;
     case 10 : query10(array, clientes);         break; /*shit function MAS FUNCIONA!*/
     case 11 : query11(array);		             break; 
     case 12 : query12(array, clientes);         break; /*shit function INCOMPLETA*/
     case 13 : query13(array);                   break;
     case 14 : query14(array,produtos,clientes); break;
     default : printf("Query invalida\n");
  	}
  	execQueries(array,produtos,clientes);
}

int main(){
	clock_t begin, end; /*Contadores de tempo de execucao para query 1*/
	double time_spent;
	char nome[10];

	FILE *fprodutos = fopen("Ficheiros/FichProdutos.txt","r");
	FILE *fclientes = fopen("Ficheiros/FichClientes.txt","r");
	FILE *fcompras;
	Catalogo produtos = NULL;
	Catalogo clientes = NULL;

	printf("Por favor introduza o path do ficheiro compras e o seu respetivo nome.\nPor exemplo: Ficheiros/Compras3.txt : ");
	scanf("%s",nome);

	fcompras  = fopen(nome,"r");

	printIntro(); /*print logotipo gesthiper*/

	begin = clock(); /*init contador*/
	produtos = guardarCodigos(fprodutos,produtos);
	clientes = guardarCodigos(fclientes,clientes);
	guardarCodigosCompras(fcompras,array,clientes,produtos);
	end = clock(); /*end contador*/

	time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 1*/
	printf("Tudo guardado e validado em %fs!",time_spent);

	execQueries(array,produtos,clientes);

	return 0;
}