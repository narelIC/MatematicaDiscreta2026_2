/*9. Escrever um programa para encontrar a solução única de três congruências usando
o Teorema Chinês do Resto. (Lembre-se de verificar se os módulos são coprimos).


Passo 1: ~*Inverso Modular*~

Cada congruência a.x≡b (mod m) é reduzida para x≡c (mod m), 
usando o inverso modular de a (mdc(a,m)=1).


Passo 2: ~*Teorema chinês do resto:*~ 

Sendo n= 3 congruências: a1.x≡b1 mod m1 ; a2.x≡b2 mod m2 ; a3.x≡b3 mod m3.
O Teorema chinês do resto diz que: x= M1.b1.r1 + ... + Mn.bn.rn. 
Sendo, M= a1 . a2 ... an; Mn= M/mn ; rn= Mn mod mn.

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define N 3

int a[N], b[N], m[N];

int euclidesEstendido(int a, int b, int *s, int *t) {
    if (b == 0) {
        *s = 1;
        *t = 0;
        return a;
    }
    int s1, t1;
    int g = euclidesEstendido(b, a % b, &s1, &t1);
    *s = t1;
    *t = s1 - (a / b) * t1;
    return g;
}

int inversoModular(int a, int m) {
    int s, t;
    euclidesEstendido(a, m, &s, &t);
    int inv = s % m;
    if (inv < 0) inv += m;
    return inv;
}

int modulosSaoCoprimos(void) {
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++) {
            int s, t;
            if (euclidesEstendido(m[i], m[j], &s, &t) != 1) {
                printf("Erro: mdc(m%d, m%d) != 1 -- os modulos nao sao coprimos.\n",
                       i + 1, j + 1);
                return 0;
            }
        }
    return 1;
}


void calcularIncognita(void) {
    if (!modulosSaoCoprimos()) {
        exit(1);
    }

    int c[N];          
    int M = 1, g, s, t;

    for (int i = 0; i < N; i++) {
        g = euclidesEstendido(a[i], m[i], &s, &t);
        if (g != 1) {
            printf("Erro: mdc(a%d, m%d) != 1 -- sem inverso para a congruencia %d.\n",
                   i + 1, i + 1, i + 1);
            exit(1);
        }
        int invA = inversoModular(a[i], m[i]);
        c[i] = (int)(((long)b[i] * invA) % m[i]);
        M *= m[i];
    }

    long x = 0;
    for (int i = 0; i < N; i++) {
        int Mi = M / m[i];
        int ri = inversoModular(Mi, m[i]);
        x += (long)c[i] * Mi * ri;
    }
    x %= M;
    if (x < 0) x += M;

    printf("Solucao: x = %ld (mod %d)\n", x, M);
}

/* Remove espacos/tabs de uma string, em cima dela mesma */
void removerEspacos(char *s) {
    char *w = s;
    for (char *r = s; *r; r++)
        if (!isspace((unsigned char)*r)) *w++ = *r;
    *w = '\0';
}

void lerCongruencias(void) {
    char linha[256];
    for (int i = 0; i < N; i++) {
        printf("Congruencia %d : ", i + 1);
        fgets(linha, sizeof(linha), stdin);
        removerEspacos(linha);

        int ok;
        if (linha[0] == 'x') {
            a[i] = 1;
            ok = sscanf(linha, "x=%dmod%d", &b[i], &m[i]) == 2;
        } else {
            ok = sscanf(linha, "%dx=%dmod%d", &a[i], &b[i], &m[i]) == 3;
        }
        if (!ok) {
            printf("Erro: formato invalido em \"%s\". Use algo como 7x=4mod9.\n", linha);
            exit(1);
        }
        printf("%s ", linha);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {

    if (argc > 1) {
        if (freopen(argv[1], "r", stdin) == NULL) {
            printf("Erro: nao consegui abrir o arquivo \"%s\".\n", argv[1]);
            return 1;
        }
    }
    lerCongruencias();
    calcularIncognita();
    return 0;
}
