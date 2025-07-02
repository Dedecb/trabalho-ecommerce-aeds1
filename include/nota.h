#include <stdio.h>
#include <string.h>

typedef struct {
    
    int codigo;
    char nome[30];
    int estoque;
    float preco;

} Produto;

extern Produto produtos[100];
extern int totalProdutos;

int buscarProdutoPorCodigo(Produto lista[], int total, int codigo) {
    
    for (int i = 0; i < total; i++) {
        
        if (lista[i].codigo == codigo) {
            
            return i;
        }
    }
    
    return -1;
}

float calcularFrete(float totalVenda) {
    
    if (totalVenda <= 100.0) {
        
        return 30.0;
    } 
    else if (totalVenda <= 300.0) {
        
        return 20.0;
    } 
    else {
        
        return 0.0;
    }
}

void emitirNotaFiscal() {
    
    int codigo, qtd;
    int posicao;
    float totalProduto, frete, totalFinal;

    char nomeCliente[50];
    char cpf[15];
    char endereco[100];

    printf("\n----- EMISSAO DE NOTA FISCAL -----\n");

    printf("Nome do cliente: ");
    scanf(" %[^\n]", nomeCliente);

    printf("CPF do cliente: ");
    scanf(" %[^\n]", cpf);

    printf("Endereco completo: ");
    scanf(" %[^\n]", endereco);

    printf("Codigo do produto: ");
    scanf("%d", &codigo);

    posicao = buscarProdutoPorCodigo(produtos, totalProdutos, codigo);

    if (posicao == -1) {
        printf("Produto nao encontrado\n");
        
        return;
    }

    printf("Produto: %s | Preco: R$ %.2f | Estoque: %d\n", 
           produtos[posicao].nome, produtos[posicao].preco, produtos[posicao].estoque);

    printf("Quantidade desejada: ");
    scanf("%d", &qtd);

    if (qtd <= 0 || qtd > produtos[posicao].estoque) {
        printf("Erro: Quantidade invalida ou insuficiente no estoque\n");
        
        return;
    }

    totalProduto = qtd * produtos[posicao].preco;
    frete = calcularFrete(totalProduto);
    totalFinal = totalProduto + frete;

    produtos[posicao].estoque -= qtd;

    printf("\n========= NOTA FISCAL =========\n");
    printf("Cliente: %s\n", nomeCliente);
    printf("CPF: %s\n", cpf);
    printf("Endereco: %s\n", endereco);
    printf("-------------------------------\n");
    printf("Produto: %s\n", produtos[posicao].nome);
    printf("Codigo: %d\n", produtos[posicao].codigo);
    printf("Quantidade: %d\n", qtd);
    printf("Preco Unitario: R$ %.2f\n", produtos[posicao].preco);
    printf("Subtotal: R$ %.2f\n", totalProduto);
    printf("Frete: R$ %.2f\n", frete);
    printf("TOTAL A PAGAR: R$ %.2f\n", totalFinal);
    printf("===============================\n");
}