//Escrever um programa para determinar o mdc e o mmc de dois inteiros com base em seus fatores primos.

#include <stdio.h>

#define MAX_FATORES 100

typedef struct {
    int primo;
    int expoente;
} Fator;

typedef struct {
    Fator fatores[MAX_FATORES];
    int qtd;
} Fatoracao;

Fatoracao fatorar(int n) {
    Fatoracao f = {.qtd = 0};

    if (n % 2 == 0) {
        f.fatores[f.qtd].primo = 2;
        f.fatores[f.qtd].expoente = 0;
        while (n % 2 == 0) {
            f.fatores[f.qtd].expoente++;
            n /= 2;
        }
        f.qtd++;
    }

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            f.fatores[f.qtd].primo = i;
            f.fatores[f.qtd].expoente = 0;
            while (n % i == 0) {
                f.fatores[f.qtd].expoente++;
                n /= i;
            }
            f.qtd++;
        }
    }

    if (n > 1) {
        f.fatores[f.qtd].primo = n;
        f.fatores[f.qtd].expoente = 1;
        f.qtd++;
    }

    return f;
}

void imprimirFatoracao(int n, Fatoracao f) {
    printf("%d = ", n);
    for (int i = 0; i < f.qtd; i++) {
        printf("%d^%d", f.fatores[i].primo, f.fatores[i].expoente);
        if (i < f.qtd - 1) printf(" x ");
    }
    printf("\n");
}

int potencia(int base, int exp) {
    int res = 1;
    for (int i = 0; i < exp; i++) res *= base;
    return res;
}

void calcularMdcMmc(int a, int b) {
    Fatoracao fA = fatorar(a);
    Fatoracao fB = fatorar(b);

    printf("\n--- Decomposição em Fatores Primos ---\n");
    imprimirFatoracao(a, fA);
    imprimirFatoracao(b, fB);

    int mdc = 1;
    int mmc = 1;

    int i = 0, j = 0;

    while (i < fA.qtd || j < fB.qtd) {
        if (i < fA.qtd && j < fB.qtd && fA.fatores[i].primo == fB.fatores[j].primo) {
            int p = fA.fatores[i].primo;
            int expA = fA.fatores[i].expoente;
            int expB = fB.fatores[j].expoente;

            int menorExp = (expA < expB) ? expA : expB;
            int maiorExp = (expA > expB) ? expA : expB;

            mdc *= potencia(p, menorExp);
            mmc *= potencia(p, maiorExp);

            i++;
            j++;
        } 
        else if (j >= fB.qtd || (i < fA.qtd && fA.fatores[i].primo < fB.fatores[j].primo)) {
            // Fator exclusivo de A
            int p = fA.fatores[i].primo;
            int expA = fA.fatores[i].expoente;

            mmc *= potencia(p, expA); 
            i++;
        } 
        else {
            int p = fB.fatores[j].primo;
            int expB = fB.fatores[j].expoente;

            mmc *= potencia(p, expB); 
            j++;
        }
    }

    printf("\n--- Resultados ---\n");
    printf("MDC(%d, %d) = %d\n", a, b, mdc);
    printf("MMC(%d, %d) = %d\n", a, b, mmc);
}

int main() {
    int num1, num2;

    printf("Digite dois números inteiros positivos: ");
    if (scanf("%d %d", &num1, &num2) != 2 || num1 <= 0 || num2 <= 0) {
        printf("Entrada inválida! Digite números inteiros maiores que zero.\n");
        return 1;
    }

    calcularMdcMmc(num1, num2);

    return 0;
}