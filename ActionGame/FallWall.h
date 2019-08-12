#pragma once
#include "Mob.h"
#include "Object.h"


//���ėp���p�N���X
class RedExam : public Object 
{
public:
	Rect *rect;				//�����蔻��p
	int startY;				//�����ʒu�ێ�
	RedExam(int sizeX,int sizeY,int x,int y);
	~RedExam();
};


class FallWall:
	public Mob, public Object
{
public:
	static int BirdPicHandle[2],RedExamPicHandle;	//�摜�ێ��p

	FallWall(int x,int y);		//�R���X�g���N�^
	~FallWall();				//�f�X�g���N�^

	Rect *bird;					//�摜�����蔻��p
	RedExam *redexam;		

	bool fallflag,descendflag, ascendflag;	//���~�A�㏸�t���O
	int birdanima,motionanima,index;					//�A�j���[�V�����p
	int waittime = KILLHIGHJUMPTIME;
	int picdsize[2][2] = { {0,0} ,{0,0} };					//�Q�̉摜�̂��������x,y,0 ==fly1,1 == fly2
	int startY;						//�����ʒu�ێ�

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
};

