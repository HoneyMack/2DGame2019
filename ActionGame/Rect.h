#pragma once
#include "Dxlib.h"
//���Έʒu�Ŏw��

class Rect
{
public:
	double *gx, *gy;									//�e�I�u�W�F�N�g�̍��W
	int x, y;											//�e�ɑ΂��鑊�΍��W�����i��O����j
	int sizeX, sizeY;
	Rect(int sizeX,int sizeY,double *gx,double *gy);
	~Rect();
	void Draw(int x,int y);				//�C�Ӎ��W�ɕ`��
	void Draw(Rect Camera);	//�J�����Ɛe���W����X�N���[���ɕ`��
};

