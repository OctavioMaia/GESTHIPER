typedef struct nodoCompras *Compras;
typedef struct nodo *CatalogoAux; /*declaro isto pois nao posso usar o nome Catalogo, pois ja foi declarado!!*/
 
int tamanho_AVLCompras(Compras t);
int comparar(const void *a, const void *b);
Compras inserirCompras(char s[], Compras t);
int procurarProdutos(char s[], Compras t);
int procurarClientes(char s[], Compras t);
void imprimirCompras(Compras t);
float getTotal(Compras avl[],char codigo[], int m);
float getTotalN(Compras avl,char codigo[], int m);
float getTotalP(Compras avl,char codigo[], int m);
float getTot(Compras avl, int m);
float totalLucroIntervalo(Compras array[],int mesMin, int mesMax);
int totalComprasIntervalo(Compras array[],int mesMin, int mesMax);
char** procurarComprasClienteAux(Compras c, char* produto, char** clientes, int *i);
char** procurarComprasCliente(Compras c[], char* produto);

void ordena(char** s, int *q,int n);
void ordenaAno(char** s, int *q,int n);
char** prodCompradoporClienteAux (Compras c, char* cliente, char** lista, int *i,int m);
int* codMaisComprouMes(Compras avl[] ,char cod_clientes[], int m,char** tmp);

char** naoComprou(Compras array[],CatalogoAux produtos,int *i,char** destino);
char** clienteNaoComprouAux(Compras t,CatalogoAux clientes,int *i,char** destino);
char** clienteNaoComprou(Compras array[],CatalogoAux clientes,int *i,char** destino);

char** getTotClientes(Compras c, int mes,char **dest,int *i);
int totalClientesIntervalo(Compras array[],int mesMin, int mesMax);
int procurarLista(char cliente[], char** lista);

char *getClientes (Compras a);
char *getProd (Compras a);
char getTipo (Compras a);
int getMes (Compras a);
float getLucro (Compras a);
int getQuantidade (Compras a);
int getAlturaCompras(Compras a);
Compras getEsqCompras(Compras a);
Compras getDirCompras(Compras a);
