#pragma once
#include "Rect.h"
#include "Mob.h"
#include "Object.h"

class WalkEnemy :public Mob, public Object
{
public:
	static int PicHandle[8];						//画像保持

	Rect rect = Rect(30, 30,&this->x,&this->y);

	double waittime = KILLHIGHJUMPTIME;
	int index = 0;
	int animation = 0;

	double vecX = 0;				//中心座標からの移動量
	double velocity;					//速度ベクトルを持つ

	WalkEnemy(int x, int y);			//敵の初期座標指定
	~WalkEnemy();

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
	void HitPlayer();

};

