#include<stdio.h>

//结构体是把一些单一类型组合在一起的做法

struct Stu//类型
{
	char name[20];
	int age;
	char sex[10];
};

void print(struct Stu* ps)
{
	printf("%s %d %s\n", (*ps).name, (*ps).age, (*ps).sex);//麻烦
	//结构体指针变量->成员名
	printf("%s %d %s\n", ps->name, ps->age, ps->sex);//->表示ps指向的对象的成员

}
int main()
{
	struct Stu s = { "朱贤慧",22,"女" };//类型创建s对象
	//结构体对象.成员名
	//printf("%s %d %s\n", s.name, s.age, s.sex);//顺序不能乱

	print(&s);

	return 0;
}