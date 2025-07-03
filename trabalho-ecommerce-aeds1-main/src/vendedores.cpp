#include "vendedores.h"
#include <iostream>
#include <string>
#include <limits> // Necessário para std::cin.ignore

/**
 * @file vendedores.cpp
 * @brief Implementação das funções para gerenciar o cadastro de vendedores.
 *
 * Este arquivo contém toda a lógica para o ciclo de vida dos dados de um vendedor,
 * incluindo criação, consulta, alteração e exclusão.
 * O armazenamento é feito em um array dinâmico com gerenciamento de memória manual.
 */

//================================================================================
// Construtores da Classe Vendedor
//================================================================================

/**
 * @brief Construtor padrão da classe Vendedor.
 * Inicializa um vendedor com valores vazios ou nulos.
 */
Vendedor::Vendedor() {
    nome = "";
    numero = 0;
    salario_fixo = 0.0f;
    comissoes = 0.0f;
}

/**
 * @brief Construtor parametrizado da classe Vendedor.
 * @param n O nome do vendedor.
 * @param num O número de identificação do vendedor.
 * @param sal O salário fixo do vendedor.
 */
Vendedor::Vendedor(std::string n, int num, float sal) {
    nome = n;
    numero = num;
    salario_fixo = sal;
    comissoes = 0.0f; // Comissões sempre iniciam zeradas
}

//================================================================================
// Implementação das Funções de Gerenciamento
//================================================================================

/**
 * @brief Busca um vendedor na lista pelo seu número de identificação.
 * @param lista Ponteiro para o array de vendedores.
 * @param tamanho O número atual de vendedores na lista.
 * @param numero O número do vendedor a ser procurado.
 * @return Um ponteiro para o objeto Vendedor se encontrado; caso contrário, nullptr.
 */
Vendedor* encontrarVendedor(Vendedor* lista, int tamanho, int numero) {
    for (int i = 0; i < tamanho; ++i) {
        if (lista[i].numero == numero) {
            return &lista[i]; // Retorna o endereço do vendedor encontrado
        }
    }
    return nullptr; // Retorna nulo se não encontrar
}

/**
 * @brief Insere um novo vendedor na lista, gerenciando a alocação de memória.
 * Se a capacidade do array for atingida, um novo array com o dobro da capacidade
 * é alocado, os dados são copiados e a memória antiga é liberada.
 * @param lista Referência ao ponteiro do array de vendedores.
 * @param tamanho Referência ao contador do número de vendedores.
 * @param capacidade Referência à capacidade atual do array.
 */
void inserirVendedor(Vendedor*& lista, int& tamanho, int& capacidade) {
    // Verifica se o array está cheio
    if (tamanho == capacidade) {
        // Dobra a capacidade (ou inicia com 10 se estiver vazia)
        int nova_capacidade = (capacidade == 0) ? 10 : capacidade * 2;
        Vendedor* nova_lista = new Vendedor[nova_capacidade];

        // Copia os elementos do array antigo para o novo
        for (int i = 0; i < tamanho; ++i) {
            nova_lista[i] = lista[i];
        }

        delete[] lista; // Libera a memória do array antigo
        lista = nova_lista; // O ponteiro principal agora aponta para o novo array
        capacidade = nova_capacidade;
        std::cout << "(Espaco realocado para " << capacidade << " vendedores)\n";
    }

    int numero_novo;
    std::string nome_novo;
    float salario_novo;

    std::cout << "\n--- Inserir Novo Vendedor ---\n" << "Digite o numero do vendedor: ";
    std::cin >> numero_novo;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Valida se o vendedor já existe
    if (encontrarVendedor(lista, tamanho, numero_novo) != nullptr) {
        std::cout << "!! ERRO: Ja existe um vendedor cadastrado com o numero " << numero_novo << ".\n";
        return;
    }

    std::cout << "Digite o nome do vendedor: ";
    std::getline(std::cin, nome_novo);
    std::cout << "Digite o salario fixo: ";
    std::cin >> salario_novo;

    // Adiciona o novo vendedor no final da lista
    lista[tamanho] = Vendedor(nome_novo, numero_novo, salario_novo);
    tamanho++;
    std::cout << "=> Vendedor '" << nome_novo << "' cadastrado com sucesso!\n";
}

/**
 * @brief Adiciona uma comissão a um vendedor específico.
 * A comissão é calculada como 3% do valor da venda.
 * @param lista Ponteiro para o array de vendedores.
 * @param tamanho O número atual de vendedores na lista.
 */
void adicionarComissao(Vendedor* lista, int tamanho) {
    int numero_vendedor;
    float valor_venda;

    std::cout << "\n--- Registrar Comissao de Venda ---\n" << "Digite o numero do vendedor que realizou a venda: ";
    std::cin >> numero_vendedor;

    Vendedor* vendedor_encontrado = encontrarVendedor(lista, tamanho, numero_vendedor);

    if (vendedor_encontrado == nullptr) {
        std::cout << "!! ERRO: Vendedor com numero " << numero_vendedor << " nao encontrado.\n";
        return;
    }

    std::cout << "Vendedor selecionado: " << vendedor_encontrado->nome << "\n" << "Digite o valor total da venda: R$ ";
    std::cin >> valor_venda;

    if (valor_venda < 0) {
        std::cout << "!! ERRO: O valor da venda nao pode ser negativo.\n";
        return;
    }

    float comissao_calculada = valor_venda * 0.03; // Cálculo de 3%
    vendedor_encontrado->comissoes += comissao_calculada;

    std::cout << "=> Comissao de R$ " << comissao_calculada << " adicionada com sucesso.\n"
              << "   Novo total de comissoes acumuladas: R$ " << vendedor_encontrado->comissoes << "\n";
}

/**
 * @brief Exclui um vendedor da lista.
 * A exclusão é feita encontrando o índice do vendedor e movendo todos os
 * elementos subsequentes uma posição para a esquerda.
 * @param lista Ponteiro para o array de vendedores.
 * @param tamanho Referência ao contador do número de vendedores.
 */
void excluirVendedor(Vendedor* lista, int& tamanho) {
    int numero;
    std::cout << "\n--- Excluir Vendedor ---\n" << "Digite o numero do vendedor que deseja excluir: ";
    std::cin >> numero;

    int indice_excluir = -1;
    // Encontra o índice do vendedor a ser excluído
    for (int i = 0; i < tamanho; ++i) {
        if (lista[i].numero == numero) {
            indice_excluir = i;
            break;
        }
    }

    if (indice_excluir == -1) {
        std::cout << "!! ERRO: Vendedor com numero " << numero << " nao encontrado.\n";
        return;
    }

    // Move todos os elementos após o índice uma posição para a esquerda
    for (int i = indice_excluir; i < tamanho - 1; ++i) {
        lista[i] = lista[i + 1];
    }
    tamanho--; // Decrementa o tamanho lógico da lista
    std::cout << "=> Vendedor excluido com sucesso!\n";
}

/**
 * @brief Exibe uma lista formatada de todos os vendedores cadastrados.
 * @param lista Ponteiro constante para o array de vendedores (operação de leitura).
 * @param tamanho O número atual de vendedores na lista.
 */
void consultarVendedores(const Vendedor* lista, int tamanho) {
    std::cout << "\n--- Lista de Vendedores Cadastrados ---\n";
    if (tamanho == 0) {
        std::cout << "Nenhum vendedor cadastrado no sistema.\n";
        return;
    }
    for (int i = 0; i < tamanho; ++i) {
        std::cout << "--------------------------------------\n"
                  << "   Nome: " << lista[i].nome << "\n"
                  << "   Numero: " << lista[i].numero << "\n"
                  << "   Salario Fixo: R$ " << lista[i].salario_fixo << "\n"
                  << "   Comissoes Acumuladas: R$ " << lista[i].comissoes << "\n";
    }
    std::cout << "--------------------------------------\n";
}

/**
 * @brief Altera o nome e o salário fixo de um vendedor existente.
 * @param lista Ponteiro para o array de vendedores.
 * @param tamanho O número atual de vendedores na lista.
 */
void alterarVendedor(Vendedor* lista, int tamanho) {
    int numero;
    std::cout << "\n--- Alterar Dados do Vendedor ---\n" << "Digite o numero do vendedor que deseja alterar: ";
    std::cin >> numero;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Vendedor* vendedor_encontrado = encontrarVendedor(lista, tamanho, numero);

    if (vendedor_encontrado == nullptr) {
        std::cout << "!! ERRO: Vendedor com numero " << numero << " nao encontrado.\n";
        return;
    }

    std::cout << "Vendedor encontrado: " << vendedor_encontrado->nome << "\n" << "Digite o novo nome: ";
    std::getline(std::cin, vendedor_encontrado->nome);
    std::cout << "Digite o novo salario fixo: ";
    std::cin >> vendedor_encontrado->salario_fixo;
    std::cout << "=> Dados do vendedor alterados com sucesso!\n";
}