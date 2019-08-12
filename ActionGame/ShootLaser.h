#pragma once
#include "Object.h"
#include "Mob.h"
#include "Rect.h"


class ShootLaser :
	public Object,public Mob
{
public:
	static int PicHandle_laser;				//レーザー保持用
	static int PicHandle_dispenser;			//発射装置用

	bool onceflag = true;					//一回だけ実行するためのフラグ
	bool startflag = false;					//画面に表示されたらレーザーを発射するようにするためのフラグ
	double timecount;						//画面に描画され始めた時間を保持
	//int y_started;							//画面に描画され始めたときのy座標

	Rect *laser[SHOOTLASER_SHOTTIMES];							//発射するレーザー
	double laserX[SHOOTLASER_SHOTTIMES];	//発射されたレーザーの位置を詳しく知る必要があるため別途ｘのみを用意
	int shotcount = 0;						//発射させるにあたって、何回発射されたか

	ShootLaser(int x);
	~ShootLaser();

	void Shoot(double frametime);	//弾を打つための処理
	void Motion(double frametime);	//処理
	void Draw();					//描画
	void Reset();

	bool HitCheck(Rect rect);		
	void HitPlayer();
};

