//#include "linear_list/SequenceList.h"
//#include "linear_list/LinkListWithHead.h"
//#include "stack/LinkStackWithHead.h"
//#include "queue/SequenceQueue.h"
//#include "queue/LinkQueueWithHead.h"
//#include "stack/InfixToPostfix.h"
//#include "string/SString.h"
#include "sort/RadixSort.h"

int main() {
    system("chcp 65001");

//    InteractiveMenu4StaticSqList();
//    InteractiveMenu4DynamicSqList();
//    InteractiveMenu4LinkListWithHead();

//    InteractiveMenu4SqStack();
//    InteractiveMenu4LinkStackWithHead();

//    InteractiveMenu4SqQueue();
//    InteractiveMenu4LinkQueue();

//    InfixToPostfixMain();
//    text();


    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    radixSort(arr, n);

    printf("Sorted array: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
