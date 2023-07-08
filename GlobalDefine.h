#ifndef DATASTRUCTURE_GLOBALDEFINE_H
#define DATASTRUCTURE_GLOBALDEFINE_H

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 0
#define ERROR (-1)
#define OVERFLOW (-2)

typedef int Status;
typedef int ElemType;

/**
 * 检查输入的参数是否有效
 * @return 如果输入有效，返回1；否则返回0
 */
int CheckScanf(ElemType &value) {
    int valid = 1; // 默认输入有效
    if (scanf("%d", &value) != 1) {
        valid = 0; // 输入无效
        printf("输入无效，请重新输入！\n");
        while (getchar() != '\n'); // 清空输入缓冲区
    }
    return valid;
}

#endif //DATASTRUCTURE_GLOBALDEFINE_H
