#include "correct_text.h"

// Является ли буквой
int isLetter(char symbol) {
    return (symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z');
}

// Является ли заглавной буквой
int isCapitalLetter(char symbol) {
    return symbol >= 'A' && symbol <= 'Z';
}

// Является ли строчной буквой
int isLowercaseLetter(char symbol) {
    return symbol >= 'a' && symbol <= 'z';
}

// Меняем строчную на заглавную
char changeLowercase(char symbol) {
    if (isLowercaseLetter(symbol)) {
        return symbol - 32;
    }

    return symbol;
}

// Меняем заглавную на строчную
char changeCapital(char symbol) {
    if (isCapitalLetter(symbol)) {
        return symbol + 32;
    }

    return symbol;
}

// Является концом предложения
int isSentenceEnd(char symbol) {
    return symbol == '.' || symbol == '!' || symbol == '?';
}

// Является пробелом, табом и переходом на новую строку
int isSpace(char symbol) {
    return symbol == ' ' || symbol == '\t' || symbol == '\n';
}

// Является ли знаком препинания
int isPunctuationMarks(char symbol) {
    return symbol == '.' || symbol == '!' || symbol == '?' || symbol == ',' || symbol == ':' || symbol == ';';
}

// Удаляет char по индексу и смещает весь массив влево после удаленного символа
void deleteChar(char *pointerText, int indexDeleteChar) {
    for (int i = indexDeleteChar; pointerText[i] != '\0'; i++) {
        pointerText[i] = pointerText[i + 1];
    }
}

// Добавляет пробел и сдвигает все символы вправо начиная с indexAddSpaceChar
int addSpaceChar(char *pointerText, int indexAddSpaceChar, size_t allocatedSize) {
    size_t len = strlen(pointerText);

    if (len >= allocatedSize - 2) {
        return 0;
    }

    for (int i = len; i >= indexAddSpaceChar; i--) {
        pointerText[i + 1] = pointerText[i];
    }

    pointerText[indexAddSpaceChar] = ' ';
    return 1;
}

int correctText(char *pointerText, size_t allocatedSize) {
    int isStartSentence = 1;
    int isStartText = 1;

    for (int i = 0; pointerText[i] != '\0'; i++) {
        if ((isSpace(pointerText[i]) && isStartText) || (isPunctuationMarks(pointerText[i]) && isStartText)) {
            deleteChar(pointerText, i);
        }

        if (isLetter(pointerText[i])) {
            if (isStartSentence) {
                pointerText[i] = changeLowercase(pointerText[i]);
                isStartSentence = 0;
            } else {
                pointerText[i] = changeCapital(pointerText[i]);
            }

            isStartText = 0;
        }

        if (isSentenceEnd(pointerText[i])) {
            isStartSentence = 1;
        }

        if (isSpace(pointerText[i]) && isSpace(pointerText[i + 1])) {
            deleteChar(pointerText, i);
            i--;
            continue;
        }

        if (isSpace(pointerText[i]) && isPunctuationMarks(pointerText[i + 1])) {
            deleteChar(pointerText, i);
            i--;
            continue;
        }

        if (isPunctuationMarks(pointerText[i]) && !isSpace(pointerText[i + 1])) {
            if (!addSpaceChar(pointerText, i + 1, allocatedSize)) {
                return 0;
            }

            continue;
        }
    }

    return 1;
}
