#ifndef DATASTRUCTURE_SEQUENCELIST_H
#define DATASTRUCTURE_SEQUENCELIST_H

#include "GlobalDefine.h"

// -------------------静态实现顺序表-------------------

#define MAXSIZE 10

typedef struct {
    ElemType data[MAXSIZE];
    int length;
} SqList;

// 初始化静态顺序表
Status InitSqList(SqList &L) {
    for (int i = 0; i < MAXSIZE; i++)
        L.data[i] = 0;
    L.length = 0;
    return OK;
}

// 在给定位序插入元素
Status ListInsert(SqList &L, int i, ElemType e) {
    if (i < 1 || i > L.length + 1) {
        printf("插入位序不合法！");
        return ERROR;
    }
    if (L.length >= MAXSIZE) {
        printf("当前顺序表已满！");
        return ERROR;
    }
    for (int j = L.length; j >= i; j--)
        L.data[j] = L.data[j - 1];
    L.data[i - 1] = e;
    L.length++;
    return OK;
}

Status BatchListInsert(SqList &L) {
    int value;
    int position = L.length + 1;

    printf("请输入要插入的元素（输入0表示结束）：\n");
    while (1) {
        scanf("%d", &value);
        if (value == 0) {
            break;
        }
        if (ListInsert(L, position, value) == OK) {
            printf("成功插入元素 %d\n", value);
            position++;
        } else {
            printf("插入失败！\n");
        }
    }
    return OK;
}

// 在给定位序删除元素
Status ListDelete(SqList &L, int i, ElemType &e) {
    if (i < 1 || i > L.length + 1) {
        printf("删除位序不合法！");
        return ERROR;
    }
    e = L.data[i - 1];
    for (int j = i; j < L.length; j++) {
        L.data[j - 1] = L.data[j];
    }
    L.data[L.length - 1] = 0;
    L.length--;
    return OK;
}

// 按位查找元素
ElemType GetElem(SqList L, int i) {
    if(i>MAXSIZE)
        return ERROR;
    return L.data[i - 1];
}

// 按值查找元素
int LocateElem(SqList L, ElemType e) {
    for (int i = 0; i < MAXSIZE; i++) {
        if (L.data[i] == e)
            return i + 1;
    }
    return 0;
}

void printList(SqList L) {
    if (L.length == 0) {
        printf("This List is empty!\n");
    } else {
        for (int i = 0; i < L.length; i++)
            printf("[%d]:%d  ", i + 1, L.data[i]);
        printf("\n");
    }

}

void printAllList(SqList L) {
    printf("length=%d\n", L.length);
    for (int i = 0; i < MAXSIZE; i++)
        printf("[%d]:data[%d]=%d\n", i + 1, i, L.data[i]);

}

Status interactiveMenu4StaticSqList(){
    SqList L;
    InitSqList(L); // 初始化静态顺序表

    int choice;
    ElemType value;
    int position;

    printf("-------------测试静态分配顺序表-------------\n");

    while (1) {
        printf("请输入操作：\n"
               "1：插入值\n"
               "2：批量插入值\n"
               "3：按位删除某元素\n"
               "4：按位查找\n"
               "5：按值查找\n"
               "6：打印目前顺序表\n"
               "0：退出程序\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (L.length >= MAXSIZE) {
                    printf("当前顺序表已满！\n");
                } else {
                    printf("请输入要插入的值：");
                    scanf("%d", &value);
                    printf("请输入要插入的位置：");
                    scanf("%d", &position);
                    if (ListInsert(L, position, value) == OK) {
                        printf("插入成功！\n");
                    } else {
                        printf("插入失败！\n");
                    }
                }
                break;
            case 2:
                BatchListInsert(L);
                break;
            case 3:
                if (L.length == 0) {
                    printf("当前顺序表为空！\n");
                } else {
                    printf("请输入要删除元素的位置：");
                    scanf("%d", &position);
                    if (ListDelete(L, position, value) == OK) {
                        printf("删除成功！删除的元素为：%d\n", value);
                    } else {
                        printf("删除失败！\n");
                    }
                }
                break;
            case 4:
                if (L.length == 0) {
                    printf("当前顺序表为空！\n");
                } else {
                    printf("请输入要查找的位置：");
                    scanf("%d", &position);
                    if (position < 1 || position > L.length) {
                        printf("位置不合法！\n");
                    } else {
                        value = GetElem(L, position);
                        printf("位置 %d 的元素为：%d\n", position, value);
                    }
                }
                break;
            case 5:
                if (L.length == 0) {
                    printf("当前顺序表为空！\n");
                } else {
                    printf("请输入要查找的值：");
                    scanf("%d", &value);
                    position = LocateElem(L, value);
                    if (position == 0) {
                        printf("未找到元素 %d！\n", value);
                    } else {
                        printf("元素 %d 的位置为：%d\n", value, position);
                    }
                }
                break;
            case 6:
                printf("当前顺序表内容如下：\n");
                printList(L);
                break;
            case 0:
                printf("程序已退出！\n");
                return 0;
            default:
                printf("无效的操作！\n");
                break;
        }
    }
}

// -------------------静态实现顺序表部分结束-------------------

// -------------------动态实现顺序表-------------------

#define InitSize 10

typedef struct {
    ElemType *data;
    int MaxSize;
    int length;
} SeqList;

// 初始化动态分配顺序表
Status InitSeqList(SeqList &L) {
    L.data = (ElemType *) malloc(sizeof(ElemType) * InitSize);
    L.length = 0;
    L.MaxSize = InitSize;
    for (int i = 0; i < L.MaxSize; i++)
        L.data[i] = 0;
    return OK;
}

// 动态增加顺序表最大长度
Status IncreaseSize(SeqList &L, int len) {
    ElemType *p = L.data;
    L.data = (ElemType *) malloc(sizeof(ElemType) * (L.MaxSize + len));
    for (int i = 0; i < L.MaxSize; i++)
        L.data[i] = p[i];
    L.MaxSize += len;
    free(p);
    for (int i = 0; i < L.MaxSize; i++)
        L.data[i] = 0;
    return OK;
}

// 在给定位序插入元素
Status ListInsert(SeqList &L, int i, ElemType e) {
    if (i < 1 || i > L.length + 1) {
        printf("插入位序不合法！");
        return ERROR;
    }
    if (L.length >= L.MaxSize) {
        printf("当前顺序表已满！");
        return ERROR;
    }
    for (int j = L.length; j >= i; j--)
        L.data[j] = L.data[j - 1];
    L.data[i - 1] = e;
    L.length++;
    return OK;
}

Status BatchListInsert(SeqList &L) {
    int value;
    int position = L.length + 1;

    printf("请输入要插入的元素（输入0表示结束）：\n");
    while (1) {
        scanf("%d", &value);
        if (value == 0) {
            break;
        }
        if (ListInsert(L, position, value) == OK) {
            printf("成功插入元素 %d\n", value);
            position++;
        } else {
            printf("插入失败！\n");
        }
    }
    return OK;
}


// 在给定位序删除元素
Status ListDelete(SeqList &L, int i, ElemType &e) {
    if (i < 1 || i > L.length + 1) {
        printf("删除位序不合法！");
        return ERROR;
    }
    e = L.data[i - 1];
    for (int j = i; j < L.length; j++) {
        L.data[j - 1] = L.data[j];
    }
    L.data[L.length - 1] = 0;
    L.length--;
    return OK;
}

// 按位查找元素
ElemType GetElem(SeqList L, int i) {
    if(i>L.MaxSize)
        return ERROR;
    return L.data[i - 1];
}

// 按值查找元素
int LocateElem(SeqList L, ElemType e) {
    for (int i = 0; i < L.MaxSize; i++) {
        if (L.data[i] == e)
            return i + 1;
    }
    return 0;
}

// 输出动态顺序表 data 值
void printList(SeqList L) {
    if (L.length == 0) {
        printf("This List is empty!\n");
    } else {
        for (int i = 0; i < L.length; i++)
            printf("[%d]:%d  ", i + 1, L.data[i]);
        printf("\n");
    }
}

// 输出动态顺序表最大长度
void printMaxSize(SeqList L) {
    printf("MaxSize=%d\n", L.MaxSize);
}

Status interactiveMenu4DynamicSqList(){
    SeqList L;
    InitSeqList(L); // 初始化静态顺序表

    int choice;
    ElemType value;
    int position;

    printf("-------------测试动态分配顺序表-------------\n");

    while (1) {
        printf("请输入操作：\n"
               "1：插入值\n"
               "2：批量插入值\n"
               "3：按位删除某元素\n"
               "4：按位查找\n"
               "5：按值查找\n"
               "6：增加顺序表长度\n"
               "7：打印目前顺序表\n"
               "8：获取当前表最大长度\n"
               "0：退出程序\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (L.length >= MAXSIZE) {
                    printf("当前顺序表已满！\n");
                } else {
                    printf("请输入要插入的值：");
                    scanf("%d", &value);
                    printf("请输入要插入的位置：");
                    scanf("%d", &position);
                    if (ListInsert(L, position, value) == OK) {
                        printf("插入成功！\n");
                    } else {
                        printf("插入失败！\n");
                    }
                }
                break;
            case 2:
                BatchListInsert(L);
                break;
            case 3:
                if (L.length == 0) {
                    printf("当前顺序表为空！\n");
                } else {
                    printf("请输入要删除元素的位置：");
                    scanf("%d", &position);
                    if (ListDelete(L, position, value) == OK) {
                        printf("删除成功！删除的元素为：%d\n", value);
                    } else {
                        printf("删除失败！\n");
                    }
                }
                break;
            case 4:
                if (L.length == 0) {
                    printf("当前顺序表为空！\n");
                } else {
                    printf("请输入要查找的位置：");
                    scanf("%d", &position);
                    if (position < 1 || position > L.length) {
                        printf("位置不合法！\n");
                    } else {
                        value = GetElem(L, position);
                        printf("位置 %d 的元素为：%d\n", position, value);
                    }
                }
                break;
            case 5:
                if (L.length == 0) {
                    printf("当前顺序表为空！\n");
                } else {
                    printf("请输入要查找的值：");
                    scanf("%d", &value);
                    position = LocateElem(L, value);
                    if (position == 0) {
                        printf("未找到元素 %d！\n", value);
                    } else {
                        printf("元素 %d 的位置为：%d\n", value, position);
                    }
                }
                break;
            case 6:
                printf("请输入需要扩充的长度：");
                int increaseLength;
                scanf("%d", &increaseLength);
                IncreaseSize(L, increaseLength);
                printf("表长成功增加%d\n",increaseLength);
                break;
            case 7:
                printf("当前顺序表内容如下：\n");
                printList(L);
                break;
            case 8:
                printf("当前表的最大长度如下：\n");
                printMaxSize(L);
                break;
            case 0:
                printf("程序已退出！\n");
                return 0;
            default:
                printf("无效的操作！\n");
                break;
        }
    }
}

#endif //DATASTRUCTURE_SEQUENCELIST_H
