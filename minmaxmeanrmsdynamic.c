#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARRAY_SIZE_MAX 100

void inputValueInt(int *pointer)
{
    while (1)
    {
        printf("Set the size of the array (int): ");

        if (scanf_s("%d", pointer) != 1 || getchar() != '\n')
        {
            printf("Incorrect value entered for the size of the array!\n");

            while (getchar() != '\n')
                ;

            continue;
        }

        if (*pointer <= 0 || *pointer > ARRAY_SIZE_MAX)
        {
            printf("Incorrect array size has been entered!\n");

            continue;
        }

        break;
    }
}

void printArrayInt(int *arrayInt, int sizeArray)
{

    for (int *pointer = arrayInt; pointer - arrayInt < sizeArray; pointer++)
    {
        printf("%d", *(pointer));

        if (pointer < arrayInt + sizeArray - 1)
        {
            printf(", ");
        }
    }

    printf("\n");
}

void inputArrayInt(int *arrayInt, int sizeArray)
{
    while (1)
    {
        printf("Enter the values for the array, length = %d: ", sizeArray);

        for (int *pointer = arrayInt; pointer - arrayInt < sizeArray; pointer++)
        {
            scanf_s("%d", pointer);
        }

        if (getchar() != '\n')
        {
            printf("Incorrect data was entered!\n");
            while (getchar() != '\n')
                ;

            continue;
        }

        break;
    }
}

int Min(int *arrayInt, int sizeArray)
{
    int min = *arrayInt;

    for (int *pointer = arrayInt + 1; pointer - arrayInt < sizeArray; pointer++)
    {
        if (*pointer < min)
        {
            min = *pointer;
        }
    }

    return min;
}

int Max(int *arrayInt, int sizeArray)
{
    int max = *arrayInt;

    for (int *pointer = arrayInt + 1; pointer - arrayInt < sizeArray; pointer++)
    {
        if (*pointer > max)
        {
            max = *pointer;
        }
    }

    return max;
}

float Mean(int *arrayInt, int sizeArray)
{
    int sum = 0;

    for (int *pointer = arrayInt; pointer - arrayInt < sizeArray; pointer++)
    {
        sum += *pointer;
    }

    return (float) sum / (float) sizeArray;
}

float RMS(int *arrayInt, int sizeArray)
{
    float mean = Mean(arrayInt, sizeArray);
    float sum_squared_diff = 0;

    for (int *pointer = arrayInt; pointer - arrayInt < sizeArray; pointer++)
    {
        sum_squared_diff += ((float) *pointer - mean) * ((float) *pointer - mean);
    }

    return (float) sqrt((double) sum_squared_diff / (double) sizeArray);
}

int main()
{
    int size;

    inputValueInt(&size); // НАШ КРУТОЙ РОССИЙСКИЙ СКАНФ ПОД ЖЕСТКИМИ СТЕРОИДАМИ

    int *arrayDynamic = (int *)malloc(size * sizeof(int));

    if (arrayDynamic == NULL)
    {
        printf("Failed to create dynamic array of size: %d\n", size);
        return 1;
    }

    inputArrayInt(arrayDynamic, size);

    printf("For given array values:");
    printArrayInt(arrayDynamic, size);

    printf("Minimum value: %d.\nMaximum value: %d.\nThe average value: %f.\nStandard deviation: %f.\n",
           Min(arrayDynamic, size), Max(arrayDynamic, size), Mean(arrayDynamic, size), RMS(arrayDynamic, size));

    free(arrayDynamic);

    return 0;
}
