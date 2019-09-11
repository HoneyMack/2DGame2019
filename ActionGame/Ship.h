#pragma once
#include"Object.h"
#include "Mob.h"
#include "Rect.h"
#include "define.h"
#include <math.h>

#define SHIP_SIZEX 96
#define SHIP_SIZEY 64
#define SHIP_MOVESPEED 100

class Ship :public Object,public Mob
{
public:
	static int PicHandle;

	double angle;
	bool startflag = false;

	Rect rect = Rect(SHIP_SIZEX, SHIP_SIZEY, &this->x, &this->y);

	Ship(int x, int y, double set_angle);	//コンストラクタ　
	//set_angleで向き指定 ディグリーで指定　直感的に指定できるように数学の角度を使えるようにする
	//例：135度を指定	左上に向かって斜めに進む
	~Ship();	//デストラクタ
	
	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
	void HitPlayer();
};

