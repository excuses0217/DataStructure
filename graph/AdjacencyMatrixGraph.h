#ifndef DATASTRUCTURE_ADJACENCYMATRIXGRAPH_H
#define DATASTRUCTURE_ADJACENCYMATRIXGRAPH_H

#include <stdio.h>
#include <stdlib.h>

// -------------------邻接矩阵法-------------------

#define MaxVertexNum 100 // 顶点数目的最大值
#define INFINITY 65535
typedef char VertexType; // 顶点的数据类型
typedef int EdgeType; // 带权图中边上权值的数据类型
typedef struct {
    VertexType Vex[MaxVertexNum]; // 顶点表
    EdgeType Edge[MaxVertexNum][MaxVertexNum]; // 邻接矩阵，边表
    int vexnum, arcnum; // 图的当前顶点数和弧数
} MGraph;

// 辅助函数：返回顶点x在数组中的位置
// 如果顶点x在图G中存在，则返回其在数组中的索引位置
// 如果顶点x在图G中不存在，则返回-1
int LocateVex(MGraph *G, VertexType x) {
    for (int i = 0; i < G->vexnum; i++) {
        if (G->Vex[i] == x)
            return i;
    }
    return -1;
}

// 判断图G是否存在边(x,y)
// 先找到顶点x和y在数组中的位置i和j，如果i或j为-1，说明顶点不存在，返回false
// 如果边(i,j)的权值不等于无穷，说明边存在，返回true
// 否则，返回false
bool Adjacent(MGraph *G, VertexType x, VertexType y) {
    int i = LocateVex(G, x);
    int j = LocateVex(G, y);
    if (i == -1 || j == -1) return false;
    return G->Edge[i][j] != INFINITY;
}

// 列出图G中与结点x邻接的边
// 先找到顶点x在数组中的位置i，如果i为-1，说明顶点不存在，函数结束
// 否则，遍历与顶点i相连的所有边，如果边的权值不等于无穷，说明边存在，打印边的信息
void Neighbors(MGraph *G, VertexType x) {
    int i = LocateVex(G, x);
    if (i == -1) return;

    for (int j = 0; j < G->vexnum; j++) {
        if (G->Edge[i][j] != INFINITY) {
            printf("Edge(%c,%c)\n", x, G->Vex[j]);
        }
    }
}

// 在图G中插入顶点x
// 如果图的顶点数已经达到最大值，返回false
// 否则，将顶点x添加到数组的末尾，并将与新顶点x相连的所有边的权值设置为无穷，表示没有边
// 最后，顶点数加1，返回true
bool InsertVertex(MGraph *G, VertexType x) {
    if (G->vexnum == MaxVertexNum) return false;
    G->Vex[G->vexnum] = x;
    for (int i = 0; i <= G->vexnum; i++) {
        G->Edge[G->vexnum][i] = INFINITY;
        G->Edge[i][G->vexnum] = INFINITY;
    }
    G->vexnum++;
    return true;
}

// 在图G中删除顶点x
// 先找到顶点x在数组中的位置i，如果i为-1，说明顶点不存在，返回false
// 否则，将顶点i之后的所有顶点前移一位，覆盖顶点i
// 然后，将顶点i的所有邻接边也前移一位，覆盖原来的边
// 最后，顶点数减1，返回true
bool DeleteVertex(MGraph *G, VertexType x) {
    int i = LocateVex(G, x);
    if (i == -1) return false;

    for (int j = i; j < G->vexnum - 1; j++) {
        G->Vex[j] = G->Vex[j + 1];
    }

    for (int j = 0; j < G->vexnum; j++) {
        for (int k = i; k < G->vexnum - 1; k++) {
            G->Edge[j][k] = G->Edge[j][k + 1];
        }
    }

    G->vexnum--;
    return true;
}

// 向图G中添加边(x,y)
// 先找到顶点x和y在数组中的位置i和j，如果i或j为-1，说明顶点不存在，返回false
// 如果边(i,j)的权值不等于无穷，说明边已经存在，返回false
// 否则，将边(i,j)的权值设置为weight，弧数加1，返回true
bool AddEdge(MGraph *G, VertexType x, VertexType y, EdgeType weight) {
    int i = LocateVex(G, x);
    int j = LocateVex(G, y);
    if (i == -1 || j == -1 || G->Edge[i][j] != INFINITY) return false;
    G->Edge[i][j] = weight;
    G->arcnum++;
    return true;
}

// 从图G中删除边(x,y)
// 先找到顶点x和y在数组中的位置i和j，如果i或j为-1，说明顶点不存在，返回false
// 如果边(i,j)的权值等于无穷，说明边不存在，返回false
// 否则，将边(i,j)的权值设置为无穷，弧数减1，返回true
bool RemoveEdge(MGraph *G, VertexType x, VertexType y) {
    int i = LocateVex(G, x);
    int j = LocateVex(G, y);
    if (i == -1 || j == -1 || G->Edge[i][j] == INFINITY) return false;
    G->Edge[i][j] = INFINITY;
    G->arcnum--;
    return true;
}

// 求图G中顶点x的第一个邻接点
// 先找到顶点x在数组中的位置i，如果i为-1，说明顶点不存在，返回-1
// 否则，从第一个顶点开始，找到第一个与顶点i相连的顶点j，返回j的顶点值
// 如果没有找到，说明顶点i没有邻接点，返回-1
VertexType FirstNeighbor(MGraph *G, VertexType x) {
    int i = LocateVex(G, x);
    if (i == -1) return -1;

    for (int j = 0; j < G->vexnum; j++) {
        if (G->Edge[i][j] != INFINITY) {
            return G->Vex[j];
        }
    }

    return -1;
}

// 假设图G中顶点y是顶点x的一个邻接点，返回除y外顶点x的下一个邻接点的顶点值
// 先找到顶点x和y在数组中的位置i和j，如果i或j为-1，说明顶点不存在，返回-1
// 从顶点j+1开始，找到第一个与顶点i相连的顶点k，返回k的顶点值
// 如果没有找到，说明顶点y是顶点x的最后一个邻接点，返回-1
VertexType NextNeighbor(MGraph *G, VertexType x, VertexType y) {
    int i = LocateVex(G, x);
    int j = LocateVex(G, y);
    if (i == -1 || j == -1) return -1;

    for (int k = j + 1; k < G->vexnum; k++) {
        if (G->Edge[i][k] != INFINITY) {
            return G->Vex[k];
        }
    }

    return -1;
}

// 获取图G中边(x,y)的权值
// 先找到顶点x和y在数组中的位置i和j，如果i或j为-1，说明顶点不存在，返回无穷
// 否则，返回边(i,j)的权值
EdgeType GetEdgeValue(MGraph *G, VertexType x, VertexType y) {
    int i = LocateVex(G, x);
    int j = LocateVex(G, y);
    if (i == -1 || j == -1) return INFINITY;

    return G->Edge[i][j];
}

// 设置图G中边(x,y)的权值为v
// 先找到顶点x和y在数组中的位置i和j，如果i或j为-1，说明顶点不存在，返回false
// 否则，将边(i,j)的权值设置为v，返回true
bool SetEdgeValue(MGraph *G, VertexType x, VertexType y, EdgeType v) {
    int i = LocateVex(G, x);
    int j = LocateVex(G, y);
    if (i == -1 || j == -1) return false;

    G->Edge[i][j] = v;
    return true;
}

#endif //DATASTRUCTURE_ADJACENCYMATRIXGRAPH_H
