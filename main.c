#include <stdio.h>
#include "calculadora.h"

int main() {
    // Lista de testes
    struct {
        char posFixa[100];
        char inFixa[100];
        double valor;
    } testes[] = {
        {"3 4 + 5 *", "(3 + 4) * 5", 35},
        {"7 2 * 4 +", "7 * 2 + 4", 18},
        {"8 5 2 4 + * +", "8 + (5 * (2 + 4))", 38},
        {"6 2 / 3 + 4 *", "(6 / 2 + 3) * 4", 24},
        {"9 5 2 8 * 4 + * +", "9 + (5 * (2 + 8 * 4))", 109},
        {"2 3 + log 5 /", "log(2 + 3) / 5", 0.14},
        {"10 log 3 ^ 2 +", "(log10)^3 + 2", 3},
        {"45 60 + 30 cos *", "(45 + 60) * cos(30)", 90.93},
        {"0.5 45 sen 2 ^ +", "sen(45) ^2 + 0.5", 1}
    };
    
    int nTestes = sizeof(testes) / sizeof(testes[0]);

    for (int i = 0; i < nTestes; i++) {
        char *inFixa = getFormaInFixa(testes[i].posFixa);
        double valor = getValor(testes[i].posFixa);
        
        printf("Teste %d\n", i + 1);
        printf("Notacao Pos-fixada: %s\n", testes[i].posFixa);
        printf("Notacao Infixa: %s\n", inFixa);
        printf("Valor Calculado: %.6f\n", valor);
        printf("Valor Esperado: %.6f\n\n", testes[i].valor);
    }

    return 0;
}