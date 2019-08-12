#pragma once
#include "Object.h"
#include"define.h"
#include"Mob.h"
#include"Player.h"


class Lift :public Object, public Mob
{
public:
	static int PicDownHandle;
	static int PicUpHandle;
	Lift(int set_x, int set_y,bool set_direction);   //コンストラクタ　初期座標指定 direction=TRUE->下向き direction=FALSE->上向き
	~Lift();  //デストラクタ

	int dropflag = 0;   //プレイヤーがリフトを踏んだか（リフトが下がっているか）の判定
	bool direction;

	Rect rect = Rect(LIFT_SIZEX, LIFT_SIZEY, &this->x, &this->y);

	void Motion(double frametime);  //動きの処理
	void Draw();  //描画処理
	bool HitCheck(Rect rect);  //当たり判定
	void HitPlayer();  //プレイヤー当たり判定

};
