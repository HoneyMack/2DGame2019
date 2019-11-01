#include "Urchin.h"

int Urchin::PicHandle = 0;

Urchin::Urchin(int x, int y)
{
	this->x = x;
	this->y = y;

	vx = vy = ax = 0;
	ay = URCHIN_AY;

	cir = new Circle(URCHIN_RADIUS, &this->x, &this->y);

	cir->x = 15;
	cir->y = 16;
}

Urchin::~Urchin()
{
	delete cir;
}

void Urchin::Motion(double frametime)
{
	if (CheckInCam())
		stepPosAll(frametime);
	else
		vy = 0;
}

void Urchin::Draw()
{
	if (CheckInCam()) {

#ifdef DEBUG
		cir->Draw(*Camera);
#endif
		DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
	}
}
