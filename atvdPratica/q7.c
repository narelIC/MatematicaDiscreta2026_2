#include <stdio.h>

// Funcao auxiliar com o algoritmo de euclides estendido (reaproveitada da Q6)
int mdc_estendido(int a, int b, int *s_out, int *t_out) {
    int s_ant = 1, s = 0;
    int t_ant = 0, t = 1;
    int quociente, resto;

    while (b != 0) {
        quociente = a / b;
        resto = a % b;

        a = b;
        b = resto;

        int s_novo = s_ant - quociente * s;
        int t_novo = t_ant - quociente * t;

        s_ant = s; s = s_novo;
        t_ant = t; t = t_novo;
    }

    *s_out = s_ant;
    *t_out = t_ant;
    return a;
}

int inverso_modular(int a, int b) {
    int s, t;
    int mdc = mdc_estendido(a, b, &s, &t);

    // Se nao forem coprimos (MDC diferente de 1), o inverso nao existe.
    // Retornamos -1 como indicador, ja que C nao tem null/None puro pra int.
    if (mdc != 1) {
        return -1;
    }

    // O 's' pode ser negativo. Ajustamos para o equivalente positivo no modulo b.
    int inverso = s % b;
    if (inverso < 0) {
        inverso += b;
    }
    
    return inverso;
}

int main() {
    int num = 3, mod = 11;
    int inv = inverso_modular(num, mod);

    if (inv != -1) {
        printf("O inverso de %d mod %d eh %d\n", num, mod, inv);
    } else {
        printf("Nao existe inverso de %d mod %d\n", num, mod);
    }
    return 0;
}
