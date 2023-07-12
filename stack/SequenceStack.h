#ifndef DATASTRUCTURE_SEQUENCESTACK_H
#define DATASTRUCTURE_SEQUENCESTACK_H

#include "../GlobalDefine.h"

// -------------------顺序栈-------------------

typedef struct {
    ElemType data[MAXSIZE];
    int top;
} SqStack;

/**
 * 初始化顺序栈
 * @param S 顺序栈对象
 * @return 初始化成功返回OK，否则返回ERROR
 */
Status InitSqStack(SqStack &S) {
    S.top = -1;
    return OK;
}

/**
 * 判断栈是否为空
 * @param S 顺序栈对象
 * @return 栈为空则返回true，否则返回false
 */
bool StackEmpty(SqStack S) {
    if (S.top == -1)
        return true;
    else
        return false;
}

/**
 * 获取栈顶元素
 * @param S 顺序栈对象
 * @param e 用来存放栈顶元素的变量
 * @return 获取成功返回OK，否则返回ERROR
 */
Status GetTop(SqStack S, ElemType &e) {
    if (S.top == -1)
        return ERROR;// 栈空
    e = S.data[S.top];
    return OK;
}

/**
 * 入栈操作
 * @param S 顺序栈对象
 * @param e 需要入栈的元素
 * @return 入栈成功返回OK，否则返回ERROR
 */
Status Push(SqStack &S, ElemType e) {
    if (S.top == MAXSIZE - 1)
        return ERROR;// 栈满
    S.data[++S.top] = e;
    return OK;
}

/**
 * 出栈操作
 * @param S 顺序栈对象
 * @param e 用来存放出栈元素的变量
 * @return 出栈成功返回OK，否则返回ERROR
 */
Status Pop(SqStack &S, ElemType &e) {
    if (S.top == -1)
        return ERROR;// 栈空
    e = S.data[S.top--];
    return OK;
}

/**
 * 打印顺序栈中的元素
 * @param S 顺序栈对象
 * 从栈顶到栈底依次打印元素，如果栈为空，打印提示信息
 */
void PrintList(SqStack S) {
    if (S.top == -1) {
        printf("This Stack is empty!\n");
    } else {
        for (int i = S.top; i >= 0; i--)
            printf("%d  ", S.data[i]);
        printf("\n");
    }
}

/**
 * 顺序栈的交互式菜单
 * @return 退出程序返回0
 */
Status InteractiveMenu4SqStack() {
    SqStack S;
    InitSqStack(S); // 初始化顺序栈

    int choice;
    ElemType value;

    printf("-------------测试顺序栈-------------\n");

    while (1) {
        printf("请输入操作：\n"
               "1：压栈\n"
               "2：出栈\n"
               "3：获取栈顶元素\n"
               "4：检查栈是否为空\n"
               "5：打印目前栈内容\n"
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
                if (GetTop(S, value) == OK) {
                    system("cls");
                    printf("获取栈顶元素成功！栈顶元素为：%d\n", value);
                } else {
                    system("cls");
                    printf("获取栈顶元素失败，栈已空！\n");
                }
                break;
            case 4:
                if (StackEmpty(S)) {
                    system("cls");
                    printf("当前栈为空！\n");
                } else {
                    system("cls");
                    printf("当前栈不为空！\n");
                }
                break;
            case 5:
                system("cls");
                printf("当前栈内容如下：\n");
                PrintList(S);
                break;
            case 0:
                system("cls");
                printf("程序已退出！\n");
                return 0;
            default:
                system("cls");
                printf("无效的操作！\n");
                break;
        }
    }
}

#endif //DATASTRUCTURE_SEQUENCESTACK_H
