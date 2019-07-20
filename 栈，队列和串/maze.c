#include<iostream>
#include<windows.h>
using namespace std;
 
#define MAXSIZE 100
#define ERROR 0
#define OK 1
 
typedef char Elemtype;//�����޸��������������
typedef int Status;
 
 
/*
	�㷨������
	1.ÿ�����Ӷ������������ҵ�˳������һ��Ҫ�ߵĸ���
	2.b�����ŵ�ǰ��Ϣ��0��ʾx����1��ʾy���꣬2��ʾ�߹��ø��ӵĴ���
	3.����⵽�ø��ӿ����߲���û�߹�����ջ���������������
	4.����������˼·�������˾���ջ����ԭ���ĵ�·����Ѱ���µĵ�·
	5.һ��ʼ���趨һ��ʤ�����꣬�����ߵ������ʤ���������ʤ��
*/
 
 
 
 
/*��ջ���Գɹ�*/
//ջ���ݽṹ
//���ǹ涨topָ��ջ��Ԫ�أ�bottomΪ�գ���top==bottom��ʱ��ջ��
typedef struct Stack {
	int coord[MAXSIZE][3];  //0��ʾx���꣬1��ʾy���꣬2��ʾ�߹�������ӵĴ���
	int top, bottom;        //����bottom��top����ֵΪ-1�������Ϳ��Դ�0��ʼ��������
}*st;
 
//��ʼ����ջ���Ұ�����Ԫ�ض���Ϊ0,top��bottom����ֵΪ-1
Status init_s(st s) {
	for (int i = 0; i < MAXSIZE; i++) {
		for (int j = 0; j < 3; j++) {
			s->coord[i][j] = 0;
		}
	}
	s->top = s->bottom = -1;
	return OK;
}
 
//�ж�ջ�ǲ���Ϊ��ջ������ǿ�ջ����0�����򷵻�1
Status empty(st s) {
	if (s->top == s->bottom) {
		return ERROR;//ջ��
	}
	else {
		return OK;
	}
}
 
//��ջ����
//��top++Ȼ��д������
//c���������洢��ǰ����д�������
Status push(st s, int c[3]) {
	s->top++;
	if (s->top >= MAXSIZE) {
		cout << "ջ�����Ѿ������Լ������������Ԫ����" << endl;
		s->top--;
		return ERROR;
	}
	cout << "����ֵ�ֱ��ǣ�";
	for (int i = 0; i < 3; i++) {
		s->coord[s->top][i] = c[i];
		cout << c[i];
	}
	return OK;
}
 
//��ջ����
//�ȵ���topָ���Ԫ�أ�Ȼ��top--
//b���������洢��ǰλ�õ�xy�����ߴ���
Status pop(st s,int b[3]) {
	if (empty(s) == 0) {
		//���ջ�յĻ��Ͳ��ܵ�ջ
		cout << "ջ�գ��޷�����" << endl;
		return ERROR;
	}
	else {
		//��ջ���������˳������긳ֵ����ǰ��������
		for (int i = 0; i < 3; i++) {
			b[i] = s->coord[s->top][i];
		}
		s->top--;
		return OK;
	}
}
//��ʾ��ջ��������
void test(st s) {
	int t = s->top;
	cout << "��ջ������������£�" << endl;
	cout << "x,y" << endl;
	while (t != -1) {
		cout << s->coord[t][0] << "," << s->coord[t][1]<<endl;
		t--;
	}
}
 
 
/*��ͼ���ƺʹ�ӡ���Գɹ�*/
//����һ����ά���飬����x��y����Ҫ��ӡ������������
//count�����Ѿ��߹��Ĳ�����b_x  b_y��ʾ��ǰλ��
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
	//cout << "��ǰ������" << count << endl;
	cout << "��ǰλ�ã�(" << b_x << " , " << b_y << ")" << endl;
}
 
//�����Թ�
void draw(Elemtype a[100][100]) {
	for (int i = 0; i <= 8; i++) {
		for (int j = 0; j <= 8; j++) {
			a[i][j] = '#';
		}
	}
	a[1][4] = a[1][3] = a[1][1] = 'e'; //e��ʾ�ǿ����ߵĵط�
	a[2][1] = a[2][3] = 'e';
	a[3][1] = a[3][2] = a[3][3] = a[3][4] = 'e';
	a[4][4] = 'e';
	a[5][1] = a[5][2] = a[5][3] = a[5][4] = a[5][5] = 'e';
	a[6][4] = a[6][6] = 'e';
	a[7][4] = a[7][5] = a[7][6] = a[7][7] = 'e';
	a[7][8] = '$';                      //$��ʾ���յ�
	//print(a, 9, 9);
}
 
//��ʼ���������飬start_x��start_y��һ��ʼ���ڵĸ���
void init_c(int c[100][100], int start_x,int start_y) {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			c[i][j] = 0;
		}
	}
	c[start_x][start_y] = 1;
}
 
//�ж��Ƿ�ʤ���������ǰλ�þ����յ�Ļ�����ʤ��������1�����򷵻�0
int victory(Elemtype a[100][100], int b[3]) {
	if (a[b[0]][b[1]] == '$') {
		return 1;
	}
	else {
		return 0;
	}
}
 
//�ж��Ƿ�����������ص���ԭ��ʹ�������
//start_x����ʼ��x���꣬start_y����ʼ��y����
//��������0��δ��������1
int die(int start_x, int start_y, int b[3]) {
	if (b[0] == start_x && b[1] == start_y) {
		//�ص���ԭ���������
		return 0;
	}
	else {
		return 1;
	}
}
 
//���������򣬾�����һ������ô��
/*
	�� x,y+1
	�� x-1,y
	�� x,y-1
	�� x+1,y
*/
//����c������¼ÿ�����Ӷ����Ĵ���
void run(Elemtype a[100][100],int c[100][100],int b[3],st s) {
	//���ұ߼��,��������߲���û���߹��Ļ��Ϳ�����
	//�����ߵĻ���Ҫ�ѵ�ǰλ����ջ��Ȼ���ߣ�ˢ�µ�ͼ
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
	//���ϱ߼��
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
	//����߼��
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
	//���±߼��
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
	//�ߵ������˵��û��·�������ˣ���ʱ��Ҫ����
	//�Ӷ�ջ����ջȻ�������һ��
	pop(s, b);//b�ﴢ��ľ���ջ����λ��
	c[b[0]][b[1]]++;  //��ջ֮����һ��Ĳ�����һ
	system("cls");
	print(a, 9, 9, b[0], b[1]);
	test(s);
}
 
int main()
{
	int count = 0;//��¼�߹��Ĳ���
	char a[100][100];
	draw(a);
	st s = (Stack *)malloc(sizeof(Stack));
	init_s(s);
	int b[3] = { 1,1,1 };//��1,1��ʼ��������������Ӵ���һ���غ�
	int c[100][100];//��¼����������
	init_c(c, 1, 1);
	run(a, c, b, s);
	cout << "��ǰ����Ϊ��" << ++count << endl;
	Sleep(500);
	//system("pause");
	while (victory(a, b) == 0) {
		if (die(1, 1, b) == 0) {
			cout << "�ֻص��������㣬���Ǹ��߲���ȥ���Թ�~" << endl;
			return 0;
		}
		Sleep(500);
		//system("pause");
		run(a, c, b, s);
		cout << "��ǰ����Ϊ��" << ++count << endl;
	}
	//������˵�������ʤ��
	cout << "�ɹ��߳����Թ�����" << endl;
	return 0;
}
