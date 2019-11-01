#include "Eel.h"

int Eel::PicHandle = 0;

Eel::Eel(int x, int y, bool direction)
{
	this->x = x;
	this->y = y;

	if (direction)
		vx = EEL_MOVESPEED;
	else
		vx = -EEL_MOVESPEED;

	ay = 0;

	rect.sizeX = 50;
	rect.sizeY = 11;
	rect.x = 0;
	rect.y =45;
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
		if (vx < 0) {
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
			rect.x = 0;
		}
		else {
			DrawTurnGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
			rect.x = 16;
		}

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
