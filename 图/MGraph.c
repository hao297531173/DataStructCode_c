/*
    文件名：图的邻接矩阵表示
    包括：深度优先搜索，广度优先搜索
    prim算法的最小生成树
    Kruskal算法的最小生成树
    最短路径问题之Dijkstra算法
    最短路径问题之Floyd算法
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define MAXVEX 100      //最大顶点数
#define MAXEDGE 100     //最大边集数组值
#define INFINITY 65535  //表示无穷大
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

typedef char VertexType;//顶点类型
typedef int EdgeType;   //边上权值类型
//邻接矩阵结构//
typedef struct {
	VertexType vexs[MAXVEX];     //用于存放顶点信息
	EdgeType arc[MAXVEX][MAXVEX];//用于存放权值信息
	int Vertex_num, Edge_num;    //分别用于存放顶点数和边数
}MGraph;

//构建有向图//
void CreateMGraph(MGraph *G) {
	int i, j, k, w;
	printf("请输入图的顶点数:");
	scanf_s("%d", &G->Vertex_num);
	getchar();
	printf("请输入图的边数:");
	scanf_s("%d", &G->Edge_num);
	getchar();
	for (i = 0; i < G->Vertex_num; i++) {
		//读入顶点信息
		printf("请输入第%d个顶点信息:",i+1);
		scanf_s("%c", &G->vexs[i]);
		getchar();
	}
	//初始化邻接矩阵
	for (i = 0; i < G->Vertex_num; i++) {
		for (j = 0; j < G->Vertex_num; j++) {
			G->arc[i][j] = 0;
		}
	}
	for (i = 0; i < G->Vertex_num; i++) {
		for (j = 0; j < G->Vertex_num; j++) {
			if (j == i)
				continue;
			printf("请输入从%c到%c边的权值:",G->vexs[i], G->vexs[j]);
			scanf_s("%d", &w);
			G->arc[i][j] = w;  //赋值
		}
	}
}

//打印邻接矩阵//
void printMGraph(MGraph *G) {
	printf("\t");
	for (int i = 0; i < G->Vertex_num; i++) {
		printf("V%c\t", G->vexs[i]);
	}
	printf("\n\n");
	for (int i = 0; i < G->Vertex_num; i++) {
		printf("V%c\t", G->vexs[i]);
		for (int j = 0; j < G->Vertex_num; j++) {
			if (G->arc[i][j] == INFINITY)
				printf("∞\t");
			else
				printf("%d\t", G->arc[i][j]);
		}
		printf("\n\n");
	}
}

//邻接矩阵的深度优先遍历算法//
boolean visited[MAXVEX];//访问标志数组
void DFS(MGraph *G, int i) {
	//在图中，对下标为i的元素进行递归遍历
	int j;
	visited[i] = true;//表示访问过
	printf("%c\t", G->vexs[i]);//打印结点
	for (j = 0; j < G->Vertex_num; j++) {
		if ((G->arc[i][j] != INFINITY || G->arc[i][j] != 0) && visited[j] == false) {
			//如果对j号结点有通路，并且没有被访问过的话
			DFS(G, j);//递归访问j下标的元素
		}
	}
}
//深度优先遍历操作
void DFSTraverse(MGraph *G) {
	int i;
	for (i = 0; i < G->Vertex_num; i++) {
		//先对访问数组进行初始化
		visited[i] = false;
	}
	for (i = 0; i < G->Vertex_num; i++) {
		if (visited[i] == false) {
			DFS(G, i);//对未访问过的结点进行深度优先搜索遍历
		}
	}
}

//邻接矩阵的广度优先搜索遍历//
//BFS使用了队列
void BFSTraverse(MGraph *G) {
	int i, j;
	LinkQuene Q;
	Q = (LinkQuene)malloc(sizeof(LinkQuene));
	InitQuene(Q);
	for (i = 0; i < G->Vertex_num; i++) {
		visited[i] = false;
	}
	//接着开始遍历
	for (i = 0; i < G->Vertex_num; i++) {
		if (visited[i] == false) {
			//如果没有访问过
			visited[i] = true;//表示访问
			printf("%c\t", G->vexs[i]);
			InsertQuene(Q, i);//将i入队列
			while (QueneEmpty(Q) != 1) {
				//如果队列不空的话
				DeleteQuene(Q, &i);//出队列并且把值传给i
				for (j = 0; j < G->Vertex_num; j++) {
					if ((G->arc[i][j] != INFINITY || G->arc[i][j] != 0) && visited[j] == false) {
						//如果该边存在并且另一个结点没有被访问过
						visited[j] = true; //表示被访问过
						printf("%c\t", G->vexs[j]);
						InsertQuene(Q, j);//将j入队列
					}
				}
			}
		}
	}
}

//prim算法的最小生成树//
void minispanTree_prim(MGraph *G) {
	//adjvex表示最小权值边的起始顶点，j表示结束顶点
	int min, i, j, k;//会用到的变量
	int adjvex[MAXVEX];//用来存放边的其中一个顶点
	int lowcost[MAXVEX];//用来存放当前已经连通部分的最小权值(对应于adjvex中的顶点)
	lowcost[0] = 0;//初始化第一个数值为0，表示第一个顶点已经加入最小生成树
	adjvex[0] = 0;//第一个顶点下标
	for (i = 1; i < G->Vertex_num; i++) {
		lowcost[i] = G->arc[0][i];
		adjvex[i] = 0;//一开始最小生成树的顶点只有0
	}
	//初始化完成，接下来开始生成最小生成树
	for (i = 1; i < G->Vertex_num; i++) {
		//这里表示有n个顶点要弄出n-1条边(包括v0有n个顶点)
		min = INFINITY;//初始化最小值为无穷
		j = 1;
		k = 0;//k用于存放当前权值最小边的其中一个下标
		while (j < G->Vertex_num) {
			//循环出了第一个外的全部顶点
			if (lowcost[j] != 0 && lowcost[j] < min) {
				//寻找没有完成（不为0），并且是最小的顶点的下标
				//也就是在可接触的最小权值边(lowcost)中选一个最小的
				min = lowcost[j];
				k = j;
			}
			j++;
		}
		//此时，k存放的就是当前可以接触到的最小权值边的一个顶点
		//adjvex[k]记录的是当前所能接触到的最小权值边的另一个顶点
		printf("（%d,%d）\n", adjvex[k], k);
		lowcost[k] = 0;//表示这个顶点已经加入到最小生成树中
		//接下来要寻找新的可以接触到的最小权值边
		for (j = 1; j < G->Vertex_num; j++) {
			if (lowcost[j] != 0 && G->arc[k][j] < lowcost[j]) {
				//k表示新的最小生成树顶点，可以通过它来寻找最小权值边
				lowcost[j] = G->arc[k][j];
				adjvex[j] = k;//找到了之后要把其中一个顶点改为k,表示到k的最小权值边
			}
		}
	}
}

//Kruskal算法的最小生成树//
//定义边集数组
typedef struct {
	int begin;//开始顶点的下标
	int end;  //结束顶点的下标
	int weight;//边的权重
}Edge;
//生成边集数组
void Create_array(MGraph *G,Edge edges[]) {
	int i,j,count=0;
	for (i = 0; i < G->Vertex_num; i++) {
		for (j = i + 1; j < G->Vertex_num; j++) {
			//因为是无向图，所以只要遍历矩形的一半（对角线也排除了）
			if (G->arc[i][j] != 0 && G->arc[i][j] != INFINITY) {
				//如果边存在的话
				edges[count].begin = i;//开始顶点的下标
				edges[count].end = j;//结束顶点的下标
				edges[count].weight = G->arc[i][j];//该边的权重
				count++;
			}
		}
	}
	//接下来给边集数组排序(只会冒泡法了)
	//出循环时边集数组的数量是count-1
	//排序要求从小到大
	for (i = 0; i < count; i++) {
		for (j = i + 1; j < count; j++) {
			if (edges[i].weight > edges[j].weight) {
				//如果前一个小于后一个的话就交换位置
				Edge temp;
				temp = edges[i];
				edges[i] = edges[j];
				edges[j] = temp;
			}
		}
	}
	//打印边集数组
	printf("边集数组为：\n");
	printf("\tbegin\tend\tweight\n");
	for (i = 0; i < count; i++) {
		printf("edges[%d] %d\t%d\t%d\n", i, edges[i].begin, edges[i].end, edges[i].weight);
	}
}
//查询函数，用于查找如果加入这条边的话是否存在存在回路
int Find(int *parent, int f) {
	while (parent[f] > 0) {
		//大于零就表示该边已经加入了最小生成树
		//要通过该边结点来寻找其他的可以加入最小生成树的边
		f = parent[f];
	}
	return f;
}
//算法主体
void MiniSpanTree_Kruskal(MGraph *G) {
	int i, n, m;
	Edge edges[MAXEDGE];//用于存放边集数组
	int parent[MAXVEX];	//用于存放最小生成树的边，0表示还没有加入最小生成树
						//数组下标表示边的起始点下标，数组内的值表示边的结束点下标
	//先生成边集数组
	Create_array(G, edges);
	//初始化parent数组
	for (i = 0; i < G->Vertex_num; i++) {
		parent[i] = 0;
	}
	//接着循环遍历每一条边
	printf("生成最小生成树（Kruskal算法）：\n");
	for (i = 0; i < G->Edge_num; i++) {
		n = Find(parent, edges[i].begin);
		m = Find(parent, edges[i].end);
		if (n != m) {
			//不相等就表示不存在回路
			parent[n] = m;//表示加入最小生成树
			printf("（%d，%d） %d\n", edges[i].begin, edges[i].end, edges[i].weight);
		}
	}
}

//最短路径问题之Dijkstra算法//
typedef int Pathmatirx1[MAXVEX]; //用于记录最短路径所经过的路径下标
typedef int ShortPathTable1[MAXVEX];//用于记录起始点到下标顶点的最短路径权值

//算法主体
void ShortestPath_Dijkstra(MGraph *G, int v0, Pathmatirx1 *P, ShortPathTable1 *D) {
	int v, w, k, min;
	int final[MAXVEX];//用于记录顶点是否被纳入最短路径，纳入为1，否则为0
	for (v = 0; v < G->Vertex_num; v++) {
		final[v] = 0;
		(*D)[v] = G->arc[v0][v]; //填入v0与各点间的权值
		(*P)[v] = 0;			 //初始化路径
	}
	//初始化第一个顶点
	(*D)[v0] = 0;   //第一个顶点到第一个顶点的权值为0
	final[v0] = 1;  //表示第一个顶点已经加入最短路径
	//开始主循环，求v0到各个顶点的最短路径
	for (v = 1; v < G->Vertex_num; v++) {
		//从1号顶点开始
		min = INFINITY;
		for (w = 0; w < G->Vertex_num; w++) {
			if (final[w] == 0 && (*D)[w] < min) {
				//如果这个顶点没有加入最短路径并且v0到这个顶点的路径最短
				k = w;
				min = (*D)[w];
			}
		}
		//出循环的时候已经找到了目前可以达到的最短路径
		final[k] = 1;
		//接下来更新最短路径表
		for (w = 0; w < G->Vertex_num; w++) {
			if (final[w] == 0 && (min + G->arc[k][w]) < (*D)[w]) {
				//如果该顶点没有纳入最短路径并且v0到这个顶点路径比之前的要短的话
				(*D)[w] = min + G->arc[k][w];//更新最短路径（v0到w）
				(*P)[w] = k;				 //存放前驱顶点(k到w)
			}
		}
	}
	//打印最短路径
	printf("最短路径为：\n");
	for (v = 1; v < G->Vertex_num; v++) {
		printf("（%d，%d）\n", (*P)[v], v);
	}
}

//最短路径问题之Floyd算法//
typedef int Pathmatirx[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];

void ShortestPath_Floyd(MGraph *G, Pathmatirx *P, ShortPathTable *D) {
	int v, w, k;
	//先初始化距离矩阵和路径矩阵
	for (v = 0; v < G->Vertex_num; v++) {
		for (w = 0; w < G->Vertex_num; w++) {
			(*D)[v][w] = G->arc[v][w]; //直接用权值初始化距离矩阵先
			(*P)[v][w] = w;            //用终点顶点的下标初始化路径矩阵
		}
	}
	//接下来开始主循环
	//最外层循环为中间路径
	//中间循环为起始点
	//最里层循环为终点
	for (k = 0; k < G->Vertex_num; k++) {
		for (v = 0; v < G->Vertex_num; v++) {
			for (w = 0; w < G->Vertex_num; w++) {
				if ((*D)[v][w] > (*D)[v][k] + (*D)[k][w]) {
					//如果经过中间点的距离更短的话
					(*D)[v][w] = (*D)[v][k] + (*D)[k][w];
					(*P)[v][w] = (*P)[v][k];  //这是路径v到w的下一个顶点是v到k所存顶点
				}
			}
		}
	}
	//打印距离矩阵
	printf("距离矩阵为：\n");
	printf("\t");
	for (v = 0; v < G->Vertex_num; v++) {
		printf("V%c\t", G->vexs[v]);
	}
	printf("\n\n");
	for (v = 0; v < G->Vertex_num; v++) {
		printf("V%c\t",G->vexs[v]);
		for (w = 0; w < G->Vertex_num; w++) {
			printf("%d\t", (*D)[v][w]);
		}
		printf("\n\n");
	}
	printf("\n\n");
	//打印路径矩阵
	printf("路径矩阵为：\n\t");
	for (v = 0; v < G->Vertex_num; v++) {
		printf("V%c\t", G->vexs[v]);
	}
	printf("\n\n");
	for (v = 0; v < G->Vertex_num; v++) {
		printf("V%c\t",G->vexs[v]);
		for (w = 0; w < G->Vertex_num; w++) {
			printf("%d\t", (*P)[v][w]);
		}
		printf("\n\n");
	}
	printf("\n");
	//打印最短路径
	for (v = 0; v < G->Vertex_num; v++) {
		for (w = v + 1; w < G->Vertex_num; w++) {
			printf("V%d-V%d weight：%d\t", v, w, (*D)[v][w]);
			k = (*P)[v][w];
			printf("Path：V%d", v);
			while (k != w) {
				//当k不是终点的时候
				printf(" -> V%d", k);//打印下一个顶点
				k = (*P)[k][w];     //继续寻找下一个顶点
			}
			printf(" -> V%d", w);
			printf("\n");
		}
		printf("\n");
	}
}

int main()
{
	MGraph *G;
	G = (MGraph *)malloc(sizeof(MGraph));
	CreateMGraph(G);
	system("cls");
	printf("图的邻接矩阵为：\n");
	printMGraph(G);
	//hsystem("pause");
	/*printf("深度优先搜索遍历的结果是：\n");
	DFSTraverse(G);
	printf("\n");
	printf("广度优先搜索的结果是：\n");
	BFSTraverse(G);*/
	//printf("生成的最小权值边（prim算法）：\n");
	//minispanTree_prim(G);
	//MiniSpanTree_Kruskal(G);
	Pathmatirx *P;
	ShortPathTable *D;
	P = (Pathmatirx *)malloc(sizeof(MAXVEX * MAXVEX));
	D = (ShortPathTable *)malloc(sizeof(MAXVEX * MAXVEX));
	//ShortestPath_Dijkstra(G, 0, P, D);
	ShortestPath_Floyd(G, P, D);
    return 0;
}