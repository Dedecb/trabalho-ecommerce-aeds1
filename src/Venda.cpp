// Lógica #include "produto.h"
#include <stdio.h>

extern Produto produtos[100];
extern int totalProdutos;

void registrarVenda() {
    int codigo, qtd_venda;
    int posicao;
    float valor_total;
    
    printf("\n--- REGISTRO DE VENDA ---\n");
    
    // Solicita o código do produto
    printf("Informe o codigo do produto: ");
    scanf("%d", &codigo);
    
    // Busca o produto no estoque
    posicao = buscarProdutoPorCodigo(produtos, totalProdutos, codigo);
    
    // Verifica se o produto existe
    if (posicao == -1) {
        printf("AVISO: Produto nao encontrado no estoque!\n");
        return;
    }
    
    // Mostra informações do produto encontrado
    printf("Produto: %s\n", produtos[posicao].nome);
    printf("Estoque atual: %d unidades\n", produtos[posicao].estoque);
    printf("Preco unitario: R$ %.2f\n", produtos[posicao].preco);
    
    // Solicita a quantidade a vender
    printf("\nQuantidade desejada: ");
    scanf("%d", &qtd_venda);
    
    // Verifica se há estoque suficiente
    if (qtd_venda <= 0) {
        printf("ERRO: Quantidade invalida!\n");
        return;
    }
    
    if (qtd_venda > produtos[posicao].estoque) {
        printf("ERRO: Estoque insuficiente! (Disponivel: %d)\n", produtos[posicao].estoque);
        return;
    }
    
    // Calcula o valor total da venda
    valor_total = qtd_venda * produtos[posicao].preco;
    
    // Atualiza o estoque
    produtos[posicao].estoque -= qtd_venda;
    
    // Exibe o resumo da venda
    printf("\n--- VENDA REGISTRADA ---\n");
    printf("Produto: %s\n", produtos[posicao].nome);
    printf("Quantidade: %d\n", qtd_venda);
    printf("Valor unitario: R$ %.2f\n", produtos[posicao].preco);
    printf("TOTAL: R$ %.2f\n", valor_total);
    printf("Novo estoque: %d unidades\n", produtos[posicao].estoque);
}
