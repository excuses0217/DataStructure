#ifndef DATASTRUCTURE_THREADTREE_H
#define DATASTRUCTURE_THREADTREE_H

#include "../GlobalDefine.h"

// -------------------链式二叉树-------------------

typedef struct ThreadNode {
    ElemType data;
    ThreadNode *lchild, *rchild; // 左右孩子指针
    int ltag = 0, rtag = 0;
} ThreadNode, *ThreadTree;

void visit(ThreadNode *p) {
    printf("%d ", p->data);
}

// 中序线索化二叉树
void InThread(ThreadTree &p, ThreadTree &pre) {
    if (p != NULL) {
        InThread(p->lchild, pre); // 递归，线索化左子树
        if (p->lchild == NULL) { // 左子树为空，建立前驱线索
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL) {
            pre->rchild = p; // 建立前驱节点的后继线索
            pre->rtag = 1;
        }
        pre = p; // 标记当前节点成为刚刚访问过的结点
        InThread(p->rchild, pre);
    }
}

// 中序线索化二叉树的第一个节点
ThreadNode *FirstNodeIn(ThreadNode *p) {
    while (p->ltag == 0)
        p = p->lchild; // 最左下结点（不一定是叶子节点）
    return p;
}

// 中序线索化二叉树的后继节点
ThreadNode *NextNodeIn(ThreadNode *p) {
    if (p->rtag == 0)
        return FirstNodeIn(p->rchild);
    else
        return p->rchild; // rtag==1 直接返回后继线索
}

// 中序遍历线索二叉树
void InOrder(ThreadNode *T) {
    for (ThreadNode *p = FirstNodeIn(T); p != NULL; p = NextNodeIn(p))
        visit(p);
}

// 构造前序线索二叉树
void PreThread(ThreadTree &p, ThreadTree &pre) {
    if (p != NULL) {
        if (p->lchild == NULL) {
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL) {
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;
        if (p->ltag == 0)
            PreThread(p->lchild, pre);
        PreThread(p->rchild, pre);
    }
}

// 构造前序线索二叉树的第一个节点
ThreadNode *FirstNodePre(ThreadNode *p) {
    if (p == NULL)
        return NULL;
    while (p->ltag == 0 || p->rtag == 0) {
        if (p->ltag == 0)
            p = p->lchild;
        else
            p = p->rchild;
    }
    return p;
}

// 构造前序线索二叉树的后继节点
ThreadNode *NextNodePre(ThreadNode *p) {
    if (p->rtag == 0)
        return FirstNodePre(p->rchild);
    else
        return p->rchild;
}

// 前序遍历线索二叉树
void PreOrder(ThreadNode *T) {
    for (ThreadNode *p = FirstNodePre(T); p != NULL; p = NextNodePre(p))
        visit(p);
}

// 创建前序线索二叉树
void CreatePreThread(ThreadTree T) {
    ThreadTree pre = NULL;
    if (T != NULL) {
        PreThread(T, pre);
        pre->rchild = NULL;
        pre->rtag = 1;
    }
}

// 构造后序线索二叉树
void PostThread(ThreadTree &p, ThreadTree &pre) {
    if (p != NULL) {
        PostThread(p->lchild, pre);
        PostThread(p->rchild, pre);
        if (p->lchild == NULL) {
            p->lchild = pre;
            p->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL) {
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;
    }
}

// 构造后序线索二叉树的第一个节点
ThreadNode *FirstNodePost(ThreadNode *p) {
    if (p == NULL)
        return NULL;
    while (p->ltag == 0 || p->rtag == 0) {
        if (p->rtag == 0)
            p = p->rchild;
        else
            p = p->lchild;
    }
    return p;
}

// 构造后序线索二叉树的后继节点
ThreadNode *NextNodePost(ThreadNode *p) {
    if (p->ltag == 0)
        return FirstNodePost(p->lchild);
    else
        return p->lchild;
}

// 后序遍历线索二叉树
void PostOrder(ThreadNode *T) {
    for (ThreadNode *p = FirstNodePost(T); p != NULL; p = NextNodePost(p))
        visit(p);
}

// 创建后序线索二叉树
void CreatePostThread(ThreadTree T) {
    ThreadTree pre = NULL;
    if (T != NULL) {
        PostThread(T, pre);
        pre->rchild = NULL;
        pre->rtag = 1;
    }
}

#endif //DATASTRUCTURE_THREADTREE_H
