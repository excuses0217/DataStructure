#ifndef DATASTRUCTURE_SHARESTACK_H
#define DATASTRUCTURE_SHARESTACK_H

#include "../GlobalDefine.h"

// -------------------共享栈-------------------

// 定义一个共享栈结构体
typedef struct {
    ElemType data[MAXSIZE];  // 堆栈的主体，用于存放元素
    int top0;  // 栈0的栈顶指针
    int top1;  // 栈1的栈顶指针
} ShStack;

/**
 * 初始化共享栈
 * @param S 共享栈对象
 * @return 初始化成功返回OK，否则返回ERROR
 */
Status InitSqStack(ShStack &S) {
    S.top0 = -1;
    S.top1 = MAXSIZE;
    return OK;
}

/**
 * 判断共享栈是否为空
 * @param S 共享栈对象
 * @return 如果两个栈都为空则返回true，否则返回false
 */
bool StackEmpty(ShStack S) {
    if (S.top0 == -1 && S.top1 == MAXSIZE)
        return true;
    else
        return false;
}

/**
 * 获取栈0的栈顶元素
 * @param S 共享栈对象
 * @param e 用于存储栈顶元素的变量
 * @return 如果栈为空返回ERROR，否则返回OK
 */
Status GetTop0(ShStack &S, ElemType &e) {
    if (S.top0 == -1)
        return ERROR;// 栈0为空
    e = S.data[S.top0];
    return OK;
}

/**
 * 获取栈1的栈顶元素
 * @param S 共享栈对象
 * @param e 用于存储栈顶元素的变量
 * @return 如果栈为空返回ERROR，否则返回OK
 */
Status GetTop1(ShStack &S, ElemType &e) {
    if (S.top1 == MAXSIZE)
        return ERROR;// 栈1为空
    e = S.data[S.top1];
    return OK;
}

/**
 * 将元素e压入栈0
 * @param S 共享栈对象
 * @param e 需要压入的元素
 * @return 如果栈满返回ERROR，否则返回OK
 */
Status Push0(ShStack &S, ElemType e) {
    if (S.top0 + 1 == S.top1)
        return ERROR;// 栈满
    S.data[++S.top0] = e;
    return OK;
}

/**
 * 将元素e压入栈1
 * @param S 共享栈对象
 * @param e 需要压入的元素
 * @return 如果栈满返回ERROR，否则返回OK
 */
Status Push1(ShStack &S, ElemType e) {
    if (S.top0 + 1 == S.top1)
        return ERROR;// 栈满
    S.data[--S.top1] = e;
    return OK;
}

/**
 * 弹出栈0的栈顶元素
 * @param S 共享栈对象
 * @param e 用于存储被弹出元素的变量
 * @return 如果栈为空返回ERROR，否则返回OK
 */
Status Pop0(ShStack &S, ElemType &e) {
    if (S.top0 == -1)
        return ERROR;// 栈0为空
    e = S.data[S.top0--];
    return OK;
}

/**
 * 弹出栈1的栈顶元素
 * @param S 共享栈对象
 * @param e 用于存储被弹出元素的变量
 * @return 如果栈为空返回ERROR，否则返回OK
 */
Status Pop1(ShStack &S, ElemType &e) {
    if (S.top1 == MAXSIZE)
        return ERROR;// 栈1为空
    e = S.data[S.top1++];
    return OK;
}

/**
 * 共享栈的测试函数
 * 为了测试上面定义的所有共享栈操作，包括初始化、入栈、出栈、获取栈顶元素和判断栈是否为空
 */
void testSharedStack() {
    ShStack S;
    ElemType e;

    // 初始化共享栈
    printf("初始化共享栈...\n");
    if (InitSqStack(S) == OK)
        printf("初始化成功！\n");
    else
        printf("初始化失败！\n");

    // 判断初始化后的共享栈是否为空
    printf("判断栈是否为空...\n");
    if (StackEmpty(S))
        printf("栈为空！\n");
    else
        printf("栈不为空！\n");

    // 入栈操作测试
    printf("入栈操作...\n");
    if (Push0(S, 1) == OK) // 栈0入栈
        printf("元素1成功入栈0！\n");
    else
        printf("元素1入栈0失败！\n");

    if (Push1(S, 2) == OK) // 栈1入栈
        printf("元素2成功入栈1！\n");
    else
        printf("元素2入栈1失败！\n");

    // 获取栈顶元素测试
    printf("获取栈顶元素...\n");
    if (GetTop0(S, e) == OK)
        printf("栈0的栈顶元素是：%d\n", e);
    else
        printf("获取栈0的栈顶元素失败！\n");

    if (GetTop1(S, e) == OK)
        printf("栈1的栈顶元素是：%d\n", e);
    else
        printf("获取栈1的栈顶元素失败！\n");

    // 出栈操作测试
    printf("出栈操作...\n");
    if (Pop0(S, e) == OK)
        printf("栈0的栈顶元素%d出栈成功！\n", e);
    else
        printf("栈0出栈失败！\n");

    if (Pop1(S, e) == OK)
        printf("栈1的栈顶元素%d出栈成功！\n", e);
    else
        printf("栈1出栈失败！\n");
}

#endif //DATASTRUCTURE_SHARESTACK_H
