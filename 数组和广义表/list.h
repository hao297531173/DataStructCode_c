/*
    文件名：广义表的两种存储结构
*/

#include <stdio.h>
#include <stdlib.h>

//广义表的头尾链表存储表示
typedef int AtomType;

typedef enum{ATOM, LIST} ElemTag;   //ATOM=0表示原子，LIST=1表示子表
typedef struct GLNode{
    ElemTag tag;        //公共部分，用于区别是原子还是子表
    union {
        AtomType  atom; //原子结点的数据域
        struct {
            struct GLNode *hp, *tp;
        } ptr;      //子表的指针域，分别指向表头和表尾
    };
} *GList;

//广义表的扩展线性链表存储表示
typedef enum{ATOM, LIST} ElemTag;
typedef struct GLNode{
    ElemTag  tag;
    union {
        AtomType atom;
        struct GLNode *hp;
    };
    struct GLNode *tp;
} *GList;