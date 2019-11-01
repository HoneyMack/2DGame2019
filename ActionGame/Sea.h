#pragma once
#include "Mob.h"
#include "Object.h"
#include "Stage.h"



class Sea : public Object
{
public:
	static int PicHandle[];

	static Sea* first;
	static Sea* last;

	Sea* former;
	Sea* next;


	Rect rect = Rect(SEA_SIZEX, SEA_SIZEY, &this->x, &this->y);

	//static bool InWaterFlag = false;

	Sea(int x, int y,int direction);	//direction:0�g�Ȃ��A�㉺�E���̓�i���l�r�b�g�Ŏw��B��O�����߂�ǂ������̂ŕςȐ������Ȃ��悤�ɁI�I�I�������
	~Sea();

	int direction;

	int index;

	void ChainMaker();	//���X�g�ł��ׂĂ̊C�̔������������
	void ChainCutter();
	bool HasNext();	//���X�g�̎��̗v�f�����邩

	int HitCheckReturnSea(Rect rect);	//rect���������Ă��邩�𒲂ׂ�B�߂�l��rect�𒆐S�Ƃ��ē���������

	static void AllDelete();
	static void AllDelete(Sea* sea);

	void Draw();

	static int PlayerHitCheck(Rect rect);	//Player������Ă΂�鏈��

	//void Motion(double frametime);
	//bool HitCheck(Rect rect);
	//void HitPlayer();

};

