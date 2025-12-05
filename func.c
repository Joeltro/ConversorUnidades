/**
 * @file func.c
 * @brief Implementação completa das funções de conversão, histórico, validação e execução do programa.
 */

#include "func.h"

/**
 * @brief Adiciona uma nova célula vazia após a célula fornecida.
 * @param cel Ponteiro para a célula atual.
 */
void addToList(celula* cel) {
    celula* a = malloc(sizeof(celula));
    a->command = NULL;
    a->prox = cel->prox;
    cel->prox = a;
}

/**
 * @brief Adiciona um comando ao histórico (lista encadeada) de forma recursiva.
 * @param cel Ponteiro para a célula atual na lista.
 * @param input String contendo o comando a ser adicionado.
 * @param count Número do comando (utilizado para indexação).
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
 * @brief Função recursiva que calcula a exponencial de um número a com expoente b.
 * 
 * Aceita expoentes negativos e positivos.
 * 
 * @param a Base.
 * @param b Expoente (inteiro).
 * @return Resultado de a^b como long double.
 */
long double exponencial(long double a, int b) { // função recursiva que calcula a exponencial de um número a com expoente b
    if(b == 0) {// se o expoente é igual a 0, retorna um numero 1
        return 1;
    } else if(b == 1) { // se o expoente é igual a 1, retorna o próprio número  
        return a;
    } else if(b == -1) { // se o expoente é igual a -1, retorna o número inverso
        return 1/a;
    } else if(b > 0) { // se o expoente é maior que 0 chama-se o número multiplicado por ele mesmo e passando expoente -  1
        return a * exponencial(a, b - 1); 
    } else {
        return 1/a * exponencial(a, b + 1); // se não, chama o inverso do número passando ele multiplicando pelo expoente até o expoente chegar a 0
    }
}

/**
 * @brief Imprime a lista de histórico de comandos.
 * 
 * Percorre recursivamente a lista encadeada e imprime cada comando.
 * @param cel Ponteiro para o início da lista.
 */
void viewHistory(celula* cel) { // função de visualização da lista do histórico de comandos
    if(cel->prox == NULL) { // verificação se a lista está vazia
        printf("Lista vazia\n");
    } else if((cel->prox)->prox == NULL) { // se o cel que aponta para o proximo que aponta para o proximo for NULL, printa a lista
        printf("%s\n", cel->command);
    } else {
        printf("%s\n", cel->command); // se não for null, ele vai printando a lista e chamando a função recursivamente
        viewHistory(cel->prox);
    }
}

/**
 * @brief Lógica de conversão de um dígito para decimal (utilizada na conversão de base).
 * 
 * Converte caracteres '0'-'9' e 'A'-'F' para seus valores numéricos e acumula no ponteiro sum.
 * 
 * @param array String contendo o número.
 * @param base Base numérica do número.
 * @param count Índice do caractere a ser processado.
 * @param power Potência associada à posição do dígito.
 * @param sum Ponteiro para o acumulador do resultado decimal.
 */
void decLogic(char* array, int base, int count, int power, long double* sum) {
    if(*(array + count) == 'A') {
        *sum += 10 * exponencial(base, power);
    } else if(*(array + count) == 'B') {
        *sum += 11 * exponencial(base, power);
    } else if(*(array + count) == 'C') {
        *sum += 12 * exponencial(base, power);
    } else if(*(array + count) == 'D') {
        *sum += 13 * exponencial(base, power);
    } else if(*(array + count) == 'E') {
        *sum += 14 * exponencial(base, power);
    } else if(*(array + count) == 'F') {
        *sum += 15 * exponencial(base, power);
    } else if(*(array + count) - '0' < 10) {
        *sum += (*(array + count) - '0') * exponencial(base, power);
    }
}

/**
 * @brief Converte recursivamente uma string representando um número em uma base qualquer para decimal.
 * 
 * @param array String contendo o número.
 * @param base Base do número.
 * @param count Índice inicial (geralmente strlen - 1).
 * @param power Potência inicial (geralmente 0).
 * @param sum Ponteiro para o acumulador do resultado decimal.
 */
void baseDecConvert(char* array, int base, int count, int power, long double* sum) {
    if(count == 0) {
        decLogic(array, base, count, power, sum);
    } else {
        decLogic(array, base, count, power, sum); // -> função que contém a logica da mudança de base
        baseDecConvert(array, base, count - 1, power + 1, sum); // essa função será retornada enquanto o contador não for 0
    }
}

/**
 * @brief Inverte uma string recursivamente (necessário para mostrar números na ordem correta).
 * 
 * @param array String a ser invertida.
 * @param start Índice inicial.
 * @param end Índice final.
 */
void reverseString(char* array, int start, int end) {
    if(end == start) {
        return;
    } else if(end - start == 1) {
        array[start] ^= array[end];
        array[end] ^= array[start];
        array[start] ^= array[end];
    } else {
        array[start] ^= array[end];
        array[end] ^= array[start];
        array[start] ^= array[end];
        reverseString(array, start + 1, end - 1);
    }
}

/**
 * @brief Encontra as partes do número e as bases a partir de uma string no formato esperado.
 * 
 * Procura por pontos, parênteses e identificadores de base.
 * 
 * @param array Entrada completa.
 * @param array2 Buffer para parte inteira do número.
 * @param array3 Buffer para parte decimal do número.
 * @param base Buffer para base original (texto dentro de parênteses ou sequencia após ')').
 * @param base2 Buffer para base destino (sequencia de caracteres após a base original).
 */
void findBase(char* array, char* array2, char* array3, char* base, char* base2) { // função que acha a base do numero -> numero(base)
    for(int i = 0; i < 100; i++) {
        if(array[i] == '.') {
            strncpy(array2, array, i);
            for(int j = i; j < 100; j++) {
                if(array[j] == '(') {
                    strncpy(array3, (array + i + 1), j - (i + 1));
                    for(int k = j; k < 100; k++) {
                        if(array[k] == ')') {
                            strncpy(base, (array + j + 1), k - (j + 1));
                            for(int l = k + 1; l < 100; l++) {
                                if((array[l] >= 48 && array[l] <= 57) || (array[l] >= 65 && array[l] <= 90) || (array[l] >= 97 && array[l] <= 122)) {
                                    strcpy(base2, (array + l));
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    break;        
                }
            }
            break;
        } else if(array[i] == '(') { // esse algoritmo é utilizado para ignorar o parentesis e e ler apenas o número que está dentro dele
            strncpy(array2, array, i);
            for(int j = i; j < 100; j++) {
                if(array[j] == ')') {
                    strncpy(base, (array + i + 1), j - (i + 1)); // utiliza-se o atoi para ler a parte inteira da string após ignorar o parentesis
                    for(int k = j + 1; k < 100; k++) {
                        if((array[k] >= 48 && array[k] <= 57) || (array[k] >= 65 && array[k] <= 90) || (array[k] >= 97 && array[k] <= 122)) {
                            strcpy(base2, (array + k));
                            break;
                        }
                    }
                    break;
                } 
            }
            break;
        }
    }
}

/**
 * @brief Converte restos de divisão em dígitos/letters (0-9, A-F) para montagem de número em base destino.
 * 
 * @param base Base destino.
 * @param count Índice no buffer de resposta.
 * @param resp Buffer de resposta onde o dígito convertido é colocado.
 * @param n Valor atual (long long) a ser convertido.
 */
void hexLogic(int base, int count, char* resp, long long n) {
    if(n % base < 10) {
        *(resp + count) = (n % base + '0');
    } else if(n % base == 10) {
        *(resp + count) = 'A';
    } else if(n % base == 11) {
        *(resp + count) = 'B';
    } else if(n % base == 12) {
        *(resp + count) = 'C';
    } else if(n % base == 13) {
        *(resp + count) = 'D';
    } else if(n % base == 14) {
        *(resp + count) = 'E';
    } else if(n % base == 15) {
        *(resp + count) = 'F';
    }
}

/**
 * @brief Converte parte inteira de número decimal para base destino de forma recursiva.
 * 
 * @param base Base destino.
 * @param count Índice no buffer de resposta.
 * @param resp Buffer de resposta para os dígitos.
 * @param n Valor inteiro a ser convertido.
 */
void baseHexConvert(int base, int count, char* resp, long long n) {
    if(n < base) {
        hexLogic(base, count, resp, n); // se o numero for menor que base, apenas retorna a função
    } else {
        hexLogic(base, count, resp, n); // se não, a função será repetida n vezes até que n seja menor que a base
        baseHexConvert(base, count + 1, resp, n / base);
    } 
}

/**
 * @brief Converte parte fracionária de número decimal para base destino (tratamento para floats).
 * 
 * @param base Base destino.
 * @param resp Buffer de resposta para parte fracionária.
 * @param n Parte fracionária a ser convertida (entre 0 e 1).
 */
void baseHexConvertFloat(int base, char* resp, long double n) {// função de conversão de bases hexadecimais com números com pontos flutuantes
    int count = 0;
    for(int i = 0; i < 99 && ((n - (long long)n < 0.999) || count == 0) && n != 0; i++) {
        n *= base;
        long double temp = n;
        temp += 0.001;
        if((int)temp == 15) {
            resp[count] = 'F';
            count++;
        } else if((int)temp == 14) {
            resp[count] = 'E';
            count++;
        } else if((int)temp == 13) {
            resp[count] = 'D';
            count++;
        } else if((int)temp == 12) {
            resp[count] = 'C';
            count++;
        } else if((int)temp == 11) {
            resp[count] = 'B';
            count++;
        } else if((int)temp == 10) {
            resp[count] = 'A';
            count++;
        } else {
            resp[count] = (int)temp + '0';
            count++;
        }
        n -= (long long)n;
    }
}

/**
 * @brief Verifica se os caracteres da string são válidos para a base fornecida.
 * 
 * Retorna 1 se válido, 0 se inválido (imprime mensagem de erro).
 * 
 * @param array String contendo o número (somente parte a ser validada).
 * @param num Valor numérico representando a base (ex: 10, 16).
 * @return int 1 se válido, 0 se inválido.
 */
int confirmValidNum(char* array, long double num) { // verificação se o número é valido para a base selecionada
    for(int i = 0; i < 100 && array[i] != 0; i++) {
        if((*(array + i) >= 48) && (*(array + i) <= 57) && *(array + i) - '0' >= num) {
            printf("Numero invalido para base selecionada\n");
            return 0;
        } else if((num == 15) && array[i] >= 70) {
            printf("Numero invalido para base selecionada\n");
            return 0;
        } else if((num == 14) && array[i] >= 69) {
            printf("Numero invalido para base selecionada\n");
            return 0;
        } else if((num == 13) && array[i] >= 68) {
            printf("Numero invalido para base selecionada\n");
            return 0;
        } else if((num == 12) && array[i] >= 67) {
            printf("Numero invalido para base selecionada\n");
            return 0;
        } else if((num == 11) && array[i] >= 66) {
            printf("Numero invalido para base selecionada\n");
            return 0;
        } else if((num == 10) && array[i] >= 65) {
            printf("Numero invalido para base selecionada\n");
            return 0;
        }
    }
    return 1;
}

/**
 * @struct weight
 * @brief Struct usada para conversão de unidades com fator de multiplicação.
 */
typedef struct weight { // struct para conversão de unidades
    char* name;
    long double weight;
} peso;

/**
 * @brief Converte entre bases e formata o resultado em uma string alocada.
 * 
 * @param number String original (usada para montar saída).
 * @param convertNumber Parte inteira do número a ser convertida.
 * @param convertNumberDecimal Parte fracionária do número a ser convertida.
 * @param base Base original.
 * @param base2 Base destino.
 * @return char* String alocada contendo a conversão no formato "original = convertido". Deve ser liberada pelo chamador.
 */
char* convertBase(char* number, char* convertNumber, char* convertNumberDecimal, int base, int base2, int negative) { // função que irá ler os números e a as bases
    int power = 0;
    long double resp = 0, resp2 = 0;
    char hexString[100] = "0";
    char hexStringFloat[100] = "0";
    char* returnString = NULL;
    int count = strlen(convertNumber) - 1;
    int count2 = strlen(convertNumberDecimal) - 1;
    if(base2 == 10) { // logica de conversão para base 10
        baseDecConvert(convertNumber, base, count, power, &resp);
        baseDecConvert(convertNumberDecimal, base, count2, -(count2 + 1), &resp2);
        baseHexConvert(10, 0, hexString, resp);
        baseHexConvertFloat(base2, hexStringFloat, resp2);
        reverseString(hexString, 0, strlen(hexString) - 1);
        if(negative) {
            printf("Convertido para base 10: -%Lf\n", resp + resp2);
            returnString = malloc((snprintf(NULL, 0, "%s = -%s.%s", number, hexString, hexStringFloat) + 1) * sizeof(char));
            sprintf(returnString, "%s = -%s.%s", number, hexString, hexStringFloat);
            return returnString;
        } else {
            printf("Convertido para base 10: %Lf\n", resp + resp2);
            returnString = malloc((snprintf(NULL, 0, "%s = %s.%s", number, hexString, hexStringFloat) + 1) * sizeof(char));
            sprintf(returnString, "%s = %s.%s", number, hexString, hexStringFloat);
            return returnString;
        }
    } else { // caso a base desejada para  conversão seja diferente de 10, cai nessa chamada
        baseDecConvert(convertNumber, base, count, power, &resp);
        baseDecConvert(convertNumberDecimal, base, count2, -(count2 + 1), &resp2); 
        baseHexConvert(base2, 0, hexString, resp);
        baseHexConvertFloat(base2, hexStringFloat, resp2);
        if(negative) {
            printf("Convertido para base %i: -", base2);
            reverseString(hexString, 0, strlen(hexString) - 1);
            printf("%s.%s\n", hexString, hexStringFloat);
            returnString = malloc((snprintf(NULL, 0, "%s = -%s.%s", number, hexString, hexStringFloat) + 1) * sizeof(char));
            sprintf(returnString, "%s = -%s.%s", number, hexString, hexStringFloat);
            return returnString;
        } else {
            printf("Convertido para base %i: ", base2);
            reverseString(hexString, 0, strlen(hexString) - 1); // passa como argumento a hexString que serve para conversão de inteiros em letras
            printf("%s.%s\n", hexString, hexStringFloat);
            returnString = malloc((snprintf(NULL, 0, "%s = %s.%s", number, hexString, hexStringFloat) + 1) * sizeof(char));
            sprintf(returnString, "%s = %s.%s", number, hexString, hexStringFloat);
            return returnString;
        }
    }
}

/**
 * @brief Converte entre unidades usando a tabela de pesos (fatores).
 * 
 * @param unidade Valor a ser convertido.
 * @param base Nome da unidade de origem.
 * @param base2 Nome da unidade destino.
 * @param values Array de structs peso contendo nomes e fatores.
 * @return long double Valor convertido ou negativo em caso de erro (base não encontrada).
 */
long double convertUnits(long double unidade,  char* base, char* base2, peso* values) { // função que utiliza da struct para converter as unidades do programa
    long double n = 0, n2 = 0;
    for(int i = 0; i < 7; i++) {
        if(!strcmp(base, (values + i)->name)) { // verifica se base(base inicial) e values são iguais, se forem diferentes executa a função
            n = (values + i)->weight; // então o long Double recebe o valor que aponta para a unidade de medida
        } else if(!strcmp(base2, (values + i)->name)) {
            n2 = (values + i)->weight;
        }
    }
    if(n != 0 && n2 != 0) {
        return unidade * (n/n2); 
    } else {
        return -unidade;
    }
}

/**
 * @brief Converte Celsius para Fahrenheit.
 * @param unidade Temperatura em Celsius.
 * @return Temperatura em Fahrenheit.
 */
long double convertCF(long double unidade) {
    return unidade = (9 * (unidade))/5 + 32; // converter Celsius para Fahrenheit
}

/**
 * @brief Converte Fahrenheit para Celsius.
 * @param unidade Temperatura em Fahrenheit.
 * @return Temperatura em Celsius.
 */
long double convertFC(long double unidade) {
    return unidade = ((unidade - 32) * 5)/9; // converter Fahrenheit para Celsius
}

/**
 * @brief Converte Celsius para Kelvin.
 * @param unidade Temperatura em Celsius.
 * @return Temperatura em Kelvin.
 */
long double convertCK(long double unidade) {
    return unidade += 273; // converter Celsius para Kelvin
}

/**
 * @brief Converte Fahrenheit para Kelvin.
 * @param unidade Temperatura em Fahrenheit.
 * @return Temperatura em Kelvin.
 */
long double convertFK(long double unidade) {
    return unidade = ((unidade - 32) * 5)/9 + 273;
}

/**
 * @brief Converte Kelvin para Celsius.
 * @param unidade Temperatura em Kelvin.
 * @return Temperatura em Celsius.
 */
long double convertKC(long double unidade) {
    return unidade -= 273; // converter Kelvin para Celsius
}

/**
 * @brief Converte Kelvin para Fahrenheit.
 * @param unidade Temperatura em Kelvin.
 * @return Temperatura em Fahrenheit.
 */
long double convertKF(long double unidade) {
    return unidade = 9 * (unidade - 273)/5 + 32 ; // converter Kelvin para Fahrenheit
}

/**
 * @brief Controlador geral para conversões de temperatura usando um vetor de ponteiros para funções.
 * 
 * Verifica as combinações de unidades e chama a função específica correspondente.
 * 
 * @param unidade Valor a ser convertido.
 * @param base Unidade origem ("C", "F" ou "K").
 * @param base2 Unidade destino ("C", "F" ou "K").
 * @param funcPointer Vetor de ponteiros para funções de conversão.
 * @return Resultado convertido ou -unidade se combinação inválida.
 */
long double convertTemp(long double unidade, char* base, char* base2, long double (*funcPointer[6])(long double)) { // função que utiliza de ponteiro para função para conversão de temperaturas
    if(!strcmp(base, "C")) { // compara se a base inicial é igual a celsius
        if(!strcmp(base2, "F")) { // compara se a base final é igual fahrenheit
            return funcPointer[0](unidade); // a depender da igualdade, chama o ponteiro para função passando o "caso"
        } else if(!strcmp(base2, "K")) {
            return funcPointer[1](unidade);
        } else if(!strcmp(base2, "C")) {
            return unidade;
        }
    } else if(!strcmp(base, "F")) {
        if(!strcmp(base2, "C")) {
            return funcPointer[2](unidade);
        } else if(!strcmp(base2, "K")) {
            return funcPointer[3](unidade);
        } else if(!strcmp(base2, "F")) {
            return unidade;
        }
    } else if(!strcmp(base, "K")) {
        if(!strcmp(base2, "C")) {
            return funcPointer[4](unidade);
        } else if(!strcmp(base2, "F")) {
            return funcPointer[5](unidade);
        } else if(!strcmp(base2, "K")) {
            return unidade;
        }
    }
    return -unidade;
}

/**
 * @brief Função interativa que realiza conversões (bases, unidades, temperatura) e registra no histórico.
 * 
 * Lê entrada do usuário, valida bases, realiza conversão correspondente e adiciona resultado ao histórico.
 * 
 * @param convertHistory Ponteiro para a lista de histórico de conversões.
 */
void convert(celula* convertHistory) {
    char number[100];
    char convertNumber[100] = "0";
    char convertNumberDecimal[100] = "0";
    char base[5] = "0", base2[5] = "0";
    int validBase = 0, validBaseDecimal = 0, negative = 0;
    peso valuesC[] = { // esse array guarda os valores predefinidos de unidades de medida
        {"mm", 0.001},
        {"cm", 0.01},
        {"m", 1},
        {"km", 1000},
        {"in", 0.0254},
        {"ft", 0.3048},
        {"mi", 1609.34},
    };
    peso valuesA[] = { // unidades de area
        {"m^2", 1},
        {"cm^2", 0.0001},
        {"ac", 4045.8564},
        {"ha", 10000},
        {"ft^2", 0.0929},
        {"in^2", 0.0006451}
    };
    peso valuesV[] = { // unidades de volume
        {"L", 1},
        {"ml", 0.001},
        {"m^3", 1000},
        {"in^3", 0.01638},
        {"ft^3", 28.3168}
    };
    peso valuesM[] = { // unidades de massa
        {"g", 1},
        {"kg", 1000},
        {"t", 1000000},
        {"lb", 453.6},
        {"oz", 28.35}
    };
    char* historyString = NULL;
    long double (*funcPointer[6])(long double) = {convertCF, convertCK, convertFC, convertFK, convertKC, convertKF};
    while(validBase == 0 || validBaseDecimal == 0) {
        negative = 0;
        long double resp = 0, resp2 = 0, sum = 0, num = 0, num2 = 0, final; 
        printf("Digite o numero que quer converter: ");
        scanf(" %99[^\n]", number);
        findBase(number, convertNumber, convertNumberDecimal, base, base2);
        if(convertNumber[0] == '-') { // verificação se o número digitado é negativo
            negative = 1;
            for(int i = 0; i < 99; i++) {
                convertNumber[i] = convertNumber[i + 1]; // caso seja negativo, o numero na posição i, recebe na posição i+1
            }
            convertNumber[99] = 0;
        }
        if(base[0] >= 48 && base[0] <= 57) {
            baseDecConvert(base, 10, strlen(base) - 1, 0, &num); // caso a base esteja naquele intervalo, essa função irá ficar chamando a função de conversão de base para poder validar
            baseDecConvert(base2, 10, strlen(base2) - 1, 0, &num2);
            validBase = confirmValidNum(convertNumber, num); // quando chamado a baseDecConvertm agora então a base está validada
            if(validBase == 1) {
                validBaseDecimal = confirmValidNum(convertNumberDecimal, num);
            }
            if(num2 < 2 || num2 > 16) { // função que verifica se a base desejada no final do calculo está no intervalo desejado
                printf("Base de conversao invalida\n");
                validBase = 0;
                validBaseDecimal = 0;
            }
            if(validBase == 1 && validBaseDecimal == 1) { // caso tudo esteja validado, então chama-se a função de conversão de base
                historyString = convertBase(number, convertNumber, convertNumberDecimal, num, num2, negative);
                addToHistory(convertHistory, historyString, 1);
                free(historyString);
                historyString = NULL;
            }
        } else if((base[0] >= 65 && base[0] <= 90) || (base[0] >= 97 && base[0] <= 122)) {
            baseDecConvert(convertNumber, 10, strlen(convertNumber) - 1, 0, &resp);
            baseDecConvert(convertNumberDecimal, 10, strlen(convertNumberDecimal) - 1, -(strlen(convertNumberDecimal)), &resp2);
            if(negative) {
                resp *= -1;
                resp2 *= -1;
            }
            sum = resp + resp2;
            final = convertTemp(sum, base, base2, funcPointer);
            if(final == -sum) {
                final = convertUnits(sum, base, base2, valuesC);
                if(final == -sum) {
                    final = convertUnits(sum, base, base2, valuesA);
                    if(final == -sum) {
                        final = convertUnits(sum, base, base2, valuesV);
                        if(final == -sum) {
                            final = convertUnits(sum, base, base2, valuesM);
                            if(final == -sum) {
                                printf("Base invalida\n");
                            } else {
                                printf("Convertido: %Lf %s\n", final, base2);
                                validBase = 1;
                                validBaseDecimal = 1;
                                historyString = malloc((snprintf(NULL, 0, "%s = %Lf", number, final) + 1) * sizeof(char));
                                sprintf(historyString, "%s = %Lf", number, final);
                                addToHistory(convertHistory, historyString, 1);
                                free(historyString);
                                historyString = NULL;
                            }
                        } else {
                            printf("Convertido: %Lf %s\n", final, base2);
                            validBase = 1;
                            validBaseDecimal = 1;
                            historyString = malloc((snprintf(NULL, 0, "%s = %Lf", number, final) + 1) * sizeof(char));
                            sprintf(historyString, "%s = %Lf", number, final);
                            addToHistory(convertHistory, historyString, 1);
                            free(historyString);
                            historyString = NULL;
                        }
                    } else {
                        printf("Convertido: %Lf %s\n", final, base2);
                        validBase = 1;
                        validBaseDecimal = 1;
                        historyString = malloc((snprintf(NULL, 0, "%s = %Lf", number, final) + 1) * sizeof(char));
                        sprintf(historyString, "%s = %Lf", number, final);
                        addToHistory(convertHistory, historyString, 1);
                        free(historyString);
                        historyString = NULL;
                    }
                } else {
                    printf("Convertido: %Lf %s\n", final, base2);
                    validBase = 1;
                    validBaseDecimal = 1;
                    historyString = malloc((snprintf(NULL, 0, "%s = %Lf", number, final) + 1) * sizeof(char));
                    sprintf(historyString, "%s = %Lf", number, final);
                    addToHistory(convertHistory, historyString, 1);
                    free(historyString);
                    historyString = NULL;
                }
            } else {
                printf("Convertido: %Lf %s\n", final, base2);
                validBase = 1;
                validBaseDecimal = 1;
                historyString = malloc((snprintf(NULL, 0, "%s = %Lf", number, final) + 1) * sizeof(char));
                sprintf(historyString, "%s = %Lf", number, final);
                addToHistory(convertHistory, historyString, 1);
                free(historyString);
                historyString = NULL;
            }
        }
    }
}

/**
 * @brief Mostra comandos disponíveis ao usuário.
 */
void () {
    printf("Commandos:\n");
    printf("convert -- Realiza conversao de unidades e bases\n");
    printf("hist -- Mostra historico de comandos e historico de conversao\n");
    //printf("op -- Realiza operacoes entre unidades diferentes\n");
    printf("q -- Sai do programa\n");
    printf("Digite ' -commando-' para ver parametros avancados\n");
}

/**
 * @brief Exibe instruções para uso do comando de conversão (formato de entrada, bases válidas, unidades).
 */
void helpConvert() {
    printf("Formato:\n.>Digitar -- 'X(Y) - Z' \nonde X eh o numero, Y a base de X e Z a base que deseja converter para\n");
    printf("=== BASES VALIDAS ===\n");
    printf("> Numeros de 2 ate 16\n");
    printf("> Comprimentos: milimetros = mm, centimetros = cm, metros = m, kilometros = km, polegadas = in, pes = ft, milhas = mi\n");
    printf("> Area: centimetros quadrados = cm^2, metros quadrados = m^2, acres = ac, hectares = ha, pes quadrados = ft^2, polegadas quadradas = in^2\n");
    printf("> Volume: litros = L, mililitros = ml, metros cubicos = m^3, polegadas cubicas = in^3, pes cubicos = ft^3\n");
    printf("> Massa: gramas = g, kilogramas = kg, tonelada = t, libra = lb, onca = oz\n");
    printf("> Temperatura: Celcius = C, Fahreinheit = F, Kelvin = K\n");
}

/**
 * @brief Verifica o comando digitado e direciona para a função apropriada.
 * 
 * Comandos suportados: help, convert, hist, help convert, q (sair).
 * 
 * @param input Comando digitado pelo usuário.
 * @param commandHistory Ponteiro para histórico de comandos (lista).
 * @param convertHistory Ponteiro para histórico de conversões (lista).
 */
void checkInput(char* input, celula* commandHistory, celula* convertHistory) { // essa função é quem irá ler os comandos digitados pelo usuario, a fim de fornecer informações sobre o programa
    if(!strcmp(input, "help")) { // se o input for help, ele mostra a lista de comandos convert
        help();
    } else if(!strcmp(input, "convert")) { // caso seja convert base, cai na situação de leitura de numero(base) e a base a qual deseja converter
        convert(convertHistory);
    } else if(!strcmp(input, "op")) {
        //op();
    } else if(!strcmp(input, "help convert")) { // caso seja help convert base, mostra a maneira como deve-se usar a conversão de bases
        helpConvert();
    } else if(!strcmp(input, "help op")) {
        //helpOp();
    } else if(!strcmp(input, "hist")) {
        printf("\n=== Historico de commandos ===\n");
        viewHistory(commandHistory);
        printf("\n=== Historico de conversoes ===\n");
        viewHistory(convertHistory);
        printf("\n");
    } else if(strcmp(input, "q")) {
        printf("Comando nao reconhecido\n"); // caso seja qualquer outro comando diferente de q e dos comandos acima, cai no caso de comando não reconhecido
    }
}

/**
 * @brief Escreve uma lista ligada de comandos em um arquivo (recursivo).
 * 
 * @param list Ponteiro para a lista de comandos.
 * @param file Ponteiro para o arquivo aberto para escrita.
 */
void writeToFile(celula* list, FILE* file) {
    if(list->prox == NULL) {
        return;
    }
    if((list->prox)->prox == NULL) {
        fprintf(file, "%s\n", list->command);
    } else {
        fprintf(file, "%s\n", list->command);
        writeToFile(list->prox, file);
    }
}

/**
 * @brief Lê um arquivo linha a linha e adiciona cada linha como um nó na lista ligada.
 * 
 * @param list Ponteiro para nó atual da lista.
 * @param file Arquivo já aberto para leitura.
 * @param count Contador auxiliar para realocar string dinamicamente.
 */
void writeToList(celula* list, FILE* file, int count) {
    int c = fgetc(file);
    if(c == EOF) {
        return;
    } else if(c == '\n') {
        char* temp = realloc(list->command, (count + 1) * sizeof(char));
        if(temp == NULL) {
            printf("Erro ao alocar memoria\n");
            return;
        } else {
            list->command = temp;
            list->command[count] = 0;
        }
        addToList(list);
        writeToList(list->prox, file, 0);
    } else {
        char* temp = realloc(list->command, (count + 1) * sizeof(char));
        if(temp == NULL) {
            printf("Erro ao alocar memoria\n");
            return;
        } else {
            list->command = temp;
            list->command[count] = c;
        }
        writeToList(list, file, count + 1);
    }
}

/**
 * @brief Libera recursivamente a memória alocada para a lista ligada.
 * 
 * @param list Ponteiro para o início da lista.
 */
void freeList(celula* list) {
    if(list == NULL) {
        return;
    } else if(list->prox == NULL) {
        free(list->command);
        list->command = NULL;
        free(list);
        list = NULL;
    } else {
        freeList(list->prox);
        free(list->command);
        list->command = NULL;
        free(list);
        list = NULL;
    }
}

/**
 * @brief Loop principal do programa: carrega históricos, processa comandos do usuário e salva ao sair.
 * 
 * - Lê arquivos "historicoDeComandos.txt" e "historicoDeConversoes.txt" se existirem.
 * - Mostra mensagem inicial.
 * - Loop de leitura de comandos até o usuário digitar "q".
 * - Ao sair, grava históricos nos arquivos e libera memória.
 */
void runtime() { // função "principal" da func.c, o qual o programa irá começar e irá rodar até receber q como input
    int start = 0;
    char input[20] = "0";
    FILE* commands = fopen("historicoDeComandos.txt", "r");
    celula* commandHistory = malloc(sizeof(celula));
    commandHistory->command = NULL;
    commandHistory->prox = NULL;
    if(commands != NULL) {
        writeToList(commandHistory, commands, 0);
        fclose(commands);
    }
    FILE* conversions = fopen("historicoDeConversoes.txt", "r");
    celula* convertHistory = malloc(sizeof(celula));
    convertHistory->command = NULL;
    convertHistory->prox = NULL;
    if(conversions != NULL) {
        writeToList(convertHistory, conversions, 0);
        fclose(conversions);
    }
    if(start == 0) {
        printf("=== Conversor de unidades ===\n");
        printf("Digite 'help' para ver commandos\n");
        start = 1;
    }
    while(strcmp(input, "q") != 0) { // logica de rodar até o programa receber q como input
        scanf(" %19[^\n]", input);
        addToHistory(commandHistory, input, 1);
        checkInput(input, commandHistory, convertHistory);
    }
    commands = fopen("historicoDeComandos.txt", "w+");
    writeToFile(commandHistory, commands);
    fclose(commands);
    conversions = fopen("historicoDeConversoes.txt", "w+");
    writeToFile(convertHistory, conversions);
    fclose(conversions);
    freeList(commandHistory);
    freeList(convertHistory);
}
