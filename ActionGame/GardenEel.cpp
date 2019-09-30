#include "GardenEel.h"
#include "Stage.h"
int GardenEel::PicHandle = 0; //チンアナゴ画像ハンドル保持


GardenEel::GardenEel(int _x, int _y, int _initPhase) {
	initX = x = _x;
	initY = y = _y;
	initPhase = _initPhase;

	//当たり判定の位置調整入れる予定(画像次第)
}

void GardenEel::Motion(double ftime) {
	if (CheckInCam() || CheckInCam(x + GARDENEEL_SIZEX, y)) {
		//現在の位置を計算し代入
		int time = (GARDENEEL_HIDINGTIME + GARDENEEL_RISINGTIME + GARDENEEL_HOLDINGTIME + GARDENEEL_FALLINGTIME) - (Stage::limit + initPhase) % (GARDENEEL_HIDINGTIME + GARDENEEL_RISINGTIME + GARDENEEL_HOLDINGTIME + GARDENEEL_FALLINGTIME);
		if (time < GARDENEEL_HIDINGTIME) y = initY; //見えないように
		else if (time < GARDENEEL_HIDINGTIME + GARDENEEL_RISINGTIME) {
			//等速直線運動で上昇
			time -= GARDENEEL_HIDINGTIME;
			y = initY - (int)(GARDENEEL_SIZEY * (double)time / GARDENEEL_RISINGTIME);
		}
		else if (time < GARDENEEL_HIDINGTIME + GARDENEEL_RISINGTIME + GARDENEEL_HOLDINGTIME) {
			y = initY - GARDENEEL_SIZEY;
		}
		else {
			time -= GARDENEEL_HIDINGTIME + GARDENEEL_RISINGTIME + GARDENEEL_HOLDINGTIME;
			y = initY - (int)(GARDENEEL_SIZEY * (1.0 - (double)time / GARDENEEL_FALLINGTIME));
		}
	}
}

void GardenEel::Draw() {
	//チンアナゴが少しでも写っていたら描画
	if (CheckInCam() || CheckInCam(x + GARDENEEL_SIZEX, y)) {
		//現在位置から初期位置まで描画
		DrawRectGraph(RelativePosX(), RelativePosY(), 0, 0, GARDENEEL_SIZEX, initY - y, PicHandle, TRUE);
	}
#ifdef DEBUG
	//collider.Draw(*Camera);
#endif 
}

bool GardenEel::HitCheck(Rect rect) {
	//当たり判定同士が衝突しているかつ、HidingTime中ではない
	if (CheckRectRect(rect, collider)
		&& (Stage::limit + initPhase) % (GARDENEEL_HIDINGTIME + GARDENEEL_RISINGTIME + GARDENEEL_FALLINGTIME + GARDENEEL_HOLDINGTIME)
		> GARDENEEL_HIDINGTIME) {
		HitPlayer();
		return true;
	}
	return false;
}

void GardenEel::HitPlayer() {
	usingP->Damage(GARDENEEL_DAMAGE, ENEMYMATCHLESSTIME);
}