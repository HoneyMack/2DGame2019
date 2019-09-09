#pragma once
#include "Rect.h"
#include "Mob.h"
#include "Object.h"

#define KILLER_MOVESPEED 40

class Killer :public Mob,public Object
{
public:
	static int PicHandle;

	Rect rect = Rect(30, 30, &this->x, &this->y);

	double waittime = KILLHIGHJUMPLIMIT;
	
	double velocity;
	bool startflag = false;

	Killer(int x, int y,bool direction);	//true:âEÇ…êiÇﬁ false:ç∂Ç…êiÇﬁ
	~Killer();

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
	void HitPlayer();

};

