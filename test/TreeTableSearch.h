//
//  TreeTableSearch.h
//  test
//
//  Created by Marshal on 2020/7/27.
//  Copyright © 2020 Marshal. All rights reserved.
//  二叉排序树BST ,平衡树、b树、b+、b*等参考地址https://zhuanlan.zhihu.com/p/27700617

#ifndef TreeTableSearch_h
#define TreeTableSearch_h

/*
 左侧节点总是小于右侧节点
 插入时，大右小左查找，一直到叶子节点大右小左插入
 删除时直接删除节点，叶子节点，正常直接删除，中间只有一个节点情况直接转接对应节点，两个节点情况直接替换成左侧最大节点即可，并清除关系
*/
//二叉树基本数据结构
typedef struct TreeNode LSTreeNode;
//在排序树、平衡树查找返回指定内容节点
LSTreeNode * search(LSTreeNode *node, int value);
//二叉排序树的插入(不允许重复，如果重复就是替换更新功能了这里就不讨论了)，如果比根节点大
LSTreeNode * insertBinSortNode(LSTreeNode *root, int data);
//删除二叉排序树某个节点（方案思路，将改替换的节点数据替换成上一个节点，上一个节点一般都是叶子节点或者没有右节点的节点，处理方便，只需将其可能存在的左节点接入到父节点的右节点即可）
//查看该过程是不是有点麻烦，之前用到的线索二叉树如果用上是不是这一步快多了😂
LSTreeNode *deleteBinSortNode(LSTreeNode *root, int data);

#endif /* TreeTableSearch_h */
