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

	//�摜�����܂����炱�̏�����������
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
			vx *= -1;	//�I�u�W�F�N�g�ɂԂ������甽�]
		}
	}
	//else if (startflag) {
	//	deathflag = true;	//��x�`�悳�ꂽ�̂���ʊO�ɏo���玀�S
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
