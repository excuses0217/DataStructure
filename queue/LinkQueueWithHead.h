#ifndef DATASTRUCTURE_LINKQUEUEWITHHEAD_H
#define DATASTRUCTURE_LINKQUEUEWITHHEAD_H

#include "../GlobalDefine.h"

// -------------------带头结点的链式队列-------------------

typedef struct LinkNode {
    ElemType data;
    LinkNode *next;
} LinkNode;

typedef struct {
    LinkNode *front, *rear;
} LinkQueue;

/**
 * 初始化队列
 * @param Q 要初始化的队列
 * @return 初始化成功返回OK，否则返回ERROR
 */
Status InitQueue(LinkQueue &Q) {
    Q.front = Q.rear = (LinkNode *) malloc(sizeof(LinkNode));
    if (Q.front == NULL || Q.rear == NULL)
        return ERROR;// 初始化失败
    Q.front->next = NULL;
    return OK;
}

/**
 * 判断队列是否为空
 * @param Q 要判断的队列
 * @return 如果队列为空返回true，否则返回false
 */
bool QueueEmpty(LinkQueue Q) {
    return Q.rear == Q.front;
}

/**
 * 获取队列的头部元素
 * @param Q 要获取头部元素的队列
 * @param e 用于存放获取到的头部元素的变量
 * @return 如果队列为空返回ERROR，否则返回OK
 */
Status GetHead(LinkQueue Q, ElemType &e) {
    if (QueueEmpty(Q))
        return ERROR;// 队列为空
    e = Q.front->next->data;
    return OK;
}

/**
 * 获取队列的长度
 * @param Q 要获取长度的队列
 * @return 返回队列的长度
 */
int QueueLength(LinkQueue Q) {
    int len = 0;
    LinkNode *p = Q.front;
    while (p != Q.rear) {
        p = p->next;
        len++;
    }
    return len;
}

/**
 * 向队列中插入一个元素
 * @param Q 要插入元素的队列
 * @param e 要插入的元素
 * @return 如果队列已满返回ERROR，否则返回OK
 */
Status EnQueue(LinkQueue &Q, ElemType e) {
    LinkNode *s = (LinkNode *) malloc(sizeof(LinkNode));
    s->data = e;
    s->next = NULL;
    Q.rear->next = s;
    Q.rear = s;
    return OK;
}

/**
 * 从队列中取出一个元素
 * @param Q 要取出元素的队列
 * @param e 用于存放取出的元素的变量
 * @return 如果队列为空返回ERROR，否则返回OK
 */
Status DeQueue(LinkQueue &Q, ElemType &e) {
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

/**
 * 打印队列内容
 * @param Q 要打印的队列
 */
void PrintQueue(LinkQueue Q) {
    if (QueueEmpty(Q)) {
        printf("队列为空！\n");
        return;
    }

    printf("队列内容如下：\n");
    LinkNode *p = Q.front->next;
    int i = 1;
    while (p != Q.rear) {
        printf("[%d]:%d ", i, p->data);
        p = p->next;
        i++;
    }
    printf("\n");
}

/**
 * 链式队列的交互式菜单
 * @return 退出程序返回0
 */
Status InteractiveMenu4LinkQueue() {
    LinkQueue Q;
    InitQueue(Q); // 初始化队列

    int choice;
    ElemType value;

    printf("-------------测试链式队列-------------\n");

    while (true) {
        printf("请输入操作：\n"
               "1：插入元素（入队）\n"
               "2：删除元素（出队）\n"
               "3：获取头部元素\n"
               "4：获取队列长度\n"
               "5：判断队列是否为空\n"
               "6：打印队列内容\n"
               "0：退出程序\n");

//        scanf("%d", &choice);
        CheckScanf(choice);

        switch (choice) {
            case 1:
                system("cls");
                printf("请输入要插入的元素：");
//                scanf("%d", &value);
                while (true)if (CheckScanf(value) == 1)break;
                if (EnQueue(Q, value) == OK) {
                    system("cls");
                    printf("元素插入成功！\n");
                } else {
                    system("cls");
                    printf("队列已满，元素插入失败！\n");
                }
                break;
            case 2:
                if (DeQueue(Q, value) == OK) {
                    system("cls");
                    printf("删除成功！删除的元素为：%d\n", value);
                } else {
                    system("cls");
                    printf("队列为空，删除失败！\n");
                }
                break;
            case 3:
                if (GetHead(Q, value) == OK) {
                    system("cls");
                    printf("头部元素为：%d\n", value);
                } else {
                    system("cls");
                    printf("队列为空！\n");
                }
                break;
            case 4:
                system("cls");
                printf("队列的长度为：%d\n", QueueLength(Q));
                break;
            case 5:
                if (QueueEmpty(Q)) {
                    system("cls");
                    printf("队列为空！\n");
                } else {
                    system("cls");
                    printf("队列不为空！\n");
                }
                break;
            case 6:
                system("cls");
                PrintQueue(Q);
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

#endif //DATASTRUCTURE_LINKQUEUEWITHHEAD_H
