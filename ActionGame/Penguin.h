#pragma once
#include "Rect.h"
#include"Mob.h"
#include "Object.h"


class Penguin : public Mob,public Object
{
public:
	static int PicHandle;

	Rect rect = Rect(30, 30, &this->x, &this->y);

	double waittime = KILLHIGHJUMPTIME;
	int index = 0;
	int animation = 0;

	bool searched = false;

	double vecX = 0;
	double velocity;

	Penguin(int x, int y);
	~Penguin();

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
	void HitPlayer();

};

