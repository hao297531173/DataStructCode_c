/*
    文件名：排序算法
    插入排序：直接插入排序，希尔排序
    交换排序：冒泡排序，快速排序
    选择排序：简单选择排序，堆排序
    归并排序
    基数排序
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int ElemType;

//线性表结构
typedef struct{
    ElemType data[MAXSIZE];
    int length;
}sqList;

//线性表的遍历
void traverse(sqList L){
    for(int i=1; i<=L.length; i++){
        printf("%d ", L.data[i]);
    }
    printf("\n");
}


/////////插入排序///////////////
//我们都是从小到大排序
//直接插入排序，时间复杂度n^2
void InsertSort(sqList &L){
    //从第二个元素开始插入
    for(int i=2; i<=L.length; i++){
        if(L.data[i] < L.data[i-1]){    //需要交换次序
            L.data[0] = L.data[i];      //设置哨兵
            L.data[i] = L.data[i-1];    
            //后移元素
            int j;
            for(j=i-2; L.data[i]>L.data[j]; j--){
                L.data[j+1] = L.data[j];    //后移元素
            }
            L.data[j+1] = L.data[0];
        }
    }
}

//折半查找版的直接插入排序
//在查找插入位置的时候时间复杂度为logn，查找n个就是nlogn
//但是关键字的移动次数还是不变
void BInsertSort(sqList &L){
    for(int i=2; i<=L.length; i++){
        if(L.data[i] < L.data[i-1]){
            L.data[0] = L.data[i];
            int high = i-1;
            int low = 1;
            int mid;
            while(low <= high){
                mid = (high + low)/2;
                if(L.data[mid] > L.data[0]){    //应该插入低半区
                    high = mid-1;
                } else {    //应该插入高半区
                    low = mid+1;
                }
            }//while
            //移动元素
            for(int j=i-1; j>=high+1; j--){
                L.data[j+1] = L.data[j];
            }
            L.data[high+1] = L.data[0];
        }
    }
}

//希尔排序
void ShellInsert(sqList &L, int dk){
    for(int i = dk+1; i<=L.length; i++){
        if(L.data[i] < L.data[i-dk]){
            L.data[0] = L.data[i];
            int j;
            for(j = i-dk; j>0 && L.data[0]<L.data[j]; j-=dk){
                L.data[j+dk] = L.data[j];
            }
            L.data[j+dk] = L.data[0];
        }
    }
}
//dlta[]是增量序列
int dlta[3] = {5, 3, 1};
void ShellSort(sqList &L, int dlta[], int t){
    for(int k=0; k<t; k++){
        ShellInsert(L, dlta[k]);
    }
}

////////交换排序/////////////
//冒泡排序
void bubble(sqList &L){
    for(int i=L.length; i>=2; i--){
        int flag = 1;
        for(int j=1; j<=i; j++){
            if(L.data[j] > L.data[j+1]){
                flag = 0;
                ElemType temp = L.data[j];
                L.data[j] = L.data[j+1];
                L.data[j+1] = temp;
            }
        }
        if(flag == 1){
            return;
        }
    }
}

//快速排序（真的挺快的）
//要让关键字左边的元素都比关键字小，右边的元素都比关键字大
int Partition(sqList &L, int low, int high){
    L.data[0] = L.data[low];    //暂存关键字
    while(low < high){
        while(low < high && L.data[high] >= L.data[0]) high--;
        L.data[low] = L.data[high];     //找到右边一个比关键字小的换到low位置
        while(low < high && L.data[low] <= L.data[0]) low++;
        L.data[high] = L.data[low];     //找到左边一个比关键字大的换到high位置
    }
    L.data[high] = L.data[0];   //此时low=high了
    return high;
}

void QSort(sqList &L ,int low, int high){
    if(low < high){
        int pivotloc = Partition(L, low, high);
        QSort(L, low, pivotloc-1);
        QSort(L, pivotloc+1, high);
    }
}

///////////选择排序///////////////
//简单选择排序(真的很简单)
void EasySelect(sqList &L){
    for(int i=1; i<L.length; i++){
        int j = i+1;
        int min = i;
        while(j<=L.length){
            if(L.data[j] < L.data[min]){
                min = j;        //找到最小元素的下标
            }
            j++;
        }
        if(min != i){   //交换
            ElemType temp = L.data[i];
            L.data[i] = L.data[min];
            L.data[min] = temp;
        }
    }
}

//堆排序(很快，但是不好想)
//从小到大排序要使用小根堆
void HeapAdjust(sqList &L, int s, int m){
    //本函数进入条件为，除了结点s之外都满足堆的定义
    //调整s使整棵树变成大根堆
    L.data[0] = L.data[s];
    for(int i=s*2; i<=m; i*=2){ //直接指向s的孩子结点
        if(i<m && L.data[i] < L.data[i+1]) i++; //选择最大的那个孩子结点
        if(L.data[0] > L.data[i]) break;    //s就应该在这里了
        L.data[s] = L.data[i];  //小的结点上去
        s = i;  //下一个待插入的结点是i，用s来指向
    }
    L.data[s] = L.data[0];
}

void HeapSort(sqList &L){
    //建大顶堆
    for(int i=L.length/2; i>=1; i--){   //从第一个有孩子结点的结点开始调整
        HeapAdjust(L, i, L.length);
    }
    for(int i=L.length; i>1; i--){
        ElemType temp = L.data[1];
        L.data[1] = L.data[i];
        L.data[i] = temp;
        HeapAdjust(L, 1, i-1);
    }
}

///////归并排序//////////
//需要两个数组
void Merge(sqList SR, sqList &TR, int i, int m, int n){
    int j, k;
    //k是TR指针，i是SR左半边指针，j是SR右半边指针
    for(j=m+1, k=i; i<=m && j<=n; k++){
        if(SR.data[i] < SR.data[j]) TR.data[k] = SR.data[i++];
        else TR.data[k] = SR.data[j++];
    }
    while(i<=m) TR.data[k++] = SR.data[i++];
    while(j<=n) TR.data[k++] = SR.data[j++];
}

void MSort(sqList SR, sqList &TR, int s, int t){
    sqList TR2; //注意这里需要在每一层递归写一个变量，用于记录归并的中间结果
    if(s == t) TR.data[s] = SR.data[s]; 
    else {
        int m = (s+t)/2;
        MSort(SR, TR2, s, m);
        MSort(SR, TR2, m+1, t);
        Merge(TR2, TR, s, m, t);
    }
}

//////////基数排序////////////
//好麻烦，不写了