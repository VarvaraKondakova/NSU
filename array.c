#include <stdio.h>
#include <math.h>

#define ARRAY_SIZE_MAX 100

int intputArrayInt(int arrayInt[], int sizeArray)
{
    printf("Enter array elements of length %d: ", sizeArray);
    for (int i = 0; i < sizeArray; i++)
    {
        if (scanf("%d", &arrayInt[i]) != 1)
        {
            printf("scanf() не съел получаемое значение, что знчит были введены неверные данные\n");
            return 1;
        }
    }

    if (getchar() != '\n')
    {
        printf("После цикла ввода каких-либо значений в массив осталось что-то в потоке ввода\n");
        return 1;
    }

    return 0;
}

void outputArrayInt(int arrayInt[], int sizeArray)
{
    printf("Данные, введенные в массив: ");
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
}

int main()
{
    int sizeArray;

    printf("Введите размер массива: ");
    if (scanf("%d", &sizeArray) != 1 || getchar() != '\n')
    {
        printf("sizeArray не равен int\n");
        return 1;
    }

    if (sizeArray < 1 || sizeArray > 100)
    {
        printf("Размер создаваемого массива больше максимального или меньше 1\n");
        return 1;
    }

    printf("sizeArray = %d\n", sizeArray);

    int arrayInt[sizeArray];

    if (intputArrayInt(arrayInt, sizeArray) == 1)
    {
        printf("Ошибка, при работе функции `intputArrayInt`!\n");
        return 1;
    }

    outputArrayInt(arrayInt, sizeArray);

    return 0;
}
