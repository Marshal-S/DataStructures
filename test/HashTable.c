//
//  HashTable.c
//  test
//
//  Created by Marshal on 2020/8/21.
//  Copyright © 2020 Marshal. All rights reserved.
//

#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>

//数字分析法
int hashNum1(int num) {
    return num % 1000;
}
int hashNum2(int num) {
    return num % 100;
}
int hashNum3(int num) {
    return (num % 100 + num / 100 % 100) % 100;
}
void numAnaliseWay() {
    int numList[9] = {432456, 432231, 432342, 432111, 432666, 432123, 432555, 432533, 432876};
    //据观察数字的前三位都是432，可以使用后面的数字作为键值，那么根据后面的键值映射的范围为0~999
    int hashList[1000]; //这就是存取数据的hash了
    
    //存放数值，取后面三位
    for (int i = 0; i < 9; i++) {
        int key = hashNum1(numList[i]);
        hashList[key] = numList[i];
    }
    
    //取出数值
    int findNum = 432231;
    int res = hashList[hashNum1(findNum)];
    if (res) {
        //找到了,res就是key对应的结果，这个内容可以是数值，也可以是一个结构体或者对象
    }
    
    //当然上面有点浪费，也可以取后两位也行，hashNum2,方法同上
    //也可以使用后面四位，分别的结果作为key值，取后两位也可以，hashNum3
}


//取余法
int hashNum4(int num) {
    return num % 23; //除数p的设定 n < p < m 也就是介于存取的数字长度和哈希表长度之间
}
void divideResidueWay() {
    int numList[20] = {456, 231, 342, 111, 666, 123, 555, 533, 876, 432, 234, 234, 234, 545, 565, 453, 345, 354, 1234, 4556}; // n 20
    int hashList[30]; //m 30
    for (int i = 0; i < 20; i++) {
        int key = hashNum4(numList[i]);
        hashList[key] = numList[i];
    }
    //取出数值
    int findNum = 231;
    int res = hashList[hashNum4(findNum)];
    if (res) {
        //找到了,res就是key对应的结果，这个内容可以是数值，也可以是一个结构体或者对象
    }
}


//平方取中法（当前散列表长度100则取中间两位）
int hashNum5(int num) {
    return num * num % 100 / 100; //当前为三位数一下相乘，则范围为 0 ~ 1000000
}
void powMiddleWay() {
    int numList[20] = {456, 231, 342, 111, 666, 123, 555, 533, 876, 432, 234, 234, 234, 545, 565, 453, 345, 354, 123, 456};
    int hashList[100];
    for (int i = 0; i < 20; i++) {
        int key = hashNum5(numList[i]);
        hashList[key] = numList[i];
    }
    //取出数值
    int findNum = 456;
    int res = hashList[hashNum5(findNum)];
    if (res) {
        //找到了,res就是key对应的结果，这个内容可以是数值，也可以是一个结构体或者对象
    }
}


//折叠法,将其按照固定长度分为几段，然后累加取几位
int hashNum6(long num) {
    int res = 0;
    while (num > 0) {
        res += num % 1000;
        num /= 1000;
    }
    return res % 1000;
}
void foldingWay() {
    long numList[5] = {4561231231241, 12387234872637, 2938748237, 182872638742, 234234};
    long hashList[1000]; //散列表长度1000则取中间三位
    for (int i = 0; i < 5; i++) {
        int key = hashNum6(numList[i]);
        hashList[key] = numList[i];
    }
    //取出数值
    long findNum = 4561231231241;
    long res = hashList[hashNum6(findNum)];
    if (res) {
        //找到了,res就是key对应的结果，这个内容可以是数值，也可以是一个结构体或者对象
    }
}

//冲突解决方案（通过上面也大致可以猜到，一定会存在存放到同一个地方的情况，下面就是处理冲突的方法）
//线性探测法
int crashLineHandle(int *hashList, int index, int length, int data) {
    int lastIndex = index;
    do {
        index++;
        index = index % length;
        int tem = hashList[index];
        if (tem) continue;
        else return index;
    } while (lastIndex == index);
    return -1;
}

//双散列函数探测法
int crashDoubleLineHandle(int *hashList, int index, int length, int data) {
    int lastIndex = index;
    do {
        index += 11; //与现行探测法不同的是，设置一定间隔，和总长度length互为素数，能减少探测间隔，例如11
        index = index % length;
        int tem = hashList[index];
        if (tem) continue;
        else return index;
    } while (lastIndex == index);
    return -1;
}
void crashLineWay() {
    int numList[6] = {123, 456, 789, 122, 233, 123};
    int hashList[1000]; //散列表长度1000则取中间三位
    for (int i = 0; i < 6; i++) {
        int key = hashNum1(numList[i]);//随意选择一种解决方案
        if (hashList[key]) {
            //冲突了
            int index = crashLineHandle(hashList, key, 1000, numList[i]);
            if (index == -1) return; //满了
        }
        hashList[key] = numList[i];
    }
    //取出数值
    int findNum = 123;
    int res = hashList[hashNum1(findNum)];
    if (res) {
        //找到了,res就是key对应的结果，这个内容可以是数值，也可以是一个结构体或者对象
    }
}


//链地址法
typedef struct node {
    int data;
    struct node *next;
} LSNode;
//冲突时插入逻辑
void crashLinkHandle(LSNode *node, int data) {
    LSNode *nNode = (LSNode *)malloc(sizeof(LSNode));
    nNode->data = data;
    
    //直接插入到第二个即可（由于不知道会先查哪个数，所以该方法效率相对较高)
    nNode->next = node->next;
    node->next = nNode;
}
//冲突时查找逻辑
LSNode *findLinkNode(LSNode *node, int data) {
    while (node->data != data) {
        node = node->next;
    }
    return node;
}
void crashLinkWay() {
    int numList[6] = {123, 456, 789, 122, 233, 123};
    LSNode hashList[1000];
    for (int i = 0; i < 6; i++) {
        int key = hashNum1(numList[i]);//随意选择一种解决方案
        LSNode node = hashList[key];
        if (node.data) {
            //冲突了,解决链表冲突
            crashLinkHandle(&node, numList[i]);
        }else {
            node.data = numList[i];
        }
    }
    //取出数值
    int findNum = 123;
    LSNode *res = findLinkNode(&hashList[hashNum1(findNum)], findNum);
    if (res) {
        //找到了
    }
    
}

