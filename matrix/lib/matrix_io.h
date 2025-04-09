#ifndef MATRIX_IO_H
#define MATRIX_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct
{
    double **pointerDynamicMatrix;
    int rows;
    int columns;
} Matrix_NxM;

int InitMatrix(Matrix_NxM *matrix);
int freeMatrix(Matrix_NxM *matrix);
int PrintMatrix(const Matrix_NxM *matrix);
int inputMatrix(Matrix_NxM *matrix);
int inputValueRowsAndColumns(Matrix_NxM *matrix);
int fillMatrixRandom(Matrix_NxM *matrix);
int searchingForElementIndexDynamicMatrix(const Matrix_NxM *matrix, int row, int column);
int readingMatrixFromFile(Matrix_NxM *matrix, const char *pathToFile);

#endif
