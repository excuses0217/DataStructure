#ifndef DATASTRUCTURE_STATICLINKLIST_H
#define DATASTRUCTURE_STATICLINKLIST_H

#include "../GlobalDefine.h"

// -------------------静态链表-------------------

typedef struct {
    ElemType data;
    int next;
} SLinkList[MAXSIZE];

// 初始化静态链表
Status InitList(SLinkList &L) {
    for (int i = 0; i < MAXSIZE; i++) {
        L[i].data = 0;           // 初始化数据域为0
        L[i].next = -1;         // -1表示没有下一个元素，即为空
    }
    return OK;
}

// 在指定位置插入元素
Status ListInsert(SLinkList &L, int i, ElemType e) {
    int j, k = 0;  // k是头节点
    if (i < 1) {
        printf("插入位序不合法！");
        return ERROR;
    }
    // 查找可用位置
    int avail = 0;
    while (L[avail].next != -1) avail++;

    for (j = 1; j < i && k != -1; j++) {
        k = L[k].next;
    }
    if (k == -1) {
        printf("插入位序不合法！");
        return ERROR;
    }
    L[avail].data = e;         // 设置数据
    L[avail].next = L[k].next; // 调整链接
    L[k].next = avail;

    return OK;
}

// 批量插入元素至静态链表
Status BatchSLinkListInsert(SLinkList &L) {
    int value;
    int position = 1;
    int tail = 0; // 用于跟踪链表的尾部

    // 寻找链表的尾部
    while (L[tail].next != -1) {
        tail = L[tail].next;
        position++;
    }

    printf("请输入要插入的元素（输入0表示结束）：\n");
    while (true) {
//        scanf("%d", &value);
        while (true) if (CheckScanf(value) == 1) break;

        if (value == 0) {
            break;
        }
        if (ListInsert(L, position, value) == OK) {
            printf("成功插入元素 %d\n", value);
            position++;
            tail = L[tail].next; // 更新尾部
        } else {
            printf("插入失败！\n");
        }
    }
    return OK;
}

// 在指定位置删除元素，并返回被删除的元素
Status ListDelete(SLinkList &L, int i, ElemType &e) {
    int j, k = 0;  // k是头节点
    if (i < 1) {
        printf("删除位序不合法！");
        return ERROR;
    }

    for (j = 1; j < i - 1 && k != -1; j++) {
        k = L[k].next;
    }
    if (k == -1 || L[k].next == -1) {
        printf("删除位序不合法！");
        return ERROR;
    }

    int del = L[k].next;       // 被删除节点的位置
    e = L[del].data;           // 保存被删除节点的数据
    L[k].next = L[del].next;   // 调整链接
    L[del].next = -1;          // 将被删除的节点标记为可用

    return OK;
}

// 按位查找元素
ElemType GetElem(SLinkList L, int i) {
    int j, k = 0;  // k是头节点
    for (j = 1; j < i && k != -1; j++) {
        k = L[k].next;
    }
    if (k == -1) return ERROR; // 查找失败

    return L[k].data;
}

// 按值查找元素的位置
int LocateElem(SLinkList L, ElemType e) {
    int i = 0;
    while (i != -1 && L[i].data != e) {
        i = L[i].next;
    }
    if (i == -1) return 0; // 如果没找到，返回0

    return i + 1;
}

// 打印链表
void PrintList(SLinkList L) {
    int i = 0;
    while (L[i].next != -1) {
        printf("[%d]:%d  ", i + 1, L[i].data);
        i = L[i].next;
    }
    printf("\n");
}

#endif //DATASTRUCTURE_STATICLINKLIST_H
