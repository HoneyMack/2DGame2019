#pragma once
#include "Dxlib.h"
#include "Rect.h"


class Circle
{
public:
	int radius;			//半径
	int x, y;			//円の中心の相対座標
	double *gx, *gy;		//親オブジェクトの座標を示すポインタ
	Circle(int radius , double *gx, double *gy);
	~Circle();
	void Draw(int x,int y);		//円の描画
	void Draw(Rect Camera);
};

