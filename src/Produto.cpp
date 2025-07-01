#include "produto.h"
#include <stdio.h>
#include <string.h>


int encontrarProduto(Produto lista[], int qtdAtual, int codigoBusca) {
    for (int i = 0; i < qtdAtual; i++) {
        if (lista[i].id == codigoBusca) {
            return i; 
        }
    }
    return -1; 
}


void cadastrarNovoProduto(Produto lista[], int* qtdAtual) {
    if (*qtdAtual >= TAMANHO_MAXIMO) {
        printf("ERRO: Limite de produtos atingido!\n");
        return;
    }

    Produto novoItem;
    
    printf("\n--- CADASTRO DE NOVO PRODUTO ---\n");
    
    printf("Digite o codigo do produto: ");
    scanf("%d", &novoItem.id);


    if (encontrarProduto(lista, *qtdAtual, novoItem.id) != -1) {
        printf("ERRO: Ja existe um produto com este codigo!\n");
        return;
    }

    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", novoItem.descricao);

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &novoItem.quantidade);

    printf("Digite o valor unitario (R$): ");
    scanf("%f", &novoItem.valor);

  
    lista[*qtdAtual] = novoItem;
    (*qtdAtual)++;
    
    printf("Produto cadastrado com sucesso!\n");
}


void mostrarProdutosCadastrados(Produto lista[], int qtdAtual) {
    if (qtdAtual == 0) {
        printf("\nAVISO: Nao ha produtos cadastrados.\n");
        return;
    }

    printf("\n--- LISTA DE PRODUTOS (%d) ---\n", qtdAtual);
    for (int i = 0; i < qtdAtual; i++) {
        printf("COD: %d | Nome: %s | Estoque: %d | Preco: R$ %.2f\n",
               lista[i].id, lista[i].descricao,
               lista[i].quantidade, lista[i].valor);
    }
}


void removerProduto(Produto lista[], int* qtdAtual, int codigoRemover) {
    int posicao = encontrarProduto(lista, *qtdAtual, codigoRemover);
    
    if (posicao == -1) {
        printf("ERRO: Produto nao encontrado!\n");
        return;
    }


    for (int i = posicao; i < *qtdAtual - 1; i++) {
        lista[i] = lista[i + 1];
    }

    (*qtdAtual)--;
    printf("Produto removido com sucesso!\n");
}#include "produto.h" 
#include <string.h>


extern Produto produtos[100];
extern int totalProdutos;


int buscarProdutoPorCodigo(int codigo) {
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;  
}


void inserirProduto() {
    
    if (totalProdutos >= 100) {
        printf("Sistema atingiu o limite máximo de produtos!\n");
        return;
    }

    Produto novo;
    
    printf("\n--- NOVO CADASTRO DE PRODUTO ---\n");
    
   
    printf("Informe o código (6 dígitos): ");
    if (scanf("%d", &novo.codigo) != 1 || novo.codigo <= 0) {
        printf("Código inválido! Deve ser número positivo.\n");
        while (getchar() != '\n');  
        return;
    }

    
    if (buscarProdutoPorCodigo(novo.codigo) != -1) {
        printf("Erro: Código %d já está cadastrado!\n", novo.codigo);
        return;
    }

    
    printf("Nome do produto (max 30 caracteres): ");
    scanf(" %[^\n]30", novo.nome);  

    printf("Quantidade em estoque: ");
    if (scanf("%d", &novo.estoque) != 1 || novo.estoque < 0) {
        printf("Quantidade inválida! Deve ser número positivo.\n");
        while (getchar() != '\n');
        return;
    }

    printf("Preço unitário (R$): ");
    if (scanf("%f", &novo.preco) != 1 || novo.preco <= 0) {
        printf("Preço inválido! Deve ser valor positivo.\n");
        while (getchar() != '\n');
        return;
    }

   
    produtos[totalProdutos] = novo;
    totalProdutos++;
    
    printf("\n✅ Produto cadastrado com sucesso!\n");
}


void listarProdutos() {
    printf("\n--- RELATÓRIO DE PRODUTOS ---\n");
    
    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado no sistema.\n");
        return;
    }

    // Cabeçalho formatado
    printf("%-6s  %-30s  %-8s  %-10s\n", 
           "CÓDIGO", "PRODUTO", "ESTOQUE", "PREÇO");
    printf("--------------------------------------------\n");
    

    for (int i = 0; i < totalProdutos; i++) {
        printf("%06d  %-30s  %8d  R$ %7.2f\n",
               produtos[i].codigo,
               produtos[i].nome,
               produtos[i].estoque,
               produtos[i].preco);
    }
    
    printf("\nTotal de produtos cadastrados: %d\n", totalProdutos);
}