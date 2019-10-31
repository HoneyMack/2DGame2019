#pragma once
#include "Rect.h"
#include "Mob.h"
#include "Object.h"

class Blockforblock :public Mob, public Object
{
public:
	static int PicHandle;
	static bool startflag;
	static bool liveflag;

	int fx;

	Rect rect = Rect(32, 32, &this->x, &this->y);

	Blockforblock(int x, int y,int fx);	//fx�����v���C���[���u���ɍs������N��
	~Blockforblock();

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);

};

