#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
#define MAXSIZE 100

//链式前向星的存储结构
struct edge{
    int to;     //指向那个顶点
    int next;   //同起点的下一条边的编号
    int weight; //该边的权重
} edges[MAXSIZE];
int head[MAXSIZE];

//将head数组初始化为-1
void InitHead(){
    memset(head, -1, sizeof(head));
}

int sumE = 0;   //边的不编号，从0开始

//加边操作
void addEdge(int st, int ed, int we){
    edges[sumE].to = ed;
    edges[sumE].weight = we;
    edges[sumE].next = head[st];
    head[st] = sumE++;
}
//遍历链式前向星结构
void Traverse(){
    for(int i=0; i<MAXSIZE; i++){
        if(head[i] != -1){
            printf("head[%d]:", i);
            for(int j=head[i]; j!=-1; j=edges[j].next){
                printf("%d ", edges[j].to);
            }
            printf("\n");
        }
    }
}

int visited[MAXSIZE];

//深度优先遍历搜索
void DFS(int);
void DFSTraverse(){
    //初始化访问数组
    for(int i=0; i<MAXSIZE; i++){
        visited[i] = 0;
    }
    for(int i=0; i<MAXSIZE; i++){
        if(head[i] != -1 && visited[i] == 0){
            DFS(i);
        }
    }
}

void DFS(int n){
    if(visited[n] == 0){
        printf(" %d ", n);
    }
    visited[n] = 1; //表示访问过了
    for(int i=head[n]; i!=-1; i=edges[i].next){
        if(!visited[edges[i].to]){
            DFS(edges[i].to);
        }
    }
}


//广度优先搜索
void BFS(int);
void BFSTraverse(){
    //初始化访问数组
    for(int i=0; i<MAXSIZE; i++){
        visited[i] = 0;
    }
    for(int i=0; i<MAXSIZE; i++){
        if(head[i] != -1 && visited[i] == 0){
            BFS(i);
        }
    }
}

void BFS(int n){
    queue<int> q;
    q.push(n);
    if(visited[n] == 0)
        printf(" %d ", n);
    visited[n] = 1;
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(int i=head[v]; i!=-1; i=edges[i].next){
            if(!visited[edges[i].to]){
                printf(" %d ", edges[i].to);
                visited[edges[i].to] = 1;
                q.push(edges[i].to);
            }
        }
    }
}

int main(){
    InitHead();
    //存图
    addEdge(1, 2, 1);
    addEdge(1, 3, 1);
    addEdge(1, 4, 1);
    addEdge(2, 4, 1);
    addEdge(2, 5, 1);
    //反向再存一遍
    addEdge(2, 1, 1);
    addEdge(3, 1, 1);
    addEdge(4, 1, 1);
    addEdge(4, 2, 1);
    addEdge(5, 2, 1);
    Traverse();
    printf("DFS: ");
    DFSTraverse();
    printf("\nBFS: ");
    BFSTraverse();
    return 0;
}