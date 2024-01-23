//
// Created by covald on 23.01.24.
//
#define _CRT_SECURE_NO_WARNINGS

#include "dynamic_string.h"

void flushBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void get_choice(int *c) {
    scanf("%d", c);
    flushBuffer();
}

char *read_string() {
    int len = 0; // изначально строка пуста
    int capacity = 1; // ёмкость контейнера динамической строки (1, так как точно будет '\0')
    char *s = (char *) malloc(sizeof(char)); // динамическая пустая строка

    char c = getchar(); // символ для чтения данных

    // читаем символы, пока не получим символ переноса строки (\n)
    while (c != '\n') {
        s[len++] = c; // заносим в строку новый символ

        // если реальный размер больше размера контейнера, то увеличим его размер
        if (len >= capacity) {
            capacity *= 2; // увеличиваем ёмкость строки в два раза
            s = (char *) realloc(s, capacity * sizeof(char)); // создаём новую строку с увеличенной ёмкостью
        }

        c = getchar(); // считываем следующий символ
    }

    s[len] = '\0'; // завершаем строку символом конца строки

    return s; // возвращаем указатель на считанную строку
}

//char *read_password(){
//    int i = 0;
//    char ch;
//    size_t length = 1;
//    char *password = malloc(length);
//
//    if (!password) {
//        // Обработка ошибки выделения памяти
//        fprintf(stderr, "Ошибка выделения памяти\n");
//        exit(EXIT_FAILURE);
//    }
//
//    printf("Введите пароль: ");
//
//    while (1) {
//        ch = getch(); // Считываем символ без отображения
//        if (ch == '\r' || ch == '\n') {
//            break; // Если введен Enter, завершаем цикл
//        } else if (ch == '\b' && i > 0) {
//            // Если введен Backspace и есть символы в строке, удаляем последний символ
//            i--;
//            printf("\b \b"); // Удаляем символ из консоли
//        } else {
//            // Если необходимо, перевыделяем память для массива пароля
//            if (i >= length - 1) {
//                length *= 2;
//                char *temp = realloc(password, length);
//                if (!temp) {
//                    // Обработка ошибки перевыделения памяти
//                    fprintf(stderr, "Ошибка перевыделения памяти\n");
//                    free(password);
//                    exit(EXIT_FAILURE);
//                }
//                password = temp;
//            }
//
//            // Сохраняем символ
//            password[i++] = ch;
//            printf("*"); // Заменяем символ на '*'
//        }
//    }
//
//    password[i] = '\0'; // Добавляем завершающий нуль для создания строки
//    printf("\n");
//
//    return password;
//}