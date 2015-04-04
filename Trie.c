/*Trie*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Trie.h"

/*Cria um nodo com 26 elementos vazio*/
Trie criar(){
	int i;
	Trie t = (Trie)malloc(sizeof(struct nodo));
	for(i=0;i<TAMANHO;i++){
		t->filhos[i]=NULL;
		t->data=-1;
	}
	return t;
}

int inserir(char *palavra,Trie t){

	int length=strlen(palavra);
	int nivel;
	int indice;

	for(nivel=0;nivel<length;nivel++){
		/*
		Percorre o nivel ate encontrar um nivel cuja letra e diferente.
		Usamos o "-A" para devolver o indice, p.ex: A-A = 0
		Logo todos os codigos comecados por A estão no indice 0, e o Z-A no indice 26
		*/
		if(isalpha(palavra[nivel]))	indice = palavra[nivel]-'A'; /*Se palavra[nivel] for uma letra, usamos o metodo do -A*/
		else indice = (palavra[nivel] -'0')+10;					 /*Caso seja um numero retiramos 0 (zero) e adicionamos 10 para estarmos no indice 
														   		   pertencente aos digitos (0-26 -> alfabeto, 26-36-> digitos)*/

		if((t->filhos[indice])==NULL){
			/*Não encontramos a letra, logo vamos criar o nodo*/
			t->filhos[indice]=criar();
		}
		t=t->filhos[indice];  /*encontramos a letra*/
		t->data=nivel; 		  /*atribuimos o nivel em que a palavra termina*/
		t->ch=palavra[nivel]; /*atribui o caracter para depois imprimir-mos usando a funcao imprimir*/
	}
	t->data=nivel; /*atribuimos o nivel em que a palavra termina*/
	return 1;
}

int procurarProdutos(char *palavra,Trie raiz){
	Trie t = raiz;
	int i;
	int indice;
	int length=strlen(palavra);
	int valor;

	if(length!=6){
		/*printf("%s é um codigo de produto inválido\n",palavra);*/
		valor =0;
		return valor; /*talvez esteja mal*/
	}
	
	for(i=0;i<length;i++){
		/*
		Percorre o nivel ate encontrar um nivel cuja letra e diferente.
		Usamos o "-A" para devolver o indice, p.ex: A-A = 0
		Logo todos os codigos comecados por A estão no indice 0, e o Z-A no indice 26
		*/
		if(isalpha(palavra[i]))	indice = palavra[i]-'A'; /*Se palavra[nivel] for uma letra, usamos o metodo do -A*/
		else indice = (palavra[i] -'0')+10;		 		 /*Caso seja um numero retiramos 0 (zero) e adicionamos 10 para estarmos no indice 
														   pertencente aos digitos (0-26 -> alfabeto, 26-36-> digitos)*/

		if(t->filhos[indice]!=NULL)
			/*Não encontramos a letra, logo vamos criar o nodo*/
			t=t->filhos[indice];
		else 
			break; /*Como o indice para essa letra ja foi criado paramos o ciclo*/
	}
	if(palavra[i]=='\0' && t->data!=-1 ) valor=1;	/*Encontramos a palavra, e vamos verificar se a posicao a seguir indica o '\0'*/
	else valor=0;						   		    /*Não se verificou as condições a cima referidas, logo a palavra não existe*/

	return valor;
}

int procurarClientes(char *palavra,Trie raiz){
	Trie t = raiz;
	int i;
	int indice;
	int length=strlen(palavra);
	int valor;
	
	if(length!=5){
		/*printf("%s é um codigo de cliente inválido\n",palavra);*/
		valor = 0;
		return valor;
	}

	for(i=0;i<length;i++){
		/*
		Percorre o nivel ate encontrar um nivel cuja letra e diferente.
		Usamos o "-A" para devolver o indice, p.ex: A-A = 0
		Logo todos os codigos comecados por A estão no indice 0, e o Z-A no indice 26
		*/
		if(isalpha(palavra[i]))	indice = palavra[i]-'A'; /*Se palavra[nivel] for uma letra, usamos o metodo do -A*/
		else indice = (palavra[i] -'0')+10;		 		 /*Caso seja um numero retiramos 0 (zero) e adicionamos 10 para estarmos no indice 
														   pertencente aos digitos (0-26 -> alfabeto, 26-36-> digitos)*/

		if(t->filhos[indice]!=NULL)
			/*Não encontramos a letra, logo vamos criar o nodo*/
			t=t->filhos[indice];
		else 
			break; /*Como o indice para essa letra ja foi criado paramos o ciclo*/
	}
	if(palavra[i]=='\0' && t->data!=-1) valor=1; 	/*Encontramos a palavra, e vamos verificar se a posicao a seguir indica o '\0'*/
	else valor=0;

	return valor; 						    		/*Não se verificou as condições a cima referidas, logo a palavra não existe*/
}

void guardar(FILE *fp,Trie t){
	char buf[10];
	int inseridos=0;
	while(fgets(buf,10,fp)){
		strtok(buf,"\n");
		inserir(buf,t);
		inseridos++;
	}
	printf("Inseridos %d códigos\n",inseridos);
}

int validarLinha(char* linha,Trie TrieClientes, Trie TrieProdutos){
	char produto[10];
	float preco;
	int unidades_compradas;
	char tipo_compra;
	char cliente[10];
	int mes;

	sscanf(linha,"%s %f %d %c %s %d",produto,&preco,&unidades_compradas,&tipo_compra,cliente,&mes);

	if(!procurarProdutos(produto,TrieProdutos) || preco<0 || unidades_compradas<0 || (tipo_compra!='N' && tipo_compra!='P') || !procurarClientes(cliente,TrieClientes) || (mes<1 || mes>12)) return 0;
		
	return 1;
}

void validarCompras(FILE *fp,Trie TrieClientes, Trie TrieProdutos){
	char buf[30];
	int validos=0,invalidos=0;

	while(fgets(buf,30,fp)){
		strtok(buf,"\r\n");
		if(validarLinha(buf,TrieClientes,TrieProdutos)) validos++;
		else invalidos++;
	}
	printf("Compras válidas: %d\n",validos);
	printf("Compras inválidas: %d\n",invalidos);
}

void imprimir(Trie t/*,char ch*/){
	/*int indice = (int)abs('A'-ch);
	
	if((t->filhos[indice]->ch)==ch){
		printf("debugmaster\n");
		imprimirAux(t->filhos[indice]);
	}*/
	int i=1;
	Trie temp = t->filhos[i];
	
	while(temp!=NULL){
		printf("%c",temp->ch);
		i++;
		temp = t->filhos[i++];	
		imprimir(temp);
	}
	printf("\n");
}

/*
void imprimirAux(Trie t){
	int indice=0;

	if(isdigit(t->filhos[indice]->ch)){
		printf("debug1\n");
		printf("%d\n",t->filhos[indice]->ch);
		imprimirAux(t->filhos[indice++]);
	}
	else if(!isdigit(t->filhos[indice]->ch)){
		printf("debug2\n");
		printf("%c\n",t->filhos[indice]->ch);
		imprimirAux(t->filhos[indice]);
	}
	else
		printf("erros\n");
}
*/
int main(){
	Trie produtos = criar();
	Trie clientes = criar();
	Trie teste = criar();

    FILE *fprodutos = fopen("FichProdutos.txt","r");
    FILE *fclientes = fopen("FichClientes.txt","r");
    FILE *fcompras  = fopen("Compras.txt","r");
   	FILE *fteste = fopen("teste.txt","r");
    /*guardar(fprodutos,produtos);
    guardar(fclientes,clientes);
	validarCompras(fcompras,clientes,produtos);*/
	guardar(fteste,teste);
	imprimir(teste);

	return 0;
}