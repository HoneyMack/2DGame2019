#pragma once
#include "Rect.h"
#include"Mob.h"
#include "Object.h"

#define PENGUIN_MOVEWIDTH 160
#define PENGUIN_HITDAMAGE 4
#define PENGUIN_SLIDINGSPEED 200
#define PENGUIN_WALKINGSPEED 100
#define PENGUIN_SEARCHINGAREA 200


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

