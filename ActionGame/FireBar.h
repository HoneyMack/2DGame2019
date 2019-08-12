#pragma once
#include"FireBall.h"

class FireBar :public Object, public Mob
{
public:
	static int PicHandle;			//���S�u���b�N�摜
	FireBar(int set_x, int set_y);
	FireBar(int set_x, int set_y, int length, int number);  //firebar�̒����{�����w��
	FireBar(int set_x, int set_y, double speed);  //firebar�̑������w��@�p���x��speed*PI/180�ɂȂ�܂��@�f�t�H���g��speed��90�ł�
	FireBar(int set_x, int set_y, bool direction);  //firebar�̉�]�̌������w��@false�Œʏ�Ɣ��Ε����������܂��@true,false�Ə������Ő錾���Ă�������(�啶������int�^�Ɣ��f����Ă��܂�����)
	FireBar(int set_x, int set_y, int set_angle);  //firebar�̈ʑ��p���w��@�ʓx�@�ł͂Ȃ��x���@�Ő錾���Ă�������
	FireBar(int set_x, int set_y, double set_speed, bool direction, int length, int number, int set_angle);  //���ׂĎw�� �x���@�Ő錾���Ă�������
	
	~FireBar();

	Rect rect = Rect(30, 30, &this->x, &this->y);

	FireBall *fireball;

	void Motion(double frametime);
	void Draw();

	bool HitCheck(Rect rect);
	void HitPlayer();

};