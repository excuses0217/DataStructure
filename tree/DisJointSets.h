#ifndef DATASTRUCTURE_UFSET_H
#define DATASTRUCTURE_UFSET_H

#define SIZE 15
int UFSets[SIZE]; // 集合元素数组

// 初始化并查集
void Initial(int S[]) {
    for (int i = 0; i < SIZE; i++)
        S[i] = -1;
}

// Find"查"操作，找到x所属集合（返回x所属根节点）
int Find(int S[], int x) {
    while (S[x] >= 0) // 循环寻找x的根
        x = S[x];
    return x; // 根的S[]小于0
}

// union”并“操作，将两个集合合并为一个
void Union(int S[], int Root1, int Root2) {
    // 要求Root1与Root2是不同的集合
    if (Root1 == Root2)return;
    if (S[Root2] > S[Root1]) { // Root2节点数更少
        S[Root1] += S[Root2]; // 累加节点总数
        S[Root2] = Root1; // 小树合并到大树
    } else {
        S[Root2] += S[Root1]; // 累加节点总数
        S[Root1] = Root2; // 小树合并到大树
    }
}

#endif //DATASTRUCTURE_UFSET_H
