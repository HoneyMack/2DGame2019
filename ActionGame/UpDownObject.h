#pragma once
#include <math.h>
#include "Object.h"
#include "define.h"
#include"Player.h"
#include "Mob.h"



class UpDownObject:public Object,public Mob
{
public:
	static int PicHandle;		//�摜�ێ�
	int movewidth;		//�U�ꕝ
	double vecY = 0;		//Object�N���X�̍��W(x,y)����㉺�ɂǂꂾ��������
	double angvel, angle = -PI/2;		//�p���x,�p�x


	Rect rect = { Rect(UPDOWN_OB_SIZEX,UPDOWN_OB_SIZEY,&this->x,&this->y) };//���̂̂����蔻��

	UpDownObject(int set_x, int set_y);//�R���X�g���N�^�@�������W�w��
	~UpDownObject(); //�f�X�g���N�^

	void Motion(double frametime);
	void Draw();			//������\��
	bool HitCheck(Rect rect);	//Player->Enemy�@�����蔻��
	void HitPlayer();
};