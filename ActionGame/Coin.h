#pragma once
#include "Mob.h"
#include "Object.h"
#include "Rect.h"


//速度、加速度はいらないのでObjectは継承しない
class Coin :
	public Mob
{
public:
	static int PicHandle[2];	//画像　表、裏
	Rect *rect;
	static int hadcoins;		//プレイヤーが保持しているコインの数を保持。
	int animation = 0;					//アニメーション

	double x, y;	//座標

	bool appear = true;			//処理をするか

	Coin(int x,int y);
	~Coin();

	void Motion(double frametime);
	void Draw();

	bool HitCheck(Rect rect);
};


