#ifndef DATASTRUCTURE_BITREE_H
#define DATASTRUCTURE_BITREE_H

#include "../GlobalDefine.h"

// -------------------链式二叉树-------------------

typedef struct BiTNode {
    ElemType data;
    BiTNode *lchild, *rchild; // 左右孩子指针
} BiTNode, *BiTree;

Status InitBiTree(BiTree &T) {
    T = (BiTree) malloc(sizeof(BiTNode));
    if (T == NULL)
        return ERROR; // 分配内存失败
    T->lchild = T->rchild = NULL;
    return OK;
}

Status DestroyBiTree(BiTree &T);

Status ClearBiTree(BiTree &T);

bool BiTreeEmpty(BiTree T);

int BiTreeDepth(BiTree T);

Status Assign(BiTree T, BiTNode *e, ElemType value);

void visit(BiTree T) {
    printf("%d ", T->data);
}

void PreOrder(BiTree T) {
    if (T != NULL) {
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BiTree T) {
    if (T != NULL) {
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}

void PostOrder(BiTree T) {
    if (T != NULL) {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        visit(T);
    }
}


#endif //DATASTRUCTURE_BITREE_H
