#include<stdio.h>

//int main()
//{
//	int a = 19;//4���ֽ�
//	&a;//ȡ��ַ������&
//	printf("%d\n", a);
//	printf("%p\n", &a);
//	int* p = &a;//*˵��p��ָ�������int˵��pָ��Ķ�����int����
//
//	char ch = 'w';
//	char* pc = &ch;
//	*p = 20;//�����ò���������˼��ͨ��p�д�ŵĵ�ַ���ҵ�p��ָ��Ķ���*p����pָ��Ķ���
//	
//	printf("%d\n", a);
//
//	return 0;
//}


int main()
{
	//����ʲô���͵�ָ�붼���ڴ���ָ�����
	//ָ������Ĵ�Сȡ����һ����ַ��ŵ�ʱ����Ҫ���ռ�
	//32λ�����ϵĵ�ַ��32bit-4byte
	//64λ�����ϵĵ�ַ��64bit-8byte
	
	printf("%zd\n", sizeof(char*));//����4��8//sizeof��zd��ӡ
	printf("%d\n", sizeof(int*));
	printf("%d\n", sizeof(double*));
	printf("%d\n", sizeof(short*));
	printf("%d\n", sizeof(float*));
	return 0;
}