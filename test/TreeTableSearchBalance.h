//
//  TreeTableSearchBalance.h
//  test
//
//  Created by Marshal on 2020/8/19.
//  Copyright © 2020 Marshal. All rights reserved.
//  基于二叉排序树之平衡二叉树AVL

#ifndef TreeTableSearchBalance_h
#define TreeTableSearchBalance_h

/*
 红黑树与AVL树进行对比
 1.AVL树由于严格平衡，查询的时间复杂度要略优于红黑树
 2.红黑树的插入删除比AVL树更便于控制操作
 3.红黑树整体性能略优于AVL树（红黑树旋转情况少于AVL树，由于红黑树不是严格平衡，只需局部达到条件）
 
总共分为四种失衡状态（失去平衡的左右层根节点组成的树，节点当做树根处理，实际可能不是真的树根，从根节点整体左转右转是针对这个的）
LL  在根左侧平衡点左节点插入新节点
    1.无右节点：三个单节点，直接合并成一个二叉节点
    2.有右节点：直接整体右旋转，原根左节点变成根节点，原根左节点右节点变成原根节点的左节点，同时原根节点变成新跟节点的右节点
LR  在根左侧平衡点右节点插入新节点
    1.无左节点：三个单节点，直接合并成一个二叉节点
    2.有左节点：
    先左旋，将平衡点的右节点变成平衡点的父节点(平衡点为其左节点)，平衡点的右节点指向其原有右节点的左节点；
    再整体右旋转，原根左节点变成根节点，原根左节点右节点变成原根节点的左节点，同时原根节点变成新跟节点的右节点
下面的刚好跟上面的对称--
RR  在根右侧平衡点右节点插入新节点
    1.无左节点：三个单节点，直接合并成一个二叉节点
    2.有左节点：直接整体左旋转，原根右节点变成根节点，原根右节点左节点变成原根节点的右节点，同时原根节点变成新跟节点的左节点
RL  在根右侧平衡点左节点插入新节点
    1.无右节点：三个单节点，直接合并成一个二叉节点
    2.有右节点：
    先右旋，将平衡点的左节点变成平衡点的父节点(平衡点为其右节点)，平衡点左节点指向其原有左节点的右节点；
    再整体左旋转，原根右节点变成根节点，原根右节点左节点变成原根节点的右节点，同时原根节点变成新跟节点的左节点
*/

typedef struct TreeNode LSTreeNode;
//int getHeight(LSTreeNode *node); //获取高度，从底下往上累加
//替换式左旋
//LSTreeNode *swapLeftRotation(LSTreeNode *root);
//替换式右旋
//LSTreeNode *swapRightRotation(LSTreeNode *root);
//平衡二叉树的插入（再二叉排序树的基础上进行改进）
LSTreeNode *insertData(LSTreeNode *root, int data);
LSTreeNode *insertBalanceNode(LSTreeNode *root, LSTreeNode *parentNode, LSTreeNode *insertNode);
//平衡二叉树的删除(在删除的基础上进行平衡)
LSTreeNode *deleteData(LSTreeNode *root, int data);
LSTreeNode *deleteBalanceNode(LSTreeNode *root, LSTreeNode *parentNode, LSTreeNode *brotherNode);


#endif /* TreeTableSearchBalance_h */
