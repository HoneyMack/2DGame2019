#pragma once
#include <math.h>
#include "Object.h"
#include "define.h"
#include"Player.h"
#include "Mob.h"



class UpDownObject:public Object,public Mob
{
public:
	static int PicHandle;		//画像保持
	int movewidth;		//振れ幅
	double vecY = 0;		//Objectクラスの座標(x,y)から上下にどれだけ動くか
	double angvel, angle = -PI/2;		//角速度,角度


	Rect rect = { Rect(UPDOWN_OB_SIZEX,UPDOWN_OB_SIZEY,&this->x,&this->y) };//物体のあたり判定

	UpDownObject(int set_x, int set_y);//コンストラクタ　初期座標指定
	~UpDownObject(); //デストラクタ

	void Motion(double frametime);
	void Draw();			//自分を表示
	bool HitCheck(Rect rect);	//Player->Enemy　あたり判定
	void HitPlayer();
};