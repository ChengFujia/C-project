#include "stars.hpp"
#define PI 3.1415926535

Star::Star(GLfloat radius,GLfloat distance,GLfloat speed,GLfloat selfSpeed,Star* parent)
{
	//todo
}

void Star::drawStar()
{
	//todo
}

void Star::update(long timeSpan)
{
	// todo
}

Planet::Planet(GLfloat radius,GLfloat distance,GLfloat speed,
				GLfloat selfSpeed,Star* parent,GLfloat rgbaColor[3]):
				Star(radius,distance,speed,selfSpeed,parent)
				{
					//todo
				}

void Planet::drawPlanet()
{
	//todo
}

LightPlanet::LightPlanet(GLfloat radius,GLfloat distance,GLfloat speed,
				GLfloat selfSpeed,Star* parent,GLfloat rgbaColor[3]):
				Planet(radius,distance,speed,selfSpeed,parent,rgbaColor)
				{
					//todo
				}

void LightPlanet::drawLight()
{
	//todo
}

