#include "SnowMan.h"

int SnowMan::PicHandle = 0;
int SnowBall::PicHandle = 0;



SnowBall::SnowBall(int _x, int _y) {
	x = _x;
	y = _y;
}

void SnowBall::Motion(double ftime) {
	//画面内にいるとき、処理する
	if (CheckInCam()) {
		int hitface = stepCircle_x(cir, ftime);
		//壁に衝突していたら殺す
		if ((hitface & RIGHT) || (hitface & LEFT)) deathflag = true;

		//移動量に応じて球を回転
		angle += (vx * ftime) / (SNOWBALL_RADIUS);

		hitface = stepCircle_y(cir, ftime);		//y方向の時間を進める
		if ((hitface & BOTTOM) || (hitface & TOP)) {
			vy = 0.0;
		}
		//落下しても死ぬようにする
		if (y > HEIGHT)
			deathflag = true;
	}
	else {
		//画面外に出たら殺す
		deathflag = true;
	}
}

void SnowBall::Draw() {
	//画面内にいるとき、処理する
	if (CheckInCam()) {
		DrawRotaGraph(RelativePosX(), RelativePosY(), 1.0, angle, PicHandle, TRUE);
	}
}

bool SnowBall::HitCheck(Rect rect) {
	if (CheckCircleRect(this->cir, rect)) {
		Object::usingP->Damage(SNOWBALL_DAMAGE, ENEMYMATCHLESSTIME);
		return true;
	}
	return false;
}

SnowMan::SnowMan(int _x, int _y,bool _direction) {
	x = _x;
	y = _y;
	direction = _direction;
	ballSetFlag = true;
	counter = 0;
	ball = new SnowBall(x, y); //要位置修正
}

void SnowMan::Motion(double ftime) {
	//画面内にいるとき、処理する
	if (CheckInCam()) {
		counter += ftime * 1000;
		//ハイジャンプ用フラグ
		
		if (waittime < KILLHIGHJUMPTIME) {
			waittime += ftime * 1000;
			//ハイジャンプ可能にする
			if (usingP->now_key & PAD_INPUT_10) {
				usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
				PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
				waittime = KILLHIGHJUMPTIME;
			}
		}
		

		//移動
		int hitface = stepRect_x(rect, ftime);
		hitface = stepRect_y(rect, ftime);		//y方向の時間を進める
		if ((hitface & BOTTOM) || (hitface & TOP)) {
			vy = 0.0;
		}

		if (ball->deathflag) {
			//もし球が死んでいる（画面外である）なら自分のところに戻し、玉の速度0,生き返らせる
			ball->x = x;
			ball->y = y; //位置要修正
			ball->vx = 0;
			ball->deathflag = false;
			ballSetFlag = true;
		}
		//もう一度転がす時間になっていて、かつボールが再装填済みであれば転がす
		if (counter > SNOWMAN_THROWINTERVAL && ballSetFlag) {
			ballSetFlag = false;
			if (direction) ball->vx = -SNOWBALL_VELOCITY;
			else ball->vx = SNOWBALL_VELOCITY;
			counter -= SNOWMAN_THROWINTERVAL;
		}
	}
}

void SnowMan::Draw() {
	//画面内にいるとき、処理する
	if (CheckInCam()) {
		DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE); //自分を描画
	}
}

bool SnowMan::HitCheck(Rect rect) {
	if (CheckRectRect(rect, this->rect)) {
		//プライヤーが落下してきて、自分の上にあたっていたら自分が死んでプレイヤーにダメージは入らない
		if (HitFaceRectRect(rect, this->rect) & TOP && usingP->vy > 0 && usingP->Ymovingflag && !(HitFaceRectRect(rect, this->rect) & BOTTOM)) {
			killedenemy++;
			PlaySoundMem(Sound::sounds[SOUND_ENEMYTREAD], DX_PLAYTYPE_BACK);
			deathflag = true;
			ball->deathflag = true;//玉も非表示に
			usingP->Knuckled(this->rect, BOTTOM);

			waittime = 0;
			//ハイジャンプ可能にする
			usingP->Animation(JUMP);
			if (usingP->now_key & PAD_INPUT_10) {

				usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
				PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
				waittime = KILLHIGHJUMPTIME;
				//usingP->vy = -JUMPSPEED;
			}
			usingP->vy = -KILLJUMP;
		}
		else
			usingP->Damage(SNOWMAN_DAMAGE, ENEMYMATCHLESSTIME);
		return true;
	}
	else
		return false;
}
