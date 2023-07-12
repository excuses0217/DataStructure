#ifndef DATASTRUCTURE_LINKSTACKWITHHEAD_H
#define DATASTRUCTURE_LINKSTACKWITHHEAD_H

#include "GlobalDefine.h"

// -------------------带头结点的链栈-------------------

typedef struct LNode {
    ElemType data;
    LNode *next;
} *LinkStack;

/**
 * 初始化带头结点的链栈
 * @param S 链栈头指针
 * @return 初始化成功返回OK，否则返回ERROR
 */
Status InitList(LinkStack &S) {
    S = (LinkStack) malloc(sizeof(LNode));
    if (S == NULL)
        return ERROR;// 初始化失败
    S->next = NULL;
    return OK;
}

/**
 * 销毁链栈，释放内存
 * @param S 链栈头指针
 * @return 销毁成功返回OK，否则返回ERROR
 */
Status DestroyList(LinkStack &S) {
    // 链栈为空，无法销毁
    if (S == NULL)
        return ERROR;
    LNode *p = S, *q;
    while (p != NULL) {
        q = p;
        p = p->next;
        free(q);
    }
    S = NULL;
    return OK;
}

/**
 * 判断栈是否为空
 * @param S 顺序栈对象
 * @return 栈为空则返回true，否则返回false
 */
bool StackEmpty(LinkStack S) {
    if (S->next == NULL)
        return true;
    else
        return false;
}

/**
 * 获取栈长度
 * @param S 顺序栈对象
 * @return 返回栈长度
 */
int StackLength(LinkStack S) {
    int len = 0;
    LNode *p = S;
    while (p->next != NULL) {
        p = p->next;
        len++;
    }
    return len;
}

/**
 * 获取栈顶元素
 * @param S 顺序栈对象
 * @param e 用来存放栈顶元素的变量
 * @return 获取成功返回OK，否则返回ERROR
 */
Status GetTop(LinkStack S, ElemType &e) {
    if (S->next==NULL)
        return ERROR; // 栈空，报错
    e = S->next->data;
    return OK;
}

/**
 * 入栈操作
 * @param S 顺序栈对象
 * @param e 需要入栈的元素
 * @return 入栈成功返回OK，否则返回ERROR
 */
Status Push(LinkStack &S, ElemType e) {
    LNode *p = (LNode *) malloc(sizeof(LNode));
    if(p==NULL)
        return ERROR;// 内存分配失败
    p->data = e;
    p->next = S->next;
    S->next = p;
    return OK;
}

/**
 * 出栈操作
 * @param S 顺序栈对象
 * @param e 用来存放出栈元素的变量
 * @return 出栈成功返回OK，否则返回ERROR
 */
Status Pop(LinkStack &S, ElemType &e) {
    if(StackEmpty(S))
        return ERROR;
    LNode *p = S->next;
    e = p->data;
    S->next = p->next;
    free(p);
    return OK;
}

/**
 * 打印顺序栈中的元素
 * @param S 顺序栈对象
 * 从栈顶到栈底依次打印元素，如果栈为空，打印提示信息
 */
void PrintList(LinkStack S) {
    if (StackEmpty(S)) {
        printf("This Stack is empty!\n");
    } else {
        LNode *p = S->next;
        int count = 1;
        while (p != NULL) {
            printf("[%d]:%d  ", count, p->data);
            p = p->next;
            count++;
        }
        printf("\n");
    }
}

/**
 * 链栈的交互式菜单
 * @return 退出程序返回0
 */
Status InteractiveMenu4LinkStack() {
    LinkStack S;
    InitList(S); // 初始化链栈

    int choice;
    ElemType value;

    printf("-------------测试链栈-------------\n");

    while (1) {
        printf("请输入操作：\n"
               "1：压栈\n"
               "2：出栈\n"
               "3：获取栈长度\n"
               "4：获取栈顶元素\n"
               "5：检查栈是否为空\n"
               "6：打印目前栈内容\n"
               "7：销毁栈(并重新初始化栈)\n"
               "0：退出程序\n");

        CheckScanf(choice);

        switch (choice) {
            case 1:
                system("cls");
                printf("请输入要压栈的值：");
                while (1)if (CheckScanf(value) == 1)break;
                if (Push(S, value) == OK) {
                    system("cls");
                    printf("压栈成功！\n");
                } else {
                    system("cls");
                    printf("压栈失败，栈已满！\n");
                }
                break;
            case 2:
                if (Pop(S, value) == OK) {
                    system("cls");
                    printf("出栈成功！出栈的元素为：%d\n", value);
                } else {
                    system("cls");
                    printf("出栈失败，栈已空！\n");
                }
                break;
            case 3:
                system("cls");
                printf("当前栈长度为%d\n", StackLength(S));
                break;
            case 4:
                if (GetTop(S, value) == OK) {
                    system("cls");
                    printf("获取栈顶元素成功！栈顶元素为：%d\n", value);
                } else {
                    system("cls");
                    printf("获取栈顶元素失败，栈已空！\n");
                }
                break;
            case 5:
                if (StackEmpty(S)) {
                    system("cls");
                    printf("当前栈为空！\n");
                } else {
                    system("cls");
                    printf("当前栈不为空！\n");
                }
                break;
            case 6:
                system("cls");
                printf("当前栈内容如下：\n");
                PrintList(S);
                break;
            case 7:
                if (DestroyList(S) == OK) {
                    system("cls");
                    printf("销毁栈成功！\n");
                    // 重新初始化栈
                    InitList(S);
                } else {
                    system("cls");
                    printf("销毁栈失败！\n");
                }
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

#endif //DATASTRUCTURE_LINKSTACKWITHHEAD_H
