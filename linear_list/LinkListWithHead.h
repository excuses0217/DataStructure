#ifndef DATASTRUCTURE_LINKLISTWITHHEAD_H
#define DATASTRUCTURE_LINKLISTWITHHEAD_H

#include "GlobalDefine.h"

// -------------------带头结点的单链表-------------------

typedef struct LNode {
    ElemType data;
    LNode *next;
} LNode, *LinkList;

/**
 * 初始化带头结点的单链表
 * @param L 单链表头指针
 * @return 初始化成功返回OK，否则返回ERROR
 */
Status InitList(LinkList &L) {
    L = (LinkList) malloc(sizeof(LNode));
    if (L == NULL)
        return ERROR;
    L->next = NULL;
    return OK;
}

/**
 * 销毁链表，释放内存
 * @param L 单链表头指针
 * @return 销毁成功返回OK，否则返回ERROR
 */
Status DestroyList(LinkList &L) {
    // 链表为空，无法销毁
    if (L == NULL)
        return ERROR;
    LNode *p = L, *q;
    while (p != NULL) {
        q = p;
        p = p->next;
        free(q);
    }
    L = NULL;
    return OK;
}

/**
 * 求带头结点的单链表长度
 * @param L 单链表头指针
 * @return 单链表长度
 */
int Length(LinkList L) {
    int len = 0;
    LNode *p = L;
    while (p->next != NULL) {
        p = p->next;
        len++;
    }
    return len;
}

/**
 * 获取指定位置的结点
 * @param L 单链表头指针
 * @param i 指定位置
 * @return 指定位置的结点指针，如果位置非法则返回NULL
 */
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
    int j = 0;// 当前 p 指向第 j 个结点
    while (p != NULL && j < i) {
        p = p->next;
        j++;
    }
    return p;
}

/**
 * 按值查找结点
 * @param L 单链表头指针
 * @param e 待查找的元素值
 * @return 找到数据域等于e的结点指针，如果找不到则返回NULL
 */
LNode *LocateNode(LinkList L, ElemType e) {
    LNode *p = L->next;
    // 从第1个结点开始查找数据域为e的结点
    while (p != NULL && p->data != e)
        p = p->next;
    return p;
}

/**
 * 在指定结点之前插入元素
 * @param p 指定结点的指针
 * @param e 待插入的元素值
 * @return 插入成功返回OK，否则返回ERROR
 */
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

/**
 * 在指定结点之前插入结点
 * @param p 指定结点的指针
 * @param s 待插入的结点指针
 * @return 插入成功返回OK，否则返回ERROR
 */
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

/**
 * 在指定结点之后插入元素
 * @param p 指定结点的指针
 * @param e 待插入的元素值
 * @return 插入成功返回OK，否则返回ERROR
 */
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

/**
 * 在指定结点之后插入结点
 * @param p 指定结点的指针
 * @param s 待插入的结点指针
 * @return 插入成功返回OK，否则返回ERROR
 */
Status InsertNextNode(LNode *p, LNode *s) {
    if (p == NULL || s == NULL)
        return ERROR;
    s->next = p->next;
    p->next = s;
    return OK;
}

/**
 * 删除指定位置结点
 * @param L 单链表头指针
 * @param i 指定位置
 * @param e 用于返回被删除的元素值
 * @return 删除成功返回OK，否则返回ERROR
 */
Status ListDelete(LinkList &L, int i, ElemType &e) {
    if (i < 1)
        return ERROR;
    LNode *p = GetElem(L, i - 1);
    if (p == NULL || p->next == NULL)
        return ERROR;// i 值不合法或者找不到要删除的结点（没有第 i 个结点）
    LNode *q = p->next;
    e = q->data;
    p->next = q->next;
    free(q);
    return OK;
}

/**
 * 使用交换值的方法，删除指定结点（不能删除最后一个结点）
 * @param p 指定结点的指针
 * @return 删除成功返回OK，否则返回ERROR
 */
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

/**
 * 在指定位置插入元素
 * @param L 单链表头指针
 * @param i 指定位置
 * @param e 待插入的元素值
 * @return 插入成功返回OK，否则返回ERROR
 */
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

/**
 * 尾插法建立带头结点的单链表
 * @param L 单链表头指针
 * @return 建立的单链表头指针
 */
LinkList List_TailInsert(LinkList &L) {
    int x;
    LNode *s, *r = L;   // r 是表尾指针
    while (1) {
        printf("请输入要插入的值：");
//        scanf("%d", &x);
        while (1)if (CheckScanf(x) == 1)break;
        if (x == 0)break;             // 输入-1表示结束输入
        s = (LNode *) malloc(sizeof(LNode));
        s->data = x;
        r->next = s;
        r = s;
    }
    r->next = NULL;
    return L;
}

/**
 * 头插法建立带头结点的单链表
 * @param L 单链表头指针
 * @return 建立的单链表头指针
 */
LinkList List_HeadInsert(LinkList &L) {
    int x;
    LNode *s;
    while (1) {
        printf("请输入要插入的元素（输入0表示结束）：\n");
//        scanf("%d", &x);
        while (1)if (CheckScanf(x) == 1)break;
        if (x == 0)break;             // 输入0表示结束输入
        s = (LNode *) malloc(sizeof(LNode));
        s->data = x;
        s->next = L->next;
        L->next = s;
    }
    return L;
}

/**
 * 打印带头结点的单链表
 * @param L 单链表头指针
 */
void PrintList(LinkList L) {
    if (L->next == NULL)
        printf("This LinkList is empty!\n");
    else {
        LNode *p = L->next;
        int count = 1;
        while (p != NULL) {
            printf("[%d]:%d  ", count, p->data);
            p = p->next;
            count++;
        }
        printf("\n");
    }
}

Status InteractiveMenu4LinkListWithHead() {
    LinkList L;
    InitList(L); // 初始化单链表

    LNode *lNode;
    int choice;
    ElemType value;
    int position;

    printf("-------------测试带头结点的单链表-------------\n");

    while (1) {
        printf("请输入操作：\n"
               "1：尾插法建立单链表\n"
               "2：头尾插法建立单链表\n"
               "3：在指定位置插入结点\n"
               "4：删除指定位置结点\n"
               "5：按位查找\n"
               "6：按值查找\n"
               "7：打印目前单链表\n"
               "8：获取当前单链表长度\n"
               "0：退出程序\n");

//        scanf("%d", &choice);
        CheckScanf(choice);

        switch (choice) {
            case 1:
                system("cls");
                List_TailInsert(L);
                system("cls");
                break;
            case 2:
                system("cls");
                List_HeadInsert(L);
                system("cls");
                break;
            case 3:
                system("cls");
                printf("请输入要插入的值：");
//                scanf("%d", &value);
                while (1)if (CheckScanf(value) == 1)break;
                printf("请输入要插入的位置：");
//                scanf("%d", &position);
                while (1)if (CheckScanf(position) == 1)break;
                if (ListInsert(L, position, value) == OK) {
                    system("cls");
                    printf("插入成功！\n");
                } else {
                    system("cls");
                    printf("插入失败！\n");
                }
                break;
            case 4:
                system("cls");
                printf("请输入要删除元素的位置：");
//                scanf("%d", &position);
                while (1)if (CheckScanf(position) == 1)break;
                DeleteNode(GetElem(L, position));
                system("cls");
                break;
            case 5:
                system("cls");
                printf("请输入要查找的位置：");
//                scanf("%d", &position);
                while (1)if (CheckScanf(position) == 1)break;
                if (position < 1 || position > Length(L)) {
                    system("cls");
                    printf("位置不合法！\n");
                } else {
                    lNode = GetElem(L, position);
                    system("cls");
                    printf("位置 %d 的元素为：%d\n", position, lNode->data);
                }
                break;
            case 6:
                system("cls");
                if (L->next == NULL) {
                    printf("当前顺序表为空！\n");
                } else {
                    printf("请输入要查找的值：");
//                    scanf("%d", &value);
                    while (1)if (CheckScanf(value) == 1)break;

                    position = 0;
                    lNode = L->next;
                    // 从第1个结点开始查找数据域为e的结点
                    while (lNode != NULL && lNode->data != value) {
                        lNode = lNode->next;
                        position++;
                    }
                    if (position == 0) {
                        system("cls");
                        printf("未找到元素 %d！\n", value);
                    } else {
                        system("cls");
                        printf("元素 %d 的位置为：%d\n", value, position);
                    }
                }
                break;
            case 7:
                system("cls");
                printf("当前单链表内容如下：\n");
                PrintList(L);
                break;
            case 8:
                system("cls");
                printf("当前单链表长度为：");
                printf("%d\n", Length(L));
                break;
            case 0:
                printf("程序已退出！\n");
                return 0;
            default:
                system("cls");
                printf("无效的操作！\n");
                break;
        }
    }
}

#endif //DATASTRUCTURE_LINKLISTWITHHEAD_H

#pragma clang diagnostic pop