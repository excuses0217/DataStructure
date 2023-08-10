#ifndef DATASTRUCTURE_BUBBLESORT_H
#define DATASTRUCTURE_BUBBLESORT_H

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void BubbleSort(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool flag = false; // 表示本趟冒泡是否发生交换的标志
        for (int j = n - 1; j > i; j--)  // 一趟冒泡过程
            if (A[j - 1] > A[j]) {
                swap(A[j - 1], A[j]);
                flag = true;
            }
        if (!flag)
            return;
    }
}

#endif //DATASTRUCTURE_BUBBLESORT_H
