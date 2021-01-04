//
//  BinBlockSearch.h
//  test
//
//  Created by Marshal on 2020/7/27.
//  Copyright © 2020 Marshal. All rights reserved.
//  顺序查找、二分法查找(或折半查找)和索引查找

#ifndef BinBlockSearch_h
#define BinBlockSearch_h
 
void orderSearch(int value);//顺序查找
void showBinSearch(int value); //折半查找，前提是有序的，乱序不合适（适合有序序列查找，例如：按照索引值查找）
//blockIndex块的索引，value查找内容值，每一块都是乱序的
void showIndexSearch(int blockIndex, int value); //索引的分块查找(顺序查找就可普通遍历和折半一样了),

#endif /* BinBlockSearch_h */
