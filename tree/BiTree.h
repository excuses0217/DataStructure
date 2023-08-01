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

// 销毁二叉树
Status DestroyBiTree(BiTree &T) {
    // 如果二叉树已经为空，直接返回
    if (T == NULL)
        return OK;
    // 否则，递归销毁左右子树
    if (T->lchild != NULL)
        DestroyBiTree(T->lchild);
    if (T->rchild != NULL)
        DestroyBiTree(T->rchild);
    // 最后释放根节点的内存并将其设置为NULL
    free(T);
    T = NULL;
    return OK;
}

// 清空二叉树
Status ClearBiTree(BiTree &T) {
    // 如果二叉树已经为空，直接返回
    if (T == NULL)
        return OK;
    // 否则，递归清空左右子树
    if (T->lchild != NULL)
        ClearBiTree(T->lchild);
    if (T->rchild != NULL)
        ClearBiTree(T->rchild);
    // 清空根节点的数据并将其左右孩子设置为NULL
    T->data = 0;
    T->lchild = T->rchild = NULL;
    return OK;
}

// 判断二叉树是否为空
bool BiTreeEmpty(BiTree T) {
    // 如果二叉树的根节点为空，则认为二叉树为空
    return T == NULL;
}

// 获取二叉树的深度
int BiTreeDepth(BiTree T) {
    // 如果二叉树为空，其深度为0
    if (T == NULL)
        return 0;
    // 否则，二叉树的深度为左右子树深度的较大值加1
    int lchildDepth = BiTreeDepth(T->lchild);
    int rchildDepth = BiTreeDepth(T->rchild);
    return (lchildDepth > rchildDepth ? lchildDepth : rchildDepth) + 1;
}

// 为二叉树的某个节点赋值
Status Assign(BiTree &T, BiTNode *e, ElemType value) {
    // 如果二叉树为空，返回错误
    if (T == NULL)
        return ERROR;
    // 查找二叉树中与e相等的节点并为其赋值
    if (T == e) {
        T->data = value;
        return OK;
    } else {
        // 在左右子树中递归查找
        if (Assign(T->lchild, e, value) == OK)
            return OK;
        if (Assign(T->rchild, e, value) == OK)
            return OK;
    }
    // 如果没有找到与e相等的节点，返回错误
    return ERROR;
}

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
