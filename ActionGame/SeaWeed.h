#pragma once
#include "Mob.h"
#include "Object.h"

class SeaWeed :
	public Object, public Mob
{
public:
	static int PicHandles[SEAWEED_TOTALPICTURES];

	//weedの個数
	int width, height;

	/*(_x,_y):海藻の始点、width:海藻ブロックの横の数(右に伸びる）、height:海藻ブロック縦の数(下に伸びる)*/
	SeaWeed(int _x, int _y, int _width = 1, int _height = 1);

	void Motion(double frametime) override;
	void Draw() override;
};

