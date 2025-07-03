#include <string>
#ifndef VENDEDORES_H
#define VENDEDORES_H

struct Vendedor {
    std::string nome;
    int numero;
    float salario_fixo;
    float comissoes;

    Vendedor();
    Vendedor(std::string n, int num, float sal);
};

void inserirVendedor(Vendedor*& lista, int& tamanho, int& capacidade);
void consultarVendedores(const Vendedor* lista, int tamanho);
void alterarVendedor(Vendedor* lista, int tamanho);
void excluirVendedor(Vendedor* lista, int& tamanho);

#endif
