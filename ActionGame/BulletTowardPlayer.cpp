#include "BulletTowardPlayer.h"

int BulletTowardPlayer::PicHandle[] = { 0,0 };

BulletTowardPlayer::BulletTowardPlayer(int x, int y)
{
	this->x = x;
	this->y = y;

	cir = new Circle(BULLETTOWARDPLAYER_RADIUS,&this->x,&this->y);

	//‰æ‘œ‚Æ‚ ‚½‚è”»’è‚ð‡‚í‚¹‚é
	GetGraphSize(PicHandle[0],&cir->x,&cir->y);
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
		if(picflag)
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle[0], TRUE);
		else
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle[1], TRUE);

#ifdef DEBUG
		cir->Draw(*Camera);
#endif
	}
}