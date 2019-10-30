#pragma once
#include "Rect.h"
#include "Mob.h"
#include "Object.h"
#include "BulletTowardPlayer.h"

#define CRAB_BULLETS 3	//玉（泡）の数
#define CRAB_SPEED	50	//移動する速さ
#define CRAB_MOVEWIDTH 100	//行動範囲
#define CRAB_HITDAMAGE	5
#define CRAB_FIRINGSPEED 2000
#define CRAB_TIMEBFOREFIRING 1000	//がめんに入ってから球を発射し始めるまでの時間
#define CRAB_INTERVAL 10000
#define BUBBLE_SPEED 60	//泡の上昇スピード
#define BUBBLE_HITDAMAGE 5	//泡のダメージ


class Crab:public Mob,public Object
{
public:
	static int PicHandle;

	Rect rect = Rect(30, 30, &this->x, &this->y);
	BulletTowardPlayer* BTP[CRAB_BULLETS];

	int bulletcounter = 0;	//次に発射される弾を保持
	bool firedflag = false;	//打てる状況になって弾を発射したか
	double pasttime;	//時間を累積

	double velocity;	//左右移動の速度
	double vecX = 0;	//中心からの座標
	int centerX;	//移動の中心

	Crab(int x, int y);
	~Crab();

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);

};

