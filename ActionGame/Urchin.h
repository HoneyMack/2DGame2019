#pragma once
#include "Circle.h"
#include "Mob.h"
#include "Object.h"

//ウニ
#define URCHIN_RADIUS 15	//半径
#define URCHIN_AY 100	//重力加速度

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

