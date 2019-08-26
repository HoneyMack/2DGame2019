#pragma once
#include "Object.h"
#include "Mob.h"
#include "BulletTowardPlayer.h"
#include "math.h"

class ShootEnemy:public Mob,public Object
{
public:
	static int PicHandle;
	BulletTowardPlayer *BTP[SHOOTENEMY_BULLETS];

	Rect rect = Rect(SHOOTENEMY_SIZEX,SHOOTENEMY_SIZEY,&this->x,&this->y); 

	int bulletcounter = 0;//次に発射される弾を保持
	int waittime = KILLHIGHJUMPTIME;
	bool firedflag = false; //打てる状況になって球を発射したか	
	double pasttime;	//時間を累積

	double velocity;	//左右移動の速度
	double vecX = 0;	//中心からの座標
	int centerX; //移動の中心

	ShootEnemy(int x, int y);
	~ShootEnemy();

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
};

