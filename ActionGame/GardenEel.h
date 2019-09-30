#pragma once
#include "Object.h"
#include "Mob.h"


class GardenEel :
	public Object, public Mob
{
public:
	static int PicHandle; //チンアナゴ画像ハンドル保持

	int initX, initY; //初期位置を保持
	int initPhase;//初期位相
	Rect collider = Rect(GARDENEEL_SIZEX, GARDENEEL_SIZEY, &this->x, &this->y);//当たり判定用矩形

	GardenEel(int _x, int _y, int _initPhase = 0); //初期位置,初期位相


	void Motion(double ftime) override;
	void Draw() override;
	//プレイヤーの当たり判定rectと自分の当たり判定colliderを比較して当たっていたらダメージ
	bool HitCheck(Rect rect) override;
	//プレイヤーに衝突していた時の処理
	void HitPlayer() override;
};

