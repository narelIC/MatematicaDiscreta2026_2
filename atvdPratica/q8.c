/*
8. Escrever um programa para encontrar a solução de uma congruência do tipo ax ≡
b mod m.
*/
#include <stdio.h>

int euclidesEstendido(int a, int b, int *s, int *t) {
    if (b == 0) { *s = 1; *t = 0; return a; }
    int s1, t1;
    int g = euclidesEstendido(b, a % b, &s1, &t1);
    *s = t1;
    *t = s1 - (a / b) * t1;
    return g;
}

int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[1], "r");
    int a, b, m;
    fscanf(f, "%d %d %d", &a, &b, &m);
    fclose(f);

    int s, t;
    int d = euclidesEstendido(a, m, &s, &t);

    if (b % d != 0) {
        printf("Sem solucao: mdc(%d,%d)=%d nao divide %d\n", a, m, d, b);
        return 1;
    }

    int A = a / d, B = b / d, M = m / d;
    int s2, t2;
    euclidesEstendido(A, M, &s2, &t2);
    int inv = s2 % M;
    if (inv < 0) inv += M;

    int x0 = (int)(((long)B * inv) % M);
    if (x0 < 0) x0 += M;

    printf("Existem %d solucao(oes) modulo %d:\n", d, m);
    for (int k = 0; k < d; k++)
        printf("x = %d\n", x0 + k * M);

    return 0;
}
