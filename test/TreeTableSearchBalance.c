//
//  TreeTableSearchBalance.c
//  test
//
//  Created by Marshal on 2020/8/19.
//  Copyright © 2020 Marshal. All rights reserved.
//  平衡二叉树

#include "TreeTableSearchBalance.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *parentNode;
    struct TreeNode *l, *r;
}LSTreeNode;

//获取高度，从底下往上累加，调用频率较高，改成强制内联
static __attribute__((always_inline)) int getHeight(LSTreeNode *node) {
    int heightX = 0;
    while (node) {
        heightX++;
        node = node->l ? node->l : node->r;
    }
    return heightX;
}

//左旋rightNode必须存在
#pragma mark --替换式左旋，右节点作为临时变量，已经交接好父子关系，方便统一使用
static __attribute__((always_inline)) void swapLeftRotation(LSTreeNode *parentNode, LSTreeNode *rightNode) {
    int data = parentNode->data;
    parentNode->data = rightNode->data;
    rightNode->data = data;
    parentNode->r = rightNode->r;
    rightNode->r->parentNode = parentNode;
    rightNode->r = rightNode->l;
    rightNode->l = parentNode->l;
    if (parentNode->l) parentNode->l->parentNode = rightNode;
    parentNode->l = rightNode;
}

//右旋leftNode必须存在
#pragma mark --替换式右旋，通过左节点作为临时变量，已经交接好父子关系，方便统一使用
static __attribute__((always_inline)) void swapRightRotation(LSTreeNode *parentNode, LSTreeNode *leftNode) {
    int data = parentNode->data;
    parentNode->data = leftNode->data;
    leftNode->data = data;
    parentNode->l = leftNode->l;
    leftNode->l->parentNode = parentNode;
    leftNode->l = leftNode->r;
    leftNode->r = parentNode->r;
    if (parentNode->r) parentNode->r->parentNode = leftNode;
    parentNode->r = leftNode;
}

#pragma mark --平衡二叉树的插入（再二叉排序树的基础上进行改进）
LSTreeNode *insertData(LSTreeNode *root, int data) {
    LSTreeNode *node = (LSTreeNode *)malloc(sizeof(LSTreeNode));
    node->data = data;
    if (!root) return node;
    LSTreeNode *p = root, *s = NULL;//s为插入节点的位置
    while (p) {
        s = p;
        if (p->data == data) {
            free(node);
            return root; //重复可以进行替换值结束
        }
        if (p->data > data) {
            p = p->l;
        }else {
            p = p->r;
        }
    }
    _Bool isLeft = s->data > data;
    if (isLeft) {
        s->l = node;
    }else {
        s->r = node;
    }
    node->parentNode = s; //设置父节点
    //正常的插入一个新节点到此结束
    //此时需要开始平衡二叉树
    insertBalanceNode(root, s, node);
    return root;
}

//平衡插入的新节点, 以插入节点父节点为基准
LSTreeNode *insertBalanceNode(LSTreeNode *root, LSTreeNode *parentNode, LSTreeNode *insertNode) {
    LSTreeNode *grandNode = parentNode->parentNode;
    //不存在则到达根节点，不满足两层，不需要平衡
    if (!grandNode) return root;
    //计算左右分支差
    int heightX = getHeight(grandNode->l) - getHeight(grandNode->r);
    //分支高度差小于2才需要直接平衡，否则一直平衡到树根
    if (abs(heightX) < 2) {
        //需要自下而上平衡到根节点，只平衡一个树是不行的，可能当前树内部本身就是平衡的，但是和另外一个数出现了高度差
        //父节点代替当前节点继续向上平衡,毕竟要一层一层向上走
        return insertBalanceNode(root, grandNode, parentNode);
    }
    //此时需要直接平衡平衡
    //注意细节：因为是插入节点，node一定是指向插入的分支方向的那个根节点的子节点
    if (heightX > 0) {
        //插入分支属于左分支，查看左分支是插入到了node左边还是右边
        //处理不平衡
        if (parentNode->r == insertNode) {
            //如果是从右侧插入，先左旋
            swapLeftRotation(parentNode, insertNode);
        }
        //直接整体右旋即可平衡
        swapRightRotation(grandNode, parentNode);
    }else {
        //右侧分支较多
        if (parentNode->l == insertNode) {
            //如果是从左侧插入，先左旋
            swapRightRotation(parentNode, insertNode);
        }
        swapLeftRotation(grandNode, parentNode);
    }
    //平衡完一次后消除当前插入造成的结果，直接结束即可
    return root;
}

#pragma --mark --平衡二叉树的删除(在删除的基础上进行平衡)
LSTreeNode *deleteData(LSTreeNode *root, int data) {
    if (!root) return NULL;
    LSTreeNode *p = root, *s = NULL;
    while (p) {
        if (p->data == data) break;
        s = p;
        if (p->data < data) {
            p = p->r;
        }else {
            p = p->l;
        }
    }
    if (!p) return root; //没找到删除失败
    
    if (!p->l && !p->r) {
        //为叶子节点
        if (p == root) root = NULL;
        else if (s->l == p) s->l = NULL;
        else s->r = NULL;
    }else if (!p->l && p->r) {
        //只有右节点
        if (p == root) root = s->r;
        else if (s->l == p) s->l = p->r;
        else s->r = p->r;
        if (p->r) p->r->parentNode = s;
    }else if (p->l && !p->r) {
        //只有左节点
        if (p == root) root = s->l;
        else if (s->l == p) s->l = p->l;
        else s->r = p->l;
        if (p->l) p->l->parentNode = s;
    }else {
        //找到左侧最后一个节点替换掉删除节点内容，然后删除左节点最后一个内容
        LSTreeNode *q = p; //记录被删除的及诶单
        s = p; //保存删除点的父节点
        p = p->l; //找到要替换的删除节点的节点
        while (p->r) {
            q = p;
            p = p->r;
        }
        q->data = p->data;
        if (s == q) {
            s->l = p->l;
            if (p->l) p->l->parentNode = s;
        }
        else {
            q->r = p->l;
            if (p->l) p->l->parentNode = q;
        }
    }
    //父节点存在才有平衡必要(不存在说明删除的为根节点)
    if (s) {
        LSTreeNode *brotherNode = s->l == p ? s->r : s->l;
        
        root = deleteBalanceNode(root, s, brotherNode);
    }
    free(p);
    return root;
}

//平衡二叉树的删除(在删除的基础上进行平衡)，从删除节点向上平衡，那么与插入相似，当前分支作为缺少的分支，找另外一个分支对比平衡，如果平衡，那么当前分支取父节点继续向上递归平衡即可
LSTreeNode *deleteBalanceNode(LSTreeNode *root, LSTreeNode *parentNode, LSTreeNode *brotherNode) {
    //不存在则到达根节点，不满足两层，不需要平衡
    if (!parentNode) return root;
    
    int heightX = getHeight(parentNode->l) - getHeight(parentNode->r);
    if (abs(heightX) < 2) {
        //平衡这的直接向上对比一直倒根节点方可确认没有失衡
        //注意：可以通过父节点和删除节点自动排除同时存在两个节点情况(同时左右孩子删除完不影响平衡)，其实起始处判断一次，可以优化效率
        return deleteBalanceNode(root, parentNode->parentNode, parentNode);
    }
    //出现了不平衡开始平衡，部分同插入一致
    if (heightX > 0) {
        //右侧为删除节点所在树枝,左侧偏高，从左侧平衡
        if (getHeight(brotherNode->l) - getHeight(brotherNode->r) < 0) {
            //此时为LR型，先局部左旋，此时右侧节点一定存在
            swapLeftRotation(brotherNode, brotherNode->r);
        }
        //直接整体右旋即可平衡
        swapRightRotation(parentNode, brotherNode);
    }else {
        //左侧为删除节点所在树枝，右侧偏高,从右侧平衡
        if (getHeight(brotherNode->l) - getHeight(brotherNode->r) > 0) {
            //此时为RL型，先局部右旋，此时左侧节点一定存在
            swapRightRotation(brotherNode, brotherNode->l);
        }
        //直接整体左旋即可平衡
        swapLeftRotation(parentNode, brotherNode);
    }
    //平衡完毕后即可直接结束,每一次删除最多只会出现一次失衡
    return root;
}



