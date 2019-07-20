#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

int main(){
    sqList L;
    L.data[1] = 8;
    L.data[2] = 7;
    L.data[3] = 6;
    L.data[4] = 5;
    L.data[5] = 4;
    L.data[6] = 3;
    L.data[7] = 2;
    L.data[8] = 1;
    L.length = 8;
    traverse(L);
    //InsertSort(L);
    //BInsertSort(L);
    //ShellSort(L, dlta, 3);
    //bubble(L);
    //QSort(L, 1, L.length);
    //EasySelect(L);
    //HeapSort(L);
    sqList SR = L;
    sqList TR;
    TR.length = 8;
    MSort(SR, TR, 1, 8);
    traverse(TR);
    return 0;
}