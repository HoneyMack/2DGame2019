#pragma once
#include "Mob.h"
#include "Object.h"



class Sea : public Object
{
public:
	static int PicHandle;

	static Sea* first;
	static Sea* last;

	Sea* former;
	Sea* next;


	Rect rect = Rect(SEA_SIZEX, SEA_SIZEY, &this->x, &this->y);

	//static bool InWaterFlag = false;

	Sea(int x, int y,int direction);	//direction:0波なし、上下右左の四ビットで指定。例外処理めんどくさいので変な数を入れないように！！！原則一つ
	~Sea();

	int direction;

	void ChainMaker();	//リストですべての海の判定を処理する
	void ChainCutter();
	bool HasNext();	//リストの次の要素があるか

	int HitCheckReturnSea(Rect rect);	//rectが当たっているかを調べる。戻り値はrectを中心として当たった面

	static void AllDelete();
	static void AllDelete(Sea* sea);

	void Draw();

	static int PlayerHitCheck(Rect rect);	//Player側から呼ばれる処理

	//void Motion(double frametime);
	//bool HitCheck(Rect rect);
	//void HitPlayer();

};

