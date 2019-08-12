#pragma once
#include "Object.h"
#include "Mob.h"
#include "Rect.h"


class ShootLaser :
	public Object,public Mob
{
public:
	static int PicHandle_laser;				//���[�U�[�ێ��p
	static int PicHandle_dispenser;			//���ˑ��u�p

	bool onceflag = true;					//��񂾂����s���邽�߂̃t���O
	bool startflag = false;					//��ʂɕ\�����ꂽ�烌�[�U�[�𔭎˂���悤�ɂ��邽�߂̃t���O
	double timecount;						//��ʂɕ`�悳��n�߂����Ԃ�ێ�
	//int y_started;							//��ʂɕ`�悳��n�߂��Ƃ���y���W

	Rect *laser[SHOOTLASER_SHOTTIMES];							//���˂��郌�[�U�[
	double laserX[SHOOTLASER_SHOTTIMES];	//���˂��ꂽ���[�U�[�̈ʒu���ڂ����m��K�v�����邽�ߕʓr���݂̂�p��
	int shotcount = 0;						//���˂�����ɂ������āA���񔭎˂��ꂽ��

	ShootLaser(int x);
	~ShootLaser();

	void Shoot(double frametime);	//�e��ł��߂̏���
	void Motion(double frametime);	//����
	void Draw();					//�`��
	void Reset();

	bool HitCheck(Rect rect);		
	void HitPlayer();
};

