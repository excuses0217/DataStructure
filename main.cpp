#include "linear_list/SequenceList.h"
//#include "linear_list/LinkListWithHead.h"
//#include "stack/LinkStackWithHead.h"
//#include "queue/SequenceQueue.h"

SqList Array2SqList(SqList &L, ElemType data[]) {
    for (int i = 0; data[i] != 0; i++) {
        ListInsert(L, L.length + 1, data[i]);
    }
    return L;
}



int main() {
    system("chcp 65001");

//    InteractiveMenu4StaticSqList();
//    InteractiveMenu4DynamicSqList();

    SqList L1;
    InitSqList(L1);
    ElemType data1[] = {1, 2, 2, 3, 4, 5, 5, 5, 6, 7,0};
    Array2SqList(L1, data1);
    PrintList(L1);

    SqList L2;
    InitSqList(L2);
    ElemType data2[] = {2, 3, 4, 5, 5, 5, 6, 6, 7, 8,0};
    Array2SqList(L2, data2);
//    PrintList(L2);

//    Delete_Same2(L1);
//    SqList L;
//    Merge(L1, L2, L);
//    PrintList(L);

    Revers(L1, 2, 6);
    PrintList(L1);

//    InteractiveMenu4LinkListWithHead();

//    testSharedStack();
//    InteractiveMenu4SqStack();
//    InteractiveMenu4LinkStackWithHead();

//    InteractiveMenu4SqQueue();

    return 0;
}
