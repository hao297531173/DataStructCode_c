/*
    文件名：图的四种存储形式
*/

#include <stdio.h>
#include <stdlib.h>

//邻接矩阵
//分别存储两个矩阵
//一个矩阵用于存顶点的信息
//另一个矩阵用于存弧的信息
#define INFINITY   65535
#define MAX_VERTEX_NUM 20

typedef int VEType;
typedef int InforType;

typedef enum{DG, DN, UDG, UDN} GraphKind;   //图的类型{有向图，有向网，无向图，无向网}

//弧矩阵
typedef struct ArcCell {
    VEType adj; //顶点关系类型，对于无权图，用0或1表示连接与否
                //对于带权图，则为其权重值
    InfoType *info; //该弧相关信息指针
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

//顶点信息矩阵
typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];    //顶点向量
    AdjMatrix arcs;                     //邻接矩阵
    int  vexnum, arcnum;                //顶点数量和边的数量
    GraphKind kind;                     //图的种类标志
}MGraph;

//邻接表
//表结点  adjvex | nextarc | info
//头结点  data | firstarc

//边结点
typedef struct ArcNode{
    int adjvex;     //该弧所指向的顶点的位置
    struct ArcNode *next;   //下一个结点指针
    InfoType *info;
}ArcNode;

//顶点结点
typedef struct VNode{
    VertexType data;    //顶点信息
    ArcNode *firstarc;
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
    AdjList vertices;   //头结点数组
    int vexnum, arcnum; //顶点数和边数
    int kind;       //当前图的种类
}AlGraph;

//十字链表
//弧结点 tailvex | headvex | hlink | tlink | info
//顶点结点 data | firstin | firstout

typedef struct ArcBox {
    int tailvex, headvex;   //该弧的尾和头结点的位置
    struct ArcBox *hlink, *tlink;   //分别为弧头相同和弧尾相同的链域
    InfoType *info;     //该弧相关信息的指针
}ArcBox;

typedef struct VexNode {
    VertexType data;
    ArcBox *firstin, *firstout; //分别指向该顶点第一条入弧和第一条出弧
}VexNode;

typedef struct {
    VexNode xlist[MAX_VERTEX_NUM];  //表头向量
    int vexnum, arcnum;         //顶点数和弧数
}OLGraph;

//邻接多重表
//弧结点 mark | ivex | ilink | jvex | jlink | info
//顶点结点 data | firstedge

typedef enum{unvisited, visited} VisitIf;

typedef struct EBox {
    VisitIf mark;       //访问标记
    int  ivex, jvex;    //该边依附的两个顶点的位置
    struct EBox *ilink, *jlink; //分别指向依附这两个顶点的下一条边
    InfoType *info;
}EBox;

typedef struct VexBox{
    VertexType data;
    EBox *firstedge;    //指向第一条依附该顶点的边
}VexBox;

typedef struct {
    VexBox adjmulist[MAX_VERTEX_NUM];
    int vexnum, edgenum;    //当前顶点数和边数
}AMLGraph;