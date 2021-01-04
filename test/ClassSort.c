//
//  ClassSort.c
//  test
//
//  Created by Marshal on 2020/7/21.
//  Copyright © 2020 Marshal. All rights reserved.
//

#include "ClassSort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#import "LSlinkList.h"

//打印结果
void showSortResult(int list[], int length, const char *name) {
    if (name && strlen(name) > 0) {
        printf("%s:\n", name);
    }
    for (int i = 0; i < length; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

//用于copylist避免干扰
int * copyList(int ori[], int length) {
    int *list = (int *)calloc(length, sizeof(int));
    for (int i = 0; i < length; i++) {
        list[i] = ori[i];
    }
    return list;
}

#pragma mark --直接插入排序
void sortByStraightInsertion(int oriList[], int length) {
    int *list = copyList(oriList, length);
    for (int i = 1; i < length; i++) {
        int pre, current = list[i];
        for (pre = i - 1; pre >= 0 && list[pre] > current; pre--) {
            list[pre + 1] = list[pre];
        }
        list[pre + 1] = current;
    }
    showSortResult(list, length, "直接插入排序");
}

#pragma mark --希尔排序(缩小增量排序)
void sortByShell(int oriList[], int length) {
    int *list = copyList(oriList, length);
    //设置分组长度，每组对应的值分别别叫，然后缩小步长(这里默认每次步长减少为原来的一半)，直到为组长1结束，注意每次缩小间距的过程，插入排序的内比较过程也会跟着缩小
    for (int gap = length/2; gap > 0; gap /= 2) {
        for (int i = gap; i < length; i++) {
            int pre, current = list[i];
            for (pre = i - gap; pre >= 0 && list[pre] > current; pre -= gap) {
                list[pre + gap] = list[pre];
            }
            list[pre + gap] = current;
        }
    }
    showSortResult(list, length, "希尔排序");
}

#pragma mark --起泡排序
void sortByBubble(int oriList[], int length) {
    int *list = copyList(oriList, length);
    for (int i = 0; i < length; i++) {
//        int noSort = true;
        for (int j = 0, last = length - i - 1; j < last; j++) {
            if (list[j] > list[j + 1]) {
                int tem = list[j + 1];
                list[j + 1] = list[j];
                list[j] = tem;
//                noSort = false;
            }
        }
//        if (noSort) break; //可以最好情况优化为O(n)
    }
    showSortResult(list, length, "起泡排序");
}

#pragma mark --快速排序
//快排实际排序逻辑
void quickSortList(int list[], int low, int hight) {
    //如果大小不合适直接结束
    if (hight <= low) return;

    int l = low, h = hight; //保存始末位置用于变更
    int pri = list[l]; //选定初始值，用于作为中间值来分组
    do {
        //从后向前查找小于指定值的索引，赋值给最小值
        while (l < h && list[h] >= pri) h--;
        if (l == h) break;
        list[l] = list[h];
        //从前向后查找小于指定值的索引，赋值给最小值
        while (l < h && list[l] <= pri) l++;
        if (l == h) break;
        list[h] = list[l];
    } while (l < h);
    //当low和hight指针指向同一个索引的时候，一轮结束，然后递归划分
    list[l] = pri;
    quickSortList(list, low, l - 1);
    quickSortList(list, l + 1, hight);
}

//快速排序（以中间值隔离大小值的方式进行，在逐渐在大小值区域继续以中间值隔离）
void sortByQuick(int oriList[], int length){
    int *list = copyList(oriList, length);
    
    quickSortList(list, 0, length - 1);
    
    showSortResult(list, length, "快速排序");
}

#pragma mark --直接选择排序
void sortByStraightSelect(int oriList[], int length) {
    int *list = copyList(oriList, length);
    for (int i = 0; i < length; i++) {
        int min = i;
        for (int j = i + 1; j < length; j++) {
            if (list[min] > list[j]) {
                min = j;
            }
        }
        int tem = list[i];
        list[i] = list[min];
        list[min] = tem;
    }
    showSortResult(list, length, "直接选择排序");
}

#pragma mark --堆排序
//调整堆为正常堆（调整成大头堆，以便于选出最大的到最后）
void heapShift(int list[], int start, int end) {
    int ori = list[start]; //保存默认根节点的值
    int sub = start * 2 + 1; //表示的是根节点的第一个子节点
    //子节点索引要在需调整范围内
    while (sub <= end) {
        //右节点也不能大于索引，并且选出最小的一个和根节点比较
        if (sub < end && list[sub] < list[sub + 1]) sub++;

        if (ori >= list[sub]) break; //不比根节点小，结束

        list[start] = list[sub];
        start = sub; //更新，用于同步更新根节点，以便于保持堆结构
        sub = sub * 2 + 1;
    }
    list[start] = ori;
}

//堆排序（堆结构为完全二叉树结构，父节点和子节点与2有不解之缘，左子节点 = 父节点索引 * 2 + 1, 右子节点 = 父节点索引 * 2 + 2）
//首先了解堆的概念，堆分为大根堆和小根堆，就是根节点比子节点要大或者小，每个父节点都是这样（根节点的两个子节点大小以及各自子节点的孩子节点大小就不能作比较了）
void sortByHeap(int oriList[], int length) {
    int *list = copyList(oriList, length);

    //将原有数组调整成大头堆，由于调整是从父节点开始，根据其索引两倍关系，从一半开始调整到根节点即可形成大头堆
    //从最下面调整，那么当顶部大于底部子节点的时候，由于下方子节点已经堆结构了，所以可以直接结束，因此倒序调整最佳
    for (int i = length / 2; i >= 0; i--) { //length / 2因为完全二叉树子节点索引最小为2n+1，所以最小也得length/2才可能会有子节点
        heapShift(list, i, length -1);
    }
    for (int i = length - 1; i > 0; i--) {
        //第一个和最后一个交换，相当于选出最值到之后，每一轮会选出一个最值到后面
        int tem = list[i];
        list[i] = list[0];
        list[0] = tem;
        heapShift(list, 0, i - 1); //每次选出的最后一个不参与比较(可以看出是和选择排序逻辑很像)
    }

    showSortResult(list, length, "堆排序");
}

#pragma mark --归并排序
//list系统给的list, length列表长度， group当前组有几何，下次合并则结果组间隔为2倍
void mergeList(int list[], int temList[], int length, int group) {
    //当每组组长已经大于等于length的时候说明最后一波已经合并完毕了
    if (group >= length) return;

    int k = 0; //temList放入新数组的最后一个索引，开区间
    //按照组长，每次数组分成 两两一组 的 N 组（length / (2*group)）,一定要取到最后一组，不然最后一组合并不进去
    for (int i = 0, last = ceil(length /  (2 * group)); i <= last; i++) {
        //每 两两一组的开始和结束索引
        int start, startEnd, end, endEnd;
        start = 2 * i * group;
        startEnd = start + group > length ? length : start + group; //开区间
        end = startEnd;
        endEnd = end + group > length ? length : end + group;

        //如果是最后一组且为单组的情况不用合并了
        if (end > length) break;
        
        //把两两一组的新排序结果 有序合并保存到新数组中(这里是顺序表，如果是链表的话就不需要了，直接后者断链，插入到合适的位置即可，节省很多开销)
        for (; start < startEnd && end < endEnd; k++) {
            if (list[start] <= list[end]) {
                temList[k] = list[start++];
            }else {
                temList[k] = list[end++];
            }
        }
        //如果其中一组全部更新到新数组了，另一组剩下的也全部更新填充进去
        if (start >= startEnd) {
            while (end < endEnd) {
                temList[k++] = list[end++];
            }
        }else {
            while (start < startEnd) {
                temList[k++] = list[start++];
            }
        }
    }
    //更新原有list数组，就不使用新的了，毕竟重新创建释放数组也需要占用开销
    for (int i = 0; i < k; i++) {
        list[i] = temList[i];
    }
    mergeList(list, temList, length, group * 2);
}

//归并排序（二路归并）
void sortByMerge(int oriList[], int length){
    int *list = copyList(oriList, length);
    //首先吧每一个选项看成一组，然后两两有序合并，单数作为单独一个使用，如此反复（后边的会存在数量不一样的合并）,如此下去便可以得出最后结果（比较适用于链表操作）
    int temList[length];
    mergeList(list, temList, length,  1);
    
    showSortResult(list, length, "归并排序");
}

#pragma mark --计数排序
void sortByCounting(int oriList[], int length) {
    int *list = copyList(oriList, length);
    
    //分别计算出最大值和最小值， 用于确定k区间
    int min, max;
    min = max = 0;
    for (int i = 1; i < length; i++) {
        if (list[min] > list[i]) min = i;
        if (list[max] < list[i]) max = i;
    }
    min = list[min];
    max = list[max];
    if (min == max) {
        showSortResult(list, length, "计数排序");
        return;
    }
    int dk = max - min + 1; //间隔为最大值-最小值+ 1
    
    int temList[dk]; //创建k长度的池子，对应的索引为list对应值-min，并初始化基数问题
    for (int i = 0; i < dk; i++) {
        temList[i] = 0;
    }
    
    for (int i = 0; i < length; i++) {
        temList[list[i] - min]++;
    }
    
    int k = 0;
    for (int i = 0; i < dk; i++) {
        while (temList[i]-- > 0) {
            list[k++] = i + min;
        }
    }
    
    showSortResult(list, length, "计数排序");
}

#pragma mark --桶排序
//桶排序,和计数排序很像，只不过按照范围映射到了若干个桶里，节省了部分内存开销，需要用到动态数组不然可能空间复杂度要到O（n + k * n ）,即每个桶大小都是N
//如果不是数字分布比较均匀只是顺序打乱的数组，如果不是，不太建议使用这个排序，毕竟其原理就是为了平局分割开数组进行桶内排序，桶太密集的话会接近计数排序
void sortByBucket(int oriList[], int length) {
    int *list = copyList(oriList, length);
    
    //分别计算出最大值和最小值， 用于确定k区间
    int min, max;
    min = max = 0;
    for (int i = 1; i < length; i++) {
        if (list[min] > list[i]) min = i;
        if (list[max] < list[i]) max = i;
    }
    min = list[min];
    max = list[max];
    if (min == max) {
        showSortResult(list, length, "桶排序");
        return;
    }
    int dk = max - min; //中间间隔数
    
    int bucket = 5; //默认5个吧
    int bucketSize = ceil(dk / bucket) + 1;//因为可能存在整倍的问题
    
    //这里的数组没有优化，默认最长顺序表，可以自行优化，或者其他语言自带的数组
    LSListNode *p[bucket];
    
    for (int i = 0; i < bucket; i++) {
        p[i] = NULL;
    }
    for (int i = 0; i < length; i++) {
        int group = (list[i] - min) / bucketSize;
        //往对应组的数组内加入数据
        p[group] = pushNode(p[group], list[i]);
    }
    //然后对每个组内成员进行排序，在有序copy到原数组即可
    int k = 0;
    for (int i = 0; i < bucket; i++) {
        int count = getListCount(p[i]);
        
        //这里使用其他内排对一个桶进行内排序（这里直接先写一个冒泡吧，避免打印干扰）
        int temList[count];
        for (int j = 0; j < count; j++) {
            temList[j] = geListNode(p[i], j)->data;
        }
        for (int x = 0; x < count; x++) {
            for (int y = 0, last = count - x - 1; y < last; y++) {
                if (temList[y] > temList[y+1]) {
                    int tem = temList[y+1];
                    temList[y+1] = temList[y];
                    temList[y] = tem;
                }
            }
        }
        //按桶的顺序放到原数组
        for (int j = 0; j < count; j++) {
            list[k++] = temList[j];
        }
    }
    
    showSortResult(list, length, "桶排序");
}

#pragma mark --基数排序
void sortByRadixSort(int oriList[], int length, int maxBit) {
    int *list = copyList(oriList, length);
    
    if (maxBit < 1) {
        //如果不给最大值位数d,那么求出来
        maxBit = 0;
        for (int i = 1; i < length; i++) {
            if (list[maxBit] < list[i]) {
                maxBit = i;
            }
        }
        int max = list[maxBit];
        maxBit = 1;
        while (max / 10) {
            max /= 10;
            maxBit++;
        }
    }
    
    int d = 10; //1~10;
    LSListNode *queue[d];
    for (int i = 0; i < maxBit; i++) {
        //初始化每一组，避免出现干扰
        for (int x = 0; x < d; x++) {
            queue[x] = NULL;
        }
        int bitNumber = pow(10, i);
        for (int k = 0; k < length; k++) {
            int num = list[k] / bitNumber % 10;
            queue[num] = pushNode(queue[num], list[k]);
        }
        for (int k = 0, j = 0; k < d; k++) {
            LSListNode *q = queue[k];
            int count = getListCount(q);
            if (count < 1) continue;
            
            while (q) {
                list[j++] = q->data;
                q = shiftNode(q);
            }
        }
    }
    
    showSortResult(list, length, "基数排序");
}
