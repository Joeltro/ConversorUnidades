#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <signal.h>

typedef struct celula {
    char command[100];
    struct celula* ant;
    struct celula* prox;
} celula;


void runtime();
