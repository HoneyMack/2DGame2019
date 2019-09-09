#include "Killer.h"

int Killer::PicHandle = 0;

Killer::Killer(int x, int y, bool direction)
{
	this->x = x;
	this->y = y;

	//velocity = KILLER_MOVESPEED;
	if (direction)
		vx = KILLER_MOVESPEED;
	else
		vx = KILLER_MOVESPEED;

	ay = 0;

	//画像が決まったらこの処理を見直す
	GetGraphSize(PicHandle, &rect.x, &rect.y);
	rect.x /= 2;
	rect.y /= 2;
	rect.x -= rect.sizeX / 2;
	rect.y -= rect.sizeY / 2 - 2;

}

Killer::~Killer()
{
}

void Killer::Motion(double frametime)
{
	if (CheckInCam()) {
		startflag = true;
		if (waittime < KILLHIGHJUMPTIME) {
			waittime += frametime * 1000;
			//ハイジャンプ可能にする
			if (usingP->now_key & PAD_INPUT_10) {
				usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
				PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
				waittime = KILLHIGHJUMPTIME;
			}
		}
		int hitface = 0x0000;
		stepPosAll(frametime);
		
	}
}

void Killer::Draw()
{
}

bool Killer::HitCheck(Rect rect)
{
	return false;
}

void Killer::HitPlayer()
{
}
