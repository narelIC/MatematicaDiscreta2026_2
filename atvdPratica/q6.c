#include <stdio.h>

// Calcula o MDC e acha s e t passando por referencia (ponteiros)
int mdc_estendido(int a, int b, int *s_out, int *t_out) {
    int s_ant = 1, s = 0;
    int t_ant = 0, t = 1;
    int quociente, resto;
    int s_novo, t_novo;

    while (b != 0) {
        quociente = a / b;
        resto = a % b;

        a = b;
        b = resto;

        s_novo = s_ant - quociente * s;
        t_novo = t_ant - quociente * t;

        s_ant = s;
        s = s_novo;

        t_ant = t;
        t = t_novo;
    }

    *s_out = s_ant;
    *t_out = t_ant;
    return a;
}

int main() {
    int num1 = 252, num2 = 198;
    int s, t, valor_mdc;
    
    // Passa o endereco de s e t pra funcao conseguir alterar os valores originais
    valor_mdc = mdc_estendido(num1, num2, &s, &t);
    printf("Combinacao linear: %d = (%d * %d) + (%d * %d)\n", valor_mdc, s, num1, t, num2);
    return 0;
}
