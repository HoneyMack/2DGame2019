#include "Stage.h"

Mob* Stage::mob = nullptr;	//最初は敵を生成しない
Fence* Stage::fence = nullptr;

int Stage::limit = 0;

Stage::Stage()
{
	Camera = new Rect(WIDTH, HEIGHT, nullptr, nullptr);	//カメラの大きさを指定
	usingP = new Player();				//プレイヤーを作成
	usingM = new Map();					//マップを作成						


	usingP->map = usingM;				//プレイヤーにマップをセット
	usingP->Camera = Camera;			//プレイヤーにカメラをセット	
	Object::Camera = Camera;			//Mobにカメラとマップ情報を与える
	Object::map = usingM;
	Object::usingP = usingP;			//プレイヤーをset
}

Stage::~Stage()
{
	Mob::AllDelete(mob);
	Fence::AllDelete(fence);

	//何も差していないことを保証
	mob = nullptr;
	fence = nullptr;

	//動的生成したメモリ開放
	delete Camera;
	delete usingP;
	delete usingM;
}


void Stage::AllUpdate(double ftime) {
	//背景画像適切に描画処理(カメラで見えているところだけ)
	int i = Camera->x / MAPPARTS_X  -1;
	while (i *MAPPARTS_X < Camera->x + WIDTH) {
		//画像がちゃんと連続するようにする.画像がないところは抜ける
		DrawGraph(i*MAPPARTS_X-Camera->x, 0, mapparts[i % ACCOUNTFORMAPPARTS], TRUE);
		i++;
	}

	//残り時間減少
	limit -= ftime * 1000;
	//何かしらのフラッシュブロックが押されたかを判定のためtrue = 光っている
	FlashBlock::flashingflag = false;
	//Fence::anyprocessed = false;	//一度でも処理されたかの処理

	Update(mob, ftime);
	switch (mode) {
	case CROSSKEYANDJUMP:
		usingP->Motion(ftime);
		//仮としてプレイヤーを中心に移動。ただし、配列を溢れないようにする
		if (usingP ->x - WIDTH / 2 > 0 && usingP->x + WIDTH / 2 < usingM->getNumX() *DOT)
			Camera->x = usingP->x - WIDTH / 2;
		break;
	case FORCEHORIZONTALSCROLL:
		//強制スクロールさせる
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
	//敵の処理の基本形
	if (mob != nullptr) {		//インスタンスを保持しているか
		if (mob->deathflag == false)
		mob->Motion(ftime);
		while (mob->HasNext()) {	//次のインスタンスを保持していたら
			mob = mob->next;
			if (mob->deathflag == false)
			mob->Motion(ftime);
		}
	}
}
void Stage::Draw(Mob *mob) {
	//敵の描画の基本形
	if (mob != nullptr) {		//インスタンスを保持しているか
		if (mob->deathflag == false)
		mob->Draw();
		while (mob->HasNext()) {	//次のインスタンスを保持していたら
			mob = mob->next;
			if(mob ->deathflag ==false)
			mob->Draw();
		}
	}
}
void Stage::AddDraw(Mob *mob) {
	//敵の描画の基本形
	if (mob != nullptr) {		//インスタンスを保持しているか
		if (mob->deathflag == false)
			mob->AddDraw();
		while (mob->HasNext()) {	//次のインスタンスを保持していたら
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

	//残りタイム,倒した敵を0に
	limit = 0;
	Mob::killedenemy = 0;

	//マップから抜けるときに所持コインをゼロに
	Coin::hadcoins = 0;

	//インスタンスの鎖を消去
	Mob::AllDelete(mob);
	Fence::AllDelete(fence);

	//何も差していないことを保証
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
