#pragma once

#include "Player.h"
#include "WalkEnemy.h"
#include "Penguin.h"
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
#include "Polarbear.h"  //new
#include "GardenEel.h"
#include "SnowMan.h"
#include "Map.h"
#include "Rect.h"
#include "Object.h"
#include "define.h"



//�w�i�摜����Ȃ��ƃo�O

class Stage
{
public:
	int mode = CROSSKEYANDJUMP;		//�v���C���[�h
	static	int limit;						//�c�莞��
	Rect* Camera;					//�`��͈͎w��p��`�̗p��
	Player* usingP;					//�v���C���[
	Map* usingM;					//�}�b�v
	int mapparts[ACCOUNTFORMAPPARTS];	//�w�i�摜�̒f��

	Stage();
	~Stage();

	void AllUpdate(double frametime);
	void AllDraw();

	void AllReset();

	void Update(double frametime);//mob�C���X�^���X�̃|�C���^��n���Ɠn����Mob�̏��������Ă����
	void Draw();					//mob�C���X�^���X�̃|�C���^��n���Ɠn����Mob�̕`������Ă����
	void AddDraw();							//mob�C���X�^���X�̃|�C���^��n���Ɠn����Mob�̕`��(�ǉ�)�����Ă����
};