#ifndef COMPRADORES_H
#define COMPRADORES_H

#define MAX_COMPRADORES 100

// 1. Define o TIPO Comprador para que todos saibam o que é
typedef struct {
    char nome[50];
    char cpf[15];
    char email[50];
    char rua[50];
    char bairro[30];
    char cidade[30];
    char estado[3];
    char cep[10];
} Comprador;

// 2. DECLARA as variáveis globais com 'extern' (promete que elas existem em algum .cpp)
extern Comprador compradores[MAX_COMPRADORES];
extern int totalCompradores;

// 3. DECLARA as funções (protótipos)
void inserirComprador();
void listarCompradores();
int buscarCompradorPorCPF(const char* cpf);

#endif