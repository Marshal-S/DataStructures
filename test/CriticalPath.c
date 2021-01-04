//
//  CriticalPath.c
//  test
//
//  Created by Marshal on 2020/9/21.
//  Copyright © 2020 Marshal. All rights reserved.
//

#include "CriticalPath.h"
#include <stdio.h>
#include <stdlib.h>

#define N 9 //总顶点数
#define MAXTIME 18 //最长工期

//出度linkList基础结构
typedef struct AdjvexNode {
    int adjvex; //顶点
    int weight; //代表边的权值(即单个活动时长)
    struct AdjvexNode *next; //这个顶点是没有顺序的，单纯是一个顶点所指向的节点而已，表示的就是一条边
} LSAdjvexNode;

typedef struct {
    int vertex; //顶点
    int id; //入度
    LSAdjvexNode *link;
}LSVertexNode;

void generateVertexNode(LSVertexNode list[]) {
    LSAdjvexNode *node1 = (LSAdjvexNode *)malloc(sizeof(LSAdjvexNode));
    node1->adjvex = 1;
    LSAdjvexNode *node2 = (LSAdjvexNode *)malloc(sizeof(LSAdjvexNode));
    node2->adjvex = 2;
    LSAdjvexNode *node3 = (LSAdjvexNode *)malloc(sizeof(LSAdjvexNode));
    node3->adjvex = 3;
    node1->next = node2;
    node2->next = node3;
    node3->next = NULL;
    list[0].link = node1;
    list[0].id = 0;
    list[0].vertex = 0;
    
    node1 = (LSAdjvexNode *)malloc(sizeof(LSAdjvexNode));
    node1->adjvex = 4;
    node1->next = NULL;
    list[1].link = node1;
    list[1].id = 1;
    list[1].vertex = 1;
    
    node1 = (LSAdjvexNode *)malloc(sizeof(LSAdjvexNode));
    node1->adjvex = 4;
    node1->next = NULL;
    list[2].link = node1;
    list[2].id = 1;
    list[2].vertex = 2;
    
    node1 = (LSAdjvexNode *)malloc(sizeof(LSAdjvexNode));
    node1->adjvex = 5;
    node1->next = NULL;
    list[3].link = node1;
    list[3].id = 1;
    list[3].vertex = 3;
    
    node1 = (LSAdjvexNode *)malloc(sizeof(LSAdjvexNode));
    node1->adjvex = 6;
    node2 = (LSAdjvexNode *)malloc(sizeof(LSAdjvexNode));
    node2->adjvex = 7;
    node1->next = node2;
    node2->next = NULL;
    list[4].link = node1;
    list[4].id = 2;
    list[4].vertex = 4;
    
    node1 = (LSAdjvexNode *)malloc(sizeof(LSAdjvexNode));
    node1->adjvex = 7;
    node1->next = NULL;
    list[5].link = node1;
    list[5].id = 1;
    list[5].vertex = 5;
    
    node1 = (LSAdjvexNode *)malloc(sizeof(LSAdjvexNode));
    node1->adjvex = 8;
    node1->next = NULL;
    list[6].link = node1;
    list[6].id = 1;
    list[6].vertex = 6;
    
    node1 = (LSAdjvexNode *)malloc(sizeof(LSAdjvexNode));
    node1->adjvex = 8;
    node1->next = NULL;
    list[7].link = node1;
    list[7].id = 2;
    list[7].vertex = 7;
    
    list[8].link = NULL;
    list[8].id = 2;
    list[8].vertex = 8;
}

//拓扑排序,顺道获取顶点的最早开始时间和排序后的结果
void tuppoSort(LSVertexNode *list, int *fastStartList, int *tupoResultList) {
    //巧妙利用入度为0的顶点作为栈的一部分，设置top指向-1即栈底，入度为0的id对齐进行入栈，top指向他，其被加入栈底
    int top = -1;
    for (int i = 0; i < N; i++) {
        if (!list[i].id) {
            list[i].id = top;
            top = i;
        }
    }
    
    int num = 0; //num表示的是拿出了几个，如果 num<N 表示里面有环
    while (top != -1) {
        num++; //默认找到了，数量+1;
        printf("%d ", top + 1);
        tupoResultList[num] = top; //保存索引结果到数组中
        
        LSAdjvexNode *link = list[top].link; //获取出边link
        
        int lineIdx = list[top].vertex; //当前边的起点索引
        
        top = list[top].id; //及时更新为下一个的，因为其后续link节点可能还会更新top
        
        while (link) {
            int idx = link->adjvex; //这个adjvex指向的不是索引，比索引要大一个，即当前边的终点实际索引
            
            //如果此边的上一个 起点最早开始时间 + 事件消耗时间 > 此边终点的最早开始时间，那么更新(判断条件主要是更新一个顶点多个事件的情况，取最长的)
            if (fastStartList[lineIdx] + link->weight > fastStartList[idx]) {
                fastStartList[idx] = fastStartList[lineIdx] + link->weight;
            }
            
            list[idx].id--;
            if (!list[idx].id) {
                //入度为0，可以作为下次待遍历的点
                list[idx].id = top;
                top = idx; //跟一开始一样做标记，跟top值交换
            }
            link = link->next;
        }
    }
    if (num < N) {
        printf("\n中间有回路!");
    }else {
        printf("\n");
    }
    
    //注意结果可能和你想想的不太一样，只要入度为零的谁在前后都一样哈
}

//用于保存边集合,用于确定关键路径涉及到的边
typedef struct {
    int fromvex;
    int tovex;
    int weight;
} LSLinesNode;

int getLinkListLinesCount(LSVertexNode *list) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        LSAdjvexNode *link = list[i].link;
        while (link) {
            link = link->next;
            count++;
        }
    }
    return count;
}

//分别获取连通图的 顶点的最早开始时间，最晚开始时间， 最早开始活动，最晚开始活动
void showCriticalPath() {
    //初始化和生成连通图的邻接表
    LSVertexNode list[N];
    generateVertexNode(list);
    int linesCount = getLinkListLinesCount(list); //获取总边数，用于初始事件(边)
    
    //分别是拓扑排序的结果，顶点最早开始时间，顶点最晚开始时间
    int tupoResultList[N], fastStartList[N], slowEndList[N];
    //活动(边)最早开始时间，活动(边)最晚开始时间
    LSLinesNode fastStartActivityList[linesCount], slowEndActivityList[linesCount];
    
    //初始化事件(边)最早开始时间和最晚开始时间默认值
    for (int i = 0; i < N; i++) {
        fastStartList[i] = 0;
        slowEndList[i] = MAXTIME;
    }
    
    //进行一波拓扑排序，获得结果的过程顺道获取到最早开始时间，通过拓扑排序结果倒序算出最晚开始时间
    tuppoSort(list, fastStartList, tupoResultList);
    
    //用于获取顶点的最晚开始时间
    for (int i = N - 1; i >= 0; i--) {
        int idx = tupoResultList[i];
        LSAdjvexNode *link = list[idx].link;
        while (link) {
            int j = link->adjvex;
            //反向获取最晚开始时间，最晚开始时间终点 - 事件长度 < 最晚开始时间起点 (最晚开始时间倒着取一定要取最小的，得保证后面的最长任务能完成)
            if (slowEndList[j] - link->weight < slowEndList[idx]) {
                slowEndList[idx] = slowEndList[j] - link->weight;
            }
        }
    }
    
    //而边的的最早开始时间和最晚开始时间，分别对应该边的起点的最早开始时间，和起点的最晚开始时间
    int nodeNum = 0;
    for (int i = 0; i < N; i++) {
        LSAdjvexNode *link = list[i].link; //起点
        while (link) {
            int  j = link->adjvex - 1; //终点
            //初始化最早开始时间的边
            LSLinesNode node = fastStartActivityList[nodeNum];
            node.fromvex = i;
            node.tovex = j;
            node.weight = fastStartList[i];
            
            //初始化最晚开始时间的边
            LSLinesNode node2 = slowEndActivityList[nodeNum];
            node2.fromvex = i;
            node2.tovex = j;
            node2.weight = slowEndList[i];
            link = link->next;
            nodeNum++;
        }
    }
    
    //遍历邻接表找出起点 最早开始时间 == 最晚开始时间的即为关键路径
    LSLinesNode keyPath[linesCount]; //由边组成的关键路径
    int keyPathCount = 0; //关键路径的实际数量
    //求出关键路径
    for (int i = 0; i < linesCount; i++) {
        LSLinesNode node = fastStartActivityList[i];
        LSLinesNode node2 = slowEndActivityList[i];
        if (node.weight == node2.weight) {
            keyPath[keyPathCount++] = node; //随便给一个就行了，能表示是那条边就行了
        }
    }
}
