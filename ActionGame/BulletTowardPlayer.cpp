#include "BulletTowardPlayer.h"

int BulletTowardPlayer::PicHandle = 0;

BulletTowardPlayer::BulletTowardPlayer(int x, int y)
{
	this->x = x;
	this->y = y;

	cir = new Circle(BULLETTOWARDPLAYER_RADIUS,&this->x,&this->y);

	//�摜�Ƃ����蔻������킹��
	GetGraphSize(PicHandle,&cir->x,&cir->y);
	cir->x /= 2;
	cir->y /= 2;
}


BulletTowardPlayer::~BulletTowardPlayer()
{
	delete cir;
}


void BulletTowardPlayer::Motion(double frametime) {
	if(CheckInCam())
		stepPosAll(frametime);
}

void BulletTowardPlayer::Draw() {
	if (CheckInCam()) {
		DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
#ifdef DEBUG
		cir->Draw(*Camera);
#endif
	}
}