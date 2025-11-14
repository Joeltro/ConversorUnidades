#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <signal.h>

typedef struct celula { // struct que será utilizada para fazer a lista do programa
    char command[100]; // são os comandos digitados pelo usúario
    struct celula* ant; // ponteiro que irá apontar para o comando anterior(dado)
    struct celula* prox; // ponteiro que irá apontar para o próximo
} celula;


void runtime();
