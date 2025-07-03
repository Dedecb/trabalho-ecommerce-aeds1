#include "notaFiscal.h"
#include <stdio.h>
#include <string.h>

/**
 * @file notaFiscal.c
 * @brief Implementação das funções para emissão de nota fiscal e cálculo de frete.
 *
 * Este arquivo contém a lógica para realizar uma venda, o que inclui buscar
 * produtos, validar estoque, calcular o valor total com frete, atualizar o
 * estoque e, por fim, exibir uma nota fiscal simplificada para o cliente.
 * Ele depende diretamente do módulo de produtos para acessar a lista de
 * produtos disponíveis.
 */

//================================================================================
// Implementação das Funções
//================================================================================

/**
 * @brief Calcula o valor do frete com base no valor total da venda.
 *
 * A política de frete é a seguinte:
 * - Vendas até R$ 100.00: Frete de R$ 30.00
 * - Vendas entre R$ 100.01 e R$ 300.00: Frete de R$ 20.00
 * - Vendas acima de R$ 300.00: Frete grátis (R$ 0.00)
 *
 * @param totalVenda O subtotal da venda (soma dos preços dos produtos).
 * @return O valor do frete a ser cobrado.
 */
float calcularFrete(float totalVenda) {
    if (totalVenda <= 100.0) {
        return 30.0;
    }
    else if (totalVenda <= 300.0) {
        return 20.0;
    }
    else {
        return 0.0; // Frete grátis
    }
}

/**
 * @brief Conduz o processo de venda e emite uma nota fiscal na tela.
 *
 * Esta função é interativa. Ela solicita os dados do cliente e os detalhes
 * do produto a ser comprado. Em seguida, busca o produto no sistema, valida a
 * quantidade em estoque, calcula os totais (subtotal, frete e total final),
 * atualiza o estoque do produto e imprime a nota fiscal formatada.
 *
 * @note Esta função modifica o estado do sistema ao dar baixa no estoque do
 * produto vendido.
 */
void emitirNotaFiscal() {
    int codigo, qtd;
    int posicao;
    float totalProduto, frete, totalFinal;

    char nomeCliente[50];
    char cpf[15];
    char endereco[100];

    printf("\n----- EMISSAO DE NOTA FISCAL -----\n");

    // Coleta dos dados do cliente
    printf("Nome do cliente: ");
    scanf(" %[^\n]", nomeCliente);

    printf("CPF do cliente: ");
    scanf(" %[^\n]", cpf);

    printf("Endereco completo: ");
    scanf(" %[^\n]", endereco);

    // Coleta dos dados do produto
    printf("Codigo do produto: ");
    scanf("%d", &codigo);

    // Busca o produto usando a função do módulo de produtos
    posicao = buscarProdutoPorCodigo(produtos, totalProdutos, codigo);

    if (posicao == -1) {
        printf("Produto nao encontrado\n");
        return;
    }

    printf("Produto: %s | Preco: R$ %.2f | Estoque: %d\n",
           produtos[posicao].nome, produtos[posicao].preco, produtos[posicao].estoque);

    printf("Quantidade desejada: ");
    scanf("%d", &qtd);

    // Validação da quantidade
    if (qtd <= 0 || qtd > produtos[posicao].estoque) {
        printf("Erro: Quantidade invalida ou insuficiente no estoque\n");
        return;
    }

    // Cálculos da venda
    totalProduto = qtd * produtos[posicao].preco;
    frete = calcularFrete(totalProduto);
    totalFinal = totalProduto + frete;

    // Efetiva a venda dando baixa no estoque
    produtos[posicao].estoque -= qtd;

    // Impressão da Nota Fiscal
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