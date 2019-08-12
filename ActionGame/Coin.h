#pragma once
#include "Mob.h"
#include "Object.h"
#include "Rect.h"


//���x�A�����x�͂���Ȃ��̂�Object�͌p�����Ȃ�
class Coin :
	public Mob
{
public:
	static int PicHandle[2];	//�摜�@�\�A��
	Rect *rect;
	static int hadcoins;		//�v���C���[���ێ����Ă���R�C���̐���ێ��B
	int animation = 0;					//�A�j���[�V����

	double x, y;	//���W

	bool appear = true;			//���������邩

	Coin(int x,int y);
	~Coin();

	void Motion(double frametime);
	void Draw();

	bool HitCheck(Rect rect);
};


