#include "produto.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>

/**
 * @file produto.cpp
 * @brief Implementação das funções para gerenciar o cadastro de produtos.
 *
 * Este arquivo contém a lógica para cadastrar e buscar produtos.
 * O armazenamento dos dados é feito através de um array global de tamanho fixo,
 * e as funções manipulam diretamente este array.
 */

//================================================================================
// Variáveis Globais
//================================================================================

Produto produtos[100];      /**< Array global para armazenar os dados dos produtos. */
int totalProdutos = 0;      /**< Contador do número atual de produtos cadastrados. */

//================================================================================
// Implementação das Funções
//================================================================================

/**
 * @brief Busca um produto em um array com base no seu código.
 *
 * Realiza uma busca linear no array fornecido.
 *
 * @param lista O array de produtos onde a busca será realizada.
 * @param total O número de produtos atualmente no array.
 * @param codigo O código do produto a ser encontrado.
 * @return O índice do produto no array se for encontrado; caso contrário, retorna -1.
 */
int buscarProdutoPorCodigo(Produto lista[], int total, int codigo) {
    for (int i = 0; i < total; i++) {
        if (lista[i].codigo == codigo) {
            return i; // Retorna o índice se o código for encontrado
        }
    }
    return -1; // Retorna -1 se o produto não for encontrado
}

/**
 * @brief Gerencia o cadastro interativo de um novo produto.
 *
 * Solicita os dados do produto ao usuário, valida se o código já existe e se
 * há espaço no array. Se todas as condições forem satisfeitas, adiciona o novo
 * produto ao array global 'produtos' e incrementa o contador 'totalProdutos'.
 */
void cadastrarProduto() {
    // Verifica se o limite de produtos foi atingido
    if (totalProdutos >= 100) {
        std::cout << "ERRO: Limite maximo de produtos atingido!" << std::endl;
        return;
    }

    Produto novo_produto;
    std::cout << "\n--- CADASTRO DE NOVO PRODUTO ---" << std::endl;

    std::cout << "Informe o codigo: ";
    std::cin >> novo_produto.codigo;

    // Limpa o buffer de entrada para evitar erros na próxima leitura
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Verifica se já existe um produto com este código
    if (buscarProdutoPorCodigo(produtos, totalProdutos, novo_produto.codigo) != -1) {
        std::cout << "ERRO: Codigo de produto ja existente!" << std::endl;
        return;
    }

    // A struct Produto parece usar um array de char, por isso std::cin.getline
    std::cout << "Informe o nome (max 29 caracteres): ";
    std::cin.getline(novo_produto.nome, 30);

    std::cout << "Informe a quantidade em estoque: ";
    std::cin >> novo_produto.estoque;

    std::cout << "Informe o preco (R$): ";
    std::cin >> novo_produto.preco;

    // Adiciona o novo produto ao array e atualiza o contador
    produtos[totalProdutos] = novo_produto;
    totalProdutos++;

    std::cout << "\n>> Produto cadastrado com sucesso!" << std::endl;
}