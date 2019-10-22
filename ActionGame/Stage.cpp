#include "Stage.h"

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
	Mob::AllDelete();
	Fence::AllDelete();

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

	Update(ftime);
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

	Draw();
	AddDraw();
}
void Stage::Update(double ftime) {
	//敵の処理の基本形
	Mob* mob = Mob::first;
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
void Stage::Draw() {
	//敵の描画の基本形
	Mob* mob = Mob::first;
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

void Stage::AddDraw() {
	//敵の描画の基本形
	Mob* mob = Mob::first;
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
	Mob::AllDelete();
	Fence::AllDelete();
	Sea::AllDelete();
}