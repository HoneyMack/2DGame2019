#pragma once
#include "Object.h"
#include "Rect.h"


//フェンス一つ分 使うときは複数使って実装

class Fence:public Object
{
public:
	static Fence *first, *last;
	Fence *former, *next;	//インスタンスの鎖に用いる

	static int PicHandle;		//画像保持
	//static bool anyprocessed;	//この処理で既にほかのフェンスが処理されているか

	Rect rect = Rect(FENCE_SIZE,FENCE_SIZE,&this->x,&this->y);		//あたり判定
	Fence(int x,int y);
	~Fence();
	
	void Draw();
	bool HasNext();						//次の要素があるか。
	int HitCheckReturnFace(Rect rect);			//rectが あたっているかを調べる。 戻り値はrectを中心として当たった面
	static void AllDelete();
	static void AllDelete(Fence *fence);
	void ChainMaker();		//インスタンスの鎖に追加。
	void ChainCutter();		//インスタンスの鎖から取り除く。

	static int PlayerHitCheck(Rect rect);	// プレイヤーから呼ばれるのはここだけ//プレイヤーのあたり判定を渡す//当たっているめんが限定的である場合正しい面が出る
};

