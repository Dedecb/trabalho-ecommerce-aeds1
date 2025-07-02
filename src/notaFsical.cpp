#include <stdio.h>
#include <string.h>
#define MAX_COMPRADORES 100


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


Comprador compradores[MAX_COMPRADORES];

int totalCompradores = 0;

int buscarCompradorPorCPF(const char* cpf) {
    
    for (int i = 0; i < totalCompradores; i++) {
        
        if (strcmp(compradores[i].cpf, cpf) == 0) {
            
            return i;
        }
    }
    
    return -1;
}


void inserirComprador() {
    
    if (totalCompradores >= MAX_COMPRADORES) {
        printf("Limite de compradores atingido!\n");
        
        return;
    }

    Comprador novo;

    printf("\n----- CADASTRO DE COMPRADOR -----\n");

    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);

    printf("CPF: ");
    scanf(" %[^\n]", novo.cpf);

    
    if (buscarCompradorPorCPF(novo.cpf) != -1) {
        printf("Erro: Já existe comprador com esse CPF!\n");
        
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

    printf("Estado: ");
    scanf(" %[^\n]", novo.estado);

    printf("CEP: ");
    scanf(" %[^\n]", novo.cep);

    
    compradores[totalCompradores] = novo;
    totalCompradores++;

    printf("Comprador cadastrado com sucesso!\n");
}



void listarCompradores() {
    
    printf("\n--- LISTA DE COMPRADORES (%d) ---\n", totalCompradores);

    
    if (totalCompradores == 0) {
        printf("Nenhum comprador cadastrado.\n");
        
        return;
    }

    
    for (int i = 0; i < totalCompradores; i++) {
        printf("Nome: %s | CPF: %s | Email: %s\n",
               compradores[i].nome, compradores[i].cpf, compradores[i].email);
        printf("Endereco: %s, %s, %s-%s, CEP: %s\n\n",
               compradores[i].rua, compradores[i].bairro, compradores[i].cidade,
               compradores[i].estado, compradores[i].cep);
    }
}


int main() {
    int opcao;

    do {
        printf("\n------ MENU - COMPRADORES ------\n");
        printf("1. Cadastrar novo comprador\n");
        printf("2. Listar compradores cadastrados\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao:");
        scanf("%d", &opcao);

        switch (opcao) {
            
            case 1:
                inserirComprador();
                
                break;
            
            case 2:
                listarCompradores();
                
                break;
            
            case 0:
                printf("Encerrando o programa...\n");
                
                break;
            
            default:
                printf("Opção invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}