/**
    文件名：数组的顺序存储表示    
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAX_ARRAY_DIM 8     //数组的最大维度

#define OK 1
#define ERROR 0
#define UNDERFLOW -1
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;

typedef struct {
    ElemType  *base;    //数据基地址
    int       dim;      //数组的维度
    int       *bounds;  //存放数组每一维度的长度    
    int       *constants;   //存放数组每一位度的基本偏移地址
} array;

//初始化数组
Status InitArray(array &a, int dim, ...){
    if(dim<1 || dim>MAX_ARRAY_DIM){
        return ERROR;
    }
    a.dim = dim;
    a.bounds = (int *)malloc(dim*sizeof(int));
    if(!a.bounds){
        return ERROR;
    }
    int elemtotal = 1;  //计算元素总数
    va_list ap;
    va_start(ap, dim);
    for(int i=0; i<dim; i++){
        a.bounds[i] = va_arg(ap, int);
        if(a.bounds[i]<0){
            return UNDERFLOW;
        }
        elemtotal *= a.bounds[i];
    }
    va_end(ap);
    a.base = (int *)malloc(elemtotal * sizeof(ElemType));
    if(!a.base){
        return OVERFLOW;
    }
    a.constants = (int *)malloc(dim * sizeof(int));
    if(!a.constants){
        return OVERFLOW;
    }
    a.constants[dim-1] = 1; //这是每个数据元素的长度
    for(int i=dim-1; i>=0; i--){
        a.constants[i] = a.bounds[i+1] * a.constants[i+1];  //这个计算公式参考数组元素地址的映射函数
    }
    return OK;
}

//销毁数组
Status DestoryArray(array &a){
    if(!a.base){
        return ERROR;
    }
    free(a.base);
    a.base = NULL;
    if(!a.bounds){
        return ERROR;
    }
    free(a.bounds);
    a.bounds = NULL;
    if(!a.constants){
        return ERROR;
    }
    free(a.constants);
    a.constants = NULL;
    return OK;
}

//给出某个元素的相对地址，用off返回
Status Locate(array a, va_list ap, int &off){
    off = 0;
    int ind;
    for(int i=0; i<a.dim; i++){
        ind = va_arg(ap, int);
        if(ind<0 || ind>=a.bounds[i]){
            return OVERFLOW;
        }
        off += a.constants[i] * ind;
    }
    return OK;
}

//返回某个下标对应的元素值
Status Value(array a, ElemType &e, ...){
    va_list ap;
    va_start(ap, e);
    Status result;
    int off;
    if((result = Locate(a, ap, off)) <= 0){
        return result;
    }
    va_end(ap);
    e = *(a.base + off);
    return OK;
}

//赋值
Status Assign(array &a, ElemType &e, ...){
    va_list ap;
    va_start(ap, e);
    Status result;
    int off;
    if((result = Locate(a, ap, off)) <= 0){
        return result;
    }
    va_end(ap);
    *(a.base + off) = e;
    return OK;
}