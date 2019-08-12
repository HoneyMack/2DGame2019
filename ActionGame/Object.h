#pragma once

#include "define.h"
#include "Map.h"
#include "DxLib.h"
#include "Player.h"
#include "Circle.h"

class Object
{
public:
	static Map *map;		//マップの情報を持つ
	static Rect *Camera;	//カメラ情報を持つ
	static Player *usingP;	//プレイヤー情報を持つ

	double x, y;			//座標
	double vx, vy;			//速度
	double ax, ay;			//加速度

	Object();		
	Object(double dx, double dy, double dvx, double dvy, double dax, double day);
	virtual ~Object();

	Object nextPosX(double frametime);		//次に進んだ時のX方向のみの情報を返す
	Object nextPosY(double frametime);		//次に進んだ時のY方向のみの情報を返す
	Object nextPosAll(double frametime);	//次に進んだ時の情報を返す
	void stepPosX(double frametime);		//X方向のみ進む
	void stepPosY(double frametime);		//Y方向のみ進む
	void stepPosAll(double frametime);		//次の座標に進む

	int stepRect_x(Rect rect, double frametime);					//マップ上のブロックとぶつかっていたらぶつからないように戻しながらx方向の時間を進める。
	int stepRect_y(Rect rect, double frametime);					//マップ上のブロックとぶつかっていたらぶつからないように戻しながらy方向の時間を進める。
	int stepCircle_x(Circle cir, double frametime);					//マップ上のブロックとぶつかっていたらぶつからないように戻しながらx方向の時間を進める。(戻し方はRectと一緒にする)
	int stepCircle_y(Circle cir, double frametime);					//マップ上のブロックとぶつかっていたらぶつからないように戻しながらy方向の時間を進める。(戻し方はRectと一緒にする)

	int CheckMapNum(Object Ob, int vecX, int vecY);	//オブジェクト＋ベクトルの位置のマップ番号を返す

	//bool CheckHitPlayer(Rect rect);				//長方形rectがプレイヤーとぶつかっているか

	bool CheckInCam();								//描画内にオブジェクトがあるか。
static 	bool CheckInCam(double x, double y);			//描画領域中にx,yは含まれているか
static 	bool CheckInCam(int x, int y);			//描画領域中にx,yは含まれているか

	double RelativePosX();							//スクリーン内座標
	double RelativePosY();							//スクリーン内座標
};