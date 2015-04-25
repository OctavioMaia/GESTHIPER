/* compras
 * Esta estrutura contém o 
 */
typedef struct nodoCompras *compras;

/* getTotal
 * Esta função dado um mês e um código de produto determina 
 * o total faturado com esse produto nesse mês.
 * Além do código do produto e dos mês, a função recebe 
 * a AVL com todos os códigos iniciados pela letra do 
 * produto desejado.
 */ 
float getTotal(compras avl[],char codigo[], int m);

/* getTotalP
 * Esta função dado um mês e um código de produto determina 
 * o total faturado com esse produto em compras em promoção 
 * ou seja do tipo 'P' nesse mês.
 */ 
float getTotalP(compras avl,char codigo[], int m);

/* getTotalN
 * Esta função dado um mês e um código de produto determina 
 * o total faturado com esse produto em compras em promoção 
 * ou seja do tipo 'N' nesse mês.
 */ 
float getTotalN(compras avl,char codigo[], int m);

/* produtosCompradosAux
 * Esta função calcula a lista dos produtos comprados
 * por um cliente passado como parametro. 
 * Cada elemento da lista contem o código do produto e 
 * o mes em que foi comprado.
 */
int* produtosCompradosAux(compras c, char* cliente, char** lista, int* quantidades,int *mes, int *i);

/* produtosComprados
 * Esta função calcula a lista de todos os produtos
 * comprados mes a mes por um determinado cliente, 
 * passado como parametro.
 */
int produtosComprados(compras c[], char* cliente,int m) ;

int calculaTotal(int *q,int *mes,int m);

/* getTot
 * Esta função determina o lucro total das compras de
 * um determinado mês passado como parametro.
 */
float getTot(compras avl, int m);

/* totalLucroIntervalo
 * Função que determina o lucro total das compras
 * dado um intervalo fechado de meses.
 * A função vai somando o lucro desde o primeiro 
 * mes do intervalo até ao ultimo, obtendo-se assim
 * o lucro total no intervalo.
 */
float totalLucroIntervalo(compras array[],int mesMin, int mesMax);
float getTotcompras(compras avl, int m);

/* totalComprasIntervalo
 * Função que determina o total das compras
 * dado um intervalo fechado de meses.
 */
int totalComprasIntervalo(compras array[],int mesMin, int mesMax);

/* calculaMax
 * Esta função calcula o máximo de uma função, devolvendo o indice
 * em que o máximo se encontra.
 */
int calculaMax(int *q,int n);

/* ordena 
 * Esta função vai determinar qual o maior elemento no array e coloca esse 
 * valor a -1.
 */
void ordena(char** s, int *q,int n);

/* comparar
 * compara duas strings
 */
int comparar(const void *a, const void *b) ; 

/* codMaisComprouMes
 * Determina a lista dos produtos que um cliente mais comprou.
 */
int* codMaisComprouMes(compras avl[] ,char cod_clientes[], int m,char** tmp);

/* totalClientesIntervalo
  * Calcula o numero de clientes que realizaram compras num intervalo de meses
  */
int totalClientesIntervalo(compras array[],int mesMin, int mesMax);
void ordenaAno(char** s, int *q,int n);
