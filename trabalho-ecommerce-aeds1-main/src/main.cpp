#include <iostream>
#include <limits> // Necessário para validar e limpar a entrada do usuário (cin)

// Inclusão dos cabeçalhos de todos os módulos do sistema
#include "produto.h"
#include "vendedores.h"
#include "compradores.h"
#include "notaFiscal.h"

/**
 * @file main.cpp
 * @brief Ponto de entrada principal do sistema de E-commerce.
 *
 * Este arquivo contém a função main() que controla o fluxo principal do programa.
 * Ele exibe o menu principal e delega as operações para os sub-menus
 * de cada módulo (Produtos, Vendedores, Compradores, Vendas).
 * Também é responsável por gerenciar a memória da lista dinâmica de vendedores.
 */

using namespace std;

//================================================================================
// Protótipos das Funções de Menu
//================================================================================

/** @brief Exibe o menu de gerenciamento de produtos. */
void menuModuloProdutos();

/**
 * @brief Exibe o menu de gerenciamento de vendedores.
 * @param lista Ponteiro de referência para a lista de vendedores.
 * @param tamanho Referência para o contador de vendedores na lista.
 * @param capacidade Referência para a capacidade atual da lista.
 */
void menuModuloVendedores(Vendedor*& lista, int& tamanho, int& capacidade);

/** @brief Exibe o menu de gerenciamento de compradores. */
void menuModuloCompradores();


//================================================================================
// Função Principal
//================================================================================

/**
 * @brief Ponto de entrada e controlador principal do programa.
 * @return 0 se o programa for encerrado com sucesso.
 */
int main() {
    //----------------------------------------------------------------------------
    // Dados Principais do Programa
    //----------------------------------------------------------------------------

    // A função main é "dona" dos dados dos vendedores e os passa como referência
    // para as funções que precisam manipulá-los.
    Vendedor* lista_vendedores = nullptr;
    int tamanho_vendedores = 0;
    int capacidade_vendedores = 0;

    // Os dados de produtos e compradores são gerenciados globalmente em seus
    // respectivos arquivos .cpp, portanto não são declarados aqui.

    //----------------------------------------------------------------------------
    // Loop do Menu Principal
    //----------------------------------------------------------------------------
    int opcao_principal;
    do {
        cout << "\n=================================\n";
        cout << "      MENU PRINCIPAL E-COMMERCE\n";
        cout << "=================================\n";
        cout << "1. Gerenciar Produtos\n";
        cout << "2. Gerenciar Vendedores\n";
        cout << "3. Gerenciar Compradores\n";
        cout << "4. Realizar Venda (Emitir Nota Fiscal)\n";
        cout << "0. Sair do Sistema\n";
        cout << "\nEscolha uma opcao: ";
        cin >> opcao_principal;

        // Validação para garantir que a entrada seja um número
        if (cin.fail()) {
            cout << "\n!! ERRO: Entrada invalida. Por favor, digite um numero.\n";
            cin.clear(); // Limpa o estado de erro do cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta a entrada inválida
            continue; // Volta para o início do loop
        }

        switch (opcao_principal) {
            case 1:
                menuModuloProdutos();
                break;
            case 2:
                // Passa os dados dos vendedores por referência para o sub-menu
                menuModuloVendedores(lista_vendedores, tamanho_vendedores, capacidade_vendedores);
                break;
            case 3:
                menuModuloCompradores();
                break;
            case 4:
                emitirNotaFiscal(); // Chama a função do módulo notaFiscal
                break;
            case 0:
                cout << "Encerrando o sistema...\n";
                break;
            default:
                cout << "\n!! Opcao invalida. Tente novamente.\n";
                break;
        }

    } while (opcao_principal != 0);

    //----------------------------------------------------------------------------
    // Limpeza de Memória
    //----------------------------------------------------------------------------
    // Libera a memória alocada para a lista de vendedores antes de encerrar
    delete[] lista_vendedores;

    return 0; // Fim do programa
}


//================================================================================
// Implementação dos Sub-Menus
//================================================================================

/**
 * @brief Apresenta e gerencia as opções do módulo de Produtos.
 */
void menuModuloProdutos() {
    int opcao;
    do {
        cout << "\n--- Modulo de Produtos ---\n";
        cout << "1. Cadastrar Produto\n";
        // TODO: Adicionar opção para listar produtos
        cout << "0. Voltar ao Menu Principal\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (cin.fail()) {
            cout << "\n!! ERRO: Entrada invalida.\n"; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
        }

        switch (opcao) {
            case 1:
                cadastrarProduto(); // Função definida em produto.cpp
                break;
            case 0:
                cout << "Voltando...\n";
                break;
            default:
                cout << "!! Opcao invalida.\n";
                break;
        }
    } while (opcao != 0);
}

/**
 * @brief Apresenta e gerencia as opções do módulo de Vendedores.
 */
void menuModuloVendedores(Vendedor*& lista, int& tamanho, int& capacidade) {
    int opcao;
    do {
        cout << "\n--- Modulo de Vendedores ---\n";
        cout << "1. Inserir Vendedor\n";
        cout << "2. Consultar Vendedores\n";
        cout << "3. Alterar Vendedor\n";
        cout << "4. Excluir Vendedor\n";
        cout << "0. Voltar ao Menu Principal\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (cin.fail()) {
            cout << "\n!! ERRO: Entrada invalida.\n"; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
        }
        
        switch (opcao) {
            case 1:
                inserirVendedor(lista, tamanho, capacidade);
                break;
            case 2:
                consultarVendedores(lista, tamanho);
                break;
            case 3:
                alterarVendedor(lista, tamanho);
                break;
            case 4:
                excluirVendedor(lista, tamanho);
                break;
            case 0:
                cout << "Voltando...\n";
                break;
            default:
                cout << "!! Opcao invalida.\n";
                break;
        }
    } while (opcao != 0);
}

/**
 * @brief Apresenta e gerencia as opções do módulo de Compradores.
 */
void menuModuloCompradores() {
    int opcao;
    do {
        cout << "\n--- Modulo de Compradores ---\n";
        cout << "1. Cadastrar Comprador\n";
        cout << "2. Listar Compradores\n";
        cout << "0. Voltar ao Menu Principal\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (cin.fail()) {
            cout << "\n!! ERRO: Entrada invalida.\n"; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue;
        }

        switch (opcao) {
            case 1:
                inserirComprador(); // Função definida em compradores.cpp
                break;
            case 2:
                listarCompradores(); // Função definida em compradores.cpp
                break;
            case 0:
                cout << "Voltando...\n";
                break;
            default:
                cout << "!! Opcao invalida.\n";
                break;
        }
    } while (opcao != 0);
}