#pragma once
#include "Rect.h"
#include "Mob.h"
#include "Object.h"
//#include "Ghost.h"


class FlashBlock :public Mob, public Object
{
public:
	static int PicHandle;
	static bool flashingflag;		//�����Ă��邩������

	Rect rect = Rect(FLASHBLOCK_SIZEX, FLASHBLOCK_SIZEY, &this->x,&this->y);//�����蔻��
	bool hitflag = false;			//�v���C���[���Ԃ�������ture
	double hittime;					//�v���C���[���Ԃ��������Ԃ�ێ�

	FlashBlock(int x, int y);		//�R���X�g���N�^
	~FlashBlock();

	void Motion(double frametime);	//����	
	void Draw();					//�`�悷��
	void AddDraw();					//�ǉ��ŕ`��
	bool HitCheck(Rect rect);
};

