#include "Eel.h"

int Eel::PicHandle = 0;

Eel::Eel(int x, int y, bool direction)
{
	this->x = x;
	this->y = y;

	if (direction)
		vx = EEL_MOVESPEED;
	else
		vx = EEL_MOVESPEED;

	ay = 0;

	//画像が決まったらこの処理を見直す
	GetGraphSize(PicHandle, &rect.x, &rect.y);
	rect.x /= 2;
	rect.y /= 2;
	rect.x -= rect.sizeX / 2;
	rect.y -= rect.sizeY / 2 - 2;
}

Eel::~Eel()
{
}

void Eel::Motion(double frametime)
{
	if (CheckInCam()) {
		startflag = true;

		int hitface = 0x0000;
		hitface = stepRect_x(rect, frametime);
		if ((hitface & RIGHT) || (hitface & LEFT)) {
			vx *= -1;	//オブジェクトにぶつかったら反転
		}
	}
	//else if (startflag) {
	//	deathflag = true;	//一度描画されたのち画面外に出たら死亡
	//}
}

void Eel::Draw()
{
	if (CheckInCam()) {
		if (vx > 0)
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
		else
			DrawTurnGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);

#ifdef DEBUG
		rect.Draw(*Camera);
#endif // DEBUG

	}
}

bool Eel::HitCheck(Rect rect)
{
	if (CheckRectRect(rect, this->rect)) {
		HitPlayer();
		return true;
	}
	else
		return false;
}

void Eel::HitPlayer()
{
	usingP->Damage(EEL_HITDAMAGE, ENEMYMATCHLESSTIME);
}
