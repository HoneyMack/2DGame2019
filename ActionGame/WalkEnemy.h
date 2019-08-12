#pragma once
#include "Rect.h"
#include "Mob.h"
#include "Object.h"

class WalkEnemy :public Mob, public Object
{
public:
	static int PicHandle[8];						//�摜�ێ�

	Rect rect = Rect(30, 30,&this->x,&this->y);

	double waittime = KILLHIGHJUMPTIME;
	int index = 0;
	int animation = 0;

	double vecX = 0;				//���S���W����̈ړ���
	double velocity;					//���x�x�N�g��������

	WalkEnemy(int x, int y);			//�G�̏������W�w��
	~WalkEnemy();

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
	void HitPlayer();

};

