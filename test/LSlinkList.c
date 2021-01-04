//
//  LSlinkList.c
//  test
//
//  Created by 李帅 on 2020/7/24.
//  Copyright © 2020 Marshal. All rights reserved.
//

#include "LSlinkList.h"
#include <stdio.h>
#include <stdlib.h>

static LSListNode *root = NULL;

LSListNode *createListNode() {
    return root;
}

int getListCount(LSListNode *node) {
    int i = 0;
    while (node) {
        node = node->next;
        i++;
    }
    return i;
}

LSListNode * geListNode(LSListNode *node, int index) {
    int i = 0;
    while (i < index && node) {
        node = node->next;
        i++;
    }
    return node;
}

LSListNode * pushNode(LSListNode *node, int data) {
    LSListNode *n = (LSListNode *)malloc(sizeof(LSListNode));
    n->data = data;
    n->next = NULL;
    if (node) {
        LSListNode *next = node;
        while (next->next) {
            next = next->next;
        }
        next->next = n;
    }else {
        node = n;
    }
    return node;
}

LSListNode *popNode(LSListNode *node) {
    if (!node) return NULL;
    LSListNode *next = node->next;
    if (!next) {
        free(node);
        return NULL;
    }
    while (next->next) {
        node = next;
        next = next->next;
    }
    
    free(node->next);
    node->next = NULL;
    return node;
}

LSListNode * shiftNode(LSListNode *node) {
    if (node) {
        LSListNode *n = node;
        node = n->next;
        free(n);
        return node;
    }
    return NULL;
}

LSListNode * unshiftNode(LSListNode *node, int data) {
    LSListNode *n = (LSListNode *)malloc(sizeof(LSListNode));
    n->data = data;
    if (node) {
        n->next = node;
    }else {
        n->next = NULL;
    }
    return n;
}
