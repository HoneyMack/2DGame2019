#pragma once
#include"Object.h"
#include"Rect.h"
#include"Mob.h"
#include"define.h"
#include"Hanmer.h"


class HanmerThrow :public Object, public Mob 
{
public:
	static int PicHandle[3];

	double velocity;
	double vecX = 0;
	double iv;

	double animation = 0;		//�A�j���[�V�������ԕێ�
	double waittime = KILLHIGHJUMPTIME;		//�n�C�W�����v�\����
	int index = 0;			//�A�j���[�V�����p
	int hanmercounter = 0;
	bool throwflag = false;
	double pasttime = 0;


	HanmerThrow(int x, int y,double iv);
	~HanmerThrow();

	Rect rect = Rect(HANMERTHROW_SIZEX, HANMERTHROW_SIZEY, &this->x, &this->y);
	Hanmer *HAnmer[THROW_HANMERS];

	void Motion(double frametime);
	void Draw();

	bool HitCheck(Rect rect);
	void HitPlayer();
};