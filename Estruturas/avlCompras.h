typedef struct nodoCompras{
	char clientes[10];
	char produtos[10];
	char tipo_compra;
	int mes;
	float lucro;
	int quantidade;
	struct nodoCompras* esq;
	struct nodoCompras* dir;
	int altura;
}*AVLCompras;
 
int tamanho_AVLCompras(AVLCompras t);
AVLCompras inserirCompras(char s[], AVLCompras t);
int procurarProdutos(char s[], AVLCompras t);
void imprimirCompras(AVLCompras t);
float getTotal(AVLCompras avl[],char codigo[], int m);
float getTotalN(AVLCompras avl,char codigo[], int m);
float getTotalP(AVLCompras avl,char codigo[], int m);
float getTot(AVLCompras avl, int m);
float totalLucroIntervalo(AVLCompras array[],int mesMin, int mesMax);
int totalComprasIntervalo(AVLCompras array[],int mesMin, int mesMax);
char** procurarComprasClienteAux(AVLCompras c, char* produto, char** clientes, int *i);
char** procurarComprasCliente(AVLCompras c[], char* produto);