#include <stdio.h>
#include <math.h>

#define ARRAY_SIZE_MAX 100

void printArray(int arrayInt[sizeArray], int sizeArray;)

int Min() {
    int min = arrayInt[0];
    for (int i = 1; i < sizeArray; i++) {
        if (arrayInt[i] < min) {
            min = arrayInt[i];
        }
    }
    return min;
}

int Max() {
    int max = arrayInt[0];
    for (int i = 1; i < sizeArray; i++) {
        if (arrayInt[i] > max) {
            max = arrayInt[i];
        }
    }
    return max;
}

float Mean() {
    int sum = 0;
    for (int i = 0; i < sizeArray; i++) {
        sum += arrayInt [i];
    }
    return (float)sum / sizeArray;
}

float RMS() {
    float mean = Mean();
    float sum_squared_diff = 0;
    for (int i = 0; i <sizeArray; i++) {
        sum_squared_diff += (arrayInt[i] - mean) * (arrayInt[i] - mean);
    }
    return sqrt(sum_squared_diff / sizeArray);
}


int main() {
    int sizeArray;
    printf("Enter array size: ");
    if (scanf_s("%d", &sizeArray) != 1 || getchar() != '\n')
    {
        printf("sizeArray is not equal to int\n");
        return 1;
    }

    if (sizeArray < 1 || sizeArray > 100)
    {
        printf("The size of the created array is greater than the maximum or less than 1\n");
        return 1;
    }

    printf("sizeArray = %d\n", sizeArray);

    printf("Enter array elements of length %d: ", sizeArray);
    int arrayInt[sizeArray];
    for (int i = 0; i < sizeArray; i++)
    {
        if (scanf_s("%d", &arrayInt[i]) != 1)
        {
            printf("scanf() did not eat the resulting value, which means incorrect data was entered\n");
            return 1;
        }
    }

    if (getchar() != '\n')
    {
        printf("After a cycle of entering some values something remains in the input stream\n");
        return 1;
    }

    printf("Data entered into the array: ");
    for (int i = 0; i < sizeArray; i++)
    {
        printf("%d", arrayInt[i]);

        if (i < sizeArray - 1)
        {
            printf(", ");
        }

        if (i == sizeArray - 1)
            printf("\n");
    }

    return 0;
}
