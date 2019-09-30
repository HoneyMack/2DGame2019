#pragma once
#include "Mob.h"
#include "Object.h"

class SeaWeed :
	public Object, public Mob
{
public:
	static int PicHandles[SEAWEED_TOTALPICTURES];

	//weedΜΒ
	int width, height;

	/*(_x,_y):CΜn_Awidth:CubNΜ‘Μ(EΙLΡιjAheight:CubNcΜ(ΊΙLΡι)*/
	SeaWeed(int _x, int _y, int _width = 1, int _height = 1);

	void Motion(double frametime) override;
	void Draw() override;
};

