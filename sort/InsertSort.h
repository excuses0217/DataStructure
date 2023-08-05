#ifndef DATASTRUCTURE_INSERTSORT_H
#define DATASTRUCTURE_INSERTSORT_H

// 直接插入排序
void InsertSort(int A[], int n) {
    int i, j, temp;
    for (i = 1; i < n; i++) { // 将各元素插入已经排好序的序列中
        if (A[i] < A[i - 1]) { // 若A[i]关键字小于前驱
            temp = A[i]; // 用temp暂存A[i]
            for (j = i - 1; j >= 0 && A[j] > temp; --j) // 检查所有前面已排好序的元素
                A[j + 1] = A[j]; // 所有大于temp的元素都向后挪位
            A[j + 1] = temp; // 复制到插入位置
        }
    }
}

// 直接插入排序（带哨兵）
void Insert_Sort(int A[], int n) {
    int i, j;
    for (i = 2; i <= n; i++) {
        if (A[i] < A[i - 1]) { // 若A[i]关键字小于前驱
            A[0] = A[i]; // 复制为哨兵，A[0]不存放元素
            for (j = i - 1; A[0] < A[j]; --j) // 检查所有前面已排好序的元素
                A[j + 1] = A[j]; // 向后挪位
            A[j + 1] = A[0]; // 复制到插入位置
        }
    }
}

#endif //DATASTRUCTURE_INSERTSORT_H
