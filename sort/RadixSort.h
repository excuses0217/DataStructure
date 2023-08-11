#ifndef DATASTRUCTURE_RADIXSORT_H
#define DATASTRUCTURE_RADIXSORT_H

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

// 定义队列结构体
typedef struct Queue {
    int items[MAX];  // 存储队列元素的数组
    int front;       // 队首索引
    int rear;        // 队尾索引
} Queue;

// 创建一个新的队列并初始化
Queue* createQueue() {
    Queue* q = malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

// 检查队列是否为空
int isEmpty(Queue* q) {
    if (q->rear == -1) {
        return 1;
    } else {
        return 0;
    }
}

// 向队列中添加一个元素
void enqueue(Queue* q, int value) {
    if (q->rear == MAX - 1) {
        printf("\nQueue is Full!!");
    } else {
        if (q->front == -1) {
            q->front = 0;
        }
        q->rear += 1;
        q->items[q->rear] = value;
    }
}

// 从队列中取出一个元素
int dequeue(Queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front += 1;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

// 获取数组中的最大值
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// 基数排序算法
void radixSort(int arr[], int n) {
    int max = getMax(arr, n);

    // 创建10个队列，对应0-9的数字
    Queue* buckets[10];
    for (int i = 0; i < 10; i++) {
        buckets[i] = createQueue();
    }

    // 遍历数组的每一个数位
    for (int exp = 1; max / exp > 0; exp *= 10) {
        for (int i = 0; i < n; i++) {
            int digit = (arr[i] / exp) % 10; // 获取当前数位的数字
            enqueue(buckets[digit], arr[i]); // 将元素加入到相应的队列中
        }

        // 从队列中取出元素，回填到数组中
        int idx = 0;
        for (int i = 0; i < 10; i++) {
            while (!isEmpty(buckets[i])) {
                arr[idx++] = dequeue(buckets[i]);
            }
        }
    }

    // 释放动态分配的内存
    for (int i = 0; i < 10; i++) {
        free(buckets[i]);
    }
}


#endif //DATASTRUCTURE_RADIXSORT_H
