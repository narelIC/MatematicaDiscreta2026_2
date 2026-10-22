#include <stdio.h>
#include <math.h>

int primo(int n, int divisor)
{
    if (n < 2)
    {
        return 0;
    }
    if (divisor > sqrt(n))
    {
        return 1;
    }
    if (n % divisor == 0)
    {
        return 0;
    }

    return primo(n, divisor +1);
}

int main()
{
    int n;

    scanf("%d", &n);

    if (primo(n, 2) == 1)
    {
        printf("É primo\n");
    }
    else
    {
        printf("Não é primo\n");
    }
    
    return 0;
}