/**
 * @file func.h
 * @brief Declarações e estruturas utilizadas no programa de conversão de unidades e bases.
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @struct celula
 * @brief Nó da lista encadeada utilizada para armazenar histórico de comandos.
 * 
 * @var celula::command
 * Texto do comando armazenado na célula.
 * 
 * @var celula::prox
 * Ponteiro para a próxima célula da lista.
 */
typedef struct celula { 
    char* command; 
    struct celula* prox; 
} celula;

/**
 * @brief Função principal responsável por executar o loop de comandos do programa.
 */
void runtime();
