#pragma once
#include "Object.h"
#include "Mob.h"
#include "Rect.h"
#include "Circle.h"

class SnowBall : public Object,public Mob{
public:
	static int PicHandle;	//��ʉ摜�n���h��
	double angle = 0.0;
	Circle cir = Circle(SNOWBALL_RADIUS, &this->x, &this->y);//�����蔻��
	SnowBall(int x,int y);

	void Motion(double ftime ) override;
	void Draw() override; 

	bool HitCheck(Rect rect) override; //�v���C���[�Ƃ̐ڐG����
};

class SnowMan: public Object,public Mob
{
public:
	static int PicHandle; //�Ⴞ��܂̉摜�n���h��
	bool direction; //���𓊂��������ێ�
	bool ballSetFlag;
	int counter; //�o�ߎ��Ԃ��J�E���g����
	int waittime; //�W����
	SnowBall* ball;
	Rect rect = Rect(SNOWMAN_SIZEX, SNOWMAN_SIZEY, &this->x, &this->y); //�����蔻��


	SnowMan(int _x,int _y,bool _direciton = false); //direction�͋���]��������

	void Motion(double ftime) override;
	void Draw() override;

	bool HitCheck(Rect rect) override;
};
