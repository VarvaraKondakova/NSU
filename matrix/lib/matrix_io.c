#include "matrix_io.h"

int InitMatrix(Matrix_NxM *matrix) {
    double **pointerArray = (double **) malloc(
            matrix->rows * sizeof(double *) + matrix->rows * matrix->columns * sizeof(double));

    if (pointerArray == NULL) {
        perror("Failed to allocate memory for the dynamic matrix!");
        return 0;
    }

    double *tempPointer = (double *) (pointerArray + matrix->rows);

    for (int i = 0; i < matrix->rows; i++)
        pointerArray[i] = tempPointer + matrix->columns * i;

    matrix->pointerDynamicMatrix = pointerArray;

    return 1;
}

int freeMatrix(Matrix_NxM *matrix) {
    if (matrix == NULL) {
        fprintf(stderr, "The matrix is not initialized!\n");
        return 0;
    }

    free(matrix->pointerDynamicMatrix);

    return 1;
}

int PrintMatrix(const Matrix_NxM *matrix) {
    if (matrix == NULL) {
        fprintf(stderr, "The matrix is not initialized!\n");
        return 0;
    }

    for (int i = 0; i < matrix->rows; i++) {
        printf("| ");

        for (int j = 0; j < matrix->columns; j++) {
            printf("%.2lf", matrix->pointerDynamicMatrix[i][j]);

            if (j < matrix->columns - 1)
                printf(" ");
        }

        printf(" |\n");
    }

    return 1;
}

int inputMatrix(Matrix_NxM *matrix) {
    if (matrix == NULL) {
        fprintf(stderr, "The matrix is not initialized!\n");
        return 0;
    }

    while (1) {
        printf("Enter the values for the matrix, size %d by %d: ", matrix->rows, matrix->columns);

        for (int i = 0; i < matrix->rows; i++) {
            for (int j = 0; j < matrix->columns; j++) {
                scanf_s("%lf", &matrix->pointerDynamicMatrix[i][j]);
            }
        }

        if (getchar() != '\n') {
            printf("Incorrect data was entered for the matrix!\n");
            while (getchar() != '\n');

            continue;
        }

        break;
    }

    return 1;
}

void inputValueInt(int *pointerValue, const char *descriptionValues) {
    while (1) {
        printf("Enter a value for the number of %s in the matrix: ", descriptionValues);

        if (scanf_s("%d", pointerValue) != 1 || getchar() != '\n') {
            printf("Incorrect value entered!\n");

            while (getchar() != '\n');

            continue;
        }

        break;
    }
}

int inputValueRowsAndColumns(Matrix_NxM *matrix) {
    if (matrix == NULL) {
        fprintf(stderr, "The matrix is not initialized!\n");
        return 0;
    }

    while (1) {
        inputValueInt(&matrix->rows, "rows");

        if (matrix->rows < 1) {
            printf("An incorrect value has been entered for the number of rows, it should be > 1!\n");

            continue;
        }

        break;
    }

    while (1) {
        inputValueInt(&matrix->columns, "columns");

        if (matrix->columns < 1) {
            printf("An incorrect value was entered for the number of columns, it should be > 1!\n");

            continue;
        }

        break;
    }

    return 1;
}

int fillMatrixRandom(Matrix_NxM *matrix) {
    if (matrix == NULL) {
        fprintf(stderr, "The matrix is not initialized!\n");
        return 0;
    }

    srand(time(NULL));

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            matrix->pointerDynamicMatrix[i][j] = (double) rand();
        }
    }

    return 1;
}

int searchingForElementIndexDynamicMatrix(const Matrix_NxM *matrix, int row, int column) {
    if (matrix == NULL) {
        fprintf(stderr, "The matrix is not initialized!\n");
        return 0;
    }

    if (row < 0 || row > matrix->rows || column < 0 || column > matrix->columns) {
        fprintf(stderr, "Incorrect element indexes in the matrix!\n");
        return 0;
    }

    return matrix->rows + row * matrix->columns + column;
}

int readingMatrixFromFile(Matrix_NxM *matrix, const char *pathToFile) {
    if (matrix == NULL || pathToFile == NULL) {
        perror(fprintf(stderr, "The matrix or the file path is not initialized!\n");
        return 0;
    }

    FILE *file = fopen(pathToFile, "r");

    if (file == NULL) {
        perror("Couldn't open the file!\n");
        return 0;
    }

    int rows, columns;

    if (fscanf_s(file, "%d %d", &rows, &columns) != 2) {
        fprintf(stderr, "Incorrect file format - the dimensions of the matrix could not be read!\n");
        fclose(file);
        return 0;
    }

    if (rows != matrix->rows || columns != matrix->columns) {
        fprintf(stderr, "The dimensions of the matrix in the file (%dx%d) do not match the current matrix (%dx%d)!\n",
                rows, columns, matrix->rows, matrix->columns);
        fclose(file);
        return 0;
    }

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            if (fscanf_s(file, "%lf", &matrix->pointerDynamicMatrix[i][j]) != 1) {
                fprintf(stderr, "Couldn't read the [%d][%d] element!\n", i, j);
                fclose(file);
                return 0;
            }
        }
    }

    fclose(file);

    return 1;
}

int saveMatrixToFile(const Matrix_NxM *matrix, const char *pathToFile) {
    if (matrix == NULL || pathToFile == NULL) {
        fprintf(stderr, "The matrix or the file path is not initialized!\n");
        return 0;
    }

    FILE *file = fopen(pathToFile, "w");

    if (file == NULL) {
        perror("Couldn't open the file for writing!\n");
        return 0;
    }

    fprintf(file, "%d %d\n", matrix->rows, matrix->columns);

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            fprintf(file, "%.2lf ", matrix->pointerDynamicMatrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);

    return 1;
}

Matrix_NxM createMatrix(int rows, int columns) {
    Matrix_NxM result = {0};

    if (rows <= 0 || columns <= 0) {
        fprintf(stderr, "Incorrect values for the number of rows and columns\n.");
        return result;
    }

    result.rows = rows,
            result.columns = columns;

    if (!InitMatrix(&result)) {
        fprintf(stderr, "Function int InitMatrix(Matrix_NxM *matrix) returned an error!\n.");
        return result;
    }

    return result;
}
