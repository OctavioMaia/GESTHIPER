#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Estruturas/avl.h"
#include "Estruturas/avlCompras.h"
#include "Estruturas/produtosUpdate.h"
#include "contabilidade.h"
#include "catalogos.h"

/* guardarCodigos
 * A função vai ler o ficheiro dos códigos dos clientes e dos Produtos armazenando os códigos num catalogo.
 */
Catalogo guardarCodigos(FILE *fp,Catalogo t){
	char buf[10], *buf2;
	while(fgets(buf,10,fp)){
		buf2=strtok(buf,"\r\n");
		t = inserir(buf2,t); 
	}
	return t;
}

/* guardarCodigosCompras
 * A função vai ler o ficheiro de compras e vai criar um array de 26 catalogos, cada uma correspondendo a uma
 * letra do alfabeto, sendo cada compra armazenda na Catalogo correspondente á primeira letra do código do produto.
 */
void guardarCodigosCompras(FILE *fp,Compras array[],Catalogo Clientes,Catalogo Produtos){
	char buf[40], *buf2;
	int indice, i;

	for(i=0;i<26;i++){
		array[i]=NULL;
	}
	while(fgets(buf,40,fp)){
		buf2=strtok(buf,"\r\n");
		if(validarLinha(buf2,Clientes,Produtos)){
			indice = buf2[0] - 'A';
			array[indice] = inserirCompras(buf2,array[indice]); 
		}
	}
}

/* guardarCodigosProdutos*/
ProdutosUpdate guardarCodigosProdutos(FILE *fp,ProdutosUpdate t,Catalogo Clientes, Catalogo Produtos){
	char buf[40];
	char *buf2;
	char produto[10];
	float preco;
	int unidades_compradas;
	char tipo;
	char cliente[10];
	int Mes;

	while(fgets(buf,40,fp)){
		buf2=strtok(buf,"\r\n");
		if(validarLinha(buf2,Clientes,Produtos)){
			sscanf(buf2,"%s %f %d %c %s %d",produto,&preco,&unidades_compradas,&tipo,cliente,&Mes);
			if(Procurar(produto,t)==1)
				update(t,produto,unidades_compradas);
			if(Procurar(produto,t)==0)
				t = inserirProdutos(buf2,t);
		}
	}
	return t;
}

void imprimirAux(char **s, int c , int l,int t, int pa) {
  	int j /*j vai ate ao numero de colunas*/, p; /*scanf da pagina a ler*/
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

void query2(Catalogo produtos){
	clock_t begin, end; /*Contadores de tempo de execucao para query 2*/
	double time_spent;
	int i=0;
	char ch, decisao;
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

void query3(Compras array[]){
	clock_t begin, end; /*Contadores de tempo de execucao para query 3*/
	double time_spent;
	char codigo[10];
	int mes, indice;
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
	char ch, decisao;
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
	int min, max;
	
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
	int mes, i;
	int j=0;
	
	printf("Introduza o codigo de cliente: ");
	scanf("%s",codigo);
	printf("Introduza o mês a pesquisar: ");
	scanf("%d",&mes);
	
	begin=clock();
	q=codMaisComprouMes(array,codigo,mes,s);
	for(i=0;s[i]!=NULL;i++){/*ELIMINA OS REPETIDOS*/
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

/*Funcao 10 funciona mas é MUITO lenta*/
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

void query12(ProdutosUpdate lista){
	clock_t begin, end; /*Contadores de tempo de execucao para query 12*/
	double time_spent;
	int valor=0;
	int i;
	int k;
	int n;
	int *q=malloc(sizeof(int)*2000000);
	int *aux=malloc(sizeof(int)*2000000);
	char **s=malloc(sizeof(char*)*2000000);
	
	printf("Introduza o numero de codigos que pretende verificar: ");
	scanf(" %d",&n);

	begin=clock();
	q=toStringProdutos(lista,s,q,aux,&valor);
	
	for(i=0;i<n;i++){
		k=calculaIndice(q);
		printf("%s",s[k]);
		printf(" %d",aux[k] );
		printf("\n");
	}

	end=clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC; 
	printf("Sucesso, demoramos %fs!\n",time_spent);
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
	char** q4= malloc(sizeof(char*)*200000); /*query 4*/
	
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

/* execQueries
 * Esta função permite escolher qual das queries o utilizador quer testar
 */
void execQueries(Compras array[],Catalogo produtos,Catalogo clientes,ProdutosUpdate lista){
	int i;
	printf("\n\033[1m Selecione a query que pretende testar(2-14): \033[0m  ");
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
     case 12 : query12(lista);     			     break; /*shit function INCOMPLETA*/
     case 13 : query13(array);                   break;
     case 14 : query14(array,produtos,clientes); break;
     default : printf("Query invalida\n");
  	}
  	execQueries(array,produtos,clientes,lista);
}

int main(){
	clock_t begin, end; /*Contadores de tempo de execucao para query 1*/
	double time_spent;
	char nome[10];

	FILE *fprodutos = fopen("Ficheiros/FichProdutos.txt","r");
	FILE *fclientes = fopen("Ficheiros/FichClientes.txt","r");
	FILE *fcompras;
	FILE *flista;
	Catalogo produtos = NULL;
	Catalogo clientes = NULL;
	ProdutosUpdate lista = NULL;

	printf("Por favor introduza o path do ficheiro compras e o seu respetivo nome.\nPor exemplo: Ficheiros/Compras3.txt : ");
	scanf("%s",nome);

	fcompras  = fopen(nome,"r");
	flista = fopen(nome,"r");

	begin = clock(); /*init contador*/
	produtos = guardarCodigos(fprodutos,produtos);
	clientes = guardarCodigos(fclientes,clientes);
	guardarCodigosCompras(fcompras,array,clientes,produtos);
	
	end = clock(); /*end contador*/
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC; /*tempo de exec query 1*/
	printf("Tudo guardado e validado em %fs!\n",time_spent);

	lista=guardarCodigosProdutos(flista,lista,clientes,produtos); /*esta lista contem apenas os codigos de produtos e a quantidade totais dos mesmos*/
	/*imprimirlista(lista);*/

    printf("\033[1m Query 2\033[0m  -  Lista e total de produtos cujo código se inicia por uma dada letra.\n");
	printf("\033[1m Query 3\033[0m  -  Número total de vendas e total faturado de um produto num mês.\n");
	printf("\033[1m Query 4\033[0m  -  Lista dos produtos que ninguem comprou.\n");
	printf("\033[1m Query 5\033[0m  -  Tabela com o nº total de produtos comprados por mês por um determinado cliente.\n");
	printf("\033[1m Query 6\033[0m  -  Lista de todos os produtos que se inicia por uma determinada letra.\n");
	printf("\033[1m Query 7\033[0m  -  Total de compras registadas e total faturado num intervalo de meses.\n");
    printf("\033[1m Query 8\033[0m  -  Códigos dos clientes que compraram um determinado produto.\n");
    printf("\033[1m Query 9\033[0m  -  Lista dos produtos de um cliente num determinado mês.\n");
    printf("\033[1m Query 10\033[0m - Lista dos clientes que realizaram compras em todos os meses do ano.\n");
    printf("\033[1m Query 11\033[0m - Ficheiro CSV contendo para cada mês o nº de compras e o nº de clientes que realizaram tais compras.\n");
    printf("\033[1m Query 12\033[0m - Lista dos N produtos mais vendidos em todo ano.\n");
    printf("\033[1m Query 13\033[0m - Três produtos que um cliente mais comprou durante o ano.\n");
    printf("\033[1m Query 14\033[0m - Número de clientes registados que nâo realizaram compras e o nº de produtos que ninguem comprou.\n");
	execQueries(array,produtos,clientes,lista); 
	return 0;
}