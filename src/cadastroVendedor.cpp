#include <iostream>
#include <string>

// A estrutura que define os dados de um vendedor.
struct Vendedor {
    std::string nome;
    int numero;
    float salario_fixo;
    float comissoes;

    // Construtor padrão (necessário para a alocação do array com 'new').
    Vendedor() : numero(0), salario_fixo(0.0f), comissoes(0.0f) {}

    // Construtor com parâmetros para facilitar a criação.
    Vendedor(std::string n, int num, float sal)
        : nome(n), numero(num), salario_fixo(sal), comissoes(0.0f) {}
};


// --- FUNÇÕES PRINCIPAIS ---


/**
 * @brief INSERIR: Adiciona um novo vendedor, gerenciando o crescimento do array.
 * Esta é a função mais complexa, pois cuida da realocação de memória quando o array atinge sua capacidade.
 * @param lista Ponteiro para o array de vendedores (por referência, pois pode mudar).
 * @param tamanho Quantidade atual de vendedores (por referência, pois vai aumentar).
 * @param capacidade Tamanho total do array alocado (por referência, pois pode mudar).
 */
void inserirVendedor(Vendedor*& lista, int& tamanho, int& capacidade) {
    // 1. VERIFICAÇÃO E REALOCAÇÃO DE MEMÓRIA
    // Se a lista está cheia (tamanho == capacidade), um novo array maior é criado.
    if (tamanho == capacidade) {
        // A nova capacidade começa em 10 e depois dobra a cada realocação.
        int nova_capacidade = (capacidade == 0) ? 10 : capacidade * 2;
        Vendedor* nova_lista = new Vendedor[nova_capacidade];

        // Os dados do array antigo são copiados para o novo.
        for (int i = 0; i < tamanho; ++i) {
            nova_lista[i] = lista[i];
        }

        // A memória do array antigo é liberada para evitar vazamento de memória.
        delete[] lista;

        // O ponteiro principal 'lista' agora aponta para o novo array maior.
        lista = nova_lista;
        capacidade = nova_capacidade;
        
        std::cout << "(Espaco realocado para " << capacidade << " vendedores)\n";
    }

    // 2. LEITURA DOS DADOS E INSERÇÃO
    // Após garantir que há espaço, os dados do novo vendedor são lidos.
    int numero_novo;
    std::string nome_novo;
    float salario_novo;

    std::cout << "\n--- Inserir Novo Vendedor ---\n" << "Digite o numero do vendedor: ";
    std::cin >> numero_novo;

    // Lógica para evitar duplicatas...
    // (Implementação do 'encontrarVendedor' é usada aqui internamente)
    bool encontrado = false;
    for (int i = 0; i < tamanho; ++i) {
        if (lista[i].numero == numero_novo) {
            encontrado = true;
            break;
        }
    }

    if (encontrado) {
        std::cout << "!! ERRO: Ja existe um vendedor com o numero " << numero_novo << ".\n";
        std::cin.ignore(10000, '\n');
        return;
    }

    std::cout << "Digite o nome do vendedor: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, nome_novo);

    std::cout << "Digite o salario fixo: ";
    std::cin >> salario_novo;

    // O novo vendedor é adicionado na primeira posição livre do array.
    lista[tamanho] = Vendedor(nome_novo, numero_novo, salario_novo);
    tamanho++; // O tamanho lógico da lista é incrementado.

    std::cout << "=> Vendedor '" << nome_novo << "' cadastrado com sucesso!\n";
}

/**
 * @brief EXCLUIR: Remove um vendedor do array.
 * A exclusão exige encontrar o vendedor e "puxar" todos os elementos seguintes
 * para a esquerda, a fim de preencher o espaço vazio.
 * @param lista Ponteiro para o array de vendedores.
 * @param tamanho Quantidade atual de vendedores (por referência, pois vai diminuir).
 */
void excluirVendedor(Vendedor* lista, int& tamanho) {
    int numero;
    std::cout << "\n--- Excluir Vendedor ---\n" << "Digite o numero do vendedor que deseja excluir: ";
    std::cin >> numero;

    // 1. ENCONTRAR O ÍNDICE DO VENDEDOR A SER EXCLUÍDO
    int indice_excluir = -1;
    for(int i = 0; i < tamanho; ++i) {
        if (lista[i].numero == numero) {
            indice_excluir = i;
            break;
        }
    }

    if (indice_excluir == -1) {
        std::cout << "!! ERRO: Vendedor com numero " << numero << " nao encontrado.\n";
        return;
    }

    // 2. DESLOCAMENTO DOS ELEMENTOS
    // Cada elemento a partir do índice de exclusão é movido uma posição para a esquerda.
    // Isso sobrescreve o elemento que foi "excluído".
    for (int i = indice_excluir; i < tamanho - 1; ++i) {
        lista[i] = lista[i + 1];
    }

    // O tamanho lógico da lista é decrementado, efetivamente removendo o último elemento (que agora é um duplicado).
    tamanho--;

    std::cout << "=> Vendedor excluido com sucesso!\n";
}

/**
 * @brief CONSULTAR: Apenas lê e exibe os dados, sem modificar a estrutura.
 */
void consultarVendedores(const Vendedor* lista, int tamanho) {
    std::cout << "\n--- Lista de Vendedores Cadastrados ---\n";
    if (tamanho == 0) {
        std::cout << "Nenhum vendedor cadastrado no sistema.\n";
        return;
    }
    for (int i = 0; i < tamanho; ++i) {
        std::cout << "--------------------------------------\n"
                  << "  Nome: " << lista[i].nome << "\n"
                  << "  Numero: " << lista[i].numero << "\n"
                  << "  Salario Fixo: R$ " << lista[i].salario_fixo << "\n"
                  << "  Comissoes Acumuladas: R$ " << lista[i].comissoes << "\n";
    }
    std::cout << "--------------------------------------\n";
}

/**
 * @brief ALTERAR: Encontra um vendedor e permite a modificação de seus dados.
 */
void alterarVendedor(Vendedor* lista, int tamanho) {
    int numero;
    std::cout << "\n--- Alterar Dados do Vendedor ---\n" << "Digite o numero do vendedor que deseja alterar: ";
    std::cin >> numero;

    Vendedor* vendedor_encontrado = nullptr;
    for (int i = 0; i < tamanho; ++i) {
        if (lista[i].numero == numero) {
            vendedor_encontrado = &lista[i];
            break;
        }
    }

    if (vendedor_encontrado == nullptr) {
        std::cout << "!! ERRO: Vendedor com numero " << numero << " nao encontrado.\n";
        return;
    }

    std::cout << "Vendedor encontrado: " << vendedor_encontrado->nome << "\n"
              << "Digite o novo nome: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, vendedor_encontrado->nome);

    std::cout << "Digite o novo salario fixo: ";
    std::cin >> vendedor_encontrado->salario_fixo;

    std::cout << "=> Dados do vendedor alterados com sucesso!\n";
}

/**
 * @brief Função principal que controla o menu e o ciclo de vida do programa.
 */
int main() {
    // Variáveis que controlam nosso array dinâmico.
    Vendedor* lista_vendedores = nullptr; // O ponteiro para o array na memória.
    int tamanho = 0;                      // O número de vendedores atualmente na lista.
    int capacidade = 0;                   // O tamanho total do array alocado.
    int opcao;

    do {
        std::cout << "\n*** Modulo de Cadastro de Vendedores (C++) ***\n"
                  << "1. Inserir Vendedor\n"
                  << "2. Consultar Vendedores\n"
                  << "3. Alterar Vendedor\n"
                  << "4. Excluir Vendedor\n"
                  << "0. Sair do Modulo\n"
                  << "Escolha uma opcao: ";
        std::cin >> opcao;

        if (std::cin.fail()) {
            std::cout << "!! Opcao invalida! Por favor, digite um numero.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            opcao = -1;
        }

        switch (opcao) {
            case 1: inserirVendedor(lista_vendedores, tamanho, capacidade); break;
            case 2: consultarVendedores(lista_vendedores, tamanho); break;
            case 3: alterarVendedor(lista_vendedores, tamanho); break;
            case 4: excluirVendedor(lista_vendedores, tamanho); break;
            case 0: std::cout << "Saindo do modulo de vendedores...\n"; break;
            default: std::cout << "!! Opcao invalida! Tente novamente.\n"; break;
        }
    } while (opcao != 0);

    // PONTO CRÍTICO: Libera toda a memória alocada para o array ao final do programa.
    // Se esta linha for esquecida, ocorrerá um vazamento de memória.
    delete[] lista_vendedores;

    return 0;
}