//
//  ThreadSecondTree.c
//  test
//
//  Created by Marshal on 2020/5/14.
//  Copyright © 2020 Marshal. All rights reserved.
//

#include "ThreadSecondTree.h"
#include <stdio.h>
#include <stdlib.h>

//线索二叉树节点
typedef struct Tree {
    int data;
    struct Tree *lchild, *rchild;
    _Bool ltag, rtag; //1表示有线索，0表示为正常左右节点
} LSTree;


typedef struct Queue {
    LSTree *data[1000];
    int front, rear;
} LSOrderQueue;
//根据列表生成一个树
LSTree *generateTree(int *list, int count) {
    LSOrderQueue queue;
    queue.front = queue.rear = 0;
    
    LSTree *root = NULL;
    for (int i = 0; i < count; i++, queue.rear++) {
        LSTree *p = NULL;
        if (list[i]) {
            p = (LSTree *)malloc(sizeof(LSTree));
            p->data = list[i];
            p->lchild = NULL;
            p->rchild = NULL;
            p->ltag = 0;
            p->rtag = 0;
        }
        queue.data[queue.rear] = p;
        if (!root) {
            root = p;
            continue;
        }
        if (queue.data[queue.front]) {
            if (queue.rear % 2 == 1) {
                queue.data[queue.front]->lchild = p;
            }else {
                queue.data[queue.front]->rchild = p;
            }
        }
        if (queue.rear % 2 == 0) queue.front++;
    }
    return root;
}

LSTree *preNode = NULL;//保留上一个节点，可以用于获取前驱节点
//生成中序线索二叉树
LSTree * generateThreeSendTree(LSTree *node) {
    if (!node) return node;
    generateThreeSendTree(node->lchild);
    if (node->lchild == NULL) node->ltag = 1;
    if (node->rchild == NULL) node->rtag = 1;
    if (preNode) {
        if (preNode->rtag == 1) preNode->rchild = node;
        if (node->ltag == 1) node->lchild = preNode;
    }
    preNode = node;
    generateThreeSendTree(node->rchild);
    return node;
}

//以下遍历均使用线索二叉树遍历（可以一个循环解决）
//中序遍历
void middle(LSTree *node) {
    if (!node) return;
    while (node->ltag == 0) node = node->lchild;//找出最左侧的节点
    while (node) {
        printf("%d\t", node->data);
        
        if (node->rtag == 1) {
            node = node->rchild;
        }else {
            node = node->rchild;
            if (node->rtag == 0) {
                //说明是一个头结点，可能存在子节点，找出最左侧节点
                while (node->ltag == 0) node = node->lchild;
            }
        }
    }
}

//前序
void front(LSTree *node) {
    if (!node) return;
    while (node) {
        printf("%d\t", node->data);
        if (node->ltag == 0) node = node->lchild;
        else {
            while (node && node->rtag == 1) node = node->rchild;
            if (node) node = node->rchild;
        }
    }
}

//后续遍历（反向， 目前是中右左，只需要反向遍历结果即可，反向后就是左右中了，推荐加入栈打印，这里就直接节省时间打印反向序列了😂）
void behind(LSTree *node) {
    if (!node) return;
    while (node) {
        printf("%d\t", node->data);
        if (node->rtag == 0) node = node->rchild;
        else {
            while (node && node->ltag == 1) node = node->lchild;
            if (node) node = node->lchild;
        }
    }
}

void m(LSTree *node) {
    if (node) {
        if (node->ltag == 0) m(node->lchild);
        printf("%d\t", node->data);
        if (node->rtag == 0) m(node->rchild);
    }
}

void f(LSTree *node) {
    if (node) {
        printf("%d\t", node->data);
        if (node->ltag == 0) f(node->lchild);
        if (node->rtag == 0) f(node->rchild);
    }
}

void b(LSTree *node) {
    if (node) {
        if (node->ltag == 0) b(node->lchild);
        if (node->rtag == 0) b(node->rchild);
        printf("%d\t", node->data);
    }
}

void showThreadSecondTree() {
    int list[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    LSTree *root = generateTree(list, 20);
    
    root = generateThreeSendTree(root);
    
    m(root);
    printf("\n");
    middle(root);
    printf("\n");
    
    f(root);
    printf("\n");
    front(root);
    printf("\n");
    
    b(root);
    printf("\n");
    behind(root);
    printf("\n");
    
}
