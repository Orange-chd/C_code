#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS


/*����������*/
/*1�������壺int age��
2�����ֱ�������ĸ�����֡��»�����ɣ������������ַ�
3�������������ǹؼ��֣�*/


//�ؼ���typedef-���Ͷ���

//typedef unsigned int uint;
//int main()
//{
//	unsigned int num = 0;//�޷�������
//	uint num2 = 1;//uint=unsigned int
//	return 0;
//}


//�ؼ���static
//1.���ξֲ�����
//2.����ȫ�ֱ���
//3.���κ���

//1.���ξֲ�����
/*void test()
{
	static int a = 1;
	//static���ξֲ�����ʱ���ı��˱����Ĵ洢λ�ã��ֲ��������������򣬲�����
	//Ӱ���˱������������ڣ���������ջ������̬�����������ڱ䳤���ͳ������������һ��
	//int a = 1;//�ֲ�����
	a++;
	printf("%d ", a);//10��2;static��2-11
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


//2.����ȫ�ֱ���

/*extern int g_val;//�����ⲿ����(int���п���)
int main()
{
	printf("%d", g_val);
	return 0;
}*/


//3.���κ���
/*extern int add(int x, int y);
int main()
{

	int a = 0;
	int b = 3;
	int z = add(a, b);
	printf("%d", z);
	return 0;
}*/

//register-�Ĵ���
//int mian()
//{
//	register int num = 1;//�������ڼĴ���
//	return 0;
//}



//define���峣���ͺ�
#define NUM 100
#define ADD(x,y) ((x)+(y))//�൱�ں���
int main()
{
	//printf("%d", NUM);
	//int n = NUM;
	//int arr[NUM] = { 0 };//NUM�ǳ���
	//return 0;

	int a = 9;
	int b = 6;
	int c = ADD(a, b);//�滻�ɺ���((a)+(b))
	printf("%d", c);
}