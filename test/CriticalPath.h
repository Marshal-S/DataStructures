//
//  CriticalPath.h
//  test
//
//  Created by Marshal on 2020/9/21.
//  Copyright © 2020 Marshal. All rights reserved.
//  关键路径，基于拓扑排序

#ifndef CriticalPath_h
#define CriticalPath_h

/*
 1. 首先初始化每个顶点的最早开始为0，然后对AOE网进行拓扑排序，在排序的过程中获取每个顶点的最早开始时间；
 2. 获取拓扑排序后，初始化每个顶点的最晚开始时间为汇点的最早开始时间，并从AOE网的汇点开始，从后往前，对每个顶点找到求其最晚开始时间；
 3. 遍历图中的每条边（方法是遍历图中每个顶点的边表），求其最早开始时间和最晚开始时间，如果二者相等，则这是个关键活动，将其加入关键路径中。
 
 Ve(j)：表示事件(顶点)的最早开始时间，在不推迟整个工期的前提下，表示从源点开始到该节点的需要的最长时间
 Vl(j)：表示事件(顶点)的最晚开始时间，在不推迟整个工期的前提下，表示从结束顶点到该点最短需要多少时间
 e(i)：表示活动(边)的最早开始时间，其实就是活动边的起点的最早发生时间, 表示该边起点的最早开始时间
 l(i)：表示活动(边)的最晚开始时间，其实就是该活动边起点的最晚发生时间，表示该边起点的最晚开始事件

 在得知以上四种统计数据后，就可以直接求得AOE关键路径上的所有的关键活动
 方法是：对于所有的边来说，如果它的最早开始时间等于最晚开始时间，称这条边所代表的活动为关键活动。由关键活动构成的路径为关键路径。
 由关键活动连接构成的路径就是关键路径了(可能会有多个路径)
*/
 
void showCriticalPath(void);//关键路径，通过拓扑排序保存到当前节点的时长，然后比较得出关键路径

#endif /* CriticalPath_h */