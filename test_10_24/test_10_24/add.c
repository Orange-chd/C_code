

static int g_val = 2025;
//static修饰全局变量的时候，这个全局变量的外部链接属性就变成了内部链接属性，其他源文件不能再使用

static int add(int x, int y)//一样失去外部链接属性
{
	return x + y;
}