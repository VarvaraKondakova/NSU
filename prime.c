#include <stdio.h>
#include <math.h>

int main()
{
    int N;
    int isPrime;
    int count = 0;
    printf("Enter number N: ");
    scanf_s("%d", &N);

    printf("Prime before %d:\n", N);
    printf("2\n");
    for (int i = 3; i <= N; i=i+2)
    {
        isPrime = 1; // Это флаг для простого числа: 1 TRUE - ДА или 0 FALSE - нет

        for (int j = 3; j < sqrt(i); j=j+2)
        {
            count++;
            if (i % j == 0)
            {
                isPrime = 0;
                break;
            }
        }

        if (isPrime)
        {
            printf("%d ", i);

        }
    }

    printf("\nNumber of prime numbers up to %d: %d\n", N, count);
    return 0;
}
