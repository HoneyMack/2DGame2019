#pragma once
#include "Object.h"
#include "Mob.h"


class GardenEel :
	public Object, public Mob
{
public:
	static int PicHandle; //�`���A�i�S�摜�n���h���ێ�

	int initX, initY; //�����ʒu��ێ�
	int initPhase;//�����ʑ�
	Rect collider = Rect(GARDENEEL_SIZEX, GARDENEEL_SIZEY, &this->x, &this->y);//�����蔻��p��`

	GardenEel(int _x, int _y, int _initPhase = 0); //�����ʒu,�����ʑ�


	void Motion(double ftime) override;
	void Draw() override;
	//�v���C���[�̓����蔻��rect�Ǝ����̓����蔻��collider���r���ē������Ă�����_���[�W
	bool HitCheck(Rect rect) override;
	//�v���C���[�ɏՓ˂��Ă������̏���
	void HitPlayer() override;
};

