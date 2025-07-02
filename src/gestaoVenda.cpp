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

// Função auxiliar para encontrar um vendedor. Retorna seu endereço na memória ou nullptr.
Vendedor* encontrarVendedor(Vendedor* lista, int tamanho, int numero) {
    for (int i = 0; i < tamanho; ++i) {
        if (lista[i].numero == numero) {
            return &lista[i];
        }
    }
    return nullptr;
}


// --- FUNÇÕES PRINCIPAIS ---


/**
 * @brief INSERIR: Adiciona um novo vendedor, gerenciando o crescimento do array.
 * Esta é a função mais complexa, pois cuida da realocação de memória.
 * @param lista Ponteiro para o array (por referência, pois pode mudar de endereço).
 * @param tamanho Quantidade atual de vendedores (por referência, pois vai aumentar).
 * @param capacidade Tamanho total alocado (por referência, pois pode mudar).
 */
void inserirVendedor(Vendedor*& lista, int& tamanho, int& capacidade) {
    // 1. VERIFICAÇÃO E REALOCAÇÃO DE MEMÓRIA
    // Se a lista está cheia, um novo array maior é criado.
    if (tamanho == capacidade) {
        // A nova capacidade começa em 10 e depois dobra a cada realocação.
        int nova_capacidade = (capacidade == 0) ? 10 : capacidade * 2;
        Vendedor* nova_lista = new Vendedor[nova_capacidade];

        // Os dados do array antigo são copiados para o novo.
        for (int i = 0; i < tamanho; ++i) {
            nova_lista[i] = lista[i];
        }

        // A memória do array antigo é liberada para evitar vazamento.
        delete[] lista;

        // O ponteiro principal 'lista' agora aponta para o novo array.
        lista = nova_lista;
        capacidade = nova_capacidade;
        std::cout << "(Espaco realocado para " << capacidade << " vendedores)\n";
    }

    // 2. LEITURA E INSERÇÃO DOS DADOS
    int numero_novo;
    std::string nome_novo;
    float salario_novo;

    std::cout << "\n--- Inserir Novo Vendedor ---\n" << "Digite o numero do vendedor: ";
    std::cin >> numero_novo;
    std::cin.ignore(10000, '\n');

    if (encontrarVendedor(lista, tamanho, numero_novo) != nullptr) {
        std::cout << "!! ERRO: Ja existe um vendedor cadastrado com o numero " << numero_novo << ".\n";
        return;
    }

    std::cout << "Digite o nome do vendedor: ";
    std::getline(std::cin, nome_novo);
    std::cout << "Digite o salario fixo: ";
    std::cin >> salario_novo;

    // O novo vendedor é adicionado na primeira posição livre.
    lista[tamanho] = Vendedor(nome_novo, numero_novo, salario_novo);
    tamanho++;
    std::cout << "=> Vendedor '" << nome_novo << "' cadastrado com sucesso!\n";
}

/**
 * @brief ADICIONAR COMISSÃO: Função chave da Sprint 2.
 * Encontra um vendedor e adiciona o valor de uma comissão às suas comissões acumuladas.
 * @param lista Ponteiro para o array de vendedores.
 * @param tamanho Quantidade atual de vendedores.
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

    // Lógica principal: calcula 3% de comissão e acumula no vendedor.
    float comissao_calculada = valor_venda * 0.03;
    vendedor_encontrado->comissoes += comissao_calculada;

    std::cout << "=> Comissao de R$ " << comissao_calculada << " adicionada com sucesso.\n"
              << "   Novo total de comissoes acumuladas: R$ " << vendedor_encontrado->comissoes << "\n";
}

/**
 * @brief EXCLUIR: Remove um vendedor do array, deslocando os elementos.
 * @param lista Ponteiro para o array.
 * @param tamanho Quantidade de vendedores (por referência, pois vai diminuir).
 */
void excluirVendedor(Vendedor* lista, int& tamanho) {
    int numero;
    std::cout << "\n--- Excluir Vendedor ---\n" << "Digite o numero do vendedor que deseja excluir: ";
    std::cin >> numero;

    int indice_excluir = -1;
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

    // Desloca todos os elementos à direita do excluído uma posição para a esquerda.
    for (int i = indice_excluir; i < tamanho - 1; ++i) {
        lista[i] = lista[i + 1];
    }
    tamanho--; // Diminui o tamanho lógico da lista.
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
    std::cin.ignore(10000, '\n');

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

/**
 * @brief Função principal que controla o menu e o ciclo de vida do programa.
 */
int main() {
    // Variáveis que controlam nosso array dinâmico.
    Vendedor* lista_vendedores = nullptr; // O ponteiro para o array na memória.
    int tamanho = 0;                      // O número de vendedores na lista.
    int capacidade = 0;                   // O tamanho total do array alocado.
    int opcao;

    do {
        std::cout << "\n*** Modulo de Vendedores (Sprint 2) ***\n"
                  << "1. Inserir Vendedor\n"
                  << "2. Consultar Vendedores\n"
                  << "3. Alterar Vendedor\n"
                  << "4. Excluir Vendedor\n"
                  << "5. Adicionar Comissao de Venda\n"
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
            case 5: adicionarComissao(lista_vendedores, tamanho); break;
            case 0: std::cout << "Saindo do modulo de vendedores...\n"; break;
            default: std::cout << "!! Opcao invalida! Tente novamente.\n"; break;
        }
    } while (opcao != 0);

    // PONTO CRÍTICO: Libera toda a memória alocada ao final do programa.
    // Se esta linha for esquecida, ocorrerá vazamento de memória.
    delete[] lista_vendedores;

    return 0;
}