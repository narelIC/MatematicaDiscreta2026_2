#include <stdio.h>
#include <time.h>

int primo(long n, int divisor)
{
    if (n % 2 == 0) 
    {
        return 0;
    }
    
    for (long i = 3; i * i <= n; i += 2) 
    {
        if (n % i == 0) 
        {
            return 0;
        }
    }
    
    return 1;
}

int main()
{
    time_t tempo_inicial = time(NULL);
    long n = 3;

    printf("2\n");

    while (time(NULL) - tempo_inicial < 60)
    {
        if (primo(n, 3) == 1)
        {
            printf("%ld\n", n);
        }   

        n += 2;
    }
    
    return 0;
}