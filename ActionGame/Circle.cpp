#include "Circle.h"



Circle::Circle(int radius, double *gx, double *gy)
{
	this->radius = radius;
	this->gx = gx;
	this->gy = gy;
	this->x = 0;
	this->y = 0;
}


Circle::~Circle()
{
}

void Circle::Draw(int x,int y) {
	DrawCircle(x,y,radius,0xFFFFFF,TRUE);
}

void Circle::Draw(Rect Camera) {
	DrawCircle(x + *gx -Camera.x,y + *gy -Camera.y,radius,0xFF00FF,TRUE);
}