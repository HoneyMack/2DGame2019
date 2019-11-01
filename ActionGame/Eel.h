#pragma once
#include "Rect.h"
#include "Mob.h"
#include "Object.h"

#define EEL_MOVESPEED 80
#define EEL_HITDAMAGE 4

class Eel :public Mob,public Object
{
public:
	static int PicHandle;

	Rect rect = Rect(60, 30, &this->x, &this->y);

	bool startflag = false;

	Eel(int x, int y, bool direction);	//true:右に進む　false:左に進む
	~Eel();

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
	void HitPlayer();
};

