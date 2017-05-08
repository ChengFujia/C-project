// 使用GLUT的基本头文件
#include <GL/glut.h>
#include "solarsystem.hpp"

// 创建图形窗口的基本宏
#define WINDOW_X_POS 50
#define WINDOW_Y_POS 50
#define WIDTH 700
#define HEIGHT 700

SolarSystem solarsystem;

// 用于注册GLUT的回调
void onDisplay(void)
{
	solarsystem.onDisplay();
}

void onUpdate(void)
{
	solarsystem.onUpdate();
}

void onKeyboard(unsigned char key,int x,int y)
{
	solarsystem.onKeyboard(key,x,y);
}

int main(int argc, char* argv[])
{
	// 对GLUT进行初始化，并处理所有的命令行的参数
	glutInit(&argc,argv);
	// 这个函数指定了使用RGBA模式的颜色索引模式；
	// 另外，还指定单缓冲 或 双缓冲
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	// 设置窗口的宽高
	glutInitWindowPosition(WINDOW_X_POS,WINDOW_Y_POS);
	// 创建一个窗口
	glutCreateWindow("SolarSystem at CFJ");

	// glutDisplayFunc的函数原型为glutDisplayFunc(void (*func)(void))
	// 这是一个回调函数，每当GLUT确定一个窗口的内容需要更新显示的时候
	// glutDisplayFunc注册的回调函数就会执行。

	// glutIdleFunc的原型函数是glutIdleFunc(void (*func)(void))
	// 指定一个函数，用于处理事件循环：处于空闲的时候，就执行这个函数

	// glutKeyboardFunc的原型函数是glutKeyboardFunc(void (*func)(unsigned char key,int x,int y))
	// 将键盘上的一个键与一个函数想关联，当这个键被按下／释放时候，函数就会被调用

	// 实际上，注册这三个回调函数
	glutDisplayFunc(onDisplay);
	glutIdleFunc(onUpdate);
	glutKeyboardFunc(onKeyboard);

	glutMainLoop();
	return 0;
}
