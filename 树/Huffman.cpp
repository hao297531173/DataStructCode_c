/**
    文件名：哈夫曼树
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Elemtype;
typedef int Status;
//赫夫曼树结点定义
typedef struct HuffmanNode {
	Elemtype weight;  //用来记录结点的权重
	Elemtype id;	  //用来唯一标识结点
	struct HuffmanNode *lchild;
	struct HuffmanNode *rchild;
}*HuffmanTree;

//构建一颗赫夫曼树//
HuffmanTree CreateHuffmanTree(int a[],int n) {
	//返回指向根结点的指针
	//数组a代表每个结点的权重，n代表叶子结点个数
	int i, j;
	HuffmanTree *temp, T;
	//动态分配n个结点的内存空间,temp为指向这些地址空间的头指针
	temp = (HuffmanTree *)malloc(n * sizeof(HuffmanNode));
	//将数组a中的权值分配给每个结点
	for (i = 0; i < n; i++) {
		temp[i] = (HuffmanTree)malloc(sizeof(HuffmanNode));
		temp[i]->weight = a[i];
		temp[i]->id = i;
		temp[i]->lchild = temp[i]->rchild = NULL;
	}
	//构建哈夫曼树
	for (i = 0; i < n - 1; i++) {
		//构建哈夫曼树需要n-1次合并
		int little1 = -1, little2;//前者存放最小的数的下标，后者存放次小的
		for (j = 0; j < n; j++) {
			if (temp[j] != NULL && little1 == -1) {
				little1 = j;
				continue;
			}
			else if (temp[j] != NULL) {
				little2 = j;
				break;//找到了就可以跳出
			}
		}
		//将权值最小的两个数给little1,2
		for (j = little2; j < n; j++) {
			if (temp[j] != NULL) {
				if (temp[j]->weight < temp[little1]->weight) {
					little2 = little1;
					little1 = j; //将次小的给2，自己留更小的一个
				}
				else if (temp[j]->weight < temp[little2]->weight) {
					little2 = j;
				}
			}
		}
		//构造结点
		T = (HuffmanTree)malloc(sizeof(HuffmanNode));
		T->weight = temp[little1]->weight + temp[little2]->weight;//权值为两结点相加
		T->lchild = temp[little1];
		T->rchild = temp[little2];

		temp[little1] = T;   //将构造的结点插入队列中
		temp[little2] = NULL;//删去另外的两个结点
	}
	return T;
}

//用广义表的形式打印这棵树//
void printHuffmanTree(HuffmanTree T) {
	if (T) {
		printf("%d", T->weight);
		if (T->lchild != NULL || T->rchild != NULL) {
			//如果不是叶子结点则执行，如果是的话直接跳出
			//有一个小森林就会有一对括号,即执行这一步
			printf("(");
			printHuffmanTree(T->lchild); //先打印左子树
			printf(",");				 //左右子树中用逗号隔开	
			printHuffmanTree(T->rchild); //再打印右子树
			printf(")");
		}
	}
}

//递归进行赫夫曼编码//
void HuffmanCode(HuffmanTree T, int depth,char str[]) {
	static int code[100];//每次递归值都不会改变,但是一棵树遍历左右子树是值是会变的
	static int i = 0;
	if (T) {
		if (T->lchild == NULL && T->rchild == NULL) {
			//如果该结点是叶子结点的话
			printf("%c的哈夫曼编码为:",str[T->id]);
			i++;
			for (int i = 0; i < depth; i++) {
				printf("%d", code[i]);
			}
			printf("\n");
		}
		else {
			//如果不是叶子结点就进行数值写入
			//左子树写0，右子树写1，根结点写0
			code[depth] = 0;
			HuffmanCode(T->lchild, depth + 1,str);
			code[depth] = 1;  //此时同样深度的code发生了改变
			HuffmanCode(T->rchild, depth + 1,str);
		}
	}
}


//赫夫曼解码//
void HuffmanDecode(HuffmanTree T, char ch[], char str[]) {
	//ch为要解码的01串，str为解码后的字符串
	int i, num[1000];//num用来存放01码
	HuffmanTree temp = NULL;
	//进行存放01码
	for (i = 0; i < strlen(ch); i++) {
		if (ch[i] == 48)
			num[i] = 0;
		else if (ch[i] == 49)
			num[i] = 1;
	}
	//进行解码
	if(T) {
		i = 0;//用来记录01串长度
		while (i < strlen(ch)) {
			//当还没有解码完的时候
			temp = T;
			while (temp->lchild != NULL && temp->rchild != NULL) {
				//当不是叶子结点的时候都要继续
				if (num[i] == 0) {
					temp = temp->lchild;//如果是0就走左边
				}
				else {
					temp = temp->rchild;//如果是1就走右边
				}
				i++;
			}
			//退出的时候就找到了叶子结点,由temp指向
			printf("%c", str[temp->id]);//输出对应的字符
		}
	}
}

int main() {
	int a[53];
	int n = 53;
	char ch[1000];//用来接收01码
	char str[53];//用来存放字母
	for (int i = 65; i <= 90; i++) {
		//大写字母从A-Z
		str[i - 65] = i;
	}
	str[26] = 32;  //空格的ASCII码
	for (int i = 97; i <= 122; i++) {
		//小写字母从a-z
		str[26 + i - 96] = i;
	}
	for (int i = 0; i < 53; i++) {
		//权重值从1-53
		a[i] = i + 1;
	}
	HuffmanTree T;
	T = (HuffmanTree)malloc(sizeof(HuffmanNode));
	T = CreateHuffmanTree(a, n);
	printf("(");
	printHuffmanTree(T);
	printf(")\n");
	HuffmanCode(T, 0,str);
	printf("请输入您要解码的01值：");
	scanf("%s",ch);
	printf("解码的结果是：\n");
	HuffmanDecode(T, ch, str);
	return 0;
}