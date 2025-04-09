#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include "matrix_io.h"

Matrix_NxM sumMatrices(Matrix_NxM *matrix1, Matrix_NxM *matrix2);
Matrix_NxM multiplyMatrices(Matrix_NxM *matrix1, Matrix_NxM *matrix2);
Matrix_NxM getSubMatrix(const Matrix_NxM *matrix, int exclude_row, int exclude_col);
double determinantMatrix(Matrix_NxM *matrix);
Matrix_NxM inverseMatrix(Matrix_NxM *matrix);

#endif
