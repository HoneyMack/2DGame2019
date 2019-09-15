#pragma once
#include "Rect.h"
#include "Mob.h"
#include "Object.h"
#include "BulletTowardPlayer.h"

#define CRAB_BULLETS 3	//�ʁi�A�j�̐�
#define CRAB_SPEED	50	//�ړ����鑬��
#define CRAB_MOVEWIDTH 100	//�s���͈�
#define CRAB_HITDAMAGE	5
#define CRAB_FIRINGSPEED 2000
#define CRAB_TIMEBFOREFIRING 1000	//���߂�ɓ����Ă��狅�𔭎˂��n�߂�܂ł̎���
#define CRAB_INTERVAL 10000
#define BUBBLE_SPEED 60	//�A�̏㏸�X�s�[�h
#define BUBBLE_HITDAMAGE 5	//�A�̃_���[�W


class Crab:public Mob,public Object
{
public:
	static int PicHandle;

	Rect rect = Rect(30, 30, &this->x, &this->y);
	BulletTowardPlayer* BTP[CRAB_BULLETS];

	int bulletcounter = 0;	//���ɔ��˂����e��ێ�
	bool firedflag = false;	//�łĂ�󋵂ɂȂ��Ēe�𔭎˂�����
	double pasttime;	//���Ԃ�ݐ�

	double velocity;	//���E�ړ��̑��x
	double vecX = 0;	//���S����̍��W
	int centerX;	//�ړ��̒��S

	Crab(int x, int y);
	~Crab();

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);

};

