#ifndef DATASTRUCTURE_HEAPSORT_H
#define DATASTRUCTURE_HEAPSORT_H

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

//建立大根堆
void BuildMaxHeap(int A[], int len) {
    for (int i = len / 2; i > 0; i--)//从后往前调整所有非终端结点
        HeadAdjust(A, i, len);
}

//将以 k为根的子树调整为大根堆
void HeadAdjust(int A[], int k, int len) {
    A[O] = A[k]; //A[0]暂存子树的根结点
    for (int i = 2 * k; i <= len; i *= 2) { //Key较大的子结点向下筛选
        if (i < len && A[i] < A[i + 1])
            i++; //取key较大的子结点的下标
        if (A[O] >= A[i]) break;//筛选结束
        else {
            A[k] = A[i]; //将A[i]调整到双亲结点上
            k = i; //修改k值，以便继续向下筛选
        }
    }
    A[k] = A[0]; //被筛选结点的值放入最终位置
}

// 堆排序
void HeapSort(int A[],int len){
    BuildMaxHeap(A, len); // 初始建堆
    for (int i=len;i>1;i--){ // n-1趟交换和建堆过程
        swap(A[i], A[1]); // 堆顶元素和堆底元素交换
        HeadAdjust(A, 1, i - 1); // 把剩余的待排序元素整理成堆
    }
}
#endif //DATASTRUCTURE_HEAPSORT_H
