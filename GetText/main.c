#include "lib/correct_text.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TERMINATOR '#'

void choiceStdinText(int *pointer);

FILE *selectInputSource(int choice);

char *myRealloc(char *pointer, size_t oldSize, size_t newSize);

char *GetText(FILE *stream, char terminator);

/**
 * Реализация функции ввода текста произвольного размера: char* GetText(FILE* stream, char terminator)
 * • Конец текста обозначается выбранным символом terminator (например, '#' или '\n')
 * • Возвращается строка в стиле C (нуль-терминированная), не включающая символа terminator
 * • Выделение точного количества необходимой памяти (собственная функция перевыделения памяти безиспользования realloc() )
 * • Использование функции корректировки из задачи 9
 * • Ввод текста из консоли или файла (выбор задается с консоли)
 */
int main() {
    int choice;
    choiceStdinText(&choice);

    FILE *inputSource = selectInputSource(choice);
    if (inputSource == NULL) {
        fprintf(stderr, "The input source could not be opened!\n");
        return 1;
    }

    if (choice == 1) {
        printf("Enter the text ending in %c:\n", TERMINATOR);
    }

    char *text = GetText(inputSource, TERMINATOR);

    if (choice == 2) {
        fclose(inputSource);
    }

    if (text != NULL) {
        printf("Edited text:\n%s\n", text);
        free(text);
    } else {
        fprintf(stderr, "An error has occurred!\n");
        return 1;
    }

    return 0;
}

void choiceStdinText(int *pointer) {
    while (1) {
        printf("Choose a text input method:\n1.Text input via the console.\n2.Reading text from a file\n_: ");

        if (scanf("%d", pointer) != 1 || getchar() != '\n') {
            printf("Incorrect value was entered for text input selection.!\n");

            while (getchar() != '\n');

            continue;
        }

        if (*pointer != 1 && *pointer != 2) {
            printf("Incorrect text input selection value has been entered!\n");

            continue;
        }

        break;
    }
}

FILE *selectInputSource(int choice) {
    if (choice == 1) {
        return stdin;
    } else {
        char filename[256];

        printf("Enter the relative path to the file: ");
        scanf("%255s", filename);

        while (getchar() != '\n');

        FILE *file = fopen(filename, "r");

        if (file == NULL) {
            fprintf(stderr, "File opening error %s\n", filename);
            return NULL;
        }

        return file;
    }
}


char *myRealloc(char *pointer, size_t oldSize, size_t newSize)
{
    if (newSize < 0)
    {
        return NULL;
    }

    if (newSize == 0)
    {
        free(pointer);
        return NULL;
    }

    if (pointer == NULL)
    {
        return (char *)malloc(newSize);
    }

    size_t newAllocateSize = oldSize < newSize ? oldSize : newSize;
    char *newPointer = (char *)malloc(newAllocateSize);
    if (newPointer == NULL)
    {
        return NULL;
    }

    if (pointer != NULL)
    {
        memcpy(newPointer, pointer, newAllocateSize);
        free(pointer);
    }

    return newPointer;
}

char *GetText(FILE *stream, char terminator) {
    size_t capacity = 100;
    size_t sizeData = 0;
    char ch;

    char *buffer = (char *) malloc(capacity * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Dynamic memory allocation error!\n");
        return NULL;
    }

    while ((ch = fgetc(stream)) != terminator && ch != EOF) {

        if (sizeData >= capacity - 1)
        {
            size_t newCapacity = capacity * 2;
            char *temp = myRealloc(buffer, capacity, newCapacity);

            if (temp == NULL) {
                fprintf(stderr, "Dynamic memory overallocation error!\n");
                free(buffer);
                return NULL;
            }

            buffer = temp;
            capacity = newCapacity;
        }

        buffer[sizeData++] = ch;
    }

    buffer[sizeData++] = '\0';

    if (!correctText(buffer, capacity)) {
        fprintf(stderr, "Couldn't edit the text!\n");
        free(buffer);
        return NULL;
    }

    char *result = (char *) myRealloc(buffer, capacity, strlen(buffer) + 1);
    if (result == NULL) {
        fprintf(stderr, "Couldn't reduce the size of the allocated memory for the string!\n");
        free(buffer);
        return NULL;
    }

    return result;
}
