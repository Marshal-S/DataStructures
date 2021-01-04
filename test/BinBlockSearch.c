//
//  BinBlockSearch.c
//  test
//
//  Created by Marshal on 2020/7/27.
//  Copyright © 2020 Marshal. All rights reserved.
//

#include "BinBlockSearch.h"
#include <stdio.h>
#include <stdlib.h>

//顺序查找
void orderSearch(int value) {
    int list[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    for (int i = 0; i < 10; i++) {
        if (list[i] == value) {
            printf("找到了，索引值是:%d \n", i);
            return;
        }
    }
    printf("没找到相关选项 \n");
}

//二分法查找
void showBinSearch(int value) {
    int list[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int start = 0, end = 9;
    int index = -1;
    while (start < end) {
        int middle = (end + start) / 2;
        if (list[middle] == value) {
            index = middle;
            break;
        }
        if (list[middle] > value) {
            start = middle + 1;
        }else {
            end = middle - 1;
        }
    }
    if (index == -1) {
        printf("没找到相关选项 \n");
    }else {
        printf("找到了，索引值是:%d \n", index);
    }
}

//索引查找
typedef struct blockObj {
    int blockIndex;
    int start, end;
} LSBlockObj;

//list值列表 blockList块结构列表 blockIndex搜索的块 value搜索的值
int searchIndex(int list[], LSBlockObj blockList[], int blockIndex, int value) {
    int res = -1;
    for (int i = 0; i < 11; i++) {
        LSBlockObj obj = blockList[i];
        if (obj.blockIndex != blockIndex) continue;
        while (obj.start <= obj.end) {
            if (list[obj.start] == value) return list[obj.start];
            obj.start++;
        }
    }
    return res;
}

void showIndexSearch(int blockIndex, int value) {
    //初始化值
    int list[100];
    for (int i = 1; i <= 100; i++) {
        list[i - 1] = arc4random() % i + 1;
    }
    LSBlockObj blockList[11];
    for (int i = 0, j = 0; i <= 100; i += 10) {
        LSBlockObj obj = blockList[j]; //这一步是赋值，没有引用关系
        obj.blockIndex = j++;
        obj.start = i;
        obj.end = i + 9;
        blockList[j] = obj;
    }
    
    //在指定块内搜索对应值内容，查看是否存在
    int res = searchIndex(list, blockList, blockIndex, value);
    
    if (res == -1) {
        printf("没找到相关选项 \n");
    }else {
        printf("找到了，值是存在是: %d\n", res);
    }
}


