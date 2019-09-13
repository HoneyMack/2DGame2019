#pragma once

#include "Player.h"
#include "WalkEnemy.h"
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
#include "HanmerThrow.h"
#include "Ghost.h"
#include "ThornBlock.h"
#include "Fence.h"
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
	Rect *Camera;					//�`��͈͎w��p��`�̗p��
	Player *usingP;					//�v���C���[
	Map *usingM;					//�}�b�v
	int mapparts[ACCOUNTFORMAPPARTS];	//�w�i�摜�̒f��

	static Fence *fence;
	static Mob *mob;	//�G�ꊇ�Ǘ�

	Stage();
	~Stage();

	void AllUpdate(double frametime);
	void AllDraw();
	
	void AllReset();

	void Update(Mob* mob, double frametime);//mob�C���X�^���X�̃|�C���^��n���Ɠn����Mob�̏��������Ă����
	void Draw(Mob* mob);					//mob�C���X�^���X�̃|�C���^��n���Ɠn����Mob�̕`������Ă����
	void AddDraw(Mob* mob);							//mob�C���X�^���X�̃|�C���^��n���Ɠn����Mob�̕`��(�ǉ�)�����Ă����
	void CreateWalkEnemy(int x, int y);
	void CreateFlashBlock(int x, int y);
	void CreateShootLaser(int x);
	void CreateUpDownObject(int x, int y);
	void CreateShootEnemy(int x ,int y);
	void CreateCoin(int x,int y);
	void CreateLift(int x, int y, bool direction);
	void CreateRope(int x,int y,int ropenum);
	void CreateJump(int x, int y);
	void CreateFallWall(int x,int y);
	void CreateTurtle(int x, int y);

	void CreateFireBar(int x, int y);
	void CreateFireBar(int x, int y, int length, int number);
	void CreateFireBar(int x, int y, double speed);
	void CreateFireBar(int x, int y, bool direction);
	void CreateFireBar(int x, int y, int angle);
	void CreateFireBar(int x, int y, double speed, bool direction, int length, int number, int angle);

	void CreateHanmerThrow(int x, int y, double iv);
	void CreateGhost(int x, int y);
	void CreateThornBlock(int x,int y);
	void CreateFence(int x, int y);

	void CreateShip(int x, int y, double angle);
};