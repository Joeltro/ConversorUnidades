#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void decLogic(char* array, int base, int count, int power, int* sum) {
    if(*(array + count) == 'A') {
        *sum += 10 * pow(base, power);
    } else if(*(array + count) == 'B') {
        *sum += 11 * pow(base, power);
    } else if(*(array + count) == 'C') {
        *sum += 12 * pow(base, power);
    } else if(*(array + count) == 'D') {
        *sum += 13 * pow(base, power);
    } else if(*(array + count) == 'E') {
        *sum += 14 * pow(base, power);
    } else if(*(array + count) == 'F') {
        *sum += 15 * pow(base, power);
    } else if(*(array + count) - '0' < 10) {
        *sum += (*(array + count) - '0') * pow(base, power);
    }
}

int baseDecConvert(char* array, int base, int count, int power, int* sum) {
    if(count < 0) {
        return 0;
    } else {
        decLogic(array, base, count, power, sum);
        return baseDecConvert(array, base, count - 1, power + 1, sum);
    }
}

void reverseString(char* array, int len) {
    if(len == 0) {
        printf("%c\n", *(array + len));
    } else {
        printf("%c", *(array + len));
        return reverseString(array, len - 1);
    }
}

void findBase(char* array, char* array2, int* base) {
    for(int i = 0; i < 100; i++) {
        if(array[i] == '(') {
            strncpy(array2, array, i);
            array2[i] = '\0';
            *base = atoi(array + i + 1);
            break;
        }
    }
}

void hexLogic(int base, int count, char* resp, int n) {
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

void baseHexConvert(int base, int count, char* resp, int n) {
    if(n < base) {
        hexLogic(base, count, resp, n);
    } else {
        hexLogic(base, count, resp, n);
        return baseHexConvert(base, count + 1, resp, n / base);
    } 
}

void convertTemp() {
    printf("Digite o numero que quer converter: \n");
    int caso;
    double unidade;
    scanf("%lf", &unidade);
    printf("Digite o caso de conversao: ");
    scanf("%i", &caso);
    switch (caso) {
    case 1:
        unidade = (9 * unidade )/5 + 32;
        printf("%.2lf\n", unidade);
        break;
    case 2:
        unidade = ((unidade - 32) * 5)/9;
        printf("%.2lf\n", unidade);
        break;
    case 3:
        unidade = unidade + 273;
        printf("%.2lf\n", unidade);
        break;
    case 4:
        unidade = ((unidade - 32) * 5)/9 + 273;
        printf("%.2lf\n", unidade);
        break;
    case 5:
        unidade = unidade - 273;
        printf("%.2lf\n", unidade);
        break;
    case 6:
        unidade = 9 * (unidade - 273)/5 + 32 ;
        printf("%.2lf\n", unidade);
        break;
    }
}

void convertBase() {
    char number[100];
    char convertNumber[100] = "0";
    int base, base2 = 0, power = 0, resp = 0;
    char hexString[100] = "0";
    while(base2 < 2 || base2 > 16) {
        printf("Digite o numero que quer converter: ");
        scanf("%99s", number);
        findBase(number, convertNumber, &base2);    
    }
    int count = strlen(convertNumber) - 1;
    printf("Digite a base que quer converter para: ");
    scanf("%i", &base);
    if(base == 10) {
        baseDecConvert(convertNumber, base2, count, power, &resp);
        printf("%i\n", resp);
    } else {
        if(base2 != 10) {
            baseDecConvert(convertNumber, base2, count, power, &resp);
            baseHexConvert(base, 0, hexString, resp);
            reverseString(hexString, strlen(hexString));
        } else {
            baseHexConvert(base, 0, hexString, atoi(convertNumber));
            reverseString(hexString, strlen(hexString));
        }
    }
}

void help() {
    printf("Commandos:\n");
    printf("convert temp -- Realiza conversao de unidades de temperatura\n");
    printf("convert base -- Realiza conversao de bases numericas\n");
    //printf("op -- Realiza operacoes entre unidades diferentes\n");
    printf("q -- Sai do programa\n");
    printf("Digite 'help -commando-' para ver parametros avancados\n");
}

void helpConvertTemp() {
    printf("Formato: Digitar Quantidade a ser convertida, em seguida digitar o caso de conversao\n");
    printf("Caso 1: Conversao de Celsius para Fahrenheit\n");
    printf("Caso 2: Conversao de Fahrenheit para Celsius\n");
    printf("Caso 3: Conversao de Celsius para Kelvin\n");
    printf("Caso 4: Conversao de Fahrenheit para Kelvin\n");
    printf("Caso 5: Conversao de Kelvin para Celsius\n");
    printf("Caso 6: Conversao de Kelvin para Fahrenheit\n");
}

void helpConvertBase() {
    printf("Formato: \n1. Digitar Quantidade a ser convertida -- X(Y), onde X eh o numero e Y sua base\n");
    printf("2. Digitar a base que desejar converter o numero para (2 - 16)");
}

void checkInput(char* input) {
    if(strcmp(input, "help") == 0) {
        help();
    } else if(strcmp(input, "convert temp") == 0) {
        convertTemp();
    } else if(strcmp(input, "convert base") == 0) {
        convertBase();
    } else if(strcmp(input, "op") == 0) {
        //op();
    } else if(strcmp(input, "help convert temp") == 0) {
        helpConvertTemp();
    } else if(strcmp(input, "help convert base") == 0) {
        helpConvertBase();
    } else if(strcmp(input, "help op") == 0) {
        //helpOp();
    } else if(strcmp(input, "q") != 0) {
        printf("Comando nao reconhecido\n");
    }
}

void runtime() {
    int start = 0;
    char input[20] = "0";
    if(start == 0) {
        printf("=== Conversor de unidades ===\n");
        printf("Digite 'help' para ver commandos\n");
        start = 1;
    }
    while(strcmp(input, "q") != 0) {
        scanf(" %[^\n]s", input);
        checkInput(input);
    }
}
