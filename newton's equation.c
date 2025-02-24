#include <stdio.h>
#include <math.h>

float Func(float x) {
    return x * x + 2;  // Пример: x^2 - 2 = 0
}

float dFunc(float x) {
    return 2 * x;  // Производная от x^2 - 2
}

float newtonMethod(float x0, float epsilon) {
    float x = x0;
    float delta;
    int iterations = 0;

    do {
        float fx = Func(x);
        float dfx = dFunc(x);

        if (dfx == 0) {
            printf("The derivative is zero. Newton's method cannot be applied.\n");
            return NAN;  // Возвращаем NaN (Not a Number)
        }

        delta = fx / dfx;
        x = x - delta;
        iterations++;

    } while (fabs(delta) > epsilon);

    printf("Number of iterations: %d\n", iterations);
    return x;
}

int main() {
    float x0, epsilon;

    printf("Enter the initial approximation x0: ");
    scanf("%f", &x0);


    printf("Enter the required accuracy (for example, 0.0001): ");
    scanf("%f", &epsilon);


    float root = newtonMethod(x0, epsilon);

    if (!isnan(root)) {
        printf("The found root: %.6f\n", root);
    }

    return 0;
}