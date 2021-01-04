//
//  MiniGenerateTree.c
//  test
//
//  Created by Marshal on 2020/5/21.
//  Copyright © 2020 Marshal. All rights reserved.
//

#include "MiniGenerateTree.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXINT 0x0FFFFFFF
#define N 6
//边集数组内容基本结构
typedef struct {
    int fromvex;
    int tovex;
    int weight;
} LSLinesNode;

//初始化一个邻接矩阵，用于保存节点位置
static int linesList[N][N] = {
    {0 , 6, MAXINT, MAXINT, 11, 14},
    {6 , 0, 21, MAXINT, MAXINT, 8},
    {MAXINT, 21, 0, 15, MAXINT, 18},
    {MAXINT, MAXINT, 15, 0, 12, MAXINT},
    {11, MAXINT, MAXINT, 12, 0, 16},
    {14, 8, 18, MAXINT, 16, 0},
};

//普里姆算法(默认系统使用临边矩阵保存的)
void generateMinTreeByPrim() {
    printf("prim算法：加点法\n");
    
    //默认给予某一个节点到其他顶点连接为最小生成树, 通过不停更新新顶点，来生成最小生成树
    int n = N - 1;
    LSLinesNode nodes[n];
    
    //将第一个点相关的所有边都放入边集数组
    for (int i = 0; i < n - 1; i++) {
        nodes[i].fromvex = 0;
        nodes[i].tovex = i + 1;
        nodes[i].weight = linesList[0][i + 1];
    }
    
    for (int i = 0; i < n; i++) {
        //找出最小的边安排到最前面
        int minIndex = i;
        int j = i + 1;
        for (; j < N; j++) {
            if (nodes[j].weight < nodes[minIndex].weight) {
                minIndex = j;
            }
        }
        //最小的边筛选出来，换到前面去，像排序一样
        if (minIndex != i) {
            LSLinesNode node = nodes[minIndex];
            nodes[minIndex] = nodes[i];
            nodes[i] = node;
        }
        
        //终点均为剩下的顶点，所以只需要当前节点与终点的边的权值与剩余对应的边权值比较，较小的替换进边集数组即可保证内部均为最小边
        for (j = i + 1; j < N; j++) {
            //默认临边矩阵
            int weight = linesList[nodes[i].tovex][nodes[j].tovex];
            if (weight < nodes[j].weight) {
                nodes[j].fromvex = nodes[i].tovex; //由于终点节点一致，只需要替换权值和初始节点即可
                nodes[j].weight = weight;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        nodes[i].fromvex++;
        nodes[i].tovex++;
        printf("fromvex:%d -- tovex:%d\n", nodes[i].fromvex, nodes[i].tovex);
    }
    printf("\n");
}


//传入邻接数组,返回有权边数
int getLinesCount(int linesList[N][N]) {
    int lines = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (linesList[i][j] > 0 && linesList[i][j] < MAXINT) {
                lines++;
            }
        }
    }
    return lines;
}

void getAllLineNodes(LSLinesNode *nodes, int *count) {
    *count = getLinesCount(linesList);
    
    //生成有值的边集数组
    int index = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (linesList[i][j] > 0 && linesList[i][j] < MAXINT) {
                nodes[index].fromvex = i;
                nodes[index].tovex = j;
                nodes[index].weight = linesList[i][j];
                index++;
            }
        }
    }
}

//克鲁斯卡尔算法,仍然用边集数组解决
void generateMinTreeByKruskal() {
    printf("kruskal算法：加边法\n");
    
    int count = 0;
    LSLinesNode nodes[count];
    
    getAllLineNodes(nodes, &count); //生成所有边的边集数组
    
    //先升序排序，然后从最小的一个个挑出n-1个没有闭环的最小生成树
    for (int i = 0; i < count; i++) {
        for (int j = i; j < count; j++) {
            if (nodes[i].weight > nodes[j].weight) {
                LSLinesNode node = nodes[i];
                nodes[i] = nodes[j];
                nodes[j] = node;
            }
        }
    }
    
    int *vertexs[N]; //顶点数组，表示被分的组，默认一人一组,保存指针方便修改分组结果一致
    for (int i = 0; i < N; i++) {
        *(vertexs[i]) = i;
    }
    
    LSLinesNode result[N-1]; //保存最终结果的边集数组
    int num = 0;
    for (int i = 0; i < count; i++) {
        LSLinesNode node = nodes[i];
        //如果两个点不在一个组
        if (vertexs[node.fromvex] != vertexs[node.tovex]) {
            result[num] = node;
            num++;
            *(vertexs[node.tovex]) = *(vertexs[node.fromvex]); //更改指针内容指向同一组
            if (num >= N-1) break;
        }
    }
    
     for (int i = 0; i < N-1; i++) {
           result[i].fromvex++;
           result[i].tovex++;
           printf("fromvex:%d -- tovex:%d \n", result[i].fromvex, result[i].tovex);
    }
    printf("\n");
}


