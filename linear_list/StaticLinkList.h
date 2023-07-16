#ifndef DATASTRUCTURE_STATICLINKLIST_H
#define DATASTRUCTURE_STATICLINKLIST_H

#include "../GlobalDefine.h"

// -------------------静态链表-------------------

typedef struct {
    ElemType data;
    int next;
} SLinkList[MAXSIZE];

#endif //DATASTRUCTURE_STATICLINKLIST_H
