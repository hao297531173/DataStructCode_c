 /**
 * 文件名：顺序存储的线性表
 * 基本操作：
 * InitList(&L)    //构造一个空的线性表L
 * DestoryList(&L) //删除一个线性表
 * ClearList(&L)   //将线性表重置为空表
 * ListEmpty(L)    //线性表的探空操作
 * ListLength(L)   //返回L中元素的个数
 * GetElem(L, i, &e)    //查找并返回第i个元素
 * LocateElem(L, e, compare())  //线性表中第一个满足compare的元素
 * PriorElem(L, cur_e, &pre_e)  //若cur_e是线性表中元素且不是第一个，则用pre_e返回它的前驱
 * NextElem(L, cur_e, &next_e)  //若cur_e是线性表中元素且不是最后一个，则用pre_e返回它的后继
 * ListInsert(&L, i, e)         //在第i个元素之前(i-2)插入新元素e
 * ListDelete(&L, i, &e)        //删除L的第i个元素，并用e返回其值
 * ListTraverse(L, visit())     //对每个元素用visit()进行遍历 
 * 下面的两个操作是书上对线性表应用的举例
 * union(&La, Lb)               //将Lb中不属于La的元素插入La中
 * MergeList(La, Lb, &Lc)       //假设La和Lb都有序，将他们归并成Lc并且也有序
 * 特点：
 * 顺序结构的线性表可以直接访问某个位置的元素
 * 但是如果内存空间不够的话需要重新分配内存，比较麻烦
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef  int  ElemType;   //这一行用来定义数据类型
typedef  int  Status;     //用来返回操作状态，成功返回1，失败返回0

#define OK  1
#define FAILED 0
#define TRUE 1
#define FALSE 0

#define LIST_INIT_SIZE  100 //线性表存储空间的初始分配量
#define LIST_INC  10        //线性表存储空间每次增加的空间数量

typedef struct {
    ElemType    *elem;  //存储空间基址
    int         length; //当前长度（元素个数）
    int         listsize;   //当前分配的存储容量
}List, *L;

//构造一个新的线性表
Status InitList(List &L){
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L.elem){
        printf("malloc failed\n");
        return FAILED;
    }
    L.length = 0;   //当前链表中没有元素
    L.listsize = LIST_INIT_SIZE;    //链表长度赋初值
    return OK;
}//InitList

//删除一个线性表
Status DestoryList(List &L){
    free(&L);
    return OK;
}//DestoryList

//将线性表变成一个空表
//将所有单元初始化为0
Status ClearList(List &L){
    for(int idx = 0; idx < L.length; idx++){
        L.elem[idx] = 0;
    }
    return OK;
}

//线性表的探空操作
Status ListEmpty(List L){
    if(L.length == 0){
        return TRUE;    //线性表是空的
    } else if(L.length == 1){
        return FALSE;   //线性表不是空的
    }
}

//返回L中元素的个数
int ListLength(List L){
    return L.length;
}

//返回链表中下标为i的元素
ElemType GetElem(List L, int i){
    if(L.length < i){
        printf("Get error\n");
        return -1;
    }
    return L.elem[i];
}

//查找线性表中第一个和e相等的元素，并且返回其下标号
//如果没有找到就返回-1
int LocateElem(List L, ElemType e){
    if(ListEmpty(L) == TRUE){
        //线性表是空的
        printf("the list is empty\n");
        return -1;
    }
    for(int idx = 0; idx<L.length; idx++){
        if(L.elem[idx] == e){
            return idx;
        }
    }
    printf("can not find e in list\n");
    return -1;
}

//找e的前驱元素，如果存在则返回其下标
//如果不存在则返回-1
int PriorElem(List L, ElemType e){
    if(ListEmpty(L) == TRUE){
        printf("ths list is empty\n");
        return -1;
    }
    for(int idx = 0; idx<L.length; idx++){
        if(L.elem[idx] == e){
            if(idx == 0){
                printf("e has no prior in ths list\n");
            } else {
                return (idx-1);
            }
        }
    }
    printf("can not find prior of e\n");
    return -1;
}

//找e的后继元素
int NextElem(List L, ElemType e){
    if(ListEmpty(L) == TRUE){
        printf("ths list is empty\n");
        return -1;
    }
    for(int idx = 0; idx<L.length; idx++){
        if(L.elem[idx] == e){
            if(idx+1 >= L.length){  //这里其实只要等于就行了
                printf("e has no next in ths list\n");
            } else {
                return (idx+1);
            }
        }
    }
    printf("can not find next of e\n");
    return -1;
}

//插入元素
//在位置i插入元素，并且将i及i后的所有元素后移一位
Status ListInsert(List &L, ElemType e, int i){
    if(i > L.length){   //插入位置太后面了，必须按照顺序来
        printf("insert error\n");
        return FAILED;
    }
    if(L.length >= L.listsize){ //内存空间不够，需要重新分配内存
        ElemType* newBase = (ElemType *)realloc(L.elem, (L.listsize+LIST_INC)*sizeof(ElemType));
        if(!newBase){
            printf("realloc failed\n");
            return FAILED;
        }
        L.elem = newBase;
        L.listsize += LIST_INC;
    }
    if(i == L.length){  //如果是插入在最后一个位置，那么直接插入就行了
        L.elem[i] = e;
        return OK;
    }
    for(int idx = L.length-1; idx>=i; idx--){
        L.elem[idx] = L.elem[idx+1];
    }
    L.elem[i] = e;
    L.length++;
    return OK;
}

//删除下标为i的元素，并用e返回
//后面元素前移一格
Status ListDelete(List &L, int i, ElemType &e){
    if(i >= L.length){
        printf("there is no such elem\n");
        return FAILED;
    }
    e = L.elem[i];
    for(int idx = i+1; idx<L.length; idx++){
        L.elem[idx] = L.elem[i-1];
    }
    L.elem[L.length-1] = 0;
    L.length--;
    return OK;
}

//遍历线性表中所有元素
Status ListTraverse(List L){
    if(L.length == 0){
        printf("there is no elem in the list\n");
        return FAILED;
    }
    for(int idx = 0; idx<L.length; idx++){
        if(idx != 0){
            printf(" ");
        }
        printf("%d", L.elem[idx]);
    }
    printf("\n");
    return OK;
}

//将Lb中不属于La的元素插入La中
Status ListUnion(List &La, List Lb){
    int La_len = ListLength(La);
    int Lb_len = ListLength(Lb);
    for(int i = 0; i < Lb_len; i++){
        ElemType e = GetElem(Lb, i);
        if(LocateElem(La, e) != -1){    //在线性表La中没有这个元素
            //则将e插入线性表中
            ListInsert(La, e, La_len);
        }
    }
    return OK;
}

//假设La和Lb都有序，将他们归并成Lc并且也有序
//假设是按照递增的顺序排序的
Status MergeList(List La, List Lb, List &Lc){
    InitList(Lc);   //初始化Lc
    int La_len = ListLength(La);
    int Lb_len = ListLength(Lb);
    int i=0, j=0;
    int idx = 0;    //这是Lc线性表的指针
    while((i<La_len) && (j<Lb_len)){    //La和Lb均非空
        ElemType ea = GetElem(La, i);
        ElemType eb = GetElem(Lb, j);
        if(ea < eb){
            ListInsert(Lc, ea, idx++);
            i++;
        } else {
            ListInsert(Lc, eb, idx++);
            j++;
        }
    }
    while(i<La_len){
        ElemType ea = GetElem(La, i);
        ListInsert(Lc, ea, idx++);
        i++;
    }
    while(j<Lb_len){
        ElemType eb = GetElem(Lb, j);
        ListInsert(Lc, eb, idx++);
        j++;
    }
    return OK;
}