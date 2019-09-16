#pragma once
#include "Rect.h"
#include "Mob.h"
#include "Object.h"

#define KILLER_MOVESPEED 200
#define KILLER_HITDAMAGE 5


class Killer :public Mob,public Object
{
public:
	static int PicHandle;

	Rect rect = Rect(30, 30, &this->x, &this->y);

	double waittime = KILLHIGHJUMPLIMIT;
	
	//double velocity;
	bool startflag = false;

	Killer(int x, int y,bool direction);	//true:右に進む false:左に進む
	~Killer();

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
	void HitPlayer();

};

