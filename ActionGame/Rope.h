#pragma once
#include "Object.h"
#include "Mob.h"
#include "define.h"
#include "Player.h"


class Rope : public Object, public Mob
{
public:
	static int rope_PicHandle;			//ロープ画像
	static int fixture_PicHandle;		//固定具画像
	static int FsizeX, FsizeY;			//固定具の画像の大きさ

	int ropelen;					//ロープの長さを保持
	int ropenum;					//何本のロープを使用するか
	Rect fixture = Rect(ROPE_FIXTURE_SIZEX, ROPE_FIXTURE_SIZEY, &this->x, &this->y);			//固定具
	Rect rope = Rect(ROPE_SIZEX, ROPE_SIZEY, &this->x, &this->y);				//ロープ
	bool catchflag;		//今ロープにつかんでいるか

	double invalidation = 100;		//ジャンプ後に当たり判定の無効か時間を設定する
					
	bool hitflag = false;

	Rope(int x, int y,int ropenum);		//コンストラクタ
	~Rope();

	void Motion(double frametime);
	bool HitCheck(Rect rect);	//Player->Enemy　あたり判定
	void Draw();
};
