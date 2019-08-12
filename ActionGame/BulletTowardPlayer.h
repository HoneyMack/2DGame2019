#pragma once
#include "Circle.h"
#include "Object.h"
#include "Mob.h"

class BulletTowardPlayer : public Object
{
public:
	static int PicHandle;
	Circle *cir;		//‚ ‚½‚è”»’è

	BulletTowardPlayer(int x,int y);
	~BulletTowardPlayer();

	void Motion(double frametime);
	void Draw();
};

