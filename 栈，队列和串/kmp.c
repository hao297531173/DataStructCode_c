/**
    文件名：kmp算法
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  OK  1
#define  ERROR  0
#define MAXSIZE 20

typedef char Elemtype;
typedef char String;
typedef int Status;
 
//截取字符串//
Status SubString(String a[], int pos,int t,String b[]) {
	//对字符串a，取从pos开始且长度为t的子串传给b
	//这里的pos是值数组元素下标
	int i, j;
	if (strlen(a) < t - pos) {
		printf("字符串长度过小");
		return ERROR;
	}
	for (i = pos,j =0 ; t > 0; t--,i++,j++) {
		b[j] = a[i];
	}
	b[j] = '\0';//这一步一定要有，没有的话就会变成烫
	return OK;
}
 
//模式匹配的暴力算法//
Status Brute_Force(String a[], String b[], int pos) {
	//在a中pos之后寻找b的子串，找到的话返回元素下标，否则返回0
	int n, m, i;
	String sub[255];
	if (pos > 0) {
		//我们之后第0号元素都存放字符串长度
		n = strlen(a);
		m = strlen(b);
		i = pos;
		while (i <= n - m + 1) {
			//n-m+1为i可以寻找的元素下标的最大范围
			SubString(a, i, m, sub);
			if (strcmp(sub, b) != 0) {
				//如果截取的字符串和子串不等的话
				i++;
			}
			else {
				//如果找到了的话
				printf("匹配的位置开始坐标为%d\n", i);
				return i;
			}
		}
		//运行到这里代表没找到
		printf("\n不匹配\n");
		return ERROR;
	}
}
 
//KMP算法//
//next数组的实现
void get_next(String b[],int *next) {
	//next函数0号元素不存放数据
	//1号元素存放的是0
	//从二号元素开始判定前面字符串最大匹配前后缀的字母个数,并且吧个数加一存放入数组中
	//i表示后缀，j表示前缀
	//如果T[i]==T[j],i和j就加一，并且next[i]=j,这是因为这里已经判定了最大匹配前后缀
	//如果不匹配的话，j就要回溯到当前元素失配时的第一个指导元素
	//然后再进行判断
	//在整个过程中，前缀是固定的，而后缀是相对的
	int i = 1, j = 0;//i是后缀，j是前缀
	printf("b[0]=%d\n", b[0]);
	next[1] = 0;   //这个别忘了
	while (i < b[0]) {
		//0号元素存放字符串长度,所以总长度要减一
		
		if (j == 0 || b[i] == b[j]) {
			//如果这两个值相等的话，代表后一个元素的next值为最大匹配前后缀j加一
			i++;
			j++;
			next[i] = j;
		}
		else {
			//如果不相等或者j没有退回到0（也就是不会i处的next值不等于1）
			//回溯
			j = next[j];
		}
	}
}

//改进之后的next函数
void get_nextval(String b[], int *nextval) {
	//实际上这个算法就是将原先next数组中的重复的比较部分直接删除
	//因为假如i3!=j3,j2!=j3,那么i3!=j2
	int i = 1, j = 0;//i为后缀，j为前缀
	nextval[1] = 0;
	while (i < b[0]) {
		//实际上i-1的时候计算的是i+1的next数组值
		if (j == 0 || b[i] == b[j]) {
			i++;
			j++;
			if (b[i] != b[j]) {
				//如果加一了之后不相等，和之前的一样
				nextval[i] = j;
			}
			else {
				//如果相等的话
				nextval[i] = nextval[j];//这样就不用重复比较了
			}
		}
		else {
			//回溯
			j = nextval[j];
		}
	}
}

//KMP算法主函数
Status Index_KMP(String a[], String b[], int pos) {
	//在a中查询pos之后的能与b匹配的串的首地址
	//如果存在就返回首地址
	//否则返回0
	//0号元素存放的是字符串的长度(包括0号元素)
	int i = pos;
	int j = 1;//这个用来指向主串
	int next[MAXSIZE];
	get_nextval(b, next);//获得next数组值
	while (i <= a[0] && j <= b[0]) {
		//在两个指针都不越界的情况下
		if (j == 0 || b[j] == a[i]) {
			//前一个条件代表第一个元素都不匹配，则增加一个元素
			//后一个条件代表匹配，则继续下一次的匹配
			//当j等于b[0]时实际上匹配已经结束，这里为了加一之后的判定匹配成功
			i++;
			j++;
			printf("%c == %c\n", b[j], a[i]);
		}
		else {
			j = next[j];//回溯
			printf("回溯到%d\n", j);
		}
	}
	//跳出循环的时候如果j大于子串长度则表示匹配
	if (j > b[0]) {
		printf("匹配到的首地址为%d", (i - b[0]));
		return i - b[0];
	}
	else {
		printf("没有匹配项");
		return ERROR;
	}
}

int main()
{ 
	String a[255], b[255];
	strcpy(a, "5abcde");
	strcpy(b, "2cd");
	b[0] = 2;
	a[0] = 5;   //这里必须写成int型才能比较大小，否则比较的是ASCII码
	Index_KMP(a, b, 1);
    return 0;
}
 