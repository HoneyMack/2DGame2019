#pragma once
#include "Mob.h"
#include "Object.h"
#include "Rect.h"
#include<random>

#define HISIZE_X 32
#define HISIZE_Y 32
#define HEALING_POINT 10

class HealingItem :public Mob,public Object
{
public:
	std::random_device rnd;

	static int PicHandle[];
	Rect rect = Rect(HISIZE_X, HISIZE_Y, &this->x, &this->y);

	int PicNum = 0;

	HealingItem(int x,int y);
	~HealingItem();

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
	void HitPlayer();
};

