//
//  HufmTree.c
//  test
//
//  Created by Marshal on 2020/5/15.
//  Copyright © 2020 Marshal. All rights reserved.
//

#include "HufmTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//线状结构哈弗曼树，n个基础节点，由于原节点或新生成节点之间两两组合，且不重复使用，那么新生成的节点总会比基础节点少1,可以自行使用观测法看出规律，严禁一些则可以使用数学归纳法证明，生成的新节点数为n-1，总结点树为2n-1

typedef struct {
    int parent; //父节点索引
    int weight; //权值
    int lchild, rchild; //左右子节点索引
} LSOrderHufmTree;

typedef struct HufmTree {
    int weight; //权值
    int index; //自己的索引，以便与编码赋值
    struct HufmTree *lchild, *rchild; //左右子节点指针
} LSListHufmTree;


//对哈弗曼树进行编码,root为哈弗曼树，list为保存编码结果数组, code为编码值，从根节点开始，默认为0,这里为了显示看着方便设置成了1
void generateHufmEncoding(LSListHufmTree *node, int *list, int code) {
    if (!node) return;
    
    code *= 2;
    
    if (node->lchild)
        generateHufmEncoding(node->lchild, list, code);
    else
        list[node->index] = code;
    
    if (node->lchild)
        generateHufmEncoding(node->rchild, list, code + 1);
    else
        list[node->index] = code * 2 + 1;
}

//生成二叉哈弗曼树
LSListHufmTree *generateHufmTree(LSOrderHufmTree root, LSOrderHufmTree *list, int index) {
    LSListHufmTree *node = (LSListHufmTree *)malloc(sizeof(LSListHufmTree));
    node->weight = root.weight;
    node->index = index;
    
    if (root.lchild >= 0)
        node->lchild = generateHufmTree(list[root.lchild], list, root.lchild);
    else
        node->lchild = NULL;
    
    if (root.rchild >= 0)
        node->rchild = generateHufmTree(list[root.rchild], list, root.rchild);
    else
        node->rchild = NULL;
    
    return node;
}

//n个节点生成哈夫曼树，那么生成的节点数为n-1，总结点树为2n-1
void generateOrderHufmTree(LSOrderHufmTree *hufmTreeList, int *list, int count) {
    int MAXCount = count*2 - 1; //n个节点生成哈夫曼树，那么生成的节点数为n-1,总结点树为2n-1
    
    //默认节点都是子节点
    for (int i = 0; i < count; i++) {
        hufmTreeList[i].weight = list[i];
        hufmTreeList[i].parent = -1;
        hufmTreeList[i].lchild = -1;
        hufmTreeList[i].rchild = -1;
    }
    int MAXINT = INT32_MAX; //假设其为最大数
    for (int i = count; i < MAXCount; i++) {
        //生成新节点的同时找出最小节点
        //找出最小的两个节点
        int min1 = 1, min2 = 1;
        int minNode1 = MAXINT, minNode2 = MAXINT;
        for (int j = 0; j < i; j++) {
            if (hufmTreeList[j].parent >= 0) continue;
            if (hufmTreeList[j].weight < minNode1) {
                minNode2 = minNode1;
                min2 = min1;
                minNode1 = hufmTreeList[j].weight;
                min1 = j;
            }else if (hufmTreeList[j].weight < minNode2) {
                minNode2 = hufmTreeList[j].weight;
                min2 = j;
            }
        }
        //从子节点后面开始生成新的虚拟父节点，作为新的节点参与计算
        hufmTreeList[i].parent = -1;
        hufmTreeList[i].weight = minNode1 + minNode2;
        hufmTreeList[i].lchild = min1;
        hufmTreeList[i].rchild = min2;
        hufmTreeList[min1].parent = i;
        hufmTreeList[min2].parent = i;
    }
}

//生成哈夫曼树
void showHufmTree() {
    int weightList[12] = {3, 37, 41, 5, 19, 21, 7, 8, 11, 14, 29, 42};
    LSOrderHufmTree hufmList[23]; //数量为2n-1 即23
    generateOrderHufmTree(hufmList, weightList, 12);
    LSListHufmTree *tree = generateHufmTree(hufmList[22], hufmList, 22); //利用最后一个节点(跟节点)，生成二叉哈弗曼树
    printf("%d", tree->weight);
    
    int encodingResult[12]; //保存编码结果
    generateHufmEncoding(tree, encodingResult, 1);
}
