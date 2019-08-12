#pragma once
#include "Rect.h"
#include "Mob.h"
#include "Object.h"
//#include "Ghost.h"


class FlashBlock :public Mob, public Object
{
public:
	static int PicHandle;
	static bool flashingflag;		//光っているかを持つ

	Rect rect = Rect(FLASHBLOCK_SIZEX, FLASHBLOCK_SIZEY, &this->x,&this->y);//あたり判定
	bool hitflag = false;			//プレイヤーがぶつかったらture
	double hittime;					//プレイヤーがぶつかった時間を保持

	FlashBlock(int x, int y);		//コンストラクタ
	~FlashBlock();

	void Motion(double frametime);	//処理	
	void Draw();					//描画する
	void AddDraw();					//追加で描画
	bool HitCheck(Rect rect);
};

