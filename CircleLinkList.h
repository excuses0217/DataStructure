#ifndef DATASTRUCTURE_CIRCLELINKLIST_H
#define DATASTRUCTURE_CIRCLELINKLIST_H

#include "GlobalDefine.h"

// -------------------带头结点的循环单链表-------------------

typedef struct LNode {
    ElemType data;
    LNode *next;
} LNode, *LinkList;

/**
 * 初始化带头结点的循环单链表
 * @param L 循环单链表头指针
 * @return 初始化成功返回OK，否则返回ERROR
 */
Status InitList(LinkList &L) {
    L = (LinkList) malloc(sizeof(LNode));
    if (L == NULL)
        return ERROR;
    L->next = L;
    return OK;
}

// -------------------带头结点的循环双链表-------------------

typedef struct DNode {
    ElemType data;
    DNode *prior, *next;
} DNode, *DLinkList;

/**
 * 初始化带头结点的循环双链表
 * @param L 双链表头指针
 * @return 初始化成功返回OK，否则返回ERROR
 */
Status InitList(DLinkList &L) {
    L = (DLinkList) malloc(sizeof(DNode));
    if (L == NULL) {
        return ERROR;
    }
    L->prior = L;
    L->next = L;
    return OK;
}

bool Empty(DLinkList L) {
    if (L->next == L) {
        return true;
    } else {
        return false;
    }
}

bool isTail(DLinkList L, DNode *p) {
    if (p->next == L) {
        return true;
    } else {
        return false;
    }
}

#endif //DATASTRUCTURE_CIRCLELINKLIST_H
