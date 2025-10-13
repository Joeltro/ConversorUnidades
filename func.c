#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


// função que possui a logica da transformação de bases
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
// função recursiva que irá ficar chamando a função decLogic que contém a logica da transformação de bases
int baseDecConvert(char* array, int base, int count, int power, int* sum) {
    if(count < 0) {
        return 0;
    } else {
        decLogic(array, base, count, power, sum); // -> função que contém a logica da mudança de base
        return baseDecConvert(array, base, count - 1, power + 1, sum); // essa função será retornada enquanto o contador não for 0
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

void findBase(char* array, char* array2, int* base) { // função que acha a base do numero -> numero(base)
    for(int i = 0; i < 100; i++) {
        if(array[i] == '(') { // esse algoritmo é utilizado para ignorar o parentesis e e ler apenas o número que está dentro dele
            strncpy(array2, array, i);
            array2[i] = '\0';
            *base = atoi(array + i + 1); // utiliza-se o atoi para ler a parte inteira da string após ignorar o parentesis
            break;
        }
    }
}

// essa função contém a logica de transformar os números maiores que 9 em letras
// além de conter a logica de transformação de bases para hexadecimal
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
// função que chama de maneira recursiva a função de cima que contém toda a logica da conversão de base
void baseHexConvert(int base, int count, char* resp, int n) {
    if(n < base) {
        hexLogic(base, count, resp, n); // se o numero for menor que base, apenas retorna a função
    } else {
        hexLogic(base, count, resp, n); // se não, a função será repetida n vezes até que n seja menor que a base
        return baseHexConvert(base, count + 1, resp, n / base);
    } 
}

void convertTemp() { // essa função é a que serve para converter temperaturas
    printf("Digite o numero que quer converter: \n");
    int caso;
    double unidade;
    scanf("%lf", &unidade);
    printf("Digite o caso de conversao: ");
    scanf("%i", &caso);
    switch (caso) { // utiliza-se um switch case nela, pois existem 6 casos no total de conversão de temperaturas
    case 1:
        unidade = (9 * unidade )/5 + 32; // converter Celsius para Fahrenheit
        printf("%.2lf\n", unidade);
        break;
    case 2:
        unidade = ((unidade - 32) * 5)/9; // converter Fahrenheit para Celsius
        printf("%.2lf\n", unidade);
        break;
    case 3:
        unidade = unidade + 273; // converter Celsius para Kelvin
        printf("%.2lf\n", unidade); 
        break;
    case 4:
        unidade = ((unidade - 32) * 5)/9 + 273;
        printf("%.2lf\n", unidade); // converter Fahrenheit para Kelvin
        break;
    case 5:
        unidade = unidade - 273; // converter Kelvin para Celsius
        printf("%.2lf\n", unidade);
        break;
    case 6:
        unidade = 9 * (unidade - 273)/5 + 32 ; // converter Kelvin para Fahrenheit
        printf("%.2lf\n", unidade);
        break;
    }
}

void convertBase() { // função que irá ler os números e a as bases
    char number[100];
    char convertNumber[100] = "0";
    int base, base2 = 0, power = 0, resp = 0;
    char hexString[100] = "0";
    while(base2 < 2 || base2 > 16) { // limitador para que seja digitados apenas bases de 2 a 16
        printf("Digite o numero que quer converter: ");
        scanf("%99s", number);
        findBase(number, convertNumber, &base2);   // função que exclui o parentesis para ler apenas o inteiro da base
    }
    int count = strlen(convertNumber) - 1;
    printf("Digite a base que quer converter para: ");
    scanf("%i", &base);
    if(base == 10) { // logica de conversão para base 10
        baseDecConvert(convertNumber, base2, count, power, &resp);
        printf("%i\n", resp);
    } else {
        if(base2 != 10) { // caso a base desejada para  conversão seja diferente de 10, cai nessa chamada
            baseDecConvert(convertNumber, base2, count, power, &resp); 
            baseHexConvert(base, 0, hexString, resp);
            reverseString(hexString, strlen(hexString)); // passa como argumento a hexString que serve para conversão de inteiros em letras
        } else {
            baseHexConvert(base, 0, hexString, atoi(convertNumber));
            reverseString(hexString, strlen(hexString));
        }
    }
}
// função que irá mostrar os comandos do programa até o momento, para nortear o usúario 
void help() {
    printf("Commandos:\n");
    printf("convert temp -- Realiza conversao de unidades de temperatura\n");
    printf("convert base -- Realiza conversao de bases numericas\n");
    //printf("op -- Realiza operacoes entre unidades diferentes\n");
    printf("q -- Sai do programa\n");
    printf("Digite 'help -commando-' para ver parametros avancados\n");
}
// função que irá mostrar os casos de conversão de temperatura, presentes no switch case
void helpConvertTemp() {
    printf("Formato: Digitar Quantidade a ser convertida, em seguida digitar o caso de conversao\n");
    printf("Caso 1: Conversao de Celsius para Fahrenheit\n");
    printf("Caso 2: Conversao de Fahrenheit para Celsius\n");
    printf("Caso 3: Conversao de Celsius para Kelvin\n");
    printf("Caso 4: Conversao de Fahrenheit para Kelvin\n");
    printf("Caso 5: Conversao de Kelvin para Celsius\n");
    printf("Caso 6: Conversao de Kelvin para Fahrenheit\n");
}
// função que irá fornecer informações sobre como o número para conversão de bases deve ser digitado, e a maneira de selecionar a base de conversão
void helpConvertBase() {
    printf("Formato: \n1. Digitar Quantidade a ser convertida -- X(Y), onde X eh o numero e Y sua base\n");
    printf("2. Digitar a base que desejar converter o numero para (2 - 16)");
}

void checkInput(char* input) { // essa função é quem irá ler os comandos digitados pelo usuario, a fim de fornecer informações sobre o programa
    if(strcmp(input, "help") == 0) { // se o input for help, ele mostra a lista de comandos convert
        help();
    } else if(strcmp(input, "convert temp") == 0) { // caso seja convert temp, cai na situação de leitura de temperatura e o caso que quer transformar
        convertTemp();
    } else if(strcmp(input, "convert base") == 0) { // caso seja convert base, cai na situação de leitura de numero(base) e a base a qual deseja converter
        convertBase();
    } else if(strcmp(input, "op") == 0) {
        //op();
    } else if(strcmp(input, "help convert temp") == 0) { // caso seja help convert temp, mostra a lista de comandos de conversão de temperaturas
        helpConvertTemp();
    } else if(strcmp(input, "help convert base") == 0) { // caso seja help convert base, mostra a maneira como deve-se usar a conversão de bases
        helpConvertBase();
    } else if(strcmp(input, "help op") == 0) {
        //helpOp();
    } else if(strcmp(input, "q") != 0) {
        printf("Comando nao reconhecido\n"); // caso seja qualquer outro comando diferente de q e dos comandos acima, cai no caso de comando não reconhecido
    }
}

void runtime() { // função "principal" da func.c, o qual o programa irá começar e irá rodar até receber q como input
    int start = 0;
    char input[20] = "0";
    if(start == 0) {
        printf("=== Conversor de unidades ===\n");
        printf("Digite 'help' para ver commandos\n");
        start = 1;
    }
    while(strcmp(input, "q") != 0) { // logica de rodar até o programa receber q como input
        scanf(" %[^\n]s", input);
        checkInput(input);
    }
}
