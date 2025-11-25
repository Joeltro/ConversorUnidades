#include "func.h"

void viewHistory(celula* cel, int count) {
    if(cel->prox == NULL) {
        printf("%s\n", cel->command);
    } else {
        printf("%i - %s\n", count, cel->command);
        viewHistory(cel->prox, count + 1);
    }
}

// função que possui a logica da transformação de bases
void decLogic(char* array, int base, int count, int power, long double* sum) {
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
void baseDecConvert(char* array, int base, int count, int power, long double* sum) {
    if(count == 0) {
        decLogic(array, base, count, power, sum);
    } else {
        decLogic(array, base, count, power, sum); // -> função que contém a logica da mudança de base
        baseDecConvert(array, base, count - 1, power + 1, sum); // essa função será retornada enquanto o contador não for 0
    }
}

//Imprime a string ao contrario, necessario para mostrar numero de forma correta.
void reverseString(char* array, int len) {
    if(len == 0) {
        printf("%c.", *(array + len));
    } else {
        printf("%c", *(array + len));
        reverseString(array, len - 1);
    }
}

void findBase(char* array, char* array2, char* array3, int* base) { // função que acha a base do numero -> numero(base)
    int limit = 0;
    for(int i = 0; i < 100; i++) {
        if(array[i] == '.') {
            strncpy(array2, array, i);
            limit = i + 1;
            for(int j = i; j < 100; j++) {
                if(array[j] == '(') {
                    strncpy(array3, (array + limit), j - limit);
                    *base = atoi(array + j + 1); // utiliza-se o atoi para ler a parte inteira da string após ignorar o parentesis
                    break;        
                }
            }
            break;
        } else if(array[i] == '(') { // esse algoritmo é utilizado para ignorar o parentesis e e ler apenas o número que está dentro dele
            strncpy(array2, array, i);
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
        baseHexConvert(base, count + 1, resp, n / base);
    } 
}

void baseHexConvertFloat(int base, char* resp, long double* n) {
    int count = 0;
    for(int i = 0; i < 99 && ((*n - (long long)*n < 0.9) || count == 0) && *n != 0; i++) {
        *n *= base;
        long double temp = *n;
        temp += 0.1;
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
        *n -= (long long)*n;
    }
}

void convertCF(double* unidade) {
        *unidade = (9 * *(unidade))/5 + 32; // converter Celsius para Fahrenheit
        printf("Temperatura convertida: %.2lf Fahreinheit\n", *unidade);
}

void convertFC(double* unidade) {
        *unidade = (*(unidade - 32) * 5)/9; // converter Fahrenheit para Celsius
        printf("Temperatura convertida: %.2lf Celcius\n", *unidade);
}

void convertCK(double* unidade) {
        *unidade += 273; // converter Celsius para Kelvin
        printf("Temperatura convertida: %.2lf Kelvin\n", *unidade);
}

void convertFK(double* unidade) {
        *unidade = (*(unidade - 32) * 5)/9 + 273;
        printf("Temperatura convertida: %.2lf Kelvin\n", *unidade); // converter Fahrenheit para Kelvin
}

void convertKC(double* unidade) {
        *unidade -= 273; // converter Kelvin para Celsius
        printf("Temperatura convertida: %.2lf Celcius\n", *unidade);
}

void convertKF(double* unidade) {
        *unidade = 9 * *(unidade - 273)/5 + 32 ; // converter Kelvin para Fahrenheit
        printf("Temperatura convertida: %.2lf Fahreinheit\n", *unidade);
}

void convertTemp() { // essa função é a que serve para converter temperaturas
    printf("Digite o numero que quer converter: \n");
    int caso;
    double unidade;
    scanf("%lf", &unidade);
    printf("Digite o caso de conversao: ");
    scanf("%i", &caso);
    void (*funcPointer[6])(double*) = {convertCF, convertFC, convertCK, convertFK, convertKC, convertKF}; //Vetor de ponteiros para funcoes
    funcPointer[caso - 1](&unidade);
}

void confirmValidNum(char* array, int* base2) {
    for(int i = 0; i < 100; i++) {
        if((*(array + i) >= 48) && (*(array + i) <= 57) && *(array + i) >= *base2 + '0') {
            printf("Numero invalido para base selecionada\n");
            *base2 = 1;
            break;
        } else if((*base2 == 15) && array[i] == 'F') {
            printf("Numero invalido para base selecionada\n");
            *base2 = 1;
            break;
        } else if((*base2 == 14) && array[i] == 'E') {
            printf("Numero invalido para base selecionada\n");
            *base2 = 1;
            break;
        } else if((*base2 == 13) && array[i] == 'D') {
            printf("Numero invalido para base selecionada\n");
            *base2 = 1;
            break;
        } else if((*base2 == 12) && array[i] == 'C') {
            printf("Numero invalido para base selecionada\n");
            *base2 = 1;
            break;
        } else if((*base2 == 11) && array[i] == 'B') {
            printf("Numero invalido para base selecionada\n");
            *base2 = 1;
            break;
        } else if((*base2 == 10) && array[i] == 'A') {
            printf("Numero invalido para base selecionada\n");
            *base2 = 1;
            break;
        }
    }
}

void convertBase() { // função que irá ler os números e a as bases
    char number[100];
    char convertNumber[100] = "0";
    char convertNumberDecimal[100] = "0";
    int base = 1, base2 = 1, power = 0, negative = 0;
    long double resp = 0, resp2 = 0;
    char hexString[100] = "0";
    char hexStringFloat[100] = "0";
    //base = Base que deseja convertar para
    //base2 = Base do numero
    while(base2 < 2 || base2 > 16) { // limitador para que seja digitados apenas bases de 2 a 16
        printf("Digite o numero que quer converter: ");
        scanf("%99s", number);
        findBase(number, convertNumber, convertNumberDecimal, &base2);   // função que exclui o parentesis para ler apenas o inteiro da base
        confirmValidNum(convertNumber, &base2);
        confirmValidNum(convertNumberDecimal, &base2);
    }
    if(convertNumber[0] == '-') {
        negative = 1;
        for(int i = 0; i < 99; i++) {
            convertNumber[i] = convertNumber[i+1];
        }
        convertNumber[99] = 0;
    }
    int count = strlen(convertNumber) - 1;
    int count2 = strlen(convertNumberDecimal) - 1;
    while(base < 2 || base > 16) {
        printf("Digite a base que quer converter para: ");
        scanf("%i", &base);
    }
    if(base == 10) { // logica de conversão para base 10
        baseDecConvert(convertNumber, base2, count, power, &resp);
        baseDecConvert(convertNumberDecimal, base2, count2, -(count2 + 1), &resp2);
        if(!negative) {
            printf("Convertido para base 10: %Lf\n", resp + resp2);
        } else {
            printf("Convertido para base 10: -%Lf\n", resp + resp2);
        }
    } else {
        if(base2 != 10) { // caso a base desejada para  conversão seja diferente de 10, cai nessa chamada
            baseDecConvert(convertNumber, base2, count, power, &resp);
            baseDecConvert(convertNumberDecimal, base2, count2, -(count2 + 1), &resp2); 
            baseHexConvert(base, 0, hexString, resp);
            baseHexConvertFloat(base, hexStringFloat, &resp2);
            if(negative) {
                printf("-");
            }
            reverseString(hexString, strlen(hexString)); // passa como argumento a hexString que serve para conversão de inteiros em letras
            printf("%s\n", hexStringFloat);
        } else {
            baseHexConvert(base, 0, hexString, atoi(convertNumber));
            baseDecConvert(convertNumberDecimal, base2, count2, -(count2 + 1), &resp2);
            baseHexConvertFloat(base, hexStringFloat, &resp2);
            if(negative) {
                printf("-");
            }
            reverseString(hexString, strlen(hexString));
            printf("%s\n", hexStringFloat);
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
    printf("2. Digitar a base que desejar converter o numero para (2 - 16)\n");
}

void checkInput(char* input, celula* history) { // essa função é quem irá ler os comandos digitados pelo usuario, a fim de fornecer informações sobre o programa
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
    } else if(strcmp(input, "hist") == 0) {
        printf("\n=== Historico de commandos ===\n");
        viewHistory(history, 1);
    } else if(strcmp(input, "q") != 0) {
        printf("Comando nao reconhecido\n"); // caso seja qualquer outro comando diferente de q e dos comandos acima, cai no caso de comando não reconhecido
    }
}

void addToList(celula* cel) {
    celula* a = malloc(sizeof(celula));
    a->ant = cel;
    a->prox = cel->prox;
    cel->prox = a;
}

void addToHistory(celula* cel, char* input) {
    if(cel->prox == NULL) {
        strcpy(cel->command, input);
        addToList(cel);
    } else {
        addToHistory(cel->prox, input);
    }
}

void runtime() { // função "principal" da func.c, o qual o programa irá começar e irá rodar até receber q como input
    int start = 0;
    char input[20] = "0";
    celula* history = malloc(sizeof(celula));
    history->ant = NULL;
    history->prox = NULL;
    if(start == 0) {
        printf("=== Conversor de unidades ===\n");
        printf("Digite 'help' para ver commandos\n");
        start = 1;
    }
    while(strcmp(input, "q") != 0) { // logica de rodar até o programa receber q como input
        scanf(" %[^\n]s", input);
        addToHistory(history, input);
        checkInput(input, history);
    }
}
