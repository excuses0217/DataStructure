#ifndef DATASTRUCTURE_LINKLISTWITHHEAD_H
#define DATASTRUCTURE_LINKLISTWITHHEAD_H

#include "GlobalDefine.h"

// -------------------带头节点的单链表-------------------

typedef struct LNode {
    ElemType data;
    LNode *next;
} LNode, *LinkList;

// 初始化单链表
Status InitList(LinkList &L) {
    L = (LNode *) malloc(sizeof(LNode));
    if (L == NULL) {
        return ERROR;
    }
    L->next = NULL;
    return OK;
}

// 求表的长度
int Length(LinkList L){
    int len = 0;
    LNode *p = L;
    while (p->next!=NULL){
        p = p->next;
        len++;
    }
    return len;
}

LNode *GetElem(LinkList L, int i) {
    if (i < 0)
        return NULL;
    LNode *p;
    p = L;
//----for 方法实现----
/*    for (int j = 0; j < i - 1; j++) {
        p = p->next;
        if (p == NULL)
            return p;
    }*/
//----while 方法实现----
    int j = 0;// 当前 p 指向第 j 个节点
    while (p != NULL && j < i) {
        p = p->next;
        j++;
    }
    return p;
}

// 按值查找，找到数据域==e 的节点
LNode *LocateNode(LinkList L, ElemType e) {
    LNode *p = L->next;
    // 从第1个结点开始查找数据域为e的结点
    while (p != NULL && p->data != e)
        p = p->next;
    return p;
}

// 前插操作：在 p 节点之前插入元素 e
Status InsertPriorNode(LNode *p, ElemType e) {
    if (p == NULL)
        return ERROR;
    LNode *s = (LNode *) malloc(sizeof(LNode));
    if (s == NULL)
        return ERROR;// 内存分配失败
    s->next = p->next;
    p->next = s;
    s->data = p->data;
    p->data = e;
    return OK;
}

// 前插操作：在 p 节点之前插入节点 s
Status InsertPriorNode(LNode *p, LNode *s) {
    if (p == NULL || s == NULL)
        return ERROR;
    s->next = p->next;
    p->next = s;
    ElemType temp = s->data;
    s->data = p->data;
    p->data = temp;
    return OK;
}

// 后插操作：在 p 节点之后插入元素 e
Status InsertNextNode(LNode *p, ElemType e) {
    if (p == NULL)
        return ERROR;
    LNode *s = (LNode *) malloc(sizeof(LNode));
    if (s == NULL)
        return ERROR;// 内存分配失败
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

// 后插操作：在 p 节点之后插入节点 s
Status InsertNextNode(LNode *p, LNode *s) {
    if (p == NULL || s == NULL)
        return ERROR;
    s->next = p->next;
    p->next = s;
    return OK;
}

// 给定位置删除元素 e
Status ListDelete(LinkList &L, int i, ElemType &e) {
    if (i < 1)
        return ERROR;
    LNode *p = GetElem(L, i - 1);
    if (p == NULL || p->next == NULL)
        return ERROR;// i 值不合法或者找不到要删除的节点（没有第 i 个节点）
    LNode *q = p->next;
    e = q->data;
    p->next = q->next;
    free(q);
    return OK;
}

// 删除指定节点 p
Status DeleteNode(LNode *p) {
    if (p == NULL)
        return ERROR;
    LNode *q = p->next;
    if (p->next == NULL)
        return ERROR;
    p->data = p->next->data;
    p->next = q->next;
    free(q);
    return OK;
}

// 给定位置插入元素
Status ListInsert(LinkList &L, int i, ElemType e) {
    if (i < 1)
        return ERROR;
    LNode *p = GetElem(L, i - 1);
//-------------------------
    if (p == NULL)
        return ERROR;// i 值不合法
    LNode *s = (LNode *) malloc(sizeof(LNode));
    if (s == NULL)
        return ERROR;// 内存分配失败
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
//----以上可直接替换为以下-----
//    return InsertNextNode(p, e);
}

void printList(LinkList L) {
    LNode *p;
    p = L->next;
    int count = 1;
    while (p != NULL) {
        printf("[%d]:%d  ", count, p->data);
        p = p->next;
        count++;
    }
    printf("\n");
}

#endif //DATASTRUCTURE_LINKLISTWITHHEAD_H
