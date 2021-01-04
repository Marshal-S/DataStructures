//
//  MinShortPath.c
//  test
//
//  Created by Marshal on 2020/6/28.
//  Copyright © 2020 Marshal. All rights reserved.
//

#include "MinShortPath.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int preNode; //上一个节点
    int node; //目的节点
    int weight; //路径长度或者权值
} LSLineNode; //临边数组基本结构，只不过先、后用名字，在这里使用更为直白

#define MAXINT 0x0FFFFFFF
#define N 4

//带权邻接矩阵
static int linesList[N][N] = {
    {0, 1, MAXINT, 4},
    {MAXINT, 0, 9, 2},
    {3, 5, 0, 8},
    {MAXINT, MAXINT, 6, 0}
};

//由于无法直接一次打印路径，下面是打印路径的逻辑
//最短路径的获取方式通过查找preNode来查找经过路径，为0时结束,打印出来即可
void printResult(LSLineNode *nodes, int v) {
    printf("\n迪杰斯特拉:\n");
    for (int i = 0; i < N; i++) {
        int result[N] = {nodes[i].node + 1, 0};
        int j = i, k = 1;
        if (i != v) {
            while (nodes[j].preNode != v) {
                result[k++] = nodes[j].preNode + 1;
                j = nodes[j].preNode;
            }
        }
        result[k] = v + 1;
        for (; k >= 0; k--) {
            printf("%d%s", result[k], k == 0 ? " ":"->");
        }
        printf(": %d \n", nodes[i].weight);
    }
}

//迪杰斯特拉算法来解决，找到最短边，在通过最短边更新其他的最短边，依次递推，最短路径点从默认集合N,到最短路径集合S,逐步更新，与prim算法很像
void showSingleMinShortPathByDijkstra(int v) {
    v--; //这里按照索引用，减1来对应
    int m = 0, min = MAXINT;
    int flag[N] = {0};//标志数组，标识顶点是否已经加入进去了
    LSLineNode nodes[N]; //保存结果数组（从指定顶点v到顶点N的路径信息）
    
    //给予结果数组初值，并找出最小的边
    for (int i = 0; i < N; i++) {
        nodes[i].weight = linesList[v][i];
        nodes[i].node = i;
        nodes[i].preNode = v;
        if (nodes[i].weight < min) {
            m = i;
            min = nodes[i].weight;
        }
    }
    
    flag[v] = 1; //默认资源边已经加入
    flag[m] = 1; //将最小的边放入S(flag)集合，置标志位即可
    min = MAXINT; //初始化最大值，用于更新最小值
    for (int i = 0; i < N; i++) {
        int temM = 0; //保存更新的最小是值，用于下一轮更新最短路径，避免m在此次循环被覆盖
        for (int j = 0; j < N; j++) {
            //已经加入S集合的点不做处理
            if (flag[j] != 0) continue;
            //开始加入新的节点进行尝试，是否存在最短路径，然后逐步迭代
            if (nodes[m].weight + linesList[m][j] < nodes[j].weight) {
                nodes[j].preNode = m;
                nodes[j].weight = nodes[m].weight + linesList[m][j];
            }
            if (nodes[j].weight < min) {
                temM = j;
                min = nodes[j].weight;
            }
        }
        m = temM;
        flag[m] = 1;
        min = MAXINT;
    }
    //此时的LSLineNode nodes即为最短路径
    printResult(nodes, v);
}


void printPath(int lines[N][N], int paths[N][N], int start, int end) {
    //那么最短路径的长度则为
    printf("\n弗洛伊德:\n");
    printf("%d->", start + 1);
    int last = start;
    int next = paths[last][end];
    while (next != -1 && next != last) {
        printf("%d-", next + 1);
        last = next;
        next = paths[next][end];
    }
    printf("%d : %d\n", end + 1, lines[start][end]);
    
    printf("生成的path矩阵:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", paths[i][j] + 1);
        }
        printf("\n");
    }
}

//弗洛伊德算法来解决两点间最短路径
void showDoubleMinShortPathByFloyd(int start, int end) {
    start--; end--;
    int paths[N][N]; //用于表示上一个路径的索引，为零则没有优化
    int lines[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            lines[i][j] = linesList[i][j];
            if (i != j && lines[i][j] < MAXINT) {
                paths[i][j] = i; //保存i-j点经过的路径i， 结果则可以表示为i->j
            }else {
                paths[i][j] = -1;
            }

        }
    }
    //通过动态规划来求出每两个点之间的最短路径
    //在每个点中添加一个顶点，查看是否总长小于直接长度，小于则替换，那么替换完成之后则就是最短路径
    for (int k = 0; k < N; k++) {
        //ik表示的是对应顶点坐标，k表示的新加入的索引
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (lines[i][k] + lines[k][j] < lines[i][j]) {
                    lines[i][j] = lines[i][k] + lines[k][j];
                    paths[i][j] = k; //记录优化过的路径(从1开始，-1未优化过)
                }
            }
        }
    }
    
    printPath(lines, paths, start, end);
    
    printf("");
}

