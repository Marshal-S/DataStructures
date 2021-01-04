//
//  TuopuSort.c
//  test
//
//  Created by Marshal on 2020/7/21.
//  Copyright © 2020 Marshal. All rights reserved.
//

#include "TuopuSort.h"
#include <stdio.h>
#include <stdlib.h>

#define N 9

//出度linkList基础结构
typedef struct AdjvexNode {
    int adjvex; //顶点
    struct AdjvexNode *next; //这个顶点是没有顺序的，单纯是一个顶点所指向的节点而已，表示的就是一条边
} LSAdjvexNode;

typedef struct {
    int vertex; //顶点
    int id; //入度
    LSAdjvexNode *link;
}LSVertexNode;

//V1--V9 实际 0--8
void generateVertexNodes(LSVertexNode list[]) {
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

//拓扑排序，从入度为零的边（没有依赖其他边）开始遍历，每遍历一个则消除其出度，如此往复
void showTuppoSort() {
    //初始化邻接表，里面包含连通图的一些信息
    LSVertexNode list[N];
    generateVertexNodes(list);
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
        
        LSAdjvexNode *link = list[top].link; //获取出边链表link
        
        top = list[top].id; //及时出栈，top指向下一个元素
        //处理该顶点所有出边
        while (link) {
            int idx = link->adjvex; //这个adjvex指向的不是索引，比索引要大一个
            list[idx].id--; //对出边对应顶点入度减1
            if (!list[idx].id) {
                //入度为0，入栈，可以作为下次待遍历的点
                list[idx].id = top; //相当于链栈的栈顶元素指向了其下面的元素，即入栈、压栈
                top = idx; //更新栈顶指针
            }
            link = link->next; //进入下一轮直到所有出边都处理完毕
        }
    }
    if (num < N) {
        printf("\n中间有回路! \n");
    }else {
        printf("\n");
    }
    //注意结果可能和你想想的不太一样，只要入度为零的谁在前后都一样
}

