/**
    文件名：图的邻接表表示
    包括深度优先搜索，广度优先搜索，关键路径和拓扑排序
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define MAXVEX 100
#define ERROR 0
#define OK 1

//队列的DAT//
typedef int Elemtype; //BFS中队列存放的是图元素下标
typedef int Status;
typedef struct QNode {
	Elemtype data;
	struct QNode *next;
}*QuenePrt;
typedef struct {
	QuenePrt front, rear;    //指针形式的对头和队尾指针
}*LinkQuene;

//构建一个队列//
Status InitQuene(LinkQuene q) {
	q->front = q->rear = (QNode *)malloc(sizeof(QNode));   //这个是头结点
	if (!q->front) {
		exit(ERROR);
	}
	q->front->next = NULL;
	return OK;
}

//插入队列操作//
Status InsertQuene(LinkQuene q, Elemtype e) {
	//将e插入到队列的队尾中
	//首先定义一个队列结点
	//然后将e复制给结点的数据域
	//然后队尾next指向该结点
	//最后队尾指针等于该节点
	QuenePrt p;
	p = (QNode *)malloc(sizeof(QNode));//申请链表的一个结点空间
	p->data = e;
	p->next = NULL;
	q->rear->next = p;
	q->rear = p;
	return OK;
}

//出队操作//
Status DeleteQuene(LinkQuene q, Elemtype *e) {
	//有三种情况
	//第一种，有很多元素，直接删除
	//第二种，只有一个元素，删除后front等于rear
	//第三种，没有元素，返回ERROE
	QuenePrt p;
	if (q->front == q->rear)
		return ERROR;
	p = q->front->next;
	*e = p->data;
	q->front->next = p->next;
	if (q->rear == p)
		q->rear = q->front;//如果只有一个结点那么尾结点指回头结点
	free(p);
	return OK;
}
//探空操作//
Status QueneEmpty(LinkQuene Q) {
	//如果是空队列返回1，否则返回0
	if (Q->front == Q->rear)
		return true;
	else
		return false;
}

typedef int Vertextype;
typedef int Edgetype;

//边表结构//
typedef struct EdgeNode {
	int adjvex;    //存储该结点对应下标
	Edgetype weight; //存储权重值
	struct EdgeNode *next;
}EdgeNode;

//顶点表结构//
typedef struct VertexNode {
	int in;
	Vertextype data;  //存储顶点信息
	EdgeNode *firstedge;  //头指针
}VertexNode,AdjList[MAXVEX];

//邻接表结构//
typedef struct {
	AdjList adjlist;  //顶点表数组
	int Vex_num, Edge_num;//顶点数和边数
}AdjGraph;

//构造顶点表,无向图//
void CreateGraph(AdjGraph *G) {
	int i, j, k, weight,none;//none用来判断是否是有向图
	EdgeNode *e;//用于动态内存分配
	printf("请输入图的顶点数量:");
	scanf_s("%d", &G->Vex_num);
	getchar();
	printf("请输入图的边的数量:");
	scanf_s("%d", &G->Edge_num);
	getchar();
	//建立顶点表,并且初始化头指针
	for (i = 0; i < G->Vex_num; i++) {
		printf("请输入第%d个顶点信息:",i+1);
		scanf_s("%d", &G->adjlist[i].data);
		getchar();
		printf("请输入第%d个顶点的入度：",i+1);
		scanf_s("%d", &G->adjlist[i].in);
		getchar();
		G->adjlist[i].firstedge = NULL;
	}
	//建立边表
	for (k =0 ; k < G->Edge_num; k++) {
		printf("请输入第%d条边（vi，vj）上的vi顶点序号:", k + 1);
		scanf_s("%d", &i);
		getchar();
		printf("请输入第这条边（vi，vj）上的vj顶点序号:");
		scanf_s("%d", &j);
		getchar();
		printf("请输入这条边的权重:");
		scanf_s("%d", &weight);
		getchar();
		printf("是否是单向边？（0表示不是，1表示是）:");
		scanf_s("%d", &none);
		getchar();
		//开始建立边表,使用头插法
		e = (EdgeNode *)malloc(sizeof(EdgeNode));
		e->adjvex = j;
		e->next = G->adjlist[i].firstedge;
		G->adjlist[i].firstedge = e;
		e->weight = weight;
		e = (EdgeNode *)malloc(sizeof(EdgeNode));
		if (none == 0) {
			//不是单向边的时候执行这段代码
			e->adjvex = i;
			e->next = G->adjlist[j].firstedge;
			G->adjlist[j].firstedge = e;
			e->weight = weight;
		}
	}
}

//打印邻接表//
void printAdjGraph(AdjGraph *G) {
	printf("in   data   adjvex  weight\n");
	EdgeNode *a = NULL;
	for (int i = 0; i < G->Vex_num; i++) {
		printf("%d", G->adjlist[i].in);
		printf("   V%d", G->adjlist[i].data);
		if (G->adjlist[i].firstedge != NULL) {
			//打印第一个边结点
			printf(" -->  ");
			printf("   %d      %d", G->adjlist[i].firstedge->adjvex, G->adjlist[i].firstedge->weight);
			a = G->adjlist[i].firstedge;//a指向第一个边界结点
		}
		else {
			printf("  NULL");
		}
		if (a != NULL) {
			while (a->next != NULL) {
				a = a->next;//指向下一个结点
				printf("\t-->");
				printf("   %d	    %d", a->adjvex, a->weight);
			}
		}
		printf("\n");
	}
}

//邻接表的深度优先搜索//
boolean visited[MAXVEX];//访问标志数组
void DFS(AdjGraph *G, int i) {
	EdgeNode *p;  //用来遍历边表
	visited[i] = true; //表示已经访问过了
	printf("%c\t", G->adjlist[i].data);//打印顶点
	p = G->adjlist[i].firstedge;
	while (p != NULL) {
		if (visited[p->adjvex] == false) {
			//如果这条边没有访问过
			DFS(G, p->adjvex);//进行递归
		}
		p = p->next;
	}
}
//接口函数
void AdjGraphTraverse(AdjGraph *G) {
	int i;
	for (i = 0; i < G->Vex_num; i++) {
		visited[i] = false;//对访问数组进行初始化
	}
	for (i = 0; i < G->Vex_num; i++) {
		if (visited[i] == false) {
			DFS(G, i);//如果没有访问过就进行访问
		}
	}
}

//邻接表的广度优先搜索//
//该算法用到了队列
void BFSTraverse(AdjGraph *G) {
	int i;
	EdgeNode *p = NULL;
	LinkQuene Q;//队列指针
	Q = (LinkQuene)malloc(sizeof(LinkQuene));
	InitQuene(Q);//初始化一个空队列
	for (i = 0; i < G->Vex_num; i++) {
		visited[i] = false;//初始化访问数组
	}
	//开始进行搜索
	for (i = 0; i < G->Vex_num; i++) {
		if (visited[i] == false) {
			//如果没有被访问过
			visited[i] = true;
			printf("%c\t", G->adjlist[i].data);//打印图元素信息
			InsertQuene(Q, i);//将元素下标入队
			while (QueneEmpty(Q) != 1) {
				//当队列不为空的时候
				DeleteQuene(Q, &i);//执行出队操作
				p = G->adjlist[i].firstedge;
				while (p != NULL) {
					if (visited[p->adjvex] == false) {
						//当这个元素没有被访问过的时候
						visited[p->adjvex] = true;
						printf("%d\t", G->adjlist[p->adjvex].data);
						InsertQuene(Q, p->adjvex);//将此顶点入队列
					}
					p = p->next;
				}
			}
		}
	}
}

//拓扑排序//
void TopologicalSort(AdjGraph *G) {
	EdgeNode *e;
	int i, k, gettop;
	int top = 0;//栈顶指针
	int count = 0;//计数器
	int *stack;
	stack = (int *)malloc(G->Vex_num * sizeof(int));//分配一个栈的内存空间
	for (i = 0; i < G->Vex_num; i++) {
		//将入度为0的结点都入栈
		if (G->adjlist[i].in == 0) {
			stack[++top] = i;//入栈
		}
	}
	printf("拓扑排序的结果为：\n");
	gettop = stack[top--];//取出栈顶元素
	printf("%d", G->adjlist[gettop].data);
	count++;//进行计数
	for (e = G->adjlist[gettop].firstedge; e; e = e->next) {
		//对该顶点弧表进行遍历减去入度
		k = e->adjvex;
		G->adjlist[k].in--;
		if (G->adjlist[k].in == 0) {
			//如果入度为0就入栈
			stack[++top] = k;
		}
	}
	while (top != 0) {
		//栈不空的话
		gettop = stack[top--];//取出栈顶元素
		printf(" -> %d", G->adjlist[gettop].data);
		count++;//进行计数
		for (e = G->adjlist[gettop].firstedge; e; e = e->next) {
			//对该顶点弧表进行遍历减去入度
			k = e->adjvex;
			G->adjlist[k].in--;
			if (G->adjlist[k].in == 0) {
				//如果入度为0就入栈
				stack[++top] = k;
			}
		}
	}
	printf("\n");
	if (count == G->Vex_num) {
		printf("该图无环路，拓扑排序完成\n");
	}
	else {
		printf("该图存在环路，拓扑排序失败\n");
	}
}

//关键路径//
int *etv, *ltv;//表示事件最早发生时间和时间最迟发生时间
int *stack2;//为最迟事件发生时间提供存储
int top2;//stack2的栈顶指针

//改进版的拓扑排序
void TopologiaclSortPro(AdjGraph *G) {
	EdgeNode *e;
	int i, k, gettop;
	int top = 0;
	int count = 0;
	int *stack1;//拓扑排序的栈
	stack1 = (int *)malloc(G->Vex_num * sizeof(int));
	for (i = 0; i < G->Vex_num; i++) {
		//初始化stack1堆栈
		if(G->adjlist[i].in == 0)
		stack1[++top] = i;
	}
	top2 = 0;
	etv = (int *)malloc(G->Vex_num * sizeof(int));//事件最早发生时间
	for (i = 0; i < G->Vex_num; i++) {
		etv[i] = 0;//初始化事件最早发生时间
	}
	stack2 = (int *)malloc(G->Vex_num * sizeof(int));
	printf("拓扑排序的结果为：\n");
	gettop = stack1[top--];
	count++;
	stack2[++top2] = gettop;//出栈了之后如stack2，为的是计算事件最晚开始时间
	printf(" %d", G->adjlist[gettop].data);
	for (e = G->adjlist[gettop].firstedge; e; e = e->next) {
		//这里实际上是检索所有入度为0顶点有关联的边
		k = e->adjvex;
		G->adjlist[k].in--;
		if (G->adjlist[k].in == 0) {
			//入栈
			stack1[++top] = k;
		}
		if (etv[gettop] + e->weight > etv[k]) {
			//最早开始时间应该是最大的那个路径，因为所有准备工作完成才能开始
			etv[k] = etv[gettop] + e->weight;
		}
	}
	while (top != 0) {
		//当stack1不空的时候
		gettop = stack1[top--];
		count++;
		stack2[++top2] = gettop;//出栈了之后如stack2，为的是计算事件最晚开始时间
		printf(" -> %d",G->adjlist[gettop].data);
		for (e = G->adjlist[gettop].firstedge; e; e = e->next) {
			//这里实际上是检索所有入度为0顶点有关联的边
			k = e->adjvex;
			G->adjlist[k].in--;
			if (G->adjlist[k].in == 0) {
				//入栈
				stack1[++top] = k;
			}
			if (etv[gettop] + e->weight > etv[k]) {
				//最早开始时间应该是最大的那个路径，因为所有准备工作完成才能开始
				etv[k] = etv[gettop] + e->weight;
			}
		}
	}
	if (count == G->Vex_num) {
		printf("\n没有回路，排序完成\n");
	}
	else {
		printf("\n存在回路，排序失败\n");
	}
	printf("事件最早开始时间为：\n");
	for (int i = 0; i < G->Vex_num; i++) {
		printf("V%d\t", i);
	}
	printf("\n");
	for (int i = 0; i < G->Vex_num; i++) {
		printf("%d\t", etv[i]);
	}
	printf("\n");
}

//关键路径
void CriticalPath(AdjGraph *G) {
	EdgeNode *e;
	int i, gettop, k, j, count = 0;
	int ete, lte;//活动最早发生时间和活动最晚发生时间
	TopologiaclSortPro(G);//排序，获得stack2堆栈
	ltv = (int *)malloc(G->Vex_num * sizeof(int));//事件最迟发生时间
	for (i = 0; i < G->Vex_num; i++) {
		//用汇点最早开始时间来初始化ltv
		ltv[i] = etv[G->Vex_num - 1];
	}
	printf("关键路径为：\n");
	while (top2 != 0) {
		//只要把stack2弹出干净就行了
		gettop = stack2[top2--];
		for (e = G->adjlist[gettop].firstedge; e; e = e->next) {
			//逐一往后退来计算事件最晚发生时间
			k = e->adjvex;
			if (ltv[k] - e->weight < ltv[gettop]) {
				//k表示从后面往前判定
				ltv[gettop] = ltv[k] - e->weight;
			}
		}
		//计算ete和lte来判断关键路径
		//这两个实际上就是边		
		for (j = 0; j < G->Vex_num; j++) {
			//从每个顶点出发
			for (e = G->adjlist[j].firstedge; e; e = e->next) {
				k = e->adjvex;
				ete = etv[j];//活动最早开始时间就是顶点的最早开始时间
				lte = ltv[k] - e->weight;
				count++;
				//如果两个相等代表这是关键路径
				if (ete == lte) {
					printf("V%d -> V%d  length：%d\n", G->adjlist[j].data, G->adjlist[k].data, e->weight);
				}
			}
		}
	}
	printf("\n");
	printf("事件最晚开始时间为：\n");
	for (int i = 0; i < G->Vex_num; i++) {
		printf("V%d\t", i);
	}
	printf("\n");
	for (int i = 0; i < G->Vex_num; i++) {
		printf("%d\t", ltv[i]);
	}
}

int main()
{
	AdjGraph *G;
	G = (AdjGraph *)malloc(sizeof(AdjGraph));
	CreateGraph(G);
	system("cls");
	printAdjGraph(G);
	//system("pause");
	//printf("深度优先搜索遍历的结果是:\n");
	//AdjGraphTraverse(G);
	//printf("\n");
	//printf("广度优先搜索遍历的结果是:\n");
	//BFSTraverse(G);
	//TopologicalSort(G);
	CriticalPath(G);
    return 0;
}