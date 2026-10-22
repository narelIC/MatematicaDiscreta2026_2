/*
 * 10.Generalize o programa da questão anterior para funcionar com n congruências ao
 * invés de somente 3, onde n será dado pelo usuário.
 *
 * Entrada: N, depois N linhas no formato  a, b, m   (cada uma e  a.x ≡ b (mod m))
 *
 * Passo 1: cada congruencia a.x≡b (mod m) e reduzida para x≡c (mod m),
 *          usando o inverso modular de a (precisa mdc(a,m)=1).
 * Passo 2: checagem de coprimos incremental: mantemos um produto
 *          acumulado P dos modulos ja lidos; um novo modulo m_i so entra
 *          se mdc(m_i, P) == 1 -- isso garante coprimalidade com TODOS os
 *          anteriores de uma vez.
 * Passo 3: Teorema Chines do Resto combina as N congruencias:
 *          M = m1.m2...mN ; Mi = M/mi ; ri = inverso de Mi mod mi
 *          x = (c1.M1.r1 + ... + cN.MN.rN) mod M
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
 
long long euclidesEstendido(long long a, long long b, long long *s, long long *t) {
    if (b == 0) { *s = 1; *t = 0; return a; }
    long long s1, t1;
    long long g = euclidesEstendido(b, a % b, &s1, &t1);
    *s = t1;
    *t = s1 - (a / b) * t1;
    return g;
}
 
long long inversoModular(long long a, long long m) {
    long long s, t;
    euclidesEstendido(a, m, &s, &t);
    long long inv = s % m;
    if (inv < 0) inv += m;
    return inv;
}
 
int multSegura(long long x, long long y, long long *resultado) {
    if (x == 0 || y == 0) { *resultado = 0; return 1; }
    if (x > LLONG_MAX / y) return 0;
    *resultado = x * y;
    return 1;
}
 

void removerEspacos(char *s) {
    char *w = s;
    for (char *r = s; *r; r++)
        if (!isspace((unsigned char)*r)) *w++ = *r;
    *w = '\0';
}
 

int parseCongruencia(char *linha, long long *a, long long *b, long long *m) {
    if (linha[0] == 'x') {
        *a = 1;
        return sscanf(linha, "x=%lldmod%lld", b, m) == 2;
    }
    return sscanf(linha, "%lldx=%lldmod%lld", a, b, m) == 3;
}
 
int main(int argc, char *argv[]) {

    if (argc > 1) {
        if (freopen(argv[1], "r", stdin) == NULL) {
            printf("Erro: nao consegui abrir o arquivo \"%s\".\n", argv[1]);
            return 1;
        }
    }
 
    int N;
    scanf("%d", &N);
    printf("Quantas congruencias (N)? %d \n", N);
    getchar();
    if (N <= 0) { printf("N invalido.\n"); return 1; }
 
    long long *a = malloc(N * sizeof(long long));
    long long *b = malloc(N * sizeof(long long));
    long long *m = malloc(N * sizeof(long long));
    long long *c = malloc(N * sizeof(long long));
    char linha[256];
 
    long long P = 1;
 
    for (int i = 0; i < N; i++) {
        printf("Congruencia %d : ", i + 1);
        if (!fgets(linha, sizeof(linha), stdin)) { printf("Entrada invalida.\n"); return 1; }
        removerEspacos(linha);
 
        if (!parseCongruencia(linha, &a[i], &b[i], &m[i])) {
            printf("Erro: formato invalido em \"%s\". Use algo como 7x=4mod15.\n", linha);
            free(a); free(b); free(m); free(c);
            return 1;
        }
 
        long long s, t;
        if (i > 0 && euclidesEstendido(m[i], P, &s, &t) != 1) {
            printf("Erro: m%d nao e coprimo com os modulos anteriores -- TCR nao se aplica.\n", i + 1);
            free(a); free(b); free(m); free(c);
            return 1;
        }
        long long novoP;
        if (i > 0 && !multSegura(P, m[i], &novoP)) {
            printf("Aviso: produto dos modulos estourou o limite representavel na congruencia %d.\n", i + 1);
            free(a); free(b); free(m); free(c);
            return 1;
        }
        P = (i == 0) ? m[i] : novoP;
 
        long long g = euclidesEstendido(a[i], m[i], &s, &t);
        if (g != 1) {
            printf("Erro: mdc(a%d, m%d) != 1 -- sem inverso para a congruencia %d.\n", i + 1, i + 1, i + 1);
            free(a); free(b); free(m); free(c);
            return 1;
        }
        long long invA = inversoModular(a[i], m[i]);
        c[i] = (b[i] % m[i]) * invA % m[i];
        if (c[i] < 0) c[i] += m[i];
 
        printf("%s \n", linha);
    }
    //printf("\n");
 
    long long M = P;
    long long x = 0;
    for (int i = 0; i < N; i++) {
        long long Mi = M / m[i];
        long long ri = inversoModular(Mi % m[i], m[i]);
        long long termo = (c[i] % m[i]) * (Mi % M) % M;
        termo = termo * ri % M;
        x = (x + termo) % M;
    }
    if (x < 0) x += M;
 
    printf("Solucao: x = %lld (mod %lld)\n", x, M);
 
    free(a); free(b); free(m); free(c);
    return 0;
}