#include "ShootLaser.h"

int ShootLaser::PicHandle_laser = 0;
int ShootLaser::PicHandle_dispenser = 0;


ShootLaser::ShootLaser(int x) :Object(), laserX() {
	//レーザーの大きさの初期化
	for (int i = 0; i < SHOOTLASER_SHOTTIMES; i++) {
		laser[i] = new Rect(384, 12, &this->x, &this->y);	//レーザーの大きさx = 384,y = 12
	}
	this->x = x;
}


ShootLaser::~ShootLaser()
{
}

void ShootLaser::Shoot(double ftime) {
	timecount += ftime;
	//時間一定以上経過& 発射する球数を超えていないか
	if (timecount * 1000 >= SHOOTLASER_LASERINTERVAL * shotcount && shotcount < SHOOTLASER_SHOTTIMES) {
		laserX[shotcount] = SHOOTLASER_POSX + 164;	//-はレーザーが発射されているように見せるため
		laser[shotcount]->y = shotcount*SHOOTLASER_MOVEINTERVAL + 15; //+はオフセット

		//音を出す
		PlaySoundMem(Sound::sounds[SOUND_LASERSHOT], DX_PLAYTYPE_BACK);
		shotcount++;
	}
	else {	//間の時間
		//まだ次の発射位置についていないなら追加
		if (y < SHOOTLASER_MOVEINTERVAL * shotcount && timecount *1000> SHOOTLASER_LASERINTERVAL * (shotcount-1) + SHOOTLASER_SHOOTWAITTIME)
			y += (double)SHOOTLASER_MOVEINTERVAL / (SHOOTLASER_LASERINTERVAL - SHOOTLASER_WAITTIME- SHOOTLASER_SHOOTWAITTIME) * ftime * 1000; //ディスペンサーを動かす
	}
}

void ShootLaser::Motion(double ftime) {
	if (CheckInCam() && !startflag && onceflag) {	//画面に映ったらフラグをtrueに
		startflag = true;
		onceflag = false;
		timecount = 0.0;
	}
	if (startflag == true) {
		Shoot(ftime);
		//発射されたレーザーのみを移動
		for (int i = 0; i < shotcount; i++) {
			laserX[i] -= SHOOTLASER_LASERSPEED*ftime;
		}
		//もし最後のレーザーが画面外に出たら初期化
		if (shotcount == SHOOTLASER_SHOTTIMES && laserX[SHOOTLASER_SHOTTIMES - 1] - Camera->x < 0)
			Reset();
	}

}

void ShootLaser::Draw() {
	if (startflag == true) {
		//発射されたレーザーのみを描画
		for (int i = 0; i < shotcount; i++) {
			DrawGraph(laserX[i], laser[i]->y +2, PicHandle_laser, TRUE);
			
#ifdef DEBUG
			Rect drect = *laser[i];//あたり判定描画
			drect.y = SHOOTLASER_MOVEINTERVAL* i + Camera->y - y + 18;
			drect.x = laserX[i] + Camera->x - x;
			drect.Draw(*Camera);
#endif
			
		}
		//ディスペンサーの描画
		if (shotcount < SHOOTLASER_SHOTTIMES)	//最後を発射するまで
			DrawGraph(SHOOTLASER_POSX, y, PicHandle_dispenser, TRUE);
	}
}

bool ShootLaser::HitCheck(Rect rect) {
	if (startflag == true) {
		//発射されたレーザーのみを判定対象に
		for (int i = 0; i < shotcount; i++) {
			Rect drect = *laser[i];
			drect.y = SHOOTLASER_MOVEINTERVAL* i + Camera->y - y + 18;
			drect.x = laserX[i] + Camera->x - x;
			if (CheckRectRect(drect, rect)) {
				HitPlayer();
				return true;
			}
		}
	}
	return false;
}

void ShootLaser::HitPlayer() {
	usingP->Damage(SHOOTLASER_HITDAMAGE,ENEMYMATCHLESSTIME);
}

void ShootLaser::Reset() {
	shotcount = 0;
	y = 0;
	startflag = false;
}