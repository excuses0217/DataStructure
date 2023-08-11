#ifndef DATASTRUCTURE_MERGESORT_H
#define DATASTRUCTURE_MERGESORT_H

#include <stdio.h>
#include <stdlib.h>

int *B = (int *) malloc((n + 1)) * sizeof(int); // 辅助数组B
void Merge(int A[], int low, int mid, int high) {
    int i, j, k;
    for (k = low; k <= high; k++)
        B[k] = A[k]; // 将A中所有元素复制到B中
    for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++) {
        if (B[i] <= B[j]) // 比较B的左右两端中的元素
            A[k] = B[i++]; // 将较小的值复制到A中
        else
            A[k] = B[j++];
    }
    while (i <= mid)A[k++] = B[i++]; // 若第一个表未检测完，复制
    while (i <= high)A[k++] = B[i++]; // 若第二个表未检测完，复制
}

void MergeSort(int A[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2; // 从中间划分两个子序列
        MergeSort(A, low, mid); // 对左侧子序列进行递归排序
        MergeSort(A, mid + 1, high); // 对右侧子序列进行递归排序
        Merge(A, low, mid, high); //归并
    }
}

#endif //DATASTRUCTURE_MERGESORT_H
