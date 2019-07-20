/**
 * 文件名：静态链表
 * 本文件将使用一个例子来介绍静态链表：求(A-B)∪(B-A)，在书P31-34
 * 静态链表可以用在不提供指针的高级语言中，比如python
 */

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

#define MAXSIZE 100

//静态链表第0号单元作为表头
typedef struct {
    ElemType  data;     //数据域
    int        cur;     //指针域
}component, SLinkList[MAXSIZE];

//查找元素，如果找到返回其下标，如果没有找到返回0
int LocateElem(SLinkList s, ElemType e){
    int i = s[0].cur;   //指向第一个元素
    while(i && s[i].data != e){
        i = s[i].cur;
    }
    return i;
}

//初始化一个空的静态链表
void InitSpace(SLinkList &space){
    for(int i=0; i<MAXSIZE-1; i++){
        space[i].cur = i+1;
    }
    space[MAXSIZE-1].cur = 0;
}

//从空闲链表中分配一个空间，若分配成功则返回其下标，否则返回0
int Malloc(SLinkList &space){
    int i = space[0].cur;
    if(space[0].cur != 0){
        space[0].cur = space[i].cur;
    }
    return i;
}

//将一个元素插入空闲链表中
void Free(SLinkList &space, int k){
    space[k].cur = space[0].cur;
    space[0].cur = k;
}

//一次出入集合A与B，然后再一位数组中建立集合(A-B)∪(B-A)
void different(SLinkList &space, int &s){
    InitSpace(space);   //初始化备用空间
    s = Malloc(space);  //s指向头结点
    int r = s;          //r指向s的当前最后一个结点
    int a, b;           //分别存放A和B两个集合的元素个数
    scanf("%d %d", &a, &b);
    for(int i=0; i<a; i++){
        int j = Malloc(space);  //分配结点
        scanf("%d", &space[i].data);//输入集合A的元素
        space[r].cur = i;
        r = i;          //r一直指向最后一个元素
    }
    space[r].cur = 0;   //尾结点的指针为空
    int n;  //用于存放集合B的元素
    for(int i=0; i<b; i++){ //依次输入集合B的元素
        scanf("'%d", &n);
        int p = s;      //用于指向k元素的前驱元素
        int k = space[s].cur;   //k指向集合A的第一个元素
        while(k!=space[r].cur && space[k].data != n){
            p = k;              //指向k元素的前驱元素
            k = space[k].cur;
        }
        if(k == space[r].cur){  //当前链表中不存在该元素，需要插入
            int j = Malloc(space);
            space[i].data = n;
            space[i].cur = space[r].cur;
            space[r].cur = i;
        } else {    //链表中已经存在该元素，需要删除
            space[p].cur = space[k].cur;
            Free(space, k); //将其加入空闲链表
            if(r == k) r = p;   //如果删除的是r所指向的结点，择婿修改表尾指针
        }
    }
}


