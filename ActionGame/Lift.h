#pragma once
#include "Object.h"
#include"define.h"
#include"Mob.h"
#include"Player.h"


class Lift :public Object, public Mob
{
public:
	static int PicDownHandle;
	static int PicUpHandle;
	Lift(int set_x, int set_y,bool set_direction);   //�R���X�g���N�^�@�������W�w�� direction=TRUE->������ direction=FALSE->�����
	~Lift();  //�f�X�g���N�^

	int dropflag = 0;   //�v���C���[�����t�g�𓥂񂾂��i���t�g���������Ă��邩�j�̔���
	bool direction;

	Rect rect = Rect(LIFT_SIZEX, LIFT_SIZEY, &this->x, &this->y);

	void Motion(double frametime);  //�����̏���
	void Draw();  //�`�揈��
	bool HitCheck(Rect rect);  //�����蔻��
	void HitPlayer();  //�v���C���[�����蔻��

};
