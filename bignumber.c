/**
 * @file    bignumber.c
 * @brief   實作費氏數列 Big number 計算
 */
#include "bignumber.h"

/**
 * @fn     - str_size
 * @brief  - 回傳字傳長度
 */
long int str_size(char *str)
{
    char *cpy = str;
    for (; *cpy != '\0'; ++cpy)
        ;
    return (long int) (cpy - str);
}

/**
 * @fn     - char_swap
 * @brief  - 字元兩兩交換
 */
static void char_swap(char *char1, char *char2)
{
    *char1 ^= *char2;
    *char2 ^= *char1;
    *char1 ^= *char2;
}

/**
 * @fn     - str_reverse
 * @brief  - 翻轉字串
 */
static void str_reverse(char *str, int size)
{
    int head = 0, tail = size - 1;
    while ((head != tail) && (tail > head)) {
        char_swap(str + head, str + tail);
        head++;
        tail--;
    }
}

/**
 * @fn     - str_cpy
 * @brief  - 將字串 src 複製到字串 dst
 */
void str_cpy(char *dst, char *src, int size)
{
    for (int i = 0; i < size; i++)
        *(dst + i) = *(src + i);
    *(dst + size) = '\0';
}

/**
 * @fn     - addString
 * @brief  - 將兩個字串相加，並儲存到 kbuf 裡
 */
void addString(char *kmin_str, char *kmax_str, char *kbuf)
{
    char min_str[BUF_SIZE], max_str[BUF_SIZE];
    long int min_size = str_size(kmin_str);
    long int max_size = str_size(kmax_str);

    str_cpy(min_str, kmin_str, min_size);
    str_cpy(max_str, kmax_str, max_size);

    str_reverse(min_str, min_size);
    str_reverse(max_str, max_size);

    int carry = 0, sum;
    long int index;

    for (index = 0; index < min_size; index++) {
        sum = max_str[index] - '0' + min_str[index] - '0' + carry;
        kbuf[index] = sum % 10 + '0';
        carry = sum / 10;
    }

    for (index = min_size; index < max_size; index++) {
        sum = max_str[index] - '0' + carry;
        kbuf[index] = sum % 10 + '0';
        carry = sum / 10;
    }

    if (carry)
        kbuf[index++] = '1';
    kbuf[index] = '\0';
    str_reverse(kbuf, index);
}
