
#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct {
    int codigo;
    char nome[30];
    int estoque;
    float preco;
} Produto;

extern Produto produtos[100];
extern int totalProdutos;

void cadastrarProduto();
int buscarProdutoPorCodigo(Produto lista[], int total, int codigo);
float calcularFrete(float totalVenda);
void emitirNotaFiscal();

#endif
