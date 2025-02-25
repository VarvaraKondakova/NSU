#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;
    double answer;
    double discriminant, root1, root2;

    printf("Enter the coefficients a, b and c: ");
    scanf_s("%lf %lf %lf", &a, &b, &c);

    discriminant = b * b - 4 * a * c;

    if (a == 0) {
        answer = -c / b;

        printf("The result is a linear equation and its answer: %.2f", answer);

    } else {

        if (discriminant > 0) {
            double sqrte = sqrt(discriminant);
            root1 = (-b + sqrte) / (2 * a);
            root2 = (-b - sqrte) / (2 * a);

            printf("Roots: %.2lf and %.2lf\n", root1, root2);
        } else if (discriminant == 0) {
            root1 = -b / (2 * a);

            printf("One roots: %.2lf\n", root1);


        } else {
            printf("There are no roots.\n");
        }
    }
    return 0;
}