#include <stdio.h>
#include <math.h>

float Func(float x) {
    return (float) fabs(sin((double) M_PI*x)); // Пример: интеграл от sin(x)
}

float TrapezoidalRule(float a, float b, int n) {
    float h = (b - a) / (float) n;
    float sum = 0.5f * (Func(a) + Func(b));

    for (int i = 1; i < n; i++) {
        float x = a + (float) i * h;
        sum += Func(x);
    }

    return sum * h;
}

int main() {
    setbuf(stdout, 0);

    float a, b;
    int n;

    while (1)
    {
        printf("Enter lower integration limit a: ");

        if (scanf("%f", &a) != 1 || getchar() != '\n')
        {
            printf("Error: input value `lower integration limit` incorrect!\n");

            while (getchar() != '\n')
                ;

            continue;
        }

        break;
    }

    while (1)
    {
        printf("Enter upper integration limit b: ");

        if (scanf("%f", &b) != 1 || getchar() != '\n')
        {
            printf("Error: input value `upper integration limit` incorrect!\n");

            while (getchar() != '\n')
                ;

            continue;
        }

        break;
    }

    while (1)
    {
        printf("Enter the number of splits n: ");

        if (scanf("%f", &n) != 1 || getchar() != '\n')
        {
            printf("Error: input value `number of splits` incorrect!\n");

            while (getchar() != '\n')
                ;

            continue;
        }

        break;
    }

    double result = TrapezoidalRule(a, b, n);
    printf("Integral value: %lf\n", result);

    // Оценка точности
    double result_double_n = TrapezoidalRule(a, b, 2 * n);
    double error = fabs(result_double_n - result) / 3.0; // Оценка погрешности по правилу Рунге
    printf("Error estimate: %lf\n", error);

    return 0;
}
