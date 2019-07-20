/**
 * 文件名：链队列
 * 基本操作：
 * Status InitQueue(&Q)     //初始化一个空队列
 * Status DestoryQueue(&Q)  //销毁队列
 * Status EnQueue(&Q, e)    //将元素e入队
 * Status DeQueue(&Q, &e)   //出队
 * Status QueueEmpty(Q)     //探空操作
 * int QueueLength(Q)       //返回队列长度
 * Status GetHead(Q, &e)    //获取队头元素值
 * Status QueueTraverse(Q)  //遍历队列中元素
 */

#include <stdio.h>
#include <stdlib.h>

typedef int QElemType;
typedef int Status;

#define OK 1
#define ERROR 0
//队列的链式存储结构
typedef struct QNode{
    QElemType   data;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct {
    QueuePtr    front;  //队头指针
    QueuePtr    rear;   //队尾指针
}LinkQueue;

//初始化空队列
Status InitQueue(LinkQueue &Q){
    //构造一个空队列Q
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode)); //构造一个队头
    if(!Q.front){
        return ERROR;
    }
    Q.front->next = NULL;
    return OK;
}

//销毁队列
Status DestoryQueue(LinkQueue &Q){
    while(Q.front){
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return OK;
}

//插入元素e
Status EnQueue(LinkQueue &Q, QElemType e){
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if(!p){
        return ERROR;
    }
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}

//删除元素，并用e返回其值
Status DeQueue(LinkQueue &Q, QElemType &e){
    if(Q.front == Q.rear){  //队空
        return ERROR;
    }
    QueuePtr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if(Q.rear == p){    //如果删除的是队尾的话
        Q.rear = Q.front;
    }
    free(p);
    return OK;
}

//探空操作，如果为空就返回1，否则返回0
Status QueueEmpty(LinkQueue Q){
    if(Q.front == Q.rear){
        return 1;
    } else {
        return 0;
    }
}

//返回队列长度
int QueueLength(LinkQueue Q){
    if(Q.front == Q.rear){
        return 0;   //队空，就返回0
    }
    int length = 1;
    QueuePtr p = Q.front->next;
    while(p->next){
        p = p->next;
        length++;
    }
    return length;
}

//若队列不空则用e返回队头元素
Status GetHead(LinkQueue Q, QElemType &e){
    if(Q.front == Q.rear){  //队空
        return ERROR;
    }
    QueuePtr p = Q.front->next;
    e = p->data;
    return OK;
}

//遍历队列中的每个元素，从队头开始
Status QueueTraverse(LinkQueue Q){
    if(Q.front == Q.rear){
        printf("the queue is empty\n");
        return ERROR;
    }
    QueuePtr p = Q.front->next;
    while(p){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}