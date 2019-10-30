#pragma once
#include "Rect.h"
#include "Mob.h"
#include "Object.h"



class Polarbear :public Mob,public Object
{
public:
	static int PicHandle;

	Rect rect = Rect(PBSIZEX, PBSIZEY, &this->x, &this->y);

	double waittime = KILLHIGHJUMPTIME;

	double vecX = 0;
	double velocity;

	Polarbear(int x, int y);
	~Polarbear();

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
	void HitPlayer();
};

