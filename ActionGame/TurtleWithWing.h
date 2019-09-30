#pragma once
#include "Object.h"
#include "Mob.h"
#include "Turtle.h"


class TurtleWithWing :
	public Object, public Mob
{
public:
	static int PicHandleWing; //�H�̉摜��ێ�
	bool isWithWing; //�H�����Ă��邩��ێ�
	Turtle* turtle;//Turtle��ێ�
	int initX, initY, initPhase;


	TurtleWithWing(int _x, int _y, int _initPhase = 0); //�R���X�g���N�^
	~TurtleWithWing();//�f�X�g���N�^

	void Motion(double ftime) override;
	void Draw() override;
};

