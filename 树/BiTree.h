/*
    文件名：二叉树和线索二叉树
*/
#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;

typedef int Status;
typedef int TElemType;

#define OK 1
#define ERROR 0

//二叉树的顺序存储表示
#define MAX_TREE_SIZE 100       //二叉树的最大结点数
typedef TElemType SqBiTree[MAX_TREE_SIZE];  //0号单元存储根结点


//二叉树的二叉链表存储表示
typedef struct BiTNode{
    TElemType   data;
    struct BiTNode *lchild, *rchild;    //左右孩子指针
}BiTNode, *BiTree;

//按照先序遍历的顺序构建二叉树
Status CreateBiTree(BiTree &T){
    TElemType ch;
    scanf("%d", &ch);
    if(ch == ' '){
        T = NULL;
    } else {
        T = (BiTNode *)malloc(sizeof(BiTNode));
        if(!T){
            return ERROR;
        }
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return OK;
}

Status visit(BiTree T){
    printf("%d\n", T->data);
    return OK;
}

//二叉树的递归先序遍历
Status PreorderTraverse(BiTree T){
    if(T){
        if(!visit(T)){
            return ERROR;
        }
        PreorderTraverse(T->lchild);
        PreorderTraverse(T->rchild);
    }
    return OK;
}

//二叉树的递归中序遍历
Status InorderTraverse(BiTree T){
    if(T){
        InorderTraverse(T->lchild);
        if(!visit(T)){
            return ERROR;
        }
        InorderTraverse(T->rchild);
    }
    return OK;
}

//二叉树的递归的后序遍历
Status PostorderTraverse(BiTree T){
    if(T){
       PostorderTraverse(T->lchild);
       PostorderTraverse(T->rchild);
       if(!visit(T)){
           return ERROR;
       }
    }
    return OK;
}

//二叉树非递归算法的中序遍历
Status InOrder(BiTree T){
    stack<BiTree> s;
    s.push(T);
    BiTree p;
    while(!s.empty()){  //当栈不空的时候
        p = s.top();
        while(p){       //疯狂地将左子树入栈
            s.push(p->lchild);
        }
        s.pop();    //将空指针出栈
        if(!s.empty()){
            p = s.top();
            s.pop();    //别忘了要出栈
            if(!visit(p)){
                return ERROR;
            }
            s.push(p->rchild);
        }
    }
    return OK;
}

//二叉树中序遍历的非递归写法的第二种写法
Status InOrder_(BiTree T){
    stack<BiTree> s;
    BiTree p = T;
    while(p || s.empty()){  //当p不为空或者栈不空
        if(p){
            s.push(p);
            p = p->lchild;
        } else {
            p = s.top();
            s.pop();
            if(!visit(p)){
                return ERROR;
            }
            p = p->rchild;      //访问完了之后就要访问右子树
        }
    }
    return OK;
}


//二叉树的二叉线索存储表示
//线索二叉树一般都有一个头结点，其lchild指向二叉树的根节点
//rchild指向遍历的最后一个结点
typedef enum pointerTag {Link, Thread};    //Link=0表示是孩子结点，Thread=1表示是前驱或者后继
typedef struct BiThrNode{
    TElemType data;
    struct BiThrNode *lchild, *rchild;
    pointerTag LTag, RTag;
}BiThrNode, *BiThrTree;

//重载访问函数
Status visit(BiThrTree T){
    printf("%d\n", T->data);
    return OK;
}


//线索二叉树的中序遍历
Status InorderThr_Traverse(BiThrTree T){
    BiThrTree p = T->lchild;    //指向二叉树的根结点
    while(p != T){  //还没有遍历完
        while(p->LTag == Link) p = p->lchild;   //一直找找到最下面的左子树
        if(!visit(p)){          //访问这个结点
            return ERROR;
        }
        while(p->RTag == Thread && p->rchild != T){ //后继存在并且不是头结点
            p = p->rchild;
            visit(p);
        }
        p = p->rchild;
    }
    return OK;
}

//线索二叉树的线索化操作
//中序遍历线索化
//线索化的前提是已经构建好了一棵二叉树
BiThrTree pre;  //我们需要一个指向前驱的全局变量
Status InThreading(BiThrTree p);
Status InorderThrThreading(BiThrTree &Thrt, BiThrTree T){
    //先构建头结点
    Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
    if(!Thrt){
        return ERROR;
    }
    Thrt->LTag = Link;  //指向根结点
    Thrt->RTag = Thread;
    Thrt->rchild = Thrt;    //指向自己先
    if(!T){
        Thrt->lchild = Thrt;    //如果是空树，则指向自己
    } else {
        Thrt->lchild = T;
        pre = Thrt; //指向前驱
        InThreading(T);
        pre->rchild = Thrt;     //将最后一个结点线索化
        pre->RTag = Thread;
        Thrt->rchild = pre;
    }
    return OK;
}

Status InThreading(BiThrTree p){
    if(p){
        InThreading(p->lchild); //左子树线索化
        if(!p->lchild){ //左子树空，则将lchild指向其前驱
            p->LTag = Thread;
            p->lchild = pre;    
        }
        if(!pre->rchild){
            pre->RTag = Thread;
            pre->rchild = p;
        }
        pre = p;
        InThreading(p->rchild); //右子树线索化
    }
    return OK;
}