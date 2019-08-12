#pragma once
#include "define.h"
#include "Rect.h"

class Mob
{
public:
	static Mob *first, *last;
	Mob *former, *next;	//インスタンスの鎖に用いる
	bool deathflag = false;	//死んだか：yes-> true
	static	int killedenemy;						//倒された敵の数

	virtual void Motion(double frametime) = 0;	//動き&処理
	virtual void Draw() = 0;		//描画
	virtual void AddDraw() {};			//追加で描画
	virtual bool HitCheck(Rect rect) { return false; };	//Player->Enemy あたっているかを調べる。デフォルトはあたり判定は持たない, プレイヤーから呼ばれるのはここだけ
	virtual void HitPlayer() {};						//プレイヤーにぶつかっていた時の処理を記述

	bool HasNext();								//次の要素があるか。
	static void AllDelete(Mob* mob);				//インスタンスの鎖をすべて消去。
	virtual void ChainMaker();		//インスタンスの鎖に追加。それぞれの敵のコンストラクタ内に記述してください。
	virtual void ChainCutter();		//インスタンスの鎖から取り除く。それぞれの敵のデストラクタ内に記述してください。

	Mob();
	virtual ~Mob();
};

