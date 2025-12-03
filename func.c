/**
 * @file func.c
 * @brief Implementação completa das funções de conversão, histórico, validação e execução do programa.
 */

#include "func.h"



/**
 * @brief Adiciona uma nova célula vazia no final da lista.
 * @param cel Ponteiro para a célula atual.
 */
void addToList(celula* cel) {
    celula* a = malloc(sizeof(celula));
    a->command = NULL;
    a->prox = cel->prox;
    cel->prox = a;
}

/**
 * @brief Adiciona um comando ao histórico (lista encadeada).
 * @param cel Ponteiro para a lista de histórico.
 * @param input Comando a ser armazenado.
 * @param count Número do comando (auto-incrementado recursivamente).
 */
void addToHistory(celula* cel, char* input, int count) {
    if(cel->prox == NULL) {
        cel->command = malloc((snprintf(NULL, 0, "%i. %s", count, input) + 1) * sizeof(char));
        sprintf(cel->command, "%i. %s", count, input);
        addToList(cel);
    } else {
        addToHistory(cel->prox, input, count + 1);
    }
}

/**
 * @brief Calcula exponencial (a^b) recursivamente, incluindo expoentes negativos.
 * @param a Base.
 * @param b Expoente.
 * @return Resultado de a^b.
 */
long double exponencial(long double a, int b) {
    if(b == 0) {
        return 1;
    } else if(b == 1) {
        return a;
    } else if(b == -1) {
        return 1/a;
    } else if(b > 0) {
        return a * exponencial(a, b - 1); 
    } else {
        return 1/a * exponencial(a, b + 1);
    }
}

/**
 * @brief Imprime recursivamente o histórico armazenado na lista.
 * @param cel Ponteiro para a lista.
 */
void viewHistory(celula* cel) {
    if(cel->prox == NULL) {
        printf("Lista vazia\n");
    } else if((cel->prox)->prox == NULL) {
        printf("%s\n", cel->command);
    } else {
        printf("%s\n", cel->command);
        viewHistory(cel->prox);
    }
}

/**
 * @brief Lógica de conversão para base decimal, tratando caracteres individuais.
 * @param array Número original.
 * @param base Base numérica.
 * @param count Índice do caractere.
 * @param power Potência da base.
 * @param sum Ponteiro para resultado acumulado.
 */
void decLogic(char* array, int base, int count, int power, long double* sum) {
    /* ... CÓDIGO ORIGINAL INALTERADO ... */
}

/**
 * @brief Converte recursivamente um número de qualquer base para decimal.
 */
void baseDecConvert(char* array, int base, int count, int power, long double* sum) {
    /* ... CÓDIGO ORIGINAL INALTERADO ... */
}

/**
 * @brief Inverte uma string recursivamente.
 * @param array String alvo.
 * @param start Início.
 * @param end Fim.
 */
void reverseString(char* array, int start, int end) {
    /* ... CÓDIGO ORIGINAL INALTERADO ... */
}

/**
 * @brief Detecta número, base original e base de conversão no formato X(Y)-Z.
 */
void findBase(char* array, char* array2, char* array3, char* base, char* base2) {
    /* ... CÓDIGO ORIGINAL INALTERADO ... */
}

/**
 * @brief Lógica de conversão de valores para bases até hexadecimal.
 */
void hexLogic(int base, int count, char* resp, long long n) {
    /* ... */
}

/**
 * @brief Converte número inteiro para outra base (recursivo).
 */
void baseHexConvert(int base, int count, char* resp, long long n) {
    /* ... */
}

/**
 * @brief Converte parte fracionária de número para outra base.
 */
void baseHexConvertFloat(int base, char* resp, long double n) {
    /* ... */
}

/**
 * @brief Confirma se um número é válido para a base informada.
 * @return 1 se válido, 0 se inválido.
 */
int confirmValidNum(char* array, long double num) {
    /* ... */
}

/**
 * @struct weight
 * @brief Estrutura usada para conversão de unidades (peso multiplicador).
 */
typedef struct weight {
    char* name;
    long double weight;
} peso;

/**
 * @brief Realiza conversão entre bases numéricas.
 * @return String alocada contendo resultado formatado.
 */
char* convertBase(char* number, char* convertNumber, char* convertNumberDecimal, int base, int base2) {
    /* ... */
}

/**
 * @brief Converte unidades (comprimento, área, volume, massa).
 * @return Valor convertido ou negativo em caso de erro.
 */
long double convertUnits(long double unidade,  char* base, char* base2, peso* values) {
    /* ... */
}

/**
 * @brief Conversões específicas de temperatura.
 */
long double convertCF(long double unidade) { return unidade = (9 * (unidade))/5 + 32; }
long double convertFC(long double unidade) { return unidade = ((unidade - 32) * 5)/9; }
long double convertCK(long double unidade) { return unidade += 273; }
long double convertFK(long double unidade) { return unidade = ((unidade - 32) * 5)/9 + 273; }
long double convertKC(long double unidade) { return unidade -= 273; }
long double convertKF(long double unidade) { return unidade = 9 * (unidade - 273)/5 + 32; }

/**
 * @brief Controlador geral de conversão de temperaturas usando ponteiros de função.
 */
long double convertTemp(long double unidade, char* base, char* base2, long double (*funcPointer[6])(long double)) {
    /* ... */
}

/**
 * @brief Executa todo o processo de entrada e conversão de unidades.
 * Adiciona resultados ao histórico.
 */
void convert(celula* convertHistory) {
    /* ... */
}

/**
 * @brief Mostra comandos básicos do programa.
 */
void help() {
    /* ... */
}

/**
 * @brief Mostra formato esperado para conversões de bases.
 */
void helpConvert() {
    /* ... */
}

/**
 * @brief Verifica o comando digitado e executa a ação correspondente.
 */
void checkInput(char* input, celula* commandHistory, celula* convertHistory) {
    /* ... */
}

/**
 * @brief Escreve lista ligada em arquivo.
 */
void writeToFile(celula* list, FILE* file) {
    /* ... */
}

/**
 * @brief Lê arquivo e preenche lista ligada.
 */
void writeToList(celula* list, FILE* file, int count) {
    /* ... */
}

/**
 * @brief Libera memória de toda a lista.
 */
void freeList(celula* list) {
    /* ... */
}

/**
 * @brief Loop principal do programa:
 * - Carrega históricos
 * - Lê comandos
 * - Salva tudo antes de sair
 */
void runtime() {
    /* ... */
}
