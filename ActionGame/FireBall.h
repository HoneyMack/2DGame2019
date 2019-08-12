#pragma once
#include"Object.h"
#include"define.h"
#include"Mob.h"
#include"Circle.h"
#include "math.h"

class FireBall : public Mob
{
public:
	static int PicHandle;

	int max_radius;//�����̑�����t�@�C���[�o�[�̒���
	int centerx, centery;	//��]�̒��S
	int radius;
	double x, y;
	double angle;
	double angvel;

	bool direction;

	int fx, fy;
	FireBall(int set_x, int set_y,int set_radius,double set_angle,double angvel,bool set_direction,int max_radius);  //�R���X�g���N�^�@�������W���v�Z
	~FireBall();

	Circle* cir;
	void Motion(double frametime);
	void Draw();

	bool HitCheck(Rect rect); //�v���C���[->enemy
};