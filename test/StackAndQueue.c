//
//  c.c
//  test
//
//  Created by Marshal on 2020/5/9.
//  Copyright © 2020 Marshal. All rights reserved.
//

#include "StackAndQueue.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1024
//栈 栈顶进，栈顶出， 先进后出
#pragma mark --顺序栈
typedef struct OrderStack {
    char data[MAXSIZE];
    int top;
} LSOrderStack;

LSOrderStack * initOrderStack() {
    LSOrderStack *stack = (LSOrderStack *)malloc(sizeof(LSOrderStack));
    stack->top = -1;
    return stack;
}

_Bool emptyOrderStack(LSOrderStack *stack) {
    return stack->top == -1;
}

_Bool orderPush(LSOrderStack *stack, char c) {
    if (stack->top + 1 > MAXSIZE) return 0; //栈满了
    stack->top++;
    stack->data[stack->top] = c;
    return 1;
}

void orderPop(LSOrderStack *stack) {
    if (emptyOrderStack(stack)) return;
    stack->data[stack->top] = 0;
    stack->top--;
}

void showOrderStack() {
    LSOrderStack *orderStack = initOrderStack();
    char *s = "abcde";
    while (*s) {
        orderPush(orderStack, *s++);
    }
    orderPop(orderStack);
    printf("orderStack:%s \n", orderStack->data);
}


#pragma mark --链栈
typedef struct ListStack {
    char data;
    struct ListStack *next;
} LSListStack;

_Bool emptyListStack(LSListStack *stack) {
    return !stack;
}

LSListStack *listPush(LSListStack *stack, char c) {
    LSListStack *next = (LSListStack *)malloc(sizeof(LSListStack));
    next->data = c;
    next->next = stack;
    return next;
}

LSListStack *listPop(LSListStack *stack) {
    if (emptyListStack(stack)) return stack;
    LSListStack *p = stack;
    stack = stack->next;
    free(p);
    return stack;
}

void showListStack() {
    LSListStack *stack = NULL;
    char *s = "abcdefg";
    while (*s) {
        stack = listPush(stack, *s++);
    }
    stack = listPop(stack);
    
    char str[10];
    LSListStack *tem = stack;
    int i = 0;
    while (tem) {
        str[i] = tem->data;
        tem = tem->next;
        i++;
    }
    str[i] = '\0';
    printf("listStack:%s \n",str);
}


#pragma mark --队列，对尾进，队头出， 先进先出
#pragma mark --顺序队列（循环队列,预留第一个空间不使用）
#define MAXQUEUE 8

typedef struct OrderQueue {
    char data[MAXQUEUE];
    int near, front;  //尾巴进，头出
} LSOrderQueue;

LSOrderQueue * initOrderQueue() {
    LSOrderQueue *queue = (LSOrderQueue *)malloc(sizeof(LSOrderQueue));
    queue->front = queue->near = MAXQUEUE-1;
    return queue;
}

_Bool emptyOrderQueue(LSOrderQueue *queue) {
    return queue->front == queue->near;
}

_Bool orderQueueEnter(LSOrderQueue *queue, char c) {
    if (queue->near + 1 % MAXQUEUE == queue->front) return 0;//队列满了不能入队
    queue->near = ++queue->near % MAXQUEUE;
    queue->data[queue->near] = c;
    return 1;
}

void orderQueueLeave(LSOrderQueue *queue) {
    if (emptyOrderQueue(queue)) return;
    queue->front = ++queue->front % MAXQUEUE;
}

void showOrderQueue() {
    LSOrderQueue *queue = initOrderQueue();
    char *s = "12345678";
    while (*s) {
        orderQueueEnter(queue, *s++);
    }
    orderQueueLeave(queue);
    
    char str[100];
    int i = 0;
    int tem = queue->front + 1;
    while ((tem -1) != queue->near) {
        str[i++] = queue->data[tem++];
        tem %= MAXQUEUE;
    }
    str[i] = '\0';
    printf("orderQueue:%s \n", str);
}


#pragma mark --链队列1
//两种数据结构，一个链表加上一个前后节点，队尾进，队头出
typedef struct listNode {
    char data;
    struct listNode *next;
} LSListNode; //节点基础数据结构

typedef struct endpointListQueue {
    LSListNode *front, *near;
}LSPointListQueue; //队列基础指针

//加入新数据到队尾巴
void pointEnter(LSPointListQueue *queue, char c) {
    LSListNode *node = (LSListNode *)malloc(sizeof(LSListNode));
    node->data = c;
    
    //不存在队首默认指向第一个
    if (!queue->front) {
        queue->near = queue->front = node;
        return;
    }
    
    //队尾指向新增元素
    queue->near->next = node;
    queue->near = node;
}

//头指针指向下一个，释放前面的数据
void pointLeave(LSPointListQueue *queue) {
    if (!queue->front) return;
    LSListNode *front = queue->front;
    queue->front = queue->front->next;
    free(front);
}


#pragma mark --链队列2
//一种数据结构，一个节点自己指向自己,多个队尾巴指向队头，queue永远指向队尾，队尾指向队头，队头指向分支节点直到队尾，多个节点形成一个环状，节省内存，队尾进，队头出
//能反向指么，不能，毕竟出队只能从队首出，需要获取到队首的下一个元素，但是还要能通过这一个指针获取队首和队尾，这样是一个非常简单的操作了
LSListNode *listQueueEnter(LSListNode *queue, char c) {
    LSListNode *node = (LSListNode *)malloc(sizeof(LSListNode));
    node->data = c;
    if (queue) {
        //多个节点首尾相接
        LSListNode *front = queue->next;
        queue->next = node;
        node->next = front;
    }else {
        queue = node->next = node; //一个节点尾指针指向自己
    }
    return queue;
}

LSListNode *listQueueLeave(LSListNode *queue) {
    if (!queue) return NULL;//没有节点
    
    if (queue->next == queue) {
        free(queue); //只有一个
        queue = NULL;
    }else {
        LSListNode *front = queue->next->next; //指向头指针的下一个,两个和多个一样
        free(queue->next);
        queue->next = front;
    }
    return queue;
}

void freeListQueue(LSListNode *queue) {
    while (queue) {
        LSListNode *p = queue;
        queue = queue->next;
        free(p);
    }
}

void showListQueue() {
    char *s = "987654321";
    LSListNode *queue = NULL;
    while (*s) {
        queue = listQueueEnter(queue, *s++);
    }
    queue = listQueueLeave(queue);
    char str[20];
    LSListNode *front = queue->next->next;
    int i = 0;
    if (front != queue) {
        do {
            str[i++] = front->data;
            front = front->next;
        } while (front != queue->next);
    }
    str[i] = '\0';
    printf("listQueue:%s \n", str);
}
