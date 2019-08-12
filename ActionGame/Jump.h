#pragma once
#include "Object.h"
#include "Mob.h"
#include "define.h"
#include "Player.h"
#include "math.h"

class Jump :public Mob, public Object
{
public:

	static int PicHandle;
	static int PicHandle_extended;
	static int NsizeY;	//�m�[�}���T�C�Y

	Rect rect = Rect(FLASHBLOCK_SIZEX, FLASHBLOCK_SIZEY, &this->x, &this->y);
	bool hitflag = false;			//�΂˂��P�U�����Ă��邩
	bool jumponce = false;			//��x���������W�����v�ł��Ȃ��悤�ɂ���
	double amplitude;				//�U��
	double radian = 0;				//�O�p�֐��p

	Jump(int x, int y);
	~Jump();
	void Draw();
	void Motion(double frametime);
	bool HitCheck(Rect rect);
	void HitPlayer();
};