#include<stdio.h>

//int main()
//{
//	int a = 19;//4个字节
//	&a;//取地址操作符&
//	printf("%d\n", a);
//	printf("%p\n", &a);
//	int* p = &a;//*说明p是指针变量，int说明p指向的对象是int类型
//
//	char ch = 'w';
//	char* pc = &ch;
//	*p = 20;//解引用操作符，意思是通过p中存放的地址，找到p所指向的对象，*p就是p指向的对象
//	
//	printf("%d\n", a);
//
//	return 0;
//}


int main()
{
	//不管什么类型的指针都是在创建指针变量
	//指针变量的大小取决于一个地址存放的时候需要多大空间
	//32位机器上的地址，32bit-4byte
	//64位机器上的地址，64bit-8byte
	
	printf("%zd\n", sizeof(char*));//都是4、8//sizeof用zd打印
	printf("%d\n", sizeof(int*));
	printf("%d\n", sizeof(double*));
	printf("%d\n", sizeof(short*));
	printf("%d\n", sizeof(float*));
	return 0;
}