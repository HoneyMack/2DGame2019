#pragma once
#include "Dxlib.h"
//相対位置で指定

class Rect
{
public:
	double *gx, *gy;									//親オブジェクトの座標
	int x, y;											//親に対する相対座標をもつ（例外あり）
	int sizeX, sizeY;
	Rect(int sizeX,int sizeY,double *gx,double *gy);
	~Rect();
	void Draw(int x,int y);				//任意座標に描画
	void Draw(Rect Camera);	//カメラと親座標からスクリーンに描画
};

