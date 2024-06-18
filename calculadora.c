// calculadora.c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Definição da estrutura da pilha de strings
typedef struct NoStr {
    char dado[100];
    struct NoStr *proximo;
} NoStr;

typedef struct {
    NoStr *topo;
} PilhaStr;

// Função para inicializar a pilha de strings
void inicializarStr(PilhaStr *pilha) {
    pilha->topo = NULL;
}

// Função para empilhar uma string na pilha
void empilharStr(PilhaStr *pilha, const char *valor) {
    NoStr *novoNo = (NoStr *)malloc(sizeof(NoStr));
    if (novoNo == NULL) {
        printf("Erro: Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    strcpy(novoNo->dado, valor);
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

// Função para desempilhar uma string da pilha
char *desempilharStr(PilhaStr *pilha) {
    if (pilha->topo != NULL) {
        NoStr *temp = pilha->topo;
        char *valor = (char *)malloc(100 * sizeof(char));
        if (valor == NULL) {
            printf("Erro: Falha na alocação de memória\n");
            exit(EXIT_FAILURE);
        }
        strcpy(valor, temp->dado);
        pilha->topo = temp->proximo;
        free(temp);
        return valor;
    } else {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

// Função para verificar se um token é um operador
int ehOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}


// Definição da estrutura da pilha
typedef struct No {
    double dado;
    struct No *proximo;
} No;

typedef struct {
    No *topo;
} Pilha;

// Função para inicializar a pilha
void inicializar(Pilha *pilha) {
    pilha->topo = NULL;
}

// Função para empilhar um valor na pilha
void empilhar(Pilha *pilha, double valor) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro: Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    novoNo->dado = valor;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

// Função para desempilhar um valor da pilha
double desempilhar(Pilha *pilha) {
    if (pilha->topo != NULL) {
        No *temp = pilha->topo;
        double valor = temp->dado;
        pilha->topo = temp->proximo;
        free(temp);
        return valor;
    } else {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

// Função para verificar se uma substring é uma função especial válida
int ehFuncaoEspecial(const char *substr) {
    if (strcmp(substr, "sen") == 0 || strcmp(substr, "cos") == 0 || strcmp(substr, "log") == 0 || strcmp(substr, "tan") == 0 || strcmp(substr, "raiz") == 0) {
        return 1;
    }
    return 0;
}

// Função principal para avaliar uma expressão em notação pós-fixada
double avaliarExpressaoPosfixada(const char *expressao) {
    Pilha pilha;
    inicializar(&pilha);
    
    int i = 0;
    while (expressao[i] != '\0') {
        if (isdigit(expressao[i]) || (expressao[i] == '.' && isdigit(expressao[i+1]))) {
            char numero[20];
            int j = 0;
            while (isdigit(expressao[i]) || expressao[i] == '.') {
                numero[j++] = expressao[i++];
            }
            numero[j] = '\0';
            double valor = atof(numero);
            empilhar(&pilha, valor);
        } else if (isalpha(expressao[i])) {
            char funcao[5];
            int j = 0;
            while (isalpha(expressao[i]) && j < 4) {
                funcao[j++] = expressao[i++];
            }
            funcao[j] = '\0';
            
            if (ehFuncaoEspecial(funcao)) {
                double operando = desempilhar(&pilha);
                double radianos = operando * M_PI / 180.0;
                
                if (strcmp(funcao, "sen") == 0) {
                    empilhar(&pilha, sin(radianos));
                } else if (strcmp(funcao, "cos") == 0) {
                    empilhar(&pilha, cos(radianos));
                } else if (strcmp(funcao, "log") == 0) {
                    empilhar(&pilha, log10(operando));
                } else if (strcmp(funcao, "tan") == 0) {
                    empilhar(&pilha, tan(radianos));
                } else if (strcmp(funcao, "raiz") == 0) {
                    empilhar(&pilha, sqrt(operando));
                }
            } else {
                printf("Erro: Função especial inválida\n");
                exit(EXIT_FAILURE);
            }
        } else if (expressao[i] == '+' || expressao[i] == '-' || expressao[i] == '*' || expressao[i] == '/' || expressao[i] == '^') {
            double operando2 = desempilhar(&pilha);
            double operando1 = desempilhar(&pilha);
            
            switch (expressao[i]) {
                case '+':
                    empilhar(&pilha, operando1 + operando2);
                    break;
                case '-':
                    empilhar(&pilha, operando1 - operando2);
                    break;
                case '*':
                    empilhar(&pilha, operando1 * operando2);
                    break;
                case '/':
                    if (operando2 != 0.0) {
                        empilhar(&pilha, operando1 / operando2);
                    } else {
                        printf("Erro: Divisão por zero\n");
                        exit(EXIT_FAILURE);
                    }
                    break;
                case '^':
                    empilhar(&pilha, pow(operando1, operando2));
                    break;
                default:
                    printf("Erro: Operador inválido\n");
                    exit(EXIT_FAILURE);
            }
            i++;
        } else if (expressao[i] == ' ' || expressao[i] == '\t') {
            i++;
        } else {
            printf("Erro: Caractere inválido na expressão\n");
            exit(EXIT_FAILURE);
        }
    }
    
    return desempilhar(&pilha);
}

// Função para converter expressão pós-fixada para infixa (não implementada)
char *getFormaInFixa(char *posFixa) {
    PilhaStr pilha;
    inicializarStr(&pilha);
    
    int i = 0;
    while (posFixa[i] != '\0') {
        if (isdigit(posFixa[i]) || (posFixa[i] == '.' && isdigit(posFixa[i+1]))) {
            char numero[20];
            int j = 0;
            while (isdigit(posFixa[i]) || posFixa[i] == '.') {
                numero[j++] = posFixa[i++];
            }
            numero[j] = '\0';
            empilharStr(&pilha, numero);
        } else if (isalpha(posFixa[i])) {
            char funcao[5];
            int j = 0;
            while (isalpha(posFixa[i]) && j < 4) {
                funcao[j++] = posFixa[i++];
            }
            funcao[j] = '\0';
            
            if (ehFuncaoEspecial(funcao)) {
                char *operando = desempilharStr(&pilha);
                char resultado[100];
                snprintf(resultado, sizeof(resultado), "%s(%s)", funcao, operando);
                empilharStr(&pilha, resultado);
                free(operando);
            } else {
                printf("Erro: Função especial inválida\n");
                exit(EXIT_FAILURE);
            }
        } else if (ehOperador(posFixa[i])) {
            char *operando2 = desempilharStr(&pilha);
            char *operando1 = desempilharStr(&pilha);
            char resultado[100];
            snprintf(resultado, sizeof(resultado), "(%s %c %s)", operando1, posFixa[i], operando2);
            empilharStr(&pilha, resultado);
            free(operando1);
            free(operando2);
            i++;
        } else if (posFixa[i] == ' ' || posFixa[i] == '\t') {
            i++;
        } else {
            printf("Erro: Caractere inválido na expressão\n");
            exit(EXIT_FAILURE);
        }
    }
    
    char *resultadoFinal = desempilharStr(&pilha);
    return resultadoFinal;
}

// Função para obter o valor de uma expressão pós-fixada
float getValor(char *posFixa) {
    return (float)avaliarExpressaoPosfixada(posFixa);
}
