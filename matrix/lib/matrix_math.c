#include "matrix_math.h"

Matrix_NxM sumMatrices(Matrix_NxM *matrix1, Matrix_NxM *matrix2)
{
    if (matrix1->rows != matrix2->rows || matrix1->columns != matrix2->columns)
    {
        perror("Matrix dimensions don't match for addition!\n");
        freeMatrix(matrix1);
        freeMatrix(matrix2);
        exit(EXIT_FAILURE);
    }

    Matrix_NxM result;
    result.rows = matrix1->rows;
    result.columns = matrix1->columns;
    InitMatrix(&result);

    for (int i = 0; i < result.rows; i++)
    {
        for (int j = 0; j < result.columns; j++)
        {
            result.pointerDynamicMatrix[i][j] = matrix1->pointerDynamicMatrix[i][j] + matrix2->pointerDynamicMatrix[i][j];
        }
    }

    return result;
}

Matrix_NxM multiplyMatrices(Matrix_NxM *matrix1, Matrix_NxM *matrix2)
{
    if (matrix1->columns != matrix2->rows)
    {
        perror("Incompatible matrix dimensions for multiplication!\n");
        freeMatrix(matrix1);
        freeMatrix(matrix2);
        exit(EXIT_FAILURE);
    }

    Matrix_NxM result;
    result.rows = matrix1->rows;
    result.columns = matrix2->columns;
    InitMatrix(&result);

    for (int i = 0; i < result.rows; i++)
    {
        for (int j = 0; j < result.columns; j++)
        {
            result.pointerDynamicMatrix[i][j] = 0;
            for (int k = 0; k < matrix1->columns; k++)
            {
                result.pointerDynamicMatrix[i][j] += matrix1->pointerDynamicMatrix[i][k] * matrix2->pointerDynamicMatrix[k][j];
            }
        }
    }

    return result;
}

Matrix_NxM getSubMatrix(const Matrix_NxM *matrix, int exclude_row, int exclude_col)
{
    Matrix_NxM subMatrix;
    subMatrix.rows = matrix->rows - 1;
    subMatrix.columns = matrix->columns - 1;
    InitMatrix(&subMatrix);

    int sub_i = 0;
    for (int i = 0; i < matrix->rows; i++)
    {
        if (i == exclude_row)
            continue;

        int sub_j = 0;
        for (int j = 0; j < matrix->columns; j++)
        {
            if (j == exclude_col)
                continue;

            subMatrix.pointerDynamicMatrix[sub_i][sub_j] = matrix->pointerDynamicMatrix[i][j];
            sub_j++;
        }
        sub_i++;
    }

    return subMatrix;
}

double determinantMatrix(Matrix_NxM *matrix)
{

    if (matrix->rows != matrix->columns)
    {
        perror("Matrix must be square to compute determinant!\n");
        freeMatrix(matrix);
        exit(EXIT_FAILURE);
    }

    int n = matrix->rows;

    if (n == 1)
        return matrix->pointerDynamicMatrix[0][0];
    if (n == 2)
    {
        return matrix->pointerDynamicMatrix[0][0] * matrix->pointerDynamicMatrix[1][1] -
               matrix->pointerDynamicMatrix[0][1] * matrix->pointerDynamicMatrix[1][0];
    }

    double det = 0.0;
    int sign = 1;

    for (int j = 0; j < n; j++)
    {
        Matrix_NxM subMatrix = getSubMatrix(matrix, 0, j);
        det += sign * matrix->pointerDynamicMatrix[0][j] * determinantMatrix(&subMatrix);
        sign *= -1;
        freeMatrix(&subMatrix);
    }

    return det;
}

Matrix_NxM inverseMatrix(Matrix_NxM *matrix)
{
    if (matrix->rows != matrix->columns)
    {
        perror("Matrix must be square to compute inverse!\n");
        freeMatrix(matrix);
        exit(EXIT_FAILURE);
    }

    int n = matrix->rows;

    if (n == 1)
    {
        perror("There is no such inverse matrix!\n");
        freeMatrix(matrix);
        exit(EXIT_FAILURE);
    }

    Matrix_NxM inverse;
    inverse.rows = n;
    inverse.columns = n;
    InitMatrix(&inverse);

    double det = determinantMatrix(matrix);

    if (fabs(det) < 1e-10)
    {
        perror("Matrix is singular (determinant = 0), inverse doesn't exist!\n");
        exit(EXIT_FAILURE);
    }

    Matrix_NxM temp;
    temp.rows = n;
    temp.columns = n;
    InitMatrix(&temp);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Matrix_NxM subMatrix = getSubMatrix(matrix, i, j);
            double minorDet = determinantMatrix(&subMatrix);

            temp.pointerDynamicMatrix[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * minorDet;

            freeMatrix(&subMatrix);
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            inverse.pointerDynamicMatrix[j][i] = temp.pointerDynamicMatrix[i][j] / det;
        }
    }

    freeMatrix(&temp);

    return inverse;
}
