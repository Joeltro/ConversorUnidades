#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celula { // struct que será utilizada para fazer a lista do programa
    char* command; // são os comandos digitados pelo usúario
    struct celula* prox; // ponteiro que irá apontar para o próximo
} celula;


void runtime();
