#pragma once
#include "Object.h"
#include "Mob.h"
#include "BulletTowardPlayer.h"
#include "math.h"

class ShootEnemy:public Mob,public Object
{
public:
	static int PicHandle;
	BulletTowardPlayer *BTP[SHOOTENEMY_BULLETS];

	Rect rect = Rect(SHOOTENEMY_SIZEX,SHOOTENEMY_SIZEY,&this->x,&this->y); 

	int bulletcounter = 0;//���ɔ��˂����e��ێ�
	int waittime = KILLHIGHJUMPTIME;
	bool firedflag = false; //�łĂ�󋵂ɂȂ��ċ��𔭎˂�����	
	double pasttime;	//���Ԃ�ݐ�

	double velocity;	//���E�ړ��̑��x
	double vecX = 0;	//���S����̍��W
	int centerX; //�ړ��̒��S

	ShootEnemy(int x, int y);
	~ShootEnemy();

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
};

