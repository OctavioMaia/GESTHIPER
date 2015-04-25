typedef struct nodo* catalogo;
typedef struct nodoCompras *comprasAux;

/* validarlinha
 * Esta função verifica se uma linha de compras é valida.
 * Ou seja, verifica se o código de produto é valido, o número de unidades
 * compradas é maior que zero, o tipo de compra é 'P' (compra em promoção)
 * ou 'N' (compra normal), o código do cliente é válido e o mês da compra
 * é válido.
 */
int validarLinha(char *linha,catalogo AVLClientes,catalogo AVLProdutos);

/* imprimirProdutos
 * Esta função vai imprimir os códigos de todos
 * os produtos iniciados por uma determinada letra MAISCULA
 * passada como parametro.
 * Estes códigos irão ser impressos numa tabela
 */
char** imprimirProdutos(catalogo produtos,char s,int *i,char **destino);

/*naoComprou
 * Esta função determina a lista de códigos de produtos
 * que ninguem comprou.
 * A função procura se o código de um produto foi vendido, ou seja, 
 * verifica se existe o código de um produto na Compras. Se não 
 * existir guarda o código do produto.
 */
char** naoComprou(comprasAux array[],catalogo produtos,int *i,char** destino);

/* imprimirClientes
 * Esta função imprime a lista do código de todos
 * os clientes que se inicie por uma letra dada 
 * como parametro.
 */
char** imprimirClientes(catalogo clientes, char s, int *i,char **destino);

/* procurarComprasClienteAux
 * A função vai determinar os códigos dos clientes e a 
 * quantidade de clientes que compraram um determinado 
 * produto, diferenciado se a compra foi normal ('N') 
 * ou em promoção ('P').
 */
char** procurarComprasClienteAux(comprasAux c, char* produto, char** clientes, int *i) ;

/* prodCompradoporClienteAux
 * Esta função copia para uma string o código de 
 * um produto, quantas vezes esse produto tiver 
 * sido comprado.
 */
char** prodCompradoporClienteAux (comprasAux c, char* cliente, char** lista, int *i,int m) ;

/* procurarComprasCliente
 * A função vai determinar os códigos dos clientes e a 
 * quantidade de clientes que compraram um determinado 
 * produto, diferenciado se a compra foi normal ('N') 
 * ou em promoção ('P').
 */
char** procurarComprasCliente(comprasAux c[], char* produto);

/* getTotClientes
 * Esta função copia para uma string o código de um 
 * cliente se este tiver realizado alguma compra num
 * mes dado como parametro.
 */
char** getTotClientes(comprasAux c, int mes,char **dest,int *i);

/* clienteNaoComprouAux
 * Esta função auxilia a função clienteNaoComprou, copiando para 
 * uma string os codigos de clientes que não realizaram qualquer 
 * compra. */ 
char** clienteNaoComprouAux(comprasAux t,catalogo clientes,int *i,char** destino);

/* clienteNaoComprou
 * Esta função verifica se um cliente realizou compras,
 * se não tiver realizado copia o código do cliente para
 * um array.
 */
char** clienteNaoComprou(comprasAux array[],catalogo clientes,int *i,char** destino);

/* imprimirLista
 * Esta função vai calcular o numero de paginas 
 * que existem, e invoca a função auxiliar  
 * imprimirAux de maneira a permitir ao utilizador 
 * um modo de navegação pelos resultados.
 */
void imprimirLista(char **s,int c,int l);

/*onde esta isto?*/
void imprimirAux(char **s, int c , int l,int t, int pa);

/* procurarLista
 * Verifica se um cliente existe num array de clientes, retornando 1 se existir, 0 caso contrário.
 */
int procurarLista(char cliente[], char** lista);

/* comprouTodosMeses
 * Verifica se um cliente fez compras todos os meses,ou seja, percorre o array da lista dos meses em que um cliente fez compras e verifica se contêm todos os meses. 
 */
int comprouTodosMeses(int *lista);

/* procurarLista
 * Esta função compara */
int procurarLista(char cliente[], char** lista);

/* mesesComprouAux
 * Esta função guarda num array os meses em que um cliente dado como parametro fez compras(verifica para uma AVLCompras).
 */
int* mesesComprouAux(comprasAux c, char* cliente, int* lista, int *i);

/* mesComprou
 * Esta função guarda num array os meses em que um cliente dado como parametro fez compras (verifica para todas as AVLCompras).
 */
char** mesComprou(comprasAux array[],char *cliente,char **lista,int *i);

/* exec
 * Cria para todos os clientes um array com os meses em que fez compras.
 */
char** exec(comprasAux array[],catalogo t, char **lista,int *i);

