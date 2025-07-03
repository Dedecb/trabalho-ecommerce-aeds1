#include "compradores.h"
#include <stdio.h>
#include <string.h>

/**
 * @file compradores.c
 * @brief Implementação das funções para gerenciar o cadastro de compradores.
 * * Este arquivo contém a lógica para inserir, buscar e listar compradores,
 * utilizando um array global como estrutura de armazenamento de dados.
 */

//================================================================================
// Variáveis Globais
//================================================================================

Comprador compradores[MAX_COMPRADORES]; /**< Array para armazenar os dados dos compradores. */
int totalCompradores = 0;               /**< Contador do número atual de compradores cadastrados. */

//================================================================================
// Implementação das Funções
//================================================================================

/**
 * @brief Busca um comprador no array pelo seu CPF.
 * * Percorre o array global 'compradores' e compara o CPF de cada um com o
 * CPF fornecido.
 * * @param cpf O CPF (string) a ser buscado.
 * @return O índice do comprador no array se encontrado, ou -1 caso contrário.
 */
int buscarCompradorPorCPF(const char* cpf) {
    for (int i = 0; i < totalCompradores; i++) {
        // Compara o CPF do comprador na posição 'i' com o CPF fornecido
        if (strcmp(compradores[i].cpf, cpf) == 0) {
            return i; // Retorna o índice se encontrou
        }
    }
    return -1; // Retorna -1 se não encontrou o CPF em todo o array
}

/**
 * @brief Cadastra um novo comprador no sistema.
 * * Solicita interativamente ao usuário os dados de um novo comprador.
 * Antes de adicionar, verifica se o limite de cadastros foi atingido e se o
 * CPF informado já não existe no sistema para evitar duplicatas.
 */
void inserirComprador() {
    // Verifica se o array de compradores já está cheio
    if (totalCompradores >= MAX_COMPRADORES) {
        printf("Limite de compradores atingido!\n");
        return;
    }

    Comprador novo; // Cria uma estrutura temporária para o novo comprador
    printf("\n----- CADASTRO DE COMPRADOR -----\n");

    // Solicita e lê os dados do novo comprador
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);

    printf("CPF: ");
    scanf(" %[^\n]", novo.cpf);

    // Valida se já existe um comprador com o mesmo CPF
    if (buscarCompradorPorCPF(novo.cpf) != -1) {
        printf("Erro: Ja existe comprador com esse CPF!\n");
        return;
    }

    printf("Email: ");
    scanf(" %[^\n]", novo.email);

    printf("Rua: ");
    scanf(" %[^\n]", novo.rua);

    printf("Bairro: ");
    scanf(" %[^\n]", novo.bairro);

    printf("Cidade: ");
    scanf(" %[^\n]", novo.cidade);

    printf("Estado (UF): ");
    scanf(" %[^\n]", novo.estado);

    printf("CEP: ");
    scanf(" %[^\n]", novo.cep);

    // Adiciona o novo comprador ao final do array
    compradores[totalCompradores] = novo;
    totalCompradores++; // Incrementa o contador de compradores

    printf("Comprador cadastrado com sucesso!\n");
}

/**
 * @brief Lista todos os compradores cadastrados.
 * * Exibe na tela uma lista formatada com as informações principais de cada
 * comprador registrado no sistema. Se nenhum comprador estiver cadastrado,
 * exibe uma mensagem informativa.
 */
void listarCompradores() {
    printf("\n--- LISTA DE COMPRADORES (%d) ---\n", totalCompradores);

    // Verifica se há compradores para listar
    if (totalCompradores == 0) {
        printf("Nenhum comprador cadastrado.\n");
        return;
    }

    // Percorre o array e imprime os dados de cada comprador
    for (int i = 0; i < totalCompradores; i++) {
        printf("Nome: %s | CPF: %s | Email: %s\n",
               compradores[i].nome, compradores[i].cpf, compradores[i].email);
        printf("Endereco: %s, %s, %s-%s, CEP: %s\n\n",
               compradores[i].rua, compradores[i].bairro, compradores[i].cidade,
               compradores[i].estado, compradores[i].cep);
    }
}