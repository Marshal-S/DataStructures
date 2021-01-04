//
//  TreeTableSearchRedBlackTree.c
//  test
//
//  Created by Marshal on 2020/8/17.
//  Copyright © 2020 Marshal. All rights reserved.
//

#include "TreeTableSearchRedBlackTree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    int color; //0红色 1黑色
    struct TreeNode *parentNode;
    struct TreeNode *l, *r;
}LSTreeNode;

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

#pragma mark --插入数据节点
//插入新数据，先插入后根据颜色节点关系平衡
LSTreeNode *insertRBTData(LSTreeNode *root, int data) {
    LSTreeNode *node = (LSTreeNode *)malloc(sizeof(LSTreeNode));
    node->parentNode = NULL;
    if (!root) {
        node->color = 1; //没有根节点插入根节点设置成黑色，不需要平衡
        return node;
    }
    LSTreeNode *p = root, *s = NULL;
    while (p) {
        s = p;
        if (p->data == data) {
            p->data = data; //赋予新的值即可，因为真实data可能不为数字，data可能只是一个key，也不需要平衡
            free(node);
            return root;
        }
        if (data < p->data) {
            p = p->l;
        }else {
            p = p->r;
        }
    }
    //除了根节点默认插入的是红色节点
    node->color = 0;
    node->parentNode = s; //设置父节点
    
    if (data < s->data) {
        s->l = node;
    }else {
        s->r = node;
    }
    return insertRBTNode(root, node); //到这里的插入节点需要进行后续的平衡操作
}

#pragma mark --平衡插入数据节点
//平衡插入的新数据，主要是处理本分支新加入的红节点，内部能消化就消化，不能消化的话，就直接拿着红节点向上接着消化
//主要通过变色旋转来平衡多出来的红色节点
LSTreeNode *insertRBTNode(LSTreeNode *root, LSTreeNode *insertNode) {
    LSTreeNode *parentNode = insertNode->parentNode; //父节点，到这里父节点肯定不为空
    if (parentNode->color == 1) return root; //父节点是黑色直接结束即可
    //祖父节点
    //如果父节点不是根节点，祖父节点也肯定存在，不会走到这里 ，因为无祖父节点的情况走到这个方法的情况只有:父节点为根节点,子节点为自下而上来的红节点不需要平衡，第一步就结束了
    LSTreeNode *grandNode = parentNode->parentNode;
    //到这里父节点一定是红色的，那么祖父节点一定是黑色的
    if (grandNode->l == parentNode) {
        //父节点是祖父节点的左节点
        if (!grandNode->r || grandNode->r->color == 1) {
            //父节点的兄弟节点不存在或者黑色
            if (parentNode->r == insertNode) {
                //当前插入节点是父节点的右节点,直接对父节点左旋, 形成和插入左子节点一样的情况
                swapLeftRotation(parentNode, insertNode);
            }
            //此时父节点和左子节点都为红色,直接右旋变色即可平衡两个连续红色节点问题，
            //这一层的旋转方案不要调用祖父节点的父节点，使用替换值的方式进行旋转，通用处理，避免出现根节点需要特殊处理的问题
            //交换父节点和祖父节点值，子节点和父节点变成了祖父节点的左右子节点
            swapRightRotation(grandNode, parentNode);
            //最后变色,本来就是值和关系交换行程的旋转，子节点和父节点变成了祖父节点的左右子节点，发现此过程节点颜色不需要变发现已经和平衡后一样
        }else {
            //叔叔节点为红色
            //父节点和叔叔节点设置成黑色，祖父节点设置成红色，不增加黑节点情况，通过变色进行平衡，但祖父会变成红色，需要自下而上平衡
            grandNode->l->color = 1;
            grandNode->r->color = 1;
            if (grandNode->parentNode) {
                grandNode->color = 0; //祖父节点不是是根节点变成红色
            }else {
                return root; //祖父节点是根节点就结束
            }
            return insertRBTNode(root, grandNode); //祖父节点变成插入节点自下而上平衡
        }
    }else {
        //父节点是祖父节点的右节点
        if (!grandNode->l || grandNode->l->color == 1) {
            //叔叔节点不存在或者黑色
            if (parentNode->l == insertNode) {
                //当前插入节点是父节点的右节点,直接对父节点右旋, 形成和插入左子节点一样的情况
                swapRightRotation(parentNode, insertNode);
            }
            //此时父节点和右子节点都为红色,直接左旋变色即可平衡两个连续红色节点问题，
            //这一层的旋转方案不要调用祖父节点的父节点，使用替换值的方式进行旋转，通用处理，避免出现根节点需要特殊处理的问题
            //交换父节点和祖父节点值，父节点和子节点变成了祖父节点的左右子节点
            swapLeftRotation(grandNode, parentNode);
            //最后变色,本来就是值和关系交换行程的旋转，父节点和子节点变成了祖父节点的左右子节点，发现此过程节点颜色不需要变发现已经和平衡后一样
        }else {
            //叔叔节点为红色
            //父节点和叔叔节点设置成黑色，祖父节点设置成红色，不增加黑节点情况，通过变色进行平衡，但祖父会变成红色，需要自下而上平衡
            grandNode->l->color = 1;
            grandNode->r->color = 1;
            if (grandNode->parentNode) {
                grandNode->color = 0; //祖父节点不是是根节点变成红色
            }else {
                return root; //祖父节点是根节点就结束
            }
            return insertRBTNode(root, grandNode); //祖父节点变成插入节点自下而上平衡
        }
    }
    return root;
}

#pragma mark --删除
//查找并删除节点
LSTreeNode *deleteRBTData(LSTreeNode *root, int data) {
    if (!root) return NULL;
    LSTreeNode *p = root, *s = NULL;
    while (p) {
        if (p->data == data) break; //找到了要删除的节点
        s = p; //否则s指向当前节点,p接着往下走
        if (p->data > data) {
            p = p->l;
        }else {
            p = p->r;
        }
    }
    if (!p) return root; //没找到要删除的节点
    //p为要删除的节点
    //下面开始，删除红黑树节点
    if (p->r && p->l) {
        //两个节点均存在，那么这次与排序二叉树和AVL树不同，从右分支找出删除节点的后继节点进行替换
        LSTreeNode *q = p; //保存被替换节点用于替换值
        s = p; //s仍然保存父节点
        p = p->r;
        while (p->l) {
            s = p;
            p = p->l;
        }
        //替换节点的值赋值到被替换节点，然后进行统一删除即可
        q->data = p->data;
        //紧接着删除节点p转化为了叶子节点或者是只有一个节点的叶子节点
    }
    //不存在两个子节点的情况了
    if (p->l) {
        //仍然有左节点，那么左节点一定是红节点，且无子节点，p节点为黑色，不然符合红黑树特征
        p->data = p->l->data;
        free(p->l);
        p->l = NULL;
    }else if (p->r) {
        //只存在右节点,那么右节点一定为红色，p是黑色，直接换色平衡即可
        p->data = p->r->data;
        free(p->r);
        p->r = NULL;
    }else {
        //没有子节点
        if (p == root) {
            //根节点
            free(p);
            root = NULL;
        }else {
            //删除节点p，并置空父节点
            if (s->l == p) s->l = NULL;
            else s->r = NULL;
            
            //由于子节点是黑色，删除后需要平衡
            if (p->color == 1) root = deleteRBTNode(root, s, NULL);
            
            free(p);
        }
    }
    return root;
}

#pragma mark --平衡删除数据节点
//删除时，一侧侧缺少一个黑色，那么得想办法补充上这个缺少的黑色节点，从父节点和右侧节点下手，如果不能平衡掉这个分支缺少的黑色节点，那么把父节点作为要删除的黑色节点位置尝试向上平衡，平衡中不会删除节点，所以不用担心节点问题
LSTreeNode *deleteRBTNode(LSTreeNode *root, LSTreeNode *parentNode, LSTreeNode *deleteNode) {
    //由于deleteNode少了个黑色的Node节点才需要平衡，所以brotherNode一定存在
    LSTreeNode *brotherNode = parentNode->l == deleteNode ? parentNode->r : parentNode->l;
    //父节点是黑色节点
    //由于deleteNode少了个黑色的Node节点才需要平衡，所以brotherNode的黑色节点至少得有一层
    if (parentNode->l == deleteNode) {
        //删除节点为左节点，兄弟节点是右节点
        if (brotherNode->color == 0) {
            //兄弟节点为红色节点,兄弟左右子节点一定都为黑色节点
            swapLeftRotation(parentNode, brotherNode); //左旋形成兄弟节点为黑节点的情况
            //更新原删除节点的最新父兄节点
            brotherNode = parentNode->l == deleteNode ? parentNode->r : parentNode->l;
            parentNode = deleteNode->parentNode;
        }
        //此时删除节点的兄弟节点为黑色
        if (brotherNode->l && brotherNode->l->color == 0 && (!brotherNode->r || brotherNode->r->color == 1)) {
            //兄弟左节点为红色，右节点为黑色或者不存在，直接右旋变成右节点为红色状态,由于替换式旋转这两个不会变色，则不需要变色
            swapRightRotation(brotherNode, brotherNode->l);
        }
        if (brotherNode->r && brotherNode->r->color == 0) {
            //兄弟节点右节点为红色
            swapLeftRotation(parentNode, brotherNode);
            parentNode->r->color = 1; //新形成的树，原父节点位置右节点变成黑色则平衡完毕
        }else {
            //根据红黑树性质，此时只剩下兄弟节点只剩下都为空或者都为黑色节点情况
            if (parentNode->color == 0) {
                //父节点为红色
                brotherNode->color = 0;
                parentNode->color = 1; //为了逻辑更清晰不提取了
            }else {
                //父节点为黑色
                brotherNode->color = 0; //兄弟节点设置红色
                if (parentNode->parentNode) {
                    //没到根节点向上消化
                    return deleteRBTNode(root, parentNode->parentNode, parentNode);
                }
                //到根节点已经平衡了结束
            }
        }
    }else {
        //删除节点为右节点，兄弟节点是左节点
        if (brotherNode->color == 0) {
            //兄弟节点为红色节点,兄弟左右子节点一定都为黑色节点
            swapRightRotation(parentNode, brotherNode); //右旋形成兄弟节点为黑节点的情况
            //更新原删除节点的最新父兄节点
            brotherNode = parentNode->l == deleteNode ? parentNode->r : parentNode->l;
            parentNode = deleteNode->parentNode;
        }
        //此时删除节点的兄弟节点为黑色
        if (brotherNode->r && brotherNode->r->color == 0 && (!brotherNode->l || brotherNode->l->color == 1)) {
            //兄弟右节点为红色，左节点为黑色或者不存在，直接左旋变成左节点为红色状态,由于替换式旋转这两个不会变色，则不需要变色
            swapLeftRotation(brotherNode, brotherNode->r);
        }
        if (brotherNode->l && brotherNode->l->color == 0) {
            //兄弟节点左节点为红色
            swapRightRotation(parentNode, brotherNode);
            parentNode->l->color = 1; //新形成的树，原父节点位置右节点变成黑色则平衡完毕
        }else {
            //根据红黑树性质，此时只剩下兄弟节点只剩下都为空或者都为黑色节点情况
            if (parentNode->color == 0) {
                //父节点为红色
                brotherNode->color = 0;
                parentNode->color = 1; //为了逻辑更清晰不提取了
            }else {
                //父节点为黑色
                brotherNode->color = 0; //兄弟节点设置红色
                if (parentNode->parentNode) {
                    //没到根节点向上消化
                    deleteRBTNode(root, parentNode->parentNode, parentNode);
                }
                //到根节点已经平衡了结束
            }
        }
    }
    return root;
}
