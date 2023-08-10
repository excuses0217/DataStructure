#ifndef DATASTRUCTURE_QUICKSORT_H
#define DATASTRUCTURE_QUICKSORT_H

void QuickSort(int A[], int low, int high) {
    if (low < high) {
        int pivotpos = Partition(A, low, high); // 划分
        QuickSort(A, low, pivotpos - 1); // 依次对两个子表进行递归排序
        QuickSort(A, pivotpos + 1, high);
    }
}

int Partition(int A[], int low, int high) { // 一趟划分
    int pivot = A[low]; // 将当前表中第一个元素设为枢轴，对表进行划分
    while (low < high) { // 循环跳出条件
        while (low < high && A[high] >= pivot)--high;
        A[low] = A[high];
        while (low < high && A[low] <= pivot)++low;
        A[high] = A[low];
    }
    A[low] = pivot; // 枢轴元素存放到最终位置
    return low; // 返回存放枢轴的最终位置
}

#endif //DATASTRUCTURE_QUICKSORT_H
