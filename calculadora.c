#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h> // Para funções matemáticas como sqrt, sin, cos, log10

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
    if (strcmp(substr, "sen") == 0 || strcmp(substr, "cos") == 0 || strcmp(substr, "log") == 0) {
        return 1;
    }
    return 0;
}

// Função principal para avaliar uma expressão em notação pós-fixada
// Função principal para avaliar uma expressão em notação pós-fixada
double avaliarExpressaoPosfixada(const char *expressao) {
    Pilha pilha;
    inicializar(&pilha);
    
    int i = 0;
    while (expressao[i] != '\0') {
        if (isdigit(expressao[i]) || (expressao[i] == '.' && isdigit(expressao[i+1]))) {
            // Se for um dígito ou um número decimal, converte para double e empilha
            char numero[20];
            int j = 0;
            while (isdigit(expressao[i]) || expressao[i] == '.') {
                numero[j++] = expressao[i++];
            }
            numero[j] = '\0';
            double valor = atof(numero);
            empilhar(&pilha, valor);
        } else if (isalpha(expressao[i])) {
            // Se for um caractere alfabético (possivelmente uma função especial)
            char funcao[4];
            int j = 0;
            while (isalpha(expressao[i]) && j < 3) {
                funcao[j++] = expressao[i++];
            }
            funcao[j] = '\0';
            
            if (ehFuncaoEspecial(funcao)) {
                // Se for uma função especial válida, desempilha o operando e aplica a função
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
                }
            } else {
                // Função especial inválida
                printf("Erro: Função especial inválida\n");
                exit(EXIT_FAILURE);
            }
        } else if (expressao[i] == '+' || expressao[i] == '-' || expressao[i] == '*' || expressao[i] == '/' || expressao[i] == '^') {
            // Se for um operador, desempilha operandos e aplica a operação
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
            i++; // Avança para o próximo caractere após o operador
        } else if (expressao[i] == ' ' || expressao[i] == '\t') {
            // Ignora espaços em branco
            i++;
        } else {
            // Caractere inválido
            printf("Erro: Caractere inválido na expressão\n");
            exit(EXIT_FAILURE);
        }
    }
    
    // O resultado final estará no topo da pilha
    return desempilhar(&pilha);
}

// Função para converter expressão pós-fixada para infixa (não implementada)
char *getFormaInFixa(char *posFixa) {
    static char inFixa[512];
    snprintf(inFixa, sizeof(inFixa), "(Conversão não implementada: %s)", posFixa);
    return inFixa;
}

// Função para obter o valor de uma expressão pós-fixada
float getValor(char *posFixa) {
    return (float)avaliarExpressaoPosfixada(posFixa);
}
