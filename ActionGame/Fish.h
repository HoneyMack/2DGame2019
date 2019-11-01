#pragma once
#include "Rect.h"
#include "Mob.h"
#include "Object.h"
#include <math.h>

#define FISH_SPEED 80	//�ړ����鑬��00
#define FISH_CHASE_DISTANCE 200	//�v���C���[�ɔ������鋗��
#define FISH_LIMIT_ANGLE 10	//�v���C���[��ǂ�������Ƃ��̍ő�p�x
#define FISH_MOVEWIDTH 1000	//���̍s���͈�
#define FISH_HITDAMAGE 5

class Fish :public Mob,public Object
{
public:
	
	static int PicHandle;
	
	Rect rect = Rect(30, 30, &this->x, &this->y);

	int fx, fy;	//�������W�ێ�
	bool chasing = false;	//�ǂ��������̃t���O
	bool canchase = true;	//�ǂ��������t���O
	double vecX = 0; 
	double velocityX;
	double velocityY;
	

	Fish(int x, int y);
	~Fish();

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
	void HitPlayer();

};

