/*Escrever um programa para decompor um determinado número inteiro em seus fatores primos.*/

#include <stdio.h>

void decomporFatoresPrimos(int n) {
    if (n <= 1) {
        printf("Não possui fatores primos (digite um número maior que 1).\n");
        return;
    }

    printf("Fatores primos de %d: ", n);

    int primeiro = 1;
    while (n % 2 == 0) {
        if (!primeiro) printf(" x ");
        printf("2");
        primeiro = 0;
        n /= 2;
    }

    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            if (!primeiro) printf(" x ");
            printf("%d", i);
            primeiro = 0;
            n /= i;
        }
    }

    if (n > 1) {
        if (!primeiro) printf(" x ");
        printf("%d", n);
    }

    printf("\n");
}

int main() {
    int numero;

    printf("Digite um número inteiro: ");
    if (scanf("%d", &numero) != 1) {
        printf("Entrada inválida!\n");
        return 1;
    }

    decomporFatoresPrimos(numero);

    return 0;
}