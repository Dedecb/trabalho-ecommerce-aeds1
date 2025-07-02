#include <iostream>
using namespace std;

// Prototipacao das funcoes (declaracoes)
void mostrarMenu();
void cadastrarProduto();
void cadastrarVendedor();
void cadastrarComprador();
void cadastrarVenda();
void emitirNotaFiscal();

int main() {
    mostrarMenu();
    return 0;
}

void mostrarMenu() {
    int opcao;
    do {
        cout << "\n MENU PRINCIPAL \n";
        cout << "1. Cadastro de Produto\n";
        cout << "2. Cadastro de Vendedor\n";
        cout << "3. Cadastro de Comprador\n";
        cout << "4. Cadastro de Venda\n";
        cout << "5. Emissao de Nota Fiscal\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1: cadastrarProduto(); break;
            case 2: cadastrarVendedor(); break;
            case 3: cadastrarComprador(); break;
            case 4: cadastrarVenda(); break;
            case 5: emitirNotaFiscal(); break;
            case 0: cout << "Saindo do sistema...\n"; break;
            default: cout << "Opcao invalida!\n";
        }

    } while (opcao != 0);
}

// Funcoes "placeholders"
void cadastrarProduto() {
    cout << "[EM DESENVOLVIMENTO] Cadastro de Produto\n";
}

void cadastrarVendedor() {
    cout << "[EM DESENVOLVIMENTO] Cadastro de Vendedor\n";
}

void cadastrarComprador() {
    cout << "[EM DESENVOLVIMENTO] Cadastro de Comprador\n";
}

void cadastrarVenda() {
    cout << "[EM DESENVOLVIMENTO] Cadastro de Venda\n";
}

void emitirNotaFiscal() {
    cout << "[EM DESENVOLVIMENTO] Emissao de Nota Fiscal\n";
}
