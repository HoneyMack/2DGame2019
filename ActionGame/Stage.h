#pragma once

#include "Player.h"
#include "WalkEnemy.h"
#include "FlashBlock.h"
#include "ShootLaser.h"
#include "UpDownObject.h"
#include "ShootEnemy.h"
#include "FireBar.h"
#include "Lift.h"
#include "Ship.h"
#include "Rope.h"
#include "Jump.h"
#include "Coin.h"
#include "FallWall.h"
#include "Turtle.h"
#include "HanmerThrow.h"
#include "Ghost.h"
#include "ThornBlock.h"
#include "Fence.h"
#include "Map.h"
#include "Rect.h"
#include "Object.h"
#include "define.h"



//背景画像入れないとバグ

class Stage
{
public:
	int mode = CROSSKEYANDJUMP;		//プレイモード
static	int limit;						//残り時間
	Rect *Camera;					//描画範囲指定用矩形の用意
	Player *usingP;					//プレイヤー
	Map *usingM;					//マップ
	int mapparts[ACCOUNTFORMAPPARTS];	//背景画像の断片

	static Fence *fence;
	static Mob *mob;	//敵一括管理

	Stage();
	~Stage();

	void AllUpdate(double frametime);
	void AllDraw();
	
	void AllReset();

	void Update(Mob* mob, double frametime);//mobインスタンスのポインタを渡すと渡したMobの処理をしてくれる
	void Draw(Mob* mob);					//mobインスタンスのポインタを渡すと渡したMobの描画をしてくれる
	void AddDraw(Mob* mob);							//mobインスタンスのポインタを渡すと渡したMobの描画(追加)をしてくれる
	void CreateWalkEnemy(int x, int y);
	void CreateFlashBlock(int x, int y);
	void CreateShootLaser(int x);
	void CreateUpDownObject(int x, int y);
	void CreateShootEnemy(int x ,int y);
	void CreateCoin(int x,int y);
	void CreateLift(int x, int y, bool direction);
	void CreateRope(int x,int y,int ropenum);
	void CreateJump(int x, int y);
	void CreateFallWall(int x,int y);
	void CreateTurtle(int x, int y);

	void CreateFireBar(int x, int y);
	void CreateFireBar(int x, int y, int length, int number);
	void CreateFireBar(int x, int y, double speed);
	void CreateFireBar(int x, int y, bool direction);
	void CreateFireBar(int x, int y, int angle);
	void CreateFireBar(int x, int y, double speed, bool direction, int length, int number, int angle);

	void CreateHanmerThrow(int x, int y, double iv);
	void CreateGhost(int x, int y);
	void CreateThornBlock(int x,int y);
	void CreateFence(int x, int y);

	void CreateShip(int x, int y, double angle);
};