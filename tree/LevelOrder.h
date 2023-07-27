#ifndef DATASTRUCTURE_HELP_H
#define DATASTRUCTURE_HELP_H

#include "BiTree.h"

// -------------------带头结点的链式队列-------------------

typedef struct LinkNode {
    BiTree data;
    LinkNode *next;
} LinkNode;

typedef struct {
    LinkNode *front, *rear;
} LinkQueue;

Status InitQueue(LinkQueue &Q) {
    Q.front = Q.rear = (LinkNode *) malloc(sizeof(LinkNode));
    if (Q.front == NULL || Q.rear == NULL)
        return ERROR;// 初始化失败
    Q.front->next = NULL;
    return OK;
}

bool QueueEmpty(LinkQueue Q) {
    return Q.rear == Q.front;
}

Status EnQueue(LinkQueue &Q, BiTree e) {
    LinkNode *s = (LinkNode *) malloc(sizeof(LinkNode));
    s->data = e;
    s->next = NULL;
    Q.rear->next = s;
    Q.rear = s;
    return OK;
}

Status DeQueue(LinkQueue &Q, BiTree &e) {
    if (QueueEmpty(Q))
        return ERROR;// 队列为空
    LinkNode *p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p) // 若原队列中只有一个结点，删除后变空
        Q.rear = Q.front;
    free(p);
    return OK;
}

// -------------------带头结点的链式队列-------------------

// 层序遍历
void levelOrder(BiTree T){
    LinkQueue Q;
    InitQueue(Q);
    BiTree p;
    EnQueue(Q, T);
    while ((!QueueEmpty(Q))) {
        DeQueue(Q, p);
        visit(p);
        if(p->lchild!=NULL)
            EnQueue(Q, p->lchild);
        if(p->rchild!=NULL)
            EnQueue(Q, p->rchild);
    }
}
#endif //DATASTRUCTURE_HELP_H
