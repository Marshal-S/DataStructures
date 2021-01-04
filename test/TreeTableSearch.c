//
//  TreeTableSearch.c
//  test
//
//  Created by Marshal on 2020/7/27.
//  Copyright © 2020 Marshal. All rights reserved.
//  数表查找

#include "TreeTableSearch.h"
#include <stdio.h>
#include <stdlib.h>

//二叉树基本数据结构
typedef struct TreeNode {
    int data;
    struct TreeNode *l, *r;
}LSTreeNode;


//在排序树、平衡树查找返回指定内容节点
LSTreeNode * search(LSTreeNode *node, int value) {
    while (node) {
        if (node->data == value) return node;
        if (node->data > value) {
            node = node->l;
        }else {
            node = node->r;
        }
    }
    return NULL; //到这里就是没找到了
}

//二叉排序树的插入(不允许重复，如果重复就是替换更新功能了这里就不讨论了)，如果比根节点大
LSTreeNode * insertBinSortNode(LSTreeNode *root, int data) {
    LSTreeNode *node = (LSTreeNode *)malloc(sizeof(LSTreeNode));
    node->data = data;
    if (!root) return node;
    LSTreeNode *p = root, *q = NULL;
    while (p) {
        q = p; //记录待插记录的父节点
        if (p->data == data) {
            free(node);
            return root;
        }; //该节点已经存在，结束（这一步可以进行替换更新功能）
        //只要比根节点大，就一直往左侧找，否则往右找，不停缩小范围，一直到叶子节点为止
        if (p->data > data) {
            p = p->l;
        }else {
            p = p->r;
        }
    }
    //比插入数据大，就放到左侧，否则右侧
    if (q->data > data) {
        q->l = node;
    }else {
        q->r = node;
    }
    return root;
}

//删除二叉排序树某个节点（方案思路，叶子节点直接删除即可，非叶子节点将改替换的节点数据替换成上一个节点，上一个节点一般都是叶子节点或者没有右节点的节点）
LSTreeNode *deleteBinSortNode(LSTreeNode *root, int data) {
    if (!root) return NULL;
    LSTreeNode *p = root, *s = NULL;
    //查看现有二叉树是否存在data节点
    while (p) {
        if (p->data == data) break;
        s = p; //保存搜索到节点的上一个节点
        if (p->data > data) {
            p = p->l;
        }else {
            p = p->r;
        }
    }
    if (!p) return root;//没找到对应的点，结束
    
    if (!p->l && !p->r) {
        //为叶子节点
        if (p == root) root = NULL; //只有根节点置空
        else if (s->l == p) s->l = NULL; //不是根节点左右节点为空
        else s->r = NULL;
    }else if (!p->l) {
        //只有右侧分支, 那么吧p的父节点指向p的指针指向p的右节点
        if (p == root) root = p->r;
        else if (s->r == p) s->r = p->r;
        else s->l = p->r;
    }else if (!p->r) {
        //同右侧指向左侧
        if (p == root) root = p->l;
        else if (s->r == p) s->r = p->l;
        else s->l = p->l;
    }else {
        //两侧都存在的
        LSTreeNode *q = p; //保存查找替换点的数值逻辑的前一个节点的父节点
        s = p; //保存找到的原始节点
        p = p->l;
        while (p->r) {
            q = p;
            p = p->r;
        }
        q->data = p->data;
        if (s == q) s->l = p->l;
        else q->r = p->l;
    }
    free(p);
    return root;
}



