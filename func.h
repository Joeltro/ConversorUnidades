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
 * Comando digitado pelo usuário.
 * 
 * @var celula::prox
 * Ponteiro para a próxima célula da lista.
 */
typedef struct celula { // struct que será utilizada para fazer a lista do programa
    char* command; // são os comandos digitados pelo usúario
    struct celula* prox; // ponteiro que irá apontar para o próximo
} celula;

/**
 * @brief Inicia o loop principal do programa, gerenciando entrada, histórico e conversões.
 */
void runtime();
