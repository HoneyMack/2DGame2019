#pragma once
#include"Object.h"
#include"define.h"
#include"Mob.h"
#include"Circle.h"
#include "math.h"

class FireBall : public Mob
{
public:
	static int PicHandle;

	int max_radius;//自分の属するファイヤーバーの長さ
	int centerx, centery;	//回転の中心
	int radius;
	double x, y;
	double angle;
	double angvel;

	bool direction;

	int fx, fy;
	FireBall(int set_x, int set_y,int set_radius,double set_angle,double angvel,bool set_direction,int max_radius);  //コンストラクタ　初期座標を計算
	~FireBall();

	Circle* cir;
	void Motion(double frametime);
	void Draw();

	bool HitCheck(Rect rect); //プレイヤー->enemy
};