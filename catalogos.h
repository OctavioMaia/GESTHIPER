typedef struct nodo* catalogo;
typedef struct nodoCompras *comprasAux;

int validarLinha(char *linha,catalogo AVLClientes,catalogo AVLProdutos);
char** imprimirProdutos(catalogo produtos,char s,int *i,char **destino);
char** naoComprou(comprasAux array[],catalogo produtos,int *i,char** destino);
char** imprimirClientes(catalogo clientes, char s, int *i,char **destino);
char** procurarComprasClienteAux(comprasAux c, char* produto, char** clientes, int *i) ;
char** prodCompradoporClienteAux (comprasAux c, char* cliente, char** lista, int *i,int m) ;
char** procurarComprasCliente(comprasAux c[], char* produto) ;
char** getTotClientes(comprasAux c, int mes,char **dest,int *i) ;
char** clienteNaoComprouAux(comprasAux t,catalogo clientes,int *i,char** destino);
char** clienteNaoComprou(comprasAux array[],catalogo clientes,int *i,char** destino);
void imprimirLista(char **s,int c,int l);
void imprimirAux(char **s, int c , int l,int t, int pa);
int procurarLista(char cliente[], char** lista);