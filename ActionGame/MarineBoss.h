#pragma once
#include "Rect.h"
#include "Mob.h"
#include "Object.h"
#include "Urchin.h"
#include <random>

#define BOSS_SIZEX 110
#define BOSS_SIZEY 95
#define BOSS_HP 5	//踏まれても生きていられる回数
#define BOSS_MOVESPEED 200
#define BOSS_WAIT 50	//行動間の時間
#define BOSS_HARDTIME 300	//硬質化している時間
#define BOSS_UNITIME_FIRST 300	//ウニを落とす時間の初期値
#define BOSS_UNI_INTERVAL 30	//ウニを落とす時間のインターヴァル
#define BOSS_UNI_CNT 20	//保持するウニの数	
#define BOSS_ACTION_INTERVAL 100
#define BOSS_HITDAMAGE 5
#define BOSS_UNI_HITDAMAGE 5
#define BOSS_DROPED_VX 800	//ボスを踏んだときに発生するプレイヤーのx方向速度
#define BOSS_DROPED_VY 200	//y方向速度


class MarineBoss	:public Mob, public Object
{
public:
	static int PicHandle[2];

	Rect rect = Rect(BOSS_SIZEX, BOSS_SIZEY, &this->x, &this->y);

	std::random_device rnd;

	Urchin* UNI[BOSS_UNI_CNT];

	double waittime = KILLHIGHJUMPTIME;
	double cnttime = 0;
	double velocity;
	double unitime;

	bool statflag = true;	//false指定	debug now
	bool HardeningFlag = false;

	int stats = 0;	
	/*
	0:何もしてない、行動を選択
	1:左方向移動
	2:高質化
	3:ウニ落とし
	4:右方向移動
	5:ウニ落とし+高質化
	6:wait
	*/

	int hp = BOSS_HP;

	int fx,tx;

	int unicnt = 0;	//ウニの番号を保持
	
	//sx,sy:初期配置座標	fx:行動範囲始点	行動範囲終点にボスを初期配置
	MarineBoss(int sx, int sy, int fx);
	~MarineBoss();

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
	void HitPlayer();


};

