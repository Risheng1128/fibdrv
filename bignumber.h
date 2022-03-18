/**
 * @file    bignumber.h
 * @brief   實作費氏數列 Big number 計算
 */

#ifndef _BIGNUMBER_H_
#define _BIGNUMBER_H_

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>

#define BUF_SIZE 256

long int str_size(char *str);
void str_cpy(char *dst, char *src, int size);
void addString(char *str1, char *str2, char *buf);

#endif /* End of _BIGNUMBER_H_ */