#pragma once
#include "Object.h"
#include "Mob.h"
#include "define.h"
#include "Player.h"
#include "math.h"

class Jump :public Mob, public Object
{
public:

	static int PicHandle;
	static int PicHandle_extended;
	static int NsizeY;	//ノーマルサイズ

	Rect rect = Rect(FLASHBLOCK_SIZEX, FLASHBLOCK_SIZEY, &this->x, &this->y);
	bool hitflag = false;			//ばねが単振動しているか
	bool jumponce = false;			//一度だけしかジャンプできないようにする
	double amplitude;				//振幅
	double radian = 0;				//三角関数用

	Jump(int x, int y);
	~Jump();
	void Draw();
	void Motion(double frametime);
	bool HitCheck(Rect rect);
	void HitPlayer();
};