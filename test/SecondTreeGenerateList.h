//
//  SecondTreeList.h
//  test
//
//  Created by Marshal on 2020/5/13.
//  Copyright © 2020 Marshal. All rights reserved.
//  保存一个二叉树，从上往下，从左往右,均为链表， 如果为线性表则左子节为父节点2n+1，右子节点位置为2n+2（只符合二叉树）,n为父节点索引

#ifndef SecondTreeList_h
#define SecondTreeList_h

//从数组生成二叉树
void generateSecondTree(int *result, int maxLength); //利用规律递归生成

//保存一个二叉树到数组里
void saveTree(void);

#endif /* SecondTreeList_h */
