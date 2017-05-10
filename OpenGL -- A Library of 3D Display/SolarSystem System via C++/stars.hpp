#ifndef star_hpp
#define star_hpp

#include <GL/glut.h>

class Star
{
	public:
		GLfloat radius;				// 星球的运行半径
		GLfloat speed,selfSpeed;	// 星球的公转、自转速度
		GLfloat distance;			// 星球的中心与父节点星球中心的距离
		GLfloat rgbaColor[4];		// 星球的颜色
		Star* parentStar;			// 父节点的星球

		Star(GLfloat radius,GLfloat distance,GLfloat speed,GLfloat selfSpeed,Star* parent); // 构造函数
		void drawStar();			// 对一般的星球的移动、旋转等活动进行绘制
		virtual void draw() {drawStar();}	// 提供默认实现，负责调用drawStar()
		virtual void update(long timeSpan);	// 参数为每次刷新画面时候的时间跨度 

	protected:
		GLfloat alphaSelf,alpha;		// 星球的自转、公转角度
};

class Planet : public Star
{
	public:
		Planet(GLfloat radius,GLfloat distance,GLfloat speed,
				GLfloat selfSpeed,Star* parent,GLfloat rgbColor[3]); // 构造函数
		void drawPlanet();			// 增加对具备自身材质的行星绘制材质
		virtual void draw() {drawPlanet();drawStar();}	// 继续向子类开放重写功能
};

class LightPlanet : public Planet
{
	public:
		LightPlanet(GLfloat radius,GLfloat distance,GLfloat speed,
				GLfloat selfSpeed,Star* parent,GLfloat rgbColor[]); // 构造函数
		void drawLight();			// 增加对提供光源的恒星绘制光照
		virtual void draw() {drawLight();drawPlanet();drawStar();}
};

#endif /* star_hpp */