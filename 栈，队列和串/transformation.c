/**
 * 文件名：使用堆栈进行数制转换
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
 
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10   //一次增加10的空间
#define ERROR 0
#define OK 1
 
typedef int Status;
typedef int Elemtype;
typedef struct Stack {
	Elemtype *top;
	Elemtype *base;
	int StackSize;
}*Sqstack;
 
//构建一个栈//
void InitStack(Sqstack s) {
	s->base = (Elemtype *)malloc(STACK_INIT_SIZE * sizeof(Elemtype));
	if (!s->base)
		exit(ERROR);
	s->top = s->base;
	s->StackSize = STACK_INIT_SIZE;
}
 
//入栈操作//
Status Push(Sqstack s, Elemtype e) {
	//将e的内容入栈
	//如栈满则追加空间
	if (s->top - s->base >= s->StackSize) {
		//两个地址相减实际上结果是地址差除以每个元素的地址值,也就是元素个数
		//这里实际上等于才是边界条件，因为我们的栈top指向空白的空间
		s->base = (Elemtype *)realloc(s->base, (s->StackSize + STACKINCREMENT) * sizeof(Sqstack));
		if (!s->base)
			exit(ERROR);
		s->top = s->base + s->StackSize;
		s->StackSize = s->StackSize + STACKINCREMENT;
	}
	*(s->top) = e;//将e放入内存空间
	s->top++;     //top继续加一，指向没使用的空间
	return OK;
}
 
//出栈操作//
Status Pop(Sqstack s, Elemtype *e) {
	//出栈之后将元素返回给e
	//判断栈是否为空栈
	if (s->top == s->base)
		//此时栈是空栈
		return ERROR;
	s->top--; //top先减一，指向有元素的内存单元
	*e = *(s->top);
	return OK;
}
 
//清空栈//
Status ClearStack(Sqstack s) {
	//实际上就是把头指针赋值给尾指针
	s->top = s->base;
	return OK;
}
 
//销毁一个栈//
Status DestoryStack(Sqstack s) {
	//销毁一个栈就是要清空栈的内存空间
	int i, len;
	len = s->StackSize;
	for (i = 0; i < len; i++) {
		free(s->base);
		s->base++;
	}
	s->base = s->top = NULL;
	s->StackSize = 0;
	return OK;
}
 
//栈内元素个数//
int Stacklen(Sqstack s) {
	return (s->top - s->base);
}



int main()
{
	Sqstack s = (Stack *)malloc(1 * sizeof(Sqstack));
	InitStack(s);
	int a[8] = { 1,1,0,0,1,0,0,1 };
	int b,c=0;//b用来存放结果,c用来存放十进制结果
	for (int i = 0; i < 8; i++) 
		//8次入栈操作
		Push(s, a[i]);
	for (int i = 0; i < 8; i++) {
		//8次出栈操作
		Pop(s, &b);//b就是出栈的数
		//二进制从最低位开始出来
		c += b * pow(2, i); 
	}
	printf("转换成十进制数:%d", c);
    return 0;
}