#include<iostream>
#include<windows.h>
using namespace std;
 
#define MAXSIZE 100
#define ERROR 0
#define OK 1
 
typedef char Elemtype;//这里修改数组的数据类型
typedef int Status;
 
 
/*
	算法描述：
	1.每个格子都按照右上左右的顺序检查下一步要走的格子
	2.b数组存放当前信息，0表示x坐标1表示y坐标，2表示走过该格子的次数
	3.若检测到该格子可以走并且没走过则入栈并且走上这个格子
	4.假如遇到了思路不能走了就退栈返回原来的道路重新寻找新的道路
	5.一开始就设定一个胜利坐标，假如走到了这个胜利坐标就算胜利
*/
 
 
 
 
/*堆栈测试成功*/
//栈数据结构
//我们规定top指向栈顶元素，bottom为空，当top==bottom的时候栈空
typedef struct Stack {
	int coord[MAXSIZE][3];  //0表示x坐标，1表示y坐标，2表示走过这个格子的次数
	int top, bottom;        //这里bottom和top赋初值为-1，这样就可以从0开始填入数据
}*st;
 
//初始化堆栈并且把数组元素都变为0,top和bottom赋初值为-1
Status init_s(st s) {
	for (int i = 0; i < MAXSIZE; i++) {
		for (int j = 0; j < 3; j++) {
			s->coord[i][j] = 0;
		}
	}
	s->top = s->bottom = -1;
	return OK;
}
 
//判断栈是不是为空栈，如果是空栈返回0，否则返回1
Status empty(st s) {
	if (s->top == s->bottom) {
		return ERROR;//栈空
	}
	else {
		return OK;
	}
}
 
//入栈操作
//先top++然后写入数据
//c数组用来存储当前可以写入的坐标
Status push(st s, int c[3]) {
	s->top++;
	if (s->top >= MAXSIZE) {
		cout << "栈满，已经不可以继续让里面添加元素了" << endl;
		s->top--;
		return ERROR;
	}
	cout << "三个值分别是：";
	for (int i = 0; i < 3; i++) {
		s->coord[s->top][i] = c[i];
		cout << c[i];
	}
	return OK;
}
 
//出栈操作
//先弹出top指向的元素，然后top--
//b数组用来存储当前位置的xy和行走次数
Status pop(st s,int b[3]) {
	if (empty(s) == 0) {
		//如果栈空的话就不能弹栈
		cout << "栈空，无法弹出" << endl;
		return ERROR;
	}
	else {
		//出栈操作，把退出的坐标赋值给当前坐标数组
		for (int i = 0; i < 3; i++) {
			b[i] = s->coord[s->top][i];
		}
		s->top--;
		return OK;
	}
}
//显示堆栈所有内容
void test(st s) {
	int t = s->top;
	cout << "堆栈里面的内容如下：" << endl;
	cout << "x,y" << endl;
	while (t != -1) {
		cout << s->coord[t][0] << "," << s->coord[t][1]<<endl;
		t--;
	}
}
 
 
/*地图绘制和打印测试成功*/
//传进一个二维数组，并且x，y代表要打印的行数和列数
//count代表已经走过的步数，b_x  b_y表示当前位置
void print(Elemtype a[100][100], int x, int y,int b_x,int b_y) {
	int i, j;
	for (int h = 0; h < y; h++) {
		cout << " -- ";
	}
	cout << endl;
	for (i = 0; i < x; i++) {
		for (j = 0; j < y; j++) {
			if (j == 0) {
				cout << "|";
			}
			if (a[i][j] == 'e') {
				if (i == b_x && j == b_y) {
					cout << " " << "P" << " |";
				}
				else {
					cout << "   |";
				}
			}
 
			else {
				cout << " " << a[i][j] << " |";
			}
		}
		cout << endl;
		for (int h = 0; h < y; h++) {
			cout << " -- ";
		}
		cout << endl;
	}
	//cout << "当前步数：" << count << endl;
	cout << "当前位置：(" << b_x << " , " << b_y << ")" << endl;
}
 
//绘制迷宫
void draw(Elemtype a[100][100]) {
	for (int i = 0; i <= 8; i++) {
		for (int j = 0; j <= 8; j++) {
			a[i][j] = '#';
		}
	}
	a[1][4] = a[1][3] = a[1][1] = 'e'; //e表示是可以走的地方
	a[2][1] = a[2][3] = 'e';
	a[3][1] = a[3][2] = a[3][3] = a[3][4] = 'e';
	a[4][4] = 'e';
	a[5][1] = a[5][2] = a[5][3] = a[5][4] = a[5][5] = 'e';
	a[6][4] = a[6][6] = 'e';
	a[7][4] = a[7][5] = a[7][6] = a[7][7] = 'e';
	a[7][8] = '$';                      //$表示是终点
	//print(a, 9, 9);
}
 
//初始化步数数组，start_x和start_y是一开始所在的格子
void init_c(int c[100][100], int start_x,int start_y) {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			c[i][j] = 0;
		}
	}
	c[start_x][start_y] = 1;
}
 
//判断是否胜利，如果当前位置就是终点的话就是胜利，返回1，否则返回0
int victory(Elemtype a[100][100], int b[3]) {
	if (a[b[0]][b[1]] == '$') {
		return 1;
	}
	else {
		return 0;
	}
}
 
//判断是否死亡，如果回到了原点就代表死亡
//start_x代表开始的x坐标，start_y代表开始的y坐标
//死亡返回0，未死亡返回1
int die(int start_x, int start_y, int b[3]) {
	if (b[0] == start_x && b[1] == start_y) {
		//回到了原点代表死亡
		return 0;
	}
	else {
		return 1;
	}
}
 
//运行主程序，决定下一步该怎么走
/*
	右 x,y+1
	上 x-1,y
	左 x,y-1
	下 x+1,y
*/
//数组c用来记录每个格子都过的次数
void run(Elemtype a[100][100],int c[100][100],int b[3],st s) {
	//往右边检查,如果可以走并且没有走过的话就可以走
	//可以走的话就要把当前位置入栈，然后走，刷新地图
	if ((a[b[0]][b[1] + 1] == 'e'|| a[b[0]][b[1] + 1] == '$' )&& c[b[0]][b[1] + 1] == 0) {
		int d[3] = {b[0],b[1]+1,1};
		push(s, b);
		for (int i = 0; i < 3; i++) {
			b[i] = d[i];
		}
		c[d[0]][d[1]]++;
		system("cls");
		print(a, 9, 9, b[0], b[1]);
		test(s);
		return;
	}
	//往上边检查
	if ((a[b[0] - 1][b[1]] == 'e'|| a[b[0] - 1][b[1]] == '$')&&c[b[0] - 1][b[1]] == 0) {
		int d[3] = {b[0]-1,b[1],1};
		push(s, b);
		for (int i = 0; i < 3; i++) {
			b[i] = d[i];
		}
		c[d[0]][d[1]]++;
		system("cls");
		print(a, 9, 9, b[0], b[1]);
		test(s);
		return;
	}
	//往左边检查
	if ((a[b[0]][b[1]-1] == 'e'|| a[b[0]][b[1] - 1] == '$')&&c[b[0]][b[1]-1] == 0) {
		int d[3] = { b[0],b[1]-1,1 };
		push(s, b);
		for (int i = 0; i < 3; i++) {
			b[i] = d[i];
		}
		c[d[0]][d[1]]++;
		system("cls");
		print(a, 9, 9, b[0], b[1]);
		test(s);
		return;
	}
	//往下边检查
	if ((a[b[0]+1][b[1]] == 'e'|| a[b[0] + 1][b[1]] == '$')&&c[b[0] + 1][b[1]] == 0) {
		int d[3] = { b[0] + 1,b[1],1 };
		push(s, b);
		for (int i = 0; i < 3; i++) {
			b[i] = d[i];
		}
		c[d[0]][d[1]]++;
		system("cls");
		print(a, 9, 9, b[0], b[1]);
		test(s);
		return;
	}
	//走到这里就说明没有路可以走了，这时候要回溯
	//从堆栈里退栈然后继续这一步
	pop(s, b);//b里储存的就是栈顶的位置
	c[b[0]][b[1]]++;  //退栈之后那一格的步数加一
	system("cls");
	print(a, 9, 9, b[0], b[1]);
	test(s);
}
 
int main()
{
	int count = 0;//记录走过的步数
	char a[100][100];
	draw(a);
	st s = (Stack *)malloc(sizeof(Stack));
	init_s(s);
	int b[3] = { 1,1,1 };//从1,1开始，并且在这个格子呆过一个回合
	int c[100][100];//记录步数的数组
	init_c(c, 1, 1);
	run(a, c, b, s);
	cout << "当前步数为：" << ++count << endl;
	Sleep(500);
	//system("pause");
	while (victory(a, b) == 0) {
		if (die(1, 1, b) == 0) {
			cout << "又回到最初的起点，这是个走不出去的迷宫~" << endl;
			return 0;
		}
		Sleep(500);
		//system("pause");
		run(a, c, b, s);
		cout << "当前步数为：" << ++count << endl;
	}
	//出来就说明获得了胜利
	cout << "成功走出了迷宫！！" << endl;
	return 0;
}
