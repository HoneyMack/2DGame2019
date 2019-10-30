#pragma once
#include "Rect.h"
#include "Mob.h"
#include "Object.h"
#include "Urchin.h"
#include <random>

#define BOSS_SIZEX 110
#define BOSS_SIZEY 95
#define BOSS_HP 5	//���܂�Ă������Ă������
#define BOSS_MOVESPEED 200
#define BOSS_WAIT 50	//�s���Ԃ̎���
#define BOSS_HARDTIME 300	//�d�������Ă��鎞��
#define BOSS_UNITIME_FIRST 300	//�E�j�𗎂Ƃ����Ԃ̏����l
#define BOSS_UNI_INTERVAL 30	//�E�j�𗎂Ƃ����Ԃ̃C���^�[���@��
#define BOSS_UNI_CNT 20	//�ێ�����E�j�̐�	
#define BOSS_ACTION_INTERVAL 100
#define BOSS_HITDAMAGE 5
#define BOSS_UNI_HITDAMAGE 5
#define BOSS_DROPED_VX 800	//�{�X�𓥂񂾂Ƃ��ɔ�������v���C���[��x�������x
#define BOSS_DROPED_VY 200	//y�������x


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

	bool statflag = true;	//false�w��	debug now
	bool HardeningFlag = false;

	int stats = 0;	
	/*
	0:�������ĂȂ��A�s����I��
	1:�������ړ�
	2:������
	3:�E�j���Ƃ�
	4:�E�����ړ�
	5:�E�j���Ƃ�+������
	6:wait
	*/

	int hp = BOSS_HP;

	int fx,tx;

	int unicnt = 0;	//�E�j�̔ԍ���ێ�
	
	//sx,sy:�����z�u���W	fx:�s���͈͎n�_	�s���͈͏I�_�Ƀ{�X�������z�u
	MarineBoss(int sx, int sy, int fx);
	~MarineBoss();

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
	void HitPlayer();


};

