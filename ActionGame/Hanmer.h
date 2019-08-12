#pragma once
#include"Object.h"
#include"Circle.h"
#include"Mob.h"
#include"define.h"
#include<math.h>


class Hanmer :public Object, public Mob
{
public:
	static int PicHandle;

	double angle;

	Hanmer(int x, int y);
	~Hanmer();

	Circle *cir;

	void Motion(double frametime);
	void Draw();

	bool HitCheck(Rect rect);
	void HitPlayer();
};