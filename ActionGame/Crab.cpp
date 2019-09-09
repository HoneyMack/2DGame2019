#include "Crab.h"

int Crab::PicHandle = 0;

Crab::Crab(int x, int y)
{
	this->x = centerX = x;
	this->y = y;

	velocity = CRAB_SPEED;

	//弾の初期化
	for (int i = 0; i < CRAB_BULLETS; i++) {
		BTP[i] = new BulletTowardPlayer(x, y);
		BTP[i]->ay = 0;
		BTP[i]->picflag = false;
	}

	

	//当たり判定を画像の中心に	画像が確定したら確認する
	GetGraphSize(PicHandle, &rect.x, &rect.y);
	rect.x /= 2;
	rect.y /= 2;
	rect.x -= rect.sizeX / 2;
	rect.y -= rect.sizeY / 2 - 2;
}

Crab::~Crab()
{
	for (int i = 0; i < CRAB_BULLETS; i++) {
		delete BTP[i];
	}
}

void Crab::Motion(double frametime)
{
	//基本は横移動
	//弾をShootEnemyを参考にして上方に打ち上げる処理を追加
	if (CheckInCam()) {
		int hitface = 0x0000;
		
		//指定した幅の名毛で往復移動する　端に来たら反転
		if (vecX + velocity * frametime > CRAB_MOVEWIDTH / 2 || vecX + velocity * frametime < -CRAB_MOVEWIDTH / 2) {
			velocity = -velocity;
		}

		//移動量更新
		vecX += velocity * frametime;

		//実際の位置更新
		x = centerX + vecX;

		hitface = stepRect_x(rect, frametime);
		if ((hitface & RIGHT) || (hitface & LEFT)) {
			velocity = -velocity;
		}

		hitface = stepRect_y(rect, frametime);
		if ((hitface & BOTTOM) || (hitface & TOP)) {
			vy = 0.0;
		}

		//球を打つ処理
		pasttime += frametime;
		if (pasttime * 1000 - CRAB_TIMEBFOREFIRING > bulletcounter * CRAB_FIRINGSPEED
			&& bulletcounter < CRAB_BULLETS) {
			//もし発射まで十分に待っていたら
			BTP[bulletcounter]->x = x;
			BTP[bulletcounter]->y = y;

			BTP[bulletcounter]->vx = 0;
			BTP[bulletcounter]->vy = -BUBBLE_SPEED;

			bulletcounter++;

			//サウンド処理を音を作ったら入れる
		}
		if (pasttime * 1000 > CRAB_INTERVAL) {
			bulletcounter = 0;
			pasttime = 0;
		}
	}
	else {
		//カメラ外　時間リセット
		pasttime = 0.0;
	}
	//弾の更新
	for (int i = 0; i < bulletcounter; i++)
		BTP[i]->Motion(frametime);
}

void Crab::Draw()
{
	if (CheckInCam()) {
		if(velocity <= 0)
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
		else
			DrawTurnGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
#ifdef DEBUG
		rect.Draw(*Camera);
#endif			
	}
	//弾の描画処理
	for (int i = 0; i < bulletcounter; i++) {
		BTP[i]->Draw();
	}
}

bool Crab::HitCheck(Rect rect)
{
	//return false;
	bool returnflag = false;
	if (CheckInCam()) {
		if (CheckRectRect(this->rect, rect)) {
			usingP->Damage(CRAB_HITDAMAGE, ENEMYMATCHLESSTIME);
			returnflag = true;
		}
	}
	for (int i = 0; i < bulletcounter; i++) {
		//弾とぶつかっているか
		if (CheckCircleRect(*BTP[i]->cir, rect)) {
			returnflag = true;
			usingP->Damage(BUBBLE_HITDAMAGE, ENEMYMATCHLESSTIME);
		}

		return returnflag;
	}
}
