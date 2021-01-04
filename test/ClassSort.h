//
//  ClassSort.h
//  test
//
//  Created by Marshal on 2020/7/21.
//  Copyright © 2020 Marshal. All rights reserved.
//  经典排序(可以参考图，部分不一样的可以参考算法本身，以前盗的图改了一改，注意使用不同语言，实现调整的情况可能空间和时间复杂度会变化)

#ifndef ClassSort_h
#define ClassSort_h

//他们的稳定不稳定表示的是排序后，值一样的情况，原有的顺序会不会被打破，未打破就代表稳定，否则不问题（例如：分数一样的小明和小白，他们本来录入顺序小明然后小白，不稳定的情况下，可能会出现先小白后小明）

//稳定：如果a原本在b前面，而a=b，排序之后a仍然在b的前面。
//不稳定：如果a原本在b的前面，而a=b，排序之后 a 可能会出现在 b 的后面。
//时间复杂度：对排序数据的总的操作次数。反映当n变化时，操作次数呈现什么规律。
//空间复杂度：是指算法在计算机内执行时所需存储空间的度量，它也是数据规模n的函数。

//*比较性排序*//
///插入排序
void sortByStraightInsertion(int list[], int length); //直接插入排序 O(n^2)
void sortByShell(int list[], int length); //希尔排序(缩小增量排序) O(nlog2n)~O(n^2)之间大约为n^1.5
///交换排序
void sortByBubble(int list[], int length); //起泡排序(冒泡排序) O(n^2)
void sortByQuick(int list[], int length); //快速排序 O(n)~O(n^2),平均为O(nlog2n)
///选择排序
void sortByStraightSelect(int list[], int length); //直接选择排序 O(n^2)
void sortByHeap(int list[], int length); //堆排序 最坏(也是平均) O(nlog2n)
//归并排序（可以多路归并排序）
void sortByMerge(int list[], int length); //归并排序（这里是二路归并排序,比较适用于链表操作） O(nlog2n)

//*非比较性排序*//   //其实仔细看计数排序和基数排序是不是有点借鉴散列表的思想
void sortByCounting(int list[], int length); //计数排序，适用整数 O(n+k) ---（k为最大最小值之间的间距 当输入的元素是n个0~k之间的整数时，或者是除了排序项其他都一样的情况），其排序速度快于任何比较排序算法。当最大值与最小值区间不是很大并且序列比较集中时，计数排序是一个很有效的排序算法
void sortByBucket(int list[], int length); //桶排序 O(n+k) --- k是桶个数，桶划分的越小，各个桶之间的数据越少，排序所用的时间也会越少。但相应的空间消耗就会增大
void sortByRadixSort(int list[], int length, int maxBit); //基数排序，适用整数 O(n*k*d)k十进制为例0~9,d数字位数  空间复杂度 O(n)就是一个索引大小的n空间


//打印结果
void showSortResult(int list[], int length, const char *name);

#endif /* ClassSort_h */
