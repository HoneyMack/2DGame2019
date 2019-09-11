#pragma once
#include"Object.h"
#include "Mob.h"
#include "Rect.h"
#include "define.h"
#include <math.h>

#define SHIP_SIZEX 96
#define SHIP_SIZEY 64
#define SHIP_MOVESPEED 100

class Ship :public Object,public Mob
{
public:
	static int PicHandle;

	double angle;
	bool startflag = false;

	Rect rect = Rect(SHIP_SIZEX, SHIP_SIZEY, &this->x, &this->y);

	Ship(int x, int y, double set_angle);	//�R���X�g���N�^�@
	//set_angle�Ō����w�� �f�B�O���[�Ŏw��@�����I�Ɏw��ł���悤�ɐ��w�̊p�x���g����悤�ɂ���
	//��F135�x���w��	����Ɍ������Ď΂߂ɐi��
	~Ship();	//�f�X�g���N�^
	
	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
	void HitPlayer();
};

