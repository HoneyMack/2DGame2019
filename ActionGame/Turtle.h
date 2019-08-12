#pragma once
#include"Object.h"
#include"Circle.h"
#include"Mob.h"
#include"define.h"


class Turtle :public Object, public Mob
{
public:
	static int PicTurtleHandle;  //亀画像(タコ)
	static int PicShellHandle[4];   //甲羅画像(たこ焼き)

	int formflag = 0;  //形態情報のフラグ
	int index = 0;		//アニメーション用
	double animation = 0;	//アニメーションカウント
	bool dflag;   //進行方向フラグ　右ー＞true
	int waittime = KILLHIGHJUMPTIME;		//ハイジャンプ可能フラグとして使用

	double velocity;	//x方向移動速度(亀形態時)
	double shellvelocity=TURTLE_SHELLSPEED;		//x方向速度(甲羅形態時)
	double vecX;	//亀形態時左右の移動量

	Turtle(int x, int y);	//コンストラクタ初期座標指定
	~Turtle();	//デストラクタ

	Circle cir = Circle(TURTLE_RADIUS, &this->x, &this->y);

	void Motion(double frametime);
	void Draw();

	bool HitCheck(Rect rect);
	void HitPlayer();
};
