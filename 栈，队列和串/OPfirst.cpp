/**
 * 文件名：使用堆栈实现算符优先算法
 * 文件名是cpp是因为使用了STL中的stack
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <ctype.h>
using namespace std;

stack<char> OPTR;   //初始化算符栈
stack<int> OPND;    //初始化数据栈

//算符优先级表，1表示大于，0表示等于，-1表示小于，2表示不合法
//第一维是前一个算符，第二位是后一个算符
int priority[7][7] = 
{{1, 1, -1, -1, -1, 1, 1},
 {1, 1, -1, -1, -1, 1, 1},
 {1, 1, 1, 1, -1, 1, 1},
 {1, 1, 1, 1, -1, 1, 1},
 {-1, -1, -1, -1, -1, 0 , 2},
 {1, 1, 1, 1, 2, 1, 1},
 {-1, -1, -1, -1, -1, 2, 0}};

//判断字符是不是运算符，如果是运算符返回1，不是运算符返回0
 int isOP(char c){
     if(c=='+' || c=='-' || c=='*' || c=='/' || 
        c=='(' || c==')' || c=='#'){
        return 1;       //是运算符
     } else {
        return 0;
     }
 }

//查表程序，如果输入为3表示出错了
 int precede(char a1, char a2){
     int a=-1 , b=-1;
     switch(a1){
        case '+':
           a = 0;
           break;
        case '-':
           a = 1;
           break;
        case '*':
           a = 2;
           break;
        case '/':
           a = 3;
           break;
        case '(':
           a = 4;
           break;
        case ')':
           a = 5;
           break;
        case '#':
           a = 6;
           break;
        default:
        return 3;   //出错
           break; 
     }
     switch(a2){
        case '+':
           b = 0;
           break;
        case '-':
           b = 1;
           break;
        case '*':
           b = 2;
           break;
        case '/':
           b = 3;
           break;
        case '(':
           b = 4;
           break;
        case ')':
           b = 5;
           break;
        case '#':
           b = 6;
           break;
        default:
        return 3;   //出错
           break; 
     }
     return priority[a][b];
 }

 //进行运算，返回运算的结果
 int operate(int a, char theta, int b){
     switch(theta){
         case '+':
            printf("%d+%d = %d\n",a, b, a+b);
            return a+b;
         case '-':
            printf("%d-%d = %d\n",a, b, a-b);
            return a-b;
         case '*':
            printf("%d*%d = %d\n",a, b, a*b);
            return a*b;
         case '/':
            printf("%d/%d = %d\n",a, b, a/b);
            return a/b;
         default:
            printf("the op is %c\n", theta);
            return 0;
     }
 }

//解析整数值，返回时c存的是下一个运算符号
int getNumber(char &c){
   int num = 0;
   num += (c-'0');
   c = getchar();
   while(isdigit(c)){
      //printf("%c", c);
      num *= 10;
      num += (c-'0');
      c = getchar();
   }
   return num;
}

//解析表达式的主函数，返回解析得到的结果
int expression(){
     OPTR.push('#');    //在开始的时候先将#入栈
     char c;
     c = getchar();
     while(c!='#' || OPTR.top() != '#'){  //只有当两个都是#时才结束解析
         //printf("%c", c);
         if(c == ' '){  //略过空格
            c = getchar();
            continue;
         }
         if(!isOP(c)){  //不是运算符则入数据栈
            int out = getNumber(c);
            //printf("out = %d\n", out);
            OPND.push(out);
         } else {    //是运算符
            int a = precede(OPTR.top(), c);
            //printf("a=%d\n", a);
            if(a == -1){   //当前运算符优先级小于前一个运算符
               OPTR.push(c);
               c = getchar();
            } else if(a == 0){   //运算符等级相等，直接消掉括号即可
               OPTR.pop();
               c = getchar();
            } else if(a == 1){   //进行运算
               char b = OPTR.top();
               OPTR.pop();
               int a1 = OPND.top();
               OPND.pop();
               int a2 = OPND.top();
               OPND.pop();
               int out = operate(a2, b, a1);
               //printf("out = %d\n", out);
               OPND.push(out);
               //注意，需要将这个算符继续比较
            } else if(a == 2){
               printf("error\n");
            }
         }
     }
      return OPND.top();   //将最终的运算结果返回
}

int main(){
   freopen("in.txt", "r", stdin);
   printf("outcome = %d\n", expression());
}