#include <stdio.h>

int main()
{
    int N;
    int isPrime;

    printf("Enter number N: ");
    scanf_s("%d", &N);

    printf("Prime before %d:\n", N);

    for (int i = 2; i <= N; i++)
    {
        isPrime = 1; // Это флаг для простого числа: 1 TRUE - ДА или 0 FALSE - нет

        for (int j = 2; j < i; j++)
        {
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

    printf("\n");
    return 0;
}
