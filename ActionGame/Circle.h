#pragma once
#include "Dxlib.h"
#include "Rect.h"


class Circle
{
public:
	int radius;			//���a
	int x, y;			//�~�̒��S�̑��΍��W
	double *gx, *gy;		//�e�I�u�W�F�N�g�̍��W�������|�C���^
	Circle(int radius , double *gx, double *gy);
	~Circle();
	void Draw(int x,int y);		//�~�̕`��
	void Draw(Rect Camera);
};

