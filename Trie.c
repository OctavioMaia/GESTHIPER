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

void inserir(char *palavra,Trie raiz){

	Trie t=raiz;
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
		t=t->filhos[indice]; /*encontramos a letra*/
		t->data=nivel; /*atribuimos o nivel em que a palavra termina*/
	}
	t->data=nivel; /*atribuimos o nivel em que a palavra termina*/
}

void procurarProdutos(char *palavra,Trie raiz){
	Trie t = raiz;
	int i;
	int indice;
	int length=strlen(palavra);

	if(length!=6){
		printf("%s é um codigo de produto inválido\n",palavra);
		return;
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
	if(palavra[i]=='\0' && t->data!=-1 ) 	/*Encontramos a palavra, e vamos verificar se a posicao a seguir indica o '\0'*/
		printf("%s existe \n",palavra);
	else 
		printf("%s não existe \n",palavra); /*Não se verificou as condições a cima referidas, logo a palavra não existe*/
}

void procurarClientes(char *palavra,Trie raiz){
	Trie t = raiz;
	int i;
	int indice;
	int length=strlen(palavra);
	
	if(length!=5){
		printf("%s é um codigo de cliente inválido\n",palavra);
		return;
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
	if(palavra[i]=='\0' && t->data!=-1 ) 	/*Encontramos a palavra, e vamos verificar se a posicao a seguir indica o '\0'*/
		printf("%s existe \n",palavra);
	else 
		printf("%s não existe \n",palavra); /*Não se verificou as condições a cima referidas, logo a palavra não existe*/
}

void guardar(FILE *fp,Trie t){
	char buf[10];

	while(!feof(fp)){
		fgets(buf,10,fp);
		strtok(buf,"\n");
		inserir(buf,t);
	}
}

void validarCompras(FILE *fp){
 /*fazer um fscanf que leia cada linha e guarda cada variavel do ficheiro compras.txt e verifique se sao validas:
 - quantidade >0
 - preco >0
 - codigo produtos/clientes correto
 - o artigo so pode estar em promocao ou normal
 - ver se no enuncido e preciso validar + alguma coisa
 */
}

int main(){
	Trie produtos = criar();
	Trie clientes = criar();

    FILE *fprodutos = fopen("FichProdutos.txt","r");
    FILE *fclientes = fopen("FichClientes.txt","r");
    FILE *fcompras = fopen("Compras.txt","r");

    guardar(fprodutos,produtos);
    guardar(fclientes,clientes);
    
	procurarProdutos("DS9002",produtos);
	procurarClientes("DO601",clientes);
	
	validarCompras(fcompras);

	return 0;
}