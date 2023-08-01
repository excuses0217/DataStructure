#ifndef DATASTRUCTURE_ADJACENCYLISTGRAPH_H
#define DATASTRUCTURE_ADJACENCYLISTGRAPH_H

#include <stdio.h>
#include <stdlib.h>

// -------------------邻接表法 无向图-------------------

#define MaxVertexNum 100 // 顶点数目的最大值
typedef char VertexType; // 顶点的数据类型
typedef int EdgeType;   // 边上的权值数据类型

// 边表节点
typedef struct ArcNode {
    int adjvex;              // 邻接点在数组中的位置（下标）
    EdgeType weight;         // 边的权值
    struct ArcNode *next;   // 指向下一个邻接点
} ArcNode;

// 顶点表节点
typedef struct VNode {
    VertexType data;        // 顶点的数据
    ArcNode *first;         // 指向第一个邻接点的指针
} VNode, AdjList[MaxVertexNum];

// 邻接表
typedef struct {
    AdjList vertices;       // 顶点数组
    int vexnum, arcnum;     // 图的当前顶点数和弧数
} ALGraph;

// 辅助函数，查找顶点位置
int LocateVex(ALGraph *G, VertexType x) {
    for (int i = 0; i < G->vexnum; i++) {
        if (G->vertices[i].data == x)
            return i;
    }
    return -1; // 顶点在图中不存在
}

// 判断图G是否存在边(x,y)
bool Adjacent(ALGraph *G, VertexType x, VertexType y) {
    int i = LocateVex(G, x);
    if (i == -1) return false;

    ArcNode *p = G->vertices[i].first;
    while (p) {
        if (G->vertices[p->adjvex].data == y)
            return true;
        p = p->next;
    }
    return false;
}

// 列出图G中与结点x邻接的边
void Neighbors(ALGraph *G, VertexType x) {
    int i = LocateVex(G, x);
    if (i == -1) return;

    ArcNode *p = G->vertices[i].first;
    while (p) {
        printf("%c -> %c\n", x, G->vertices[p->adjvex].data);
        p = p->next;
    }
}

// 在图G中插入顶点x
bool InsertVertex(ALGraph *G, VertexType x) {
    if (G->vexnum == MaxVertexNum) return false; // 顶点数组已满

    G->vertices[G->vexnum].data = x;
    G->vertices[G->vexnum].first = NULL;
    G->vexnum++;
    return true;
}

// 在图G中删除顶点x
bool DeleteVertex(ALGraph *G, VertexType x) {
    // 实现这个函数可能比较复杂，因为需要调整数组元素并删除相关的边。
    // 为了简洁，这里没有展示详细的实现。
    return false; // 简化返回
}

// 向图G中添加边
bool AddEdge(ALGraph *G, VertexType x, VertexType y) {
    int i = LocateVex(G, x);
    int j = LocateVex(G, y);
    if (i == -1 || j == -1) return false;

    // 创建新节点并将其插入到邻接表的开头
    ArcNode *newNode = (ArcNode *) malloc(sizeof(ArcNode));
    newNode->adjvex = j;
    newNode->next = G->vertices[i].first;
    G->vertices[i].first = newNode;

    // 如果是无向图，还需要从y到x添加边
    ArcNode *newNode2 = (ArcNode *) malloc(sizeof(ArcNode));
    newNode2->adjvex = i;
    newNode2->next = G->vertices[j].first;
    G->vertices[j].first = newNode2;

    return true;
}

// 从图G中删除边
bool RemoveEdge(ALGraph *G, VertexType x, VertexType y) {
    // 与AddEdge类似，但需要搜索边然后删除。
    // 为了简洁，这里没有展示详细的实现。
    return false; // 简化返回
}

// 求图G中顶点x的第一个邻接点
VertexType FirstNeighbor(ALGraph *G, VertexType x) {
    int i = LocateVex(G, x);
    if (i == -1 || !G->vertices[i].first) return -1;

    return G->vertices[G->vertices[i].first->adjvex].data;
}

// 返回除y外顶点x的下一个邻接点的顶点值
VertexType NextNeighbor(ALGraph *G, VertexType x, VertexType y) {
    int i = LocateVex(G, x);
    if (i == -1) return -1;

    ArcNode *p = G->vertices[i].first;
    while (p && G->vertices[p->adjvex].data != y) {
        p = p->next;
    }

    if (!p || !p->next) return -1;

    return G->vertices[p->next->adjvex].data;
}

// 获取图G中边(x,y)的权值
EdgeType GetEdgeValue(ALGraph *G, VertexType x, VertexType y) {
    int i = LocateVex(G, x);
    if (i == -1) return -1; // 错误值

    ArcNode *p = G->vertices[i].first;
    while (p) {
        if (G->vertices[p->adjvex].data == y)
            return p->weight;
        p = p->next;
    }
    return -1; // 边不存在
}

// 设置图G中边(x,y)的权值
bool SetEdgeValue(ALGraph *G, VertexType x, VertexType y, EdgeType v) {
    int i = LocateVex(G, x);
    if (i == -1) return false;

    ArcNode *p = G->vertices[i].first;
    while (p) {
        if (G->vertices[p->adjvex].data == y) {
            p->weight = v;
            return true;
        }
        p = p->next;
    }
    return false; // 边不存在
}

#endif //DATASTRUCTURE_ADJACENCYLISTGRAPH_H
