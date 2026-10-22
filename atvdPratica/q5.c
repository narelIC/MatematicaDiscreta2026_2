#include <stdio.h>

// Calcula o MDC usando o Algoritmo de Euclides
int mdc(int a, int b) {
    int resto;
    while (b != 0) {
        resto = a % b;
        a = b;
        b = resto;
    }
    return a;
}

int main() {
    int num1 = 252, num2 = 198;
    printf("MDC(%d, %d) = %d\n", num1, num2, mdc(num1, num2));
    return 0;
}
