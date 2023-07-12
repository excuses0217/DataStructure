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

/**
 * 销毁带头结点的循环单链表
 * @param L 循环单链表头指针
 * @return 销毁成功返回OK，否则返回ERROR
 */
Status DestroyList(LinkList &L) {
    if (L == NULL)
        return ERROR;
    LNode *p = L->next;
    while (p != L) {
        LNode *q = p->next;
        free(p);
        p = q;
    }
    free(L);
    L = NULL;
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

/**
 * 销毁带头结点的循环双链表
 * @param L 循环双链表头指针
 * @return 销毁成功返回OK，否则返回ERROR
 */
Status DestroyList(DLinkList &L) {
    if (L == NULL)
        return ERROR;
    DNode *p = L->next;
    while (p != L) {
        DNode *q = p->next;
        free(p);
        p = q;
    }
    free(L);
    L = NULL;
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

/**
 * 求带头结点的循环双链表长度
 * @param L 循环双链表头指针
 * @return 循环双链表长度
 */
int Length(DLinkList L) {
    int len = 0;
    DNode *p = L;
    while (p->next != L) {
        p = p->next;
        len++;
    }
    return len;
}

/**
 * 删除指定结点之后的结点
 * @param p 指定结点的指针
 * @return 删除成功返回OK，否则返回ERROR
 */
Status DeleteNextDNode(DNode *p) {
    if (p == NULL)
        return ERROR;
    DNode *q = p->next;
    if (q == NULL)
        return ERROR;
    p->next = q->next;
    q->next->prior = p;
    free(q);
    return OK;
}

/**
 * 在指定结点之后插入元素
 * @param p 指定结点的指针
 * @param e 待插入的元素值
 * @return 插入成功返回OK，否则返回ERROR
 */
Status InsertNextDNode(DNode *p, ElemType e) {
    if (p == NULL)
        return ERROR;
    DNode *s = (DNode *) malloc(sizeof(DNode));
    if (s == NULL)
        return ERROR;// 内存分配失败
    s->data = e;
    s->next = p->next;
    p->next->prior = s;
    s->prior = p;
    p->next = s;
    return OK;
}

/**
 * 在指定结点之后插入结点
 * @param p 指定结点的指针
 * @param s 待插入的结点指针
 * @return 插入成功返回OK，否则返回ERROR
 */
Status InsertNextDNode(DNode *p, DNode *s) {
    if (p == NULL || s == NULL)
        return ERROR;
    s->next = p->next;
    p->next->prior = s;
    s->prior = p;
    p->next = s;
    return OK;
}

#endif //DATASTRUCTURE_CIRCLELINKLIST_H
