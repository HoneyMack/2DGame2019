#pragma once
#include "Circle.h"
#include "Mob.h"
#include "Object.h"

//�E�j
#define URCHIN_RADIUS 15	//���a
#define URCHIN_AY 100	//�d�͉����x

class Urchin :public Mob, public Object
{
public:
	static int PicHandle;

	Circle* cir;

	Urchin(int x, int y);
	~Urchin();

	void Motion(double frametime);
	void Draw();

};

