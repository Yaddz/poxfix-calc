#ifndef EXPRESSAO_H
#define EXPRESSAO_H

typedef struct {
    char posFixa[512];     // Expressão na forma pos-fixa, como 3 12 4 + *
    char inFixa[512];      // Expressão na forma infixa, como 3 * (12 + 4)
    float Valor;           // Valor numérico da expressão  
} Expressao;

char *getFormaInFixa(char *Str);    // Retorna a forma infixa de Str (pos-fixa)
float getValor(char *Str);          // Calcula o valor de Str (na forma pos-fixa)


#endif
