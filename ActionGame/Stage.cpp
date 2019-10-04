#include "Stage.h"

Mob* Stage::mob = nullptr;	//�ŏ��͓G�𐶐����Ȃ�
Fence* Stage::fence = nullptr;

int Stage::limit = 0;

Stage::Stage()
{
	Camera = new Rect(WIDTH, HEIGHT, nullptr, nullptr);	//�J�����̑傫�����w��
	usingP = new Player();				//�v���C���[���쐬
	usingM = new Map();					//�}�b�v���쐬						


	usingP->map = usingM;				//�v���C���[�Ƀ}�b�v���Z�b�g
	usingP->Camera = Camera;			//�v���C���[�ɃJ�������Z�b�g	
	Object::Camera = Camera;			//Mob�ɃJ�����ƃ}�b�v����^����
	Object::map = usingM;
	Object::usingP = usingP;			//�v���C���[��set
}

Stage::~Stage()
{
	Mob::AllDelete(mob);
	Fence::AllDelete(fence);

	//���������Ă��Ȃ����Ƃ�ۏ�
	mob = nullptr;
	fence = nullptr;

	//���I���������������J��
	delete Camera;
	delete usingP;
	delete usingM;
}


void Stage::AllUpdate(double ftime) {
	//�w�i�摜�K�؂ɕ`�揈��(�J�����Ō����Ă���Ƃ��낾��)
	int i = Camera->x / MAPPARTS_X  -1;
	while (i *MAPPARTS_X < Camera->x + WIDTH) {
		//�摜�������ƘA������悤�ɂ���.�摜���Ȃ��Ƃ���͔�����
		DrawGraph(i*MAPPARTS_X-Camera->x, 0, mapparts[i % ACCOUNTFORMAPPARTS], TRUE);
		i++;
	}

	//�c�莞�Ԍ���
	limit -= ftime * 1000;
	//��������̃t���b�V���u���b�N�������ꂽ���𔻒�̂���true = �����Ă���
	FlashBlock::flashingflag = false;
	//Fence::anyprocessed = false;	//��x�ł��������ꂽ���̏���

	Update(mob, ftime);
	switch (mode) {
	case CROSSKEYANDJUMP:
		usingP->Motion(ftime);
		//���Ƃ��ăv���C���[�𒆐S�Ɉړ��B�������A�z������Ȃ��悤�ɂ���
		if (usingP ->x - WIDTH / 2 > 0 && usingP->x + WIDTH / 2 < usingM->getNumX() *DOT)
			Camera->x = usingP->x - WIDTH / 2;
		break;
	case FORCEHORIZONTALSCROLL:
		//�����X�N���[��������
		Camera->x += ftime *SCROLLSPEED;
		usingP->Motion(ftime);
		break;
	}

}

void Stage::AllDraw() {


	usingP->Draw();
	usingM->Draw(Camera);

	Draw(mob);
	AddDraw(mob);
}
void Stage::Update(Mob* mob, double ftime) {
	//�G�̏����̊�{�`
	if (mob != nullptr) {		//�C���X�^���X��ێ����Ă��邩
		if (mob->deathflag == false)
		mob->Motion(ftime);
		while (mob->HasNext()) {	//���̃C���X�^���X��ێ����Ă�����
			mob = mob->next;
			if (mob->deathflag == false)
			mob->Motion(ftime);
		}
	}
}
void Stage::Draw(Mob *mob) {
	//�G�̕`��̊�{�`
	if (mob != nullptr) {		//�C���X�^���X��ێ����Ă��邩
		if (mob->deathflag == false)
		mob->Draw();
		while (mob->HasNext()) {	//���̃C���X�^���X��ێ����Ă�����
			mob = mob->next;
			if(mob ->deathflag ==false)
			mob->Draw();
		}
	}
}
void Stage::AddDraw(Mob *mob) {
	//�G�̕`��̊�{�`
	if (mob != nullptr) {		//�C���X�^���X��ێ����Ă��邩
		if (mob->deathflag == false)
			mob->AddDraw();
		while (mob->HasNext()) {	//���̃C���X�^���X��ێ����Ă�����
			mob = mob->next;
			if (mob->deathflag == false)
				mob->AddDraw();
		}
	}
}

void Stage::AllReset() {
	Camera->x = 0;
	Camera->y = 0;

	usingM->resetMap();
	usingP->Reset();

	//�c��^�C��,�|�����G��0��
	limit = 0;
	Mob::killedenemy = 0;

	//�}�b�v���甲����Ƃ��ɏ����R�C�����[����
	Coin::hadcoins = 0;

	//�C���X�^���X�̍�������
	Mob::AllDelete(mob);
	Fence::AllDelete(fence);

	//���������Ă��Ȃ����Ƃ�ۏ�
	mob = nullptr;
	fence = nullptr;

}

void Stage::CreateWalkEnemy(int x, int y) {
	if (mob == nullptr)
		mob = new WalkEnemy(x, y);
	else
		new WalkEnemy(x, y);
}

void Stage::CreateFlashBlock(int x, int y) {
	if (mob == nullptr)
		mob = new FlashBlock(x, y);
	else
		new FlashBlock(x, y);
}

void Stage::CreateShootLaser(int x) {
	if (mob == nullptr)
		mob = new ShootLaser(x);
	else
		new ShootLaser(x);
}

void Stage::CreateUpDownObject(int x, int y) {
	if (mob == nullptr)
		mob = new UpDownObject(x, y);
	else
		new UpDownObject(x, y);
}
void Stage::CreateShootEnemy(int x, int y) {
	if (mob == nullptr)
		mob = new ShootEnemy(x, y);
	else
		new ShootEnemy(x, y);
}

void Stage::CreateCoin(int x,int y) {
	if (mob == nullptr)
		mob = new Coin(x, y);
	else
		new Coin(x, y);
}

void Stage::CreateLift(int x, int y, bool direction) {
	if (mob == nullptr)
		mob = new Lift(x, y, direction);
	else
		new Lift(x, y, direction);
}

void Stage::CreateFireBar(int x, int y) {
	if (mob == nullptr)
		mob = new FireBar(x, y);
	else
		new FireBar(x, y);
}
void Stage::CreateFireBar(int x, int y, int length, int number) {
	if (mob == nullptr)
		mob = new FireBar(x, y, length, number);
	else
		new FireBar(x, y, length, number);
}

void Stage::CreateFireBar(int x, int y, double speed) {
	if (mob == nullptr)
		mob = new FireBar(x, y, speed);
	else
		new FireBar(x, y, speed);
}

void Stage::CreateFireBar(int x, int y, bool direction) {
	if (mob == nullptr)
		mob = new FireBar(x, y, direction);
	else
		new FireBar(x, y, direction);
}

void Stage::CreateFireBar(int x, int y, int angle) {
	if (mob == nullptr)
		mob = new FireBar(x, y, angle);
	else
		new FireBar(x, y, angle);
}

void Stage::CreateFireBar(int x, int y, double speed, bool direction, int length, int number, int angle) {
	if (mob == nullptr)
		mob = new FireBar(x, y, speed, direction, length, number, angle);
	else
		new FireBar(x, y, speed, direction, length, number, angle);
}


void Stage::CreateRope(int x, int y,int ropenum) {
	if (mob == nullptr)
		mob = new Rope(x, y,ropenum);
	else
		new Rope(x, y,ropenum);
}

void Stage::CreateJump(int x, int y)
{
	if (mob == nullptr)
		mob = new Jump(x, y);
	else
		new Jump(x, y);
}

void Stage::CreateFallWall(int x, int y) {
	if (mob == nullptr)
		mob = new FallWall(x, y);
	else
		new FallWall(x, y);
}
void Stage::CreateTurtle(int x, int y) {
	if (mob == nullptr)
		mob = new Turtle(x, y);
	else
		new Turtle(x, y);
}
void Stage::CreateHanmerThrow(int x, int y, double iv) {
	if (mob == nullptr)
		mob = new HanmerThrow(x, y, iv);
	else
		new HanmerThrow(x, y, iv);
}

void Stage::CreateGhost(int x, int y) {
	if (mob == nullptr)
		mob = new Ghost(x, y);
	else
		new Ghost(x, y);
}

void Stage::CreateThornBlock(int x, int y) {
	if (mob == nullptr)
		mob = new ThornBlock(x, y);
	else
		new ThornBlock(x, y);
}
void Stage::CreateFence(int x, int y) {
	if (fence == nullptr)
		fence = new Fence(x, y);
	else
		new Fence(x, y);
}

void Stage::CreateFish(int x, int y)
{
	if (mob == nullptr)
		mob = new Fish(x, y);
	else
		new Fish(x, y);
}

void Stage::CreateCrab(int x, int y)
{
	if (mob == nullptr)
		mob = new Crab(x, y);
	else
		new Crab(x, y);
}
void Stage::CreateShip(int x, int y, double angle)
{	
	if (mob == nullptr)
		mob = new Ship(x, y, angle);
	else
		new Ship(x, y, angle);
}

void Stage::CreatePenguin(int x, int y)
{
	if (mob == nullptr)
		mob = new Penguin(x, y);
	else
		new Penguin(x, y);
}
