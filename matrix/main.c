#include "lib/matrix_io.h"
#include "lib/matrix_math.h"

/**
 * Работа с матрицами NхM
 * • Структура Matrix_NxM для хранения данных
 * • Данные хранятся в виде одномерного динамического массива (реализовать вычисление индекса элемента по его двумерному индексу в матрице).
 * • Функция InitMatrix() задает размер и выделяет память.
 * • Функция PrintMatrix() выводит матрицу на экран в табличном виде
 * • Функции вычисления суммы, произведения, определителя и обратной матрицы (функции не печатать результат, а возвращают его)
 * • Исходная матрица должна заполняться из файла или случайными числами
 * • Вычисление определителя с использованием рекурсивной функции (разложение по строке)
 *
 * Компиляция GCC: `gcc main.c lib/matrix_io.c lib/matrix_math.c` или для проверки `gcc -Wall -Werror -Wextra  main.c lib/matrix_io.c lib/matrix_math.c`
 * cppcheck: `cppcheck --enable=all --suppress=missingIncludeSystem main.c lib/matrix_io.c lib/matrix_math.c`
 * valgrind: `valgrind --tool=memcheck --leak-check=yes -s ./a.out`
 */
int main()
{
    Matrix_NxM matrix;

    printf("\n===== Starting the input of dimensions for the matrix. =====\n");
    inputValueRowsAndColumns(&matrix);

    printf("\n===== Starting the initialization of the matrix. =====\n");
    InitMatrix(&matrix);

    // printf("Starting data entry for the matrix.\n");
    // inputMatrix(&matrix);

    // printf("\n===== Starting automatic random data entry for the matrix. =====\n");
    // fillMatrixRandom(&matrix);

    printf("\n===== Starting data entry for the matrix from a file. =====\n");
    if (readingMatrixFromFile(&matrix, "assets/matrix_one.txt"))
    {
        printf("\n===== Starting the matrix output. =====\n");
        printf("\nThe %d by %d matrix:\n", matrix.rows, matrix.columns);
        PrintMatrix(&matrix);

        printf("\n===== Starting a search for the index of an element by its two-dimensional index in the matrix. =====\n");
        int i = 1, j = 1;
        int indexItem = searchingForElementIndexDynamicMatrix(&matrix, i, j);
        printf("According to the two-dimensional index [%d][%d], the index of the element in the dynamic array = %d (index in the data: %d), and the data = %.2lf\n",
               i, j, indexItem, indexItem - matrix.rows, *(matrix.pointerDynamicMatrix[0] + indexItem - matrix.rows));
    }

    printf("\n===== Starting the cleaning of the allocated memory for the matrix. =====\n");
    freeMatrix(&matrix);

    printf("\n===== Running mathematical functions for a matrix. =====\n");

    Matrix_NxM matrix1, matrix2, matrixAnswer;

    printf("\n===== Starting the input of dimensions for the matrix. =====\n");
    inputValueRowsAndColumns(&matrix1);
    printf("\n===== Starting the initialization of the matrix. =====\n");
    InitMatrix(&matrix1);

    printf("\n===== Starting the input of dimensions for the matrix. =====\n");
    inputValueRowsAndColumns(&matrix2);
    printf("\n===== Starting the initialization of the matrix. =====\n");
    InitMatrix(&matrix2);

    printf("\n===== Starting data entry for the matrix from a file. =====\n");
    readingMatrixFromFile(&matrix1, "assets/matrix_three.txt");
    printf("\n===== Starting data entry for the matrix from a file. =====\n");
    readingMatrixFromFile(&matrix2, "assets/matrix_four.txt");

    printf("\n===== Starting the calculation of the sum of the matrices. =====\n");
    matrixAnswer = sumMatrices(&matrix1, &matrix2);
    PrintMatrix(&matrixAnswer);
    freeMatrix(&matrixAnswer);

    printf("\n===== Starting the matrix multiplication calculation. =====\n");
    matrixAnswer = multiplyMatrices(&matrix1, &matrix2);
    PrintMatrix(&matrixAnswer);
    freeMatrix(&matrixAnswer);

    printf("\n===== Starting the calculation of the determinant of the matrix. =====\n");
    printf("Determinant %lf\n", determinantMatrix(&matrix1));

    printf("\n===== Starting the calculation of the inverse matrix. =====\n");
    matrixAnswer = inverseMatrix(&matrix1);
    PrintMatrix(&matrixAnswer);
    freeMatrix(&matrixAnswer);

    printf("\n===== Starting the cleaning of the allocated memory for the matrix. =====\n");
    freeMatrix(&matrix1);
    freeMatrix(&matrix2);

    return 0;
}
