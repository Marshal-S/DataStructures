//
//  main.m
//  test
//
//  Created by Marshal on 2020/5/8.
//  Copyright © 2020 Marshal. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "StackAndQueue.h"
#import "SecondTreeGenerateList.h"
#import "ThreadSecondTree.h"
#import "HufmTree.h"
#import "MiniGenerateTree.h"
#import "MinShortPath.h"
#import "TuopuSort.h"
#import "CriticalPath.h"
#import "ClassSort.h"
#import "BinBlockSearch.h"
#import "TreeTableSearch.h"

int main(int argc, const char * argv[]) {
    
    //栈和队列
//    showOrderStack();
//    showListStack();
//    showOrderQueue();
//    showListQueue();
//    
//    
//    showThreadSecondTree();
//    
//    showHufmTree();
    
//    generateMinTreeByPrim();
//    generateMinTreeByKruskal();
    
//    showSingleMinShortPathByDijkstra(2);
//    showDoubleMinShortPathByFloyd(2, 1);
    
//    showTuppoSort();
//    showCriticalPath();
    
    int n = 30;
    int list[n];
    for (int i = 0; i < n; i++) {
        list[i] = arc4random() % (n * 10) + 1;
    }
    showSortResult(list, n, "初始值");
    sortByStraightInsertion(list, n); //直接插入排序
    sortByShell(list, n); //希尔排序(缩小增量排序)
    sortByBubble(list, n); //起泡排序
    sortByQuick(list, n); //快速排序
    sortByStraightSelect(list, n); //直接选择排序
    sortByHeap(list, n); //堆排序
    sortByMerge(list, n); //归并排序（这里是二路归并排序
    sortByCounting(list, n); //计数排序
    sortByBucket(list, n); //桶排序
    sortByRadixSort(list, n, 0); //基数排序
    
//    showBinSearch(2);
//    showIndexSearch(2, 11);
    
    return 0;
}

