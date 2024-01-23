//
// Created by covald on 23.01.24.
//

#include "hash.h"

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

// Константы для MD5
const uint32_t k[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

const uint32_t s[] = {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

void hash_md5(char *input, char *output) {
    uint32_t h0, h1, h2, h3;

    // Инициализация переменных
    h0 = 0x67452301;
    h1 = 0xEFCDAB89;
    h2 = 0x98BADCFE;
    h3 = 0x10325476;

    // Вычисление длины в битах
    size_t originalLen = strlen(input) * 8;

    // Добавление бита "1" в конец сообщения
    char *paddedInput = (char *) malloc(strlen(input) + 64 + 8);
    strcpy(paddedInput, input);
    paddedInput[strlen(input)] = 0x80;

    // Добавление нулей
    for (size_t i = strlen(input) + 1; i % 64 != 56; i++)
        paddedInput[i] = 0;

    // Добавление длины в конец
    for (size_t i = 0; i < 8; i++)
        paddedInput[strlen(input) + 64 + i] = (originalLen >> (8 * i)) & 0xFF;

    // Обработка блоков по 512 бит (64 байта)
    for (size_t i = 0; i < strlen(paddedInput); i += 64) {
        uint32_t *chunk = (uint32_t *) &paddedInput[i];

        uint32_t a = h0, b = h1, c = h2, d = h3, f, g;

        for (int j = 0; j < 64; j++) {
            if (j < 16) {
                f = (b & c) | ((~b) & d);
                g = j;
            } else if (j < 32) {
                f = (d & b) | ((~d) & c);
                g = (5 * j + 1) % 16;
            } else if (j < 48) {
                f = b ^ c ^ d;
                g = (3 * j + 5) % 16;
            } else {
                f = c ^ (b | (~d));
                g = (7 * j) % 16;
            }

            uint32_t temp = d;
            d = c;
            c = b;
            b = b + LEFTROTATE((a + f + k[j] + chunk[g]), s[j]);
            a = temp;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
    }

    // Форматирование вывода
    sprintf(output, "%08x%08x%08x%08x", h0, h1, h2, h3);

    // Освобождение выделенной памяти
    free(paddedInput);
}

unsigned int hash_simple(char *in) {
    unsigned int hash = 0;

    while (*in) {
        hash += *in;
        in++;
    }

    return hash;
}