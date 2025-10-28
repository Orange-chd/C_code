#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS


/*变量的命名*/
/*1、有意义：int age；
2、名字必须是字母、数字、下划线组成，不能有特殊字符
3、变量名不能是关键字！*/


//关键字typedef-类型定义

//typedef unsigned int uint;
//int main()
//{
//	unsigned int num = 0;//无符号整型
//	uint num2 = 1;//uint=unsigned int
//	return 0;
//}


//关键字static
//1.修饰局部变量
//2.修饰全局变量
//3.修饰函数

//1.修饰局部变量
/*void test()
{
	static int a = 1;
	//static修饰局部变量时，改变了变量的存储位置，局部变量出了作用域，不销毁
	//影响了变量的生命周期，，变量从栈区到静态区，生命周期变长，和程序的生命周期一样
	//int a = 1;//局部变量
	a++;
	printf("%d ", a);//10个2;static：2-11
}
int main()
{
	int i = 0;
	while (i < 10)
	{
		test();
		i++;
	}
	return 0;
}*/


//2.修饰全局变量

/*extern int g_val;//声明外部符号(int可有可无)
int main()
{
	printf("%d", g_val);
	return 0;
}*/


//3.修饰函数
/*extern int add(int x, int y);
int main()
{

	int a = 0;
	int b = 3;
	int z = add(a, b);
	printf("%d", z);
	return 0;
}*/

//register-寄存器
//int mian()
//{
//	register int num = 1;//建议存放在寄存器
//	return 0;
//}



//define定义常量和宏//不是关键字，是预处理指令
#define NUM 100
#define ADD(x,y) ((x)+(y))//相当于函数
int main()
{
	//printf("%d", NUM);
	//int n = NUM;
	//int arr[NUM] = { 0 };//NUM是常量
	//return 0;

	int a = 9;
	int b = 6;
	int c = ADD(a, b);//替换成宏体((a)+(b))
	printf("%d", c);

}
