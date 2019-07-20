/**
* 文件名：串的堆分配表示与实现
 */

#include <stdio.h>
#include <stdlib.h>

//串的堆分配结构
typedef struct {
    char *ch;
    int length;
} HString;

typedef int Status;

#define OK 1
#define ERROR 0

//串的复制
Status StrAssign(HString &T, char *chars){
    //生成一个其值等于串常量chars的串T
    if(T.ch){   //如果T串有值，则先将其释放
        free(T.ch);
    }
    int length = 0; //用于记录chars的长度
    for(char *c = chars; *c; c++, length++);   //计算串chars的长度
    if(!length){    //如果是空串
        T.ch = NULL;
        T.length = 0;
    } else {
        T.ch = (char *)malloc(length * sizeof(char));
        if(!T.ch){
            return ERROR;
        }
        for(int i=0; i<length; i++){
            T.ch[i] = chars[i];
        }
        T.length = length;
    }
    return OK;
}

//返回串的长度
int StrLength(HString S){
    return S.length;
}

//比较两个串S和T，若S>T，则返回值>0，若S=T，则返回0，所S<T，则返回值<0
int StrCompare(HString S, HString T){
    //先比较字符
    for(int i=0; i<S.length && i<T.length; i++){
        if(S.ch[i]!=T.ch[i]){
            return S.ch[i] - T.ch[i];
        }
        return S.length - T.length;
    }
}

//将串S清空
Status ClearString(HString &S){
    if(S.ch){
        free(S.ch);
    }
    S.length = 0;
    return OK;
}

//将S1和S2连接并用T返回
Status Concat(HString &T, HString S1, HString S2){
    if(T.ch){
        free(T.ch);
    }
    T.ch = (char *)malloc((S1.length+S2.length) * sizeof(char));
    if(!T.ch){
        return ERROR;
    }
    for(int i=0; i<S1.length; i++){
        T.ch[i] = S1.ch[i];
    }
    for(int i=0; i<S2.length; i++){
        T.ch[S1.length+i] = S2.ch[i];
    }
    T.length = (S1.length + S2.length);
    return OK;
}

//返回串S从pos-1开始长度为len的子串
Status SubString(HString &sub, HString S, int pos, int len){
    if(pos<1 || len<0 || pos>S.length || len > S.length-pos+1){
        //开始位置错误 || 长度错误 || 开始位置大于字符串长度 || 所需长度大于可以提供长度
        return ERROR;
    }
    if(sub.ch){
        free(sub.ch);
    }
    if(!len){   //是空串
        sub.ch = NULL;
        sub.length = 0;
    } else {
        sub.ch = (char *)malloc(len*sizeof(char));
        for(int i=0; i<len; i++){
            sub.ch[i] = S.ch[pos-1+i];
        }
        sub.length = len;
    }
    return OK;
}