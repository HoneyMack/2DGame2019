#pragma once
#include "Mob.h"
#include "Object.h"

class SeaWeed :
	public Object, public Mob
{
public:
	static int PicHandles[SEAWEED_TOTALPICTURES];

	//weed�̌�
	int width, height;

	/*(_x,_y):�C���̎n�_�Awidth:�C���u���b�N�̉��̐�(�E�ɐL�т�j�Aheight:�C���u���b�N�c�̐�(���ɐL�т�)*/
	SeaWeed(int _x, int _y, int _width = 1, int _height = 1);

	void Motion(double frametime) override;
	void Draw() override;
};

