#pragma once
#include "Object.h"
#include "Mob.h"
#include "Turtle.h"


class TurtleWithWing :
	public Object, public Mob
{
public:
	static int PicHandleWing; //羽の画像を保持
	bool isWithWing; //羽がついているかを保持
	Turtle* turtle;//Turtleを保持
	int initX, initY, initPhase;


	TurtleWithWing(int _x, int _y, int _initPhase = 0); //コンストラクタ
	~TurtleWithWing();//デストラクタ

	void Motion(double ftime) override;
	void Draw() override;
};

