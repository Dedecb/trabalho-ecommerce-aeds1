#ifndef NOTAFISCAL_H
#define NOTAFISCAL_H

// Incluímos "produto.h" aqui, pois as funções de nota fiscal
// precisam saber o que é um 'Produto' e usar as funções e variáveis de produtos.
#include "produto.h"

// Declaração das funções que serão implementadas em notaFiscal.cpp
void emitirNotaFiscal();
float calcularFrete(float totalVenda);

#endif