#pragma once
#include "Object.h"
#include "Mob.h"
#include "Rect.h"
#include "Circle.h"

class SnowBall : public Object,public Mob{
public:
	static int PicHandle;	//雪玉画像ハンドル
	double angle = 0.0;
	Circle cir = Circle(SNOWBALL_RADIUS, &this->x, &this->y);//当たり判定
	SnowBall(int x,int y);

	void Motion(double ftime ) override;
	void Draw() override; 

	bool HitCheck(Rect rect) override; //プレイヤーとの接触判定
};

class SnowMan: public Object,public Mob
{
public:
	static int PicHandle; //雪だるまの画像ハンドル
	bool direction; //球を投げる向きを保持
	bool ballSetFlag;
	int counter; //経過時間をカウントする
	int waittime; //ジャン
	SnowBall* ball;
	Rect rect = Rect(SNOWMAN_SIZEX, SNOWMAN_SIZEY, &this->x, &this->y); //当たり判定


	SnowMan(int _x,int _y,bool _direciton = false); //directionは球を転がす向き

	void Motion(double ftime) override;
	void Draw() override;

	bool HitCheck(Rect rect) override;
};
