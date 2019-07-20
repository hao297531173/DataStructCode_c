/**
 * 文件名：线性表的链式存储结构
 * 基础操作：
 * LinkList InitHeadList()      //初始化头结点
 * Status GetElem(L, i, &e)     //查找链表中第i个元素，并用e返回其值
 * Status ListInsert(&L, i, e)  //在链表中第i个位置插入元素
 * Status ListDelete(&L, i, &e) //删除链表中第i个位置的元素
 * void CreateList(&L, n)       //从尾部开始构造链表
 * void MergeList(&La, &Lb, &Lc)  //将两个有序链表合并，用La来作为头结点
 * 线性表的链式存储的优点：
 * 逻辑上相邻的结点物理上可以不相邻，这让是的增加删除和修改比较方便
 * 缺点：查找只能按照顺序来查
 */

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;   //定义数据类型
typedef int Status;

#define OK 1
#define ERROR 0


//线性表的单链表存储结构
typedef struct LNode{
    ElemType    data;       //数据域
    struct LNode *next;     //指针域
}LNode, *LinkList;

//初始化链表，返回头结点
LinkList InitHeadList(){
    LinkList L;
    L = (LinkList)malloc(sizeof(LNode));    //生成新结点
    L->data = 0;
    L->next = NULL;
    return L;
}

//在链表中查找第i个元素，用e返回其数据域的值
//L为链表的头结点，不存数据
Status GetElem(LinkList L, int i, ElemType &e){
    LinkList p = L->next;
    int j = 1;  //用于计数
    while(p && j<i){    //退出条件为p为NULL或者j>=i
        p = p->next;
        j++;
    }
    if(!p || j>i){      //!p表示没有那么多元素，j>i表示输入的位置不合法，比1小
        return ERROR;
    }
    e = p->data;
    return OK;
}

//在链表的第i个位置之前插入元素
Status ListInsert(LinkList &L, int i, ElemType e){
    LinkList p = L;
    int j = 0;
    while(p && j<i-1){
        p = p->next;
        j++;
    }
    if(!p || j>i-1){
        return ERROR;
    }
    LinkList s = (LinkList)malloc(sizeof(LNode));   //生成新结点
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

//删除链表中第i个元素，并用e返回其值
Status ListDelete(LinkList &L, int i, ElemType &e){
    LinkList p = L;
    int j = 0;
    while(p->next && j<i-1){    //搜索到第i-1个元素并且保证第i个元素存在
        p = p->next;
        j++;
    }
    if(!(p->next) && j>i-1){
        return ERROR;
    }
    LinkList q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    return OK;
}

//从尾部结点开始，逐个输入结点值从而构造链表
void CreateList(LinkList &L, int n){
    L = InitHeadList(); //初始化头结点
    for(int i=0; i<n; i++){
        LinkList p = (LinkList)malloc(sizeof(LNode));
        scanf("%d", &p->data);
        p->next = L->next;
        L->next = p;
    }
}

//将两个有序表La和Lb合并
//已知单链表La和Lb按照非递减顺序排序
void MergeList(LinkList &La, LinkList &Lb, LinkList &Lc){
    LinkList pa = La->next;
    LinkList pb = Lb->next;
    LinkList pc = La;       //用La的头结点作为新链表的头结点
    Lc = pc;
    while(pa && pb){    //pa和pb都存在的情况下
        if(pa->data < pb->data){
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        } else {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa?pa:pb;        //直接将剩余部分插入链表中
    free(Lb);
}