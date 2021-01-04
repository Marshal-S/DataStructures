//
//  SecondTreeList.c
//  test
//
//  Created by Marshal on 2020/5/13.
//  Copyright © 2020 Marshal. All rights reserved.
//  

#include "SecondTreeGenerateList.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20

typedef struct Tree {
    int data;
    struct Tree *lChild, *rChild;
} LSTree;

typedef struct Queue {
    LSTree *data[MAXSIZE];
    int front, rear;
} LSOrderQueue;

//利用二叉树的父子节点关系解决
LSTree * updateTree(int *result, int n, int maxLength) {
    if (n <= maxLength) return NULL; //越界不处理
    
    LSTree *node = (LSTree *)malloc(sizeof(LSTree));
    node->data = result[n];
    node->lChild = updateTree(result, 2*n + 1, maxLength);
    node->rChild = updateTree(result, 2*n + 2, maxLength);
    return node;
}

//二叉树的生成，通过数组生成二叉树
void generateSecondTree(int *result, int maxLength) {
    if (maxLength < 1) return;
    
    LSTree *root = updateTree(result, 0, maxLength);
    //这里生成的root就是result数组生成的二叉树了
}

//更新result数组，例如二叉树的性质，节点和子节点之间的关系，第n个节点索引为 2n + 1，右节点为2n + 2
void updateResult(LSTree *node, int *result, int n) {
    if (!node) return;
    result[n] = node->data;
    updateResult(node->lChild, result, 2*n + 1);
    updateResult(node->rChild, result, 2*n + 2);
}

//保存一个二叉树到数组里
void saveTree() {
    int result[20] = {0};
    LSTree *root = NULL; //假设有值
    updateResult(root, result, 0);
    //这里result即存放好了
}
