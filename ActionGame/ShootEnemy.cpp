#include "ShootEnemy.h"

int ShootEnemy::PicHandle = 0;

ShootEnemy::ShootEnemy(int x, int y)
{
	this->x = centerX = x;
	this->y = y;

	velocity = SHOOTENEMY_MOVESPEED;

	//弾の初期化
	for (int i = 0; i < SHOOTENEMY_BULLETS; i++) {
		BTP[i] = new BulletTowardPlayer(x, y);
		BTP[i]->ay = 0;	//重力を0に
	}
	//あたり判定を画像の中心に
	GetGraphSize(PicHandle, &rect.x, &rect.y);
	rect.x /= 2;
	rect.y /= 2;
	rect.x -= rect.sizeX / 2;
	rect.y -= rect.sizeY / 2 - 2;

}


ShootEnemy::~ShootEnemy()
{
	for (int i = 0; i < SHOOTENEMY_BULLETS; i++)
		delete BTP[i];
}

void ShootEnemy::Motion(double frametime) {
	//カメラ内であるかどうか
	if (CheckInCam()) {
		//ハイジャンプ用フラグ
		if (waittime < KILLHIGHJUMPTIME) {
			waittime += frametime * 1000;
			//ハイジャンプ可能にする
			if (InKeyTrigger(usingP->now_key, PAD_INPUT_10)) {
				usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
				PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
				waittime = KILLHIGHJUMPTIME;
			}
		}
		int hitface = 0x0000;

		//指定した幅の中で往復移動させるために、端に来たら速度を反転
		if (vecX + velocity * frametime > SHOOTENEMY_MOVEWIDTH / 2 || vecX + velocity * frametime < -SHOOTENEMY_MOVEWIDTH / 2) {
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


		hitface = stepRect_y(rect, frametime);		//y方向の時間を進める
		if ((hitface & BOTTOM) || (hitface & TOP)) {
			vy = 0.0;
		}

		//球を打つ処理
		pasttime += frametime;
		if (pasttime * 1000 - SHOOTENEMY_TIMEBFOREFIRING > bulletcounter * SHOOTENEMY_FIRINGSPEED
			&& bulletcounter < SHOOTENEMY_BULLETS) {
			//もし発射まで十分待っていたら
			//弾をプレイヤーに向ける処理
			BTP[bulletcounter]->x = x;
			BTP[bulletcounter]->y = y;

			double dx = usingP->x - x + 5, dy = usingP->y - y + 10;
			double length = sqrt(dx * dx + dy * dy);
			//ゼロ除算例外
			if (length < ZEROEXCEPTION)
				length = ZEROEXCEPTION;
			BTP[bulletcounter]->vx = dx / length * BULLETTOWARDPLAYER_SPEED;
			BTP[bulletcounter]->vy = dy / length * BULLETTOWARDPLAYER_SPEED;

			bulletcounter++;
			PlaySoundMem(Sound::sounds[SOUND_ENEMYSHOOT], DX_PLAYTYPE_BACK);
		}
		//次の発射に移る
		if (pasttime * 1000 > SHOOTENEMY_INTERVAL) {
			bulletcounter = 0;
			pasttime = 0;
		}
	}
	else {
		//カメラの外の場合は時間をリセット
		pasttime = 0.0;
	}
	//弾の更新
	for (int i = 0; i < bulletcounter; i++)
		BTP[i]->Motion(frametime);
	//落下したときに死ぬようにする
	if (y > HEIGHT)
		deathflag = true;
}

void ShootEnemy::Draw() {
	if (CheckInCam()) {
		//if(!usingP->HitCheck(cir)) //デバッグ用
		if (velocity <= 0)
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
		else
			DrawTurnGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
#ifdef DEBUG
		rect.Draw(*Camera);
#endif			
	}
	//弾の描画
	for (int i = 0; i < bulletcounter; i++)
		BTP[i]->Draw();
}

bool ShootEnemy::HitCheck(Rect rect) {
	bool returnflag = false;
	if (CheckInCam()) {
		//敵とぶつかっているか
		if (CheckRectRect(this->rect, rect)) {
			//プライヤーが落下してきて、自分の上にあたっていたら自分が死んでプレイヤーにダメージは入らない
			if (HitFaceRectRect(rect, this->rect) & TOP && usingP->vy > 0 && usingP->Ymovingflag && !(HitFaceRectRect(rect, this->rect) & BOTTOM)) {
				deathflag = true;
				PlaySoundMem(Sound::sounds[SOUND_ENEMYTREAD], DX_PLAYTYPE_BACK);
				killedenemy++;
				usingP->Animation(JUMP);
				waittime = 0;
				//ハイジャンプ可能にする
				if (usingP->now_key & PAD_INPUT_10) {
					usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
					PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
					waittime = KILLHIGHJUMPTIME;
				}
				usingP->vy = -KILLJUMP;

			}
			else
				usingP->Damage(SHOOTENEMY_HITDAMAGE, ENEMYMATCHLESSTIME);
			returnflag = true;
		}
	}
	for (int i = 0; i < bulletcounter; i++) {
		//弾とぶつかっているか
		if (CheckCircleRect(*BTP[i]->cir, rect)) {
			returnflag = true;
			usingP->Damage(BULLETTOWARDPLAYER_HITDAMAGE, ENEMYMATCHLESSTIME);
		}
	}
	return returnflag;
}
