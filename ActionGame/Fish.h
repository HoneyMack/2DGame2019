#pragma once
#include "Rect.h"
#include "Mob.h"
#include "Object.h"
#include <math.h>

#define FISH_SPEED 100	//移動する速さ
#define FISH_CHASE_DISTANCE 400	//プレイヤーに反応する距離
#define FISH_LIMIT_ANGLE 10	//プレイヤーを追いかけるときの最大角度
#define FISH_MOVEWIDTH 1600	//魚の行動範囲
#define FISH_HITDAMAGE 5

class Fish :public Mob,public Object
{
public:
	
	static int PicHandle;
	
	Rect rect = Rect(30, 30, &this->x, &this->y);

	int fx, fy;	//初期座標保持
	bool chasing = false;	//追いかけ中のフラグ
	bool canchase = true;	//追いかけ許可フラグ
	double vecX = 0; 
	double velocityX;
	double velocityY;
	

	Fish(int x, int y);
	~Fish();

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
	void HitPlayer();

};

