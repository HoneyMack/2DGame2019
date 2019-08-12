#include "Rect.h"

Rect::Rect(int sizeX, int sizeY,double *gx,double *gy) 
{
	this->gx = gx;		//親の座標を示すポインタをセット
	this->gy = gy;

	x = 0;
	y = 0;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}


Rect::~Rect()
{
}

void Rect::Draw(int x,int y) {
	DrawBox(x ,y ,x + sizeX ,y + sizeY ,0xFFFFFF,TRUE);
}

void Rect::Draw(Rect Camera) {
	DrawBox(x + *gx -Camera.x, y + *gy - Camera.y, x + sizeX + *gx - Camera.x, y + sizeY + *gy - Camera.y, 0xFFFFFF, TRUE);
}