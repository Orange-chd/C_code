#include<stdio.h>

//�ṹ���ǰ�һЩ��һ���������һ�������

struct Stu//����
{
	char name[20];
	int age;
	char sex[10];
};

void print(struct Stu* ps)
{
	printf("%s %d %s\n", (*ps).name, (*ps).age, (*ps).sex);//�鷳
	//�ṹ��ָ�����->��Ա��
	printf("%s %d %s\n", ps->name, ps->age, ps->sex);//->��ʾpsָ��Ķ���ĳ�Ա

}
int main()
{
	struct Stu s = { "���ͻ�",22,"Ů" };//���ʹ���s����
	//�ṹ�����.��Ա��
	//printf("%s %d %s\n", s.name, s.age, s.sex);//˳������

	print(&s);

	return 0;
}