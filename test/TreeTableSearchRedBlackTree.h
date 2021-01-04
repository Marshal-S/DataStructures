//
//  TreeTableSearchRedBlackTree.h
//  test
//
//  Created by Marshal on 2020/8/17.
//  Copyright © 2020 Marshal. All rights reserved.
//  数表查询之红黑树
//  写完红黑树发现AVL树类似手段写似乎更好理解，更容易写了，后续可以以红黑树方式改进，部分参考自https://www.jianshu.com/p/e136ec79235c

#ifndef TreeTableSearchRedBlackTree_h
#define TreeTableSearchRedBlackTree_h

/*
 红黑树与AVL树进行对比
 1.AVL树由于严格平衡，查询的时间复杂度要略优于红黑树
 2.红黑树的插入删除比AVL树更便于控制操作
 3.红黑树整体性能略优于AVL树（红黑树旋转情况少于AVL树，由于红黑树不是严格平衡，只需局部达到条件）
 
 性质1：每个节点要么是黑色，要么是红色。
 性质2：根节点是黑色。
 性质3：每个叶子节点（NIL）是黑色（由于数据结构基础特征，实际叶子节点下都会多出来一个NULL节点，当做黑色处理，或者当不存在）。
 性质4：每个红色结点的两个子结点一定都是黑色。
 性质5：任意一结点到每个叶子结点的路径都包含数量相同的黑结点。
 */
typedef struct TreeNode LSTreeNode;
//红黑树的插入，插入后直接平衡
LSTreeNode *insertRBTData(LSTreeNode *root, int data);
LSTreeNode *insertRBTNode(LSTreeNode *root, LSTreeNode *insertNode);
//红黑树的删除，删除后直接平衡
LSTreeNode *deleteRBTData(LSTreeNode *root, int data);
LSTreeNode *deleteRBTNode(LSTreeNode *root, LSTreeNode *parentNode, LSTreeNode *deleteNode);

#endif /* TreeTableSearchRedBlackTree_h */
