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
#include "TurtleWithWing.h"
#include "HanmerThrow.h"
#include "Ghost.h"
#include "Fish.h"
#include "Crab.h"
#include "ThornBlock.h"
#include "Fence.h"
#include "Sea.h"
#include "SeaWeed.h"
#include "GardenEel.h"
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
	Rect* Camera;					//描画範囲指定用矩形の用意
	Player* usingP;					//プレイヤー
	Map* usingM;					//マップ
	int mapparts[ACCOUNTFORMAPPARTS];	//背景画像の断片

	Stage();
	~Stage();

	void AllUpdate(double frametime);
	void AllDraw();

	void AllReset();

	void Update(double frametime);//mobインスタンスのポインタを渡すと渡したMobの処理をしてくれる
	void Draw();					//mobインスタンスのポインタを渡すと渡したMobの描画をしてくれる
	void AddDraw();							//mobインスタンスのポインタを渡すと渡したMobの描画(追加)をしてくれる
};