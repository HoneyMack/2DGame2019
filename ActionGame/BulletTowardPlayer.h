#pragma once
#include "Circle.h"
#include "Object.h"
#include "Mob.h"

class BulletTowardPlayer : public Object
{
public:
	static int PicHandle[2];
	Circle *cir;		//‚ ‚½‚è”»’è

	bool picflag = true;	//true:shootenemy false:crab

	BulletTowardPlayer(int x,int y);
	~BulletTowardPlayer();

	void Motion(double frametime);
	void Draw();
};

