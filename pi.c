#include <stdio.h>
#include <math.h>

double round_to_decimal(double value, int decimal_places)
{
    double factor = pow(10.0, decimal_places);
    double temp = value * factor;
    double rounded_value = 0.0;

    if (temp >= 0)
    {
        rounded_value = (int)(temp + 0.5) / factor;
    }
    else
    {
        rounded_value = (int)(temp - 0.5) / factor;
    }

    return rounded_value;
}

int main()
{

    int decimal_places;
    double pi = 0.0;
    double sign = 1;
    int denominator = 1;
    int terms = 0;


    printf("Enter the number of decimal places: ");
    scanf_s("%d", &decimal_places);

    double precision = 1.0 / pow(10, decimal_places);

    while (1)
    {
        double term = sign * (1.0 / denominator);
        pi += term;
        sign *= -1;
        denominator += 2;
        terms++;

        if (fabs(term) <= precision)
        {
            break;
        }
    }

    pi *= 4;

    pi = round_to_decimal(pi, decimal_places);

    printf("The number of pi with an accuracy of digits: %.*f\n", decimal_places, pi);
    printf("Number of row members: %d\n", terms);

    return 0;
}
