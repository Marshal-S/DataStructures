//
//  linkList.h
//  test
//
//  Created by 李帅 on 2020/7/24.
//  Copyright © 2020 Marshal. All rights reserved.
//  顺序表和链表

#ifndef LSlinkList_h
#define LSlinkList_h

//顺序表基本数据结构
static int data[20]; //就不多说了，数组都是按固定顺序存取，如果数组大小不够用的话，需要重新调整大小，即创建一个新的数组把原来的copy过去


//链表基本数据结构， 后面数据结构可能会用到，这里封窗一下
//其结构为普通数据结构指向下一个相同结构的方式延续下去，优点扩充简单，缺点较顺序表效率低
typedef struct listNode {
    int data;
    struct listNode *next;
} LSListNode;

LSListNode *createListNode(void);

int getListCount(LSListNode *node);
LSListNode * geListNode(LSListNode *node, int index);
LSListNode * pushNode(LSListNode *node, int data); //添加一个新的到最后
LSListNode * popNode(LSListNode *node); //删除最后一项
LSListNode * shiftNode(LSListNode *node); //删除第一项
LSListNode * unshiftNode(LSListNode *node, int data); //在第一项添加数据





#endif /* LSlinkList_h */
