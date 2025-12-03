#include "func.h"

void initString(char* string, int size) {
    for(int i = 0; i < size; i++) {
        string[i] = 0;
    }
}

void addToList(celula* cel) {
    celula* a = malloc(sizeof(celula));
    a->command = NULL;
    a->prox = cel->prox;
    cel->prox = a;
}

void addToHistory(celula* cel, char* input, int count) {
    if(cel->prox == NULL) {
        cel->command = malloc((snprintf(NULL, 0, "%i. %s", count, input) + 1) * sizeof(char));
        sprintf(cel->command, "%i. %s", count, input);
        addToList(cel);
    } else {
        addToHistory(cel->prox, input, count + 1);
    }
}

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

// função que possui a logica da transformação de bases
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

// essa função contém a logica de transformar os números maiores que 9 em letras
// além de conter a logica de transformação de bases para hexadecimal
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

// função que chama de maneira recursiva a função de cima que contém toda a logica da conversão de base
void baseHexConvert(int base, int count, char* resp, long long n) {
    if(n < base) {
        hexLogic(base, count, resp, n); // se o numero for menor que base, apenas retorna a função
    } else {
        hexLogic(base, count, resp, n); // se não, a função será repetida n vezes até que n seja menor que a base
        baseHexConvert(base, count + 1, resp, n / base);
    } 
}

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

typedef struct weight { // struct para conversão de unidades
    char* name;
    long double weight;
} peso;

char* convertBase(char* number, char* convertNumber, char* convertNumberDecimal, int base, int base2) { // função que irá ler os números e a as bases
    int power = 0, negative = 0; 
    long double resp = 0, resp2 = 0;
    char hexString[100] = "0";
    char hexStringFloat[100] = "0";
    char* returnString = NULL;
    if(convertNumber[0] == '-') {
        negative = 1;
        for(int i = 0; i < 99; i++) {
            convertNumber[i] = convertNumber[i + 1];
        }
        convertNumber[99] = 0;
    }
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
            returnString = malloc((snprintf(NULL, 0, "%s = -%s.%s", number, hexString, hexStringFloat) + 1) * sizeof(char));
            sprintf(returnString, "%s = %s.%s", number, hexString, hexStringFloat);
            return returnString;
        }
    } else { // caso a base desejada para  conversão seja diferente de 10, cai nessa chamada
        baseDecConvert(convertNumber, base, count, power, &resp);
        baseDecConvert(convertNumberDecimal, base, count2, -(count2 + 1), &resp2); 
        baseHexConvert(base2, 0, hexString, resp);
        baseHexConvertFloat(base2, hexStringFloat, resp2);
        if(negative) {
            printf("Convertido para base %i: ", base2);
            reverseString(hexString, 0, strlen(hexString) - 1);
            printf("%s.%s\n", hexString, hexStringFloat);
            returnString = malloc((snprintf(NULL, 0, "%s = -%s.%s", number, hexString, hexStringFloat) + 1) * sizeof(char));
            sprintf(returnString, "%s = -%s.%s", number, hexString, hexStringFloat);
            return returnString;
        } else {
            printf("Convertido para base %i: ", base2);
            reverseString(hexString, 0, strlen(hexString) - 1); // passa como argumento a hexString que serve para conversão de inteiros em letras
            printf("%s.%s\n", hexString, hexStringFloat);
            returnString = malloc((snprintf(NULL, 0, "%s = -%s.%s", number, hexString, hexStringFloat) + 1) * sizeof(char));
            sprintf(returnString, "%s = %s.%s", number, hexString, hexStringFloat);
            return returnString;
        }
    }
}

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

long double convertCF(long double unidade) {
    return unidade = (9 * (unidade))/5 + 32; // converter Celsius para Fahrenheit
}

long double convertFC(long double unidade) {
    return unidade = ((unidade - 32) * 5)/9; // converter Fahrenheit para Celsius
}

long double convertCK(long double unidade) {
    return unidade += 273; // converter Celsius para Kelvin
}

long double convertFK(long double unidade) {
    return unidade = ((unidade - 32) * 5)/9 + 273;
}

long double convertKC(long double unidade) {
    return unidade -= 273; // converter Kelvin para Celsius
}

long double convertKF(long double unidade) {
    return unidade = 9 * (unidade - 273)/5 + 32 ; // converter Kelvin para Fahrenheit
}

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

// essa função irá converter as unidades utilizando a struct peso para guardar o valor já predefinido de cada unidade
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
        {"mL", 0.001},
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
                historyString = convertBase(number, convertNumber, convertNumberDecimal, num, num2);
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

// função que irá mostrar os comandos do programa até o momento, para nortear o usúario 
void help() {
    printf("Commandos:\n");
    printf("convert temp -- Realiza conversao de unidades e bases\n");
    //printf("op -- Realiza operacoes entre unidades diferentes\n");
    printf("q -- Sai do programa\n");
    printf("Digite 'help -commando-' para ver parametros avancados\n");
}

// função que irá fornecer informações sobre como o número para conversão de bases deve ser digitado, e a maneira de selecionar a base de conversão
void helpConvert() {
    printf("Formato:\n.>Digitar -- 'X(Y) - Z' \nonde X eh o numero, Y a base de X e Z a base que deseja converter para\n");
    printf("=== BASES VALIDAS ===\n");
    printf("> Numeros de 2 ate 16\n");
    printf("> Comprimentos: milimetros = mm, centimetros = cm, metros = m, kilometros = km, polegadas = in, pes = ft, milhas = mi\n");
    printf("> Area: centimetros quadrados = cm^2, metros quadrados = m^2, acres = ac, hectares = ha, pes quadrados = ft^2, polegadas quadradas = in^2\n");
    printf("> Volume: litros = L, mililitros = mL, metros cubicos = m^3, polegadas cubicas = in^3, pes cubicos = ft^3\n");
    printf("> Massa: gramas = g, kilogramas = kg, tonelada = t, libra = lb, onca = oz\n");
    printf("> Temperatura: Celcius = C, Fahreinheit = F, Kelvin = K\n");
}

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
