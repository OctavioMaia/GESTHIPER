typedef struct nodoCompras *compras;

float getTotal(compras avl[],char codigo[], int m);
float getTotalP(compras avl,char codigo[], int m);
float getTotalN(compras avl,char codigo[], int m);
int* produtosCompradosAux(compras c, char* cliente, char** lista, int* quantidades,int *mes, int *i) ;
int calculaTotal(int *q,int *mes,int m);
int produtosComprados(compras c[], char* cliente,int m) ;
float getTot(compras avl, int m);
float totalLucroIntervalo(compras array[],int mesMin, int mesMax);
float getTotcompras(compras avl, int m);
int totalComprasIntervalo(compras array[],int mesMin, int mesMax);
int calculaMax(int *q,int n);
void ordena(char** s, int *q,int n);
int comparar(const void *a, const void *b) ; 
int* codMaisComprouMes(compras avl[] ,char cod_clientes[], int m,char** tmp);
int totalClientesIntervalo(compras array[],int mesMin, int mesMax);
void ordenaAno(char** s, int *q,int n);
