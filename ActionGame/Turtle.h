#pragma once
#include"Object.h"
#include"Circle.h"
#include"Mob.h"
#include"define.h"


class Turtle :public Object, public Mob
{
public:
	static int PicTurtleHandle;  //�T�摜(�^�R)
	static int PicShellHandle[4];   //�b���摜(�����Ă�)

	int formflag = 0;  //�`�ԏ��̃t���O
	int index = 0;		//�A�j���[�V�����p
	double animation = 0;	//�A�j���[�V�����J�E���g
	bool dflag;   //�i�s�����t���O�@�E�[��true
	int waittime = KILLHIGHJUMPTIME;		//�n�C�W�����v�\�t���O�Ƃ��Ďg�p

	double velocity;	//x�����ړ����x(�T�`�Ԏ�)
	double shellvelocity=TURTLE_SHELLSPEED;		//x�������x(�b���`�Ԏ�)
	double vecX;	//�T�`�Ԏ����E�̈ړ���

	Turtle(int x, int y);	//�R���X�g���N�^�������W�w��
	~Turtle();	//�f�X�g���N�^

	Circle cir = Circle(TURTLE_RADIUS, &this->x, &this->y);

	void Motion(double frametime);
	void Draw();

	bool HitCheck(Rect rect);
	void HitPlayer();
};
