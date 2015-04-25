typedef struct nodo* ProdutosUpdate;

char *getProduto(ProdutosUpdate a) ;
int getQuantidadeTotal(ProdutosUpdate a) ;
int Altura(ProdutosUpdate t);
int Procurar(char s[], ProdutosUpdate t);
int MAX(int a,int b);
int update(ProdutosUpdate t, char *s,int q);
void setQuantidadeTotal(ProdutosUpdate a,int n);
ProdutosUpdate rodarEsqUmaProdutos(ProdutosUpdate t);
ProdutosUpdate rodarDirUmaProdutos(ProdutosUpdate t);
ProdutosUpdate rodarEsqDuploProdutos(ProdutosUpdate t);
ProdutosUpdate rodarDirDuploProdutos(ProdutosUpdate t);
ProdutosUpdate inserirProdutos(char s[], ProdutosUpdate t);
ProdutosUpdate getEsquerda(ProdutosUpdate a);
ProdutosUpdate getDireita(ProdutosUpdate a);