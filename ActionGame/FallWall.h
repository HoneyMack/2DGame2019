#pragma once
#include "Mob.h"
#include "Object.h"


//答案用紙用クラス
class RedExam : public Object 
{
public:
	Rect *rect;				//あたり判定用
	int startY;				//初期位置保持
	RedExam(int sizeX,int sizeY,int x,int y);
	~RedExam();
};


class FallWall:
	public Mob, public Object
{
public:
	static int BirdPicHandle[2],RedExamPicHandle;	//画像保持用

	FallWall(int x,int y);		//コンストラクタ
	~FallWall();				//デストラクタ

	Rect *bird;					//画像あたり判定用
	RedExam *redexam;		

	bool fallflag,descendflag, ascendflag;	//下降、上昇フラグ
	int birdanima,motionanima,index;					//アニメーション用
	int waittime = KILLHIGHJUMPTIME;
	int picdsize[2][2] = { {0,0} ,{0,0} };					//２つの画像のずれを持つx,y,0 ==fly1,1 == fly2
	int startY;						//初期位置保持

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
};

