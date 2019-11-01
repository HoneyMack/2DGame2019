#include "Blockforblock.h"

int Blockforblock::PicHandle = 0;
bool Blockforblock::startflag = false;
bool Blockforblock::liveflag = true;

Blockforblock::Blockforblock(int x, int y, int fx)
{
	this->x = x;
	this->y = y;
	this->fx = fx;
	startflag = false;
	liveflag = true;
}

Blockforblock::~Blockforblock()
{
}

void Blockforblock::Motion(double frametime)
{
	if (usingP->x > fx && startflag == false && liveflag == true) {
		startflag = true;

		StopSoundMem(Sound::sounds[SOUND_STAGE_SEA]);
		//音をロードして再生
		PlaySoundMem(Sound::sounds[SOUND_BOSS], DX_PLAYTYPE_LOOP, TRUE);

	}
	if (liveflag == false && deathflag == false) {
		deathflag = true;
		StopSoundMem(Sound::sounds[SOUND_BOSS]);
		//音をデリート
		DeleteSoundMem(Sound::sounds[SOUND_BOSS]);
		//音を再生
		PlaySoundMem(Sound::sounds[SOUND_BOSS_DEFEAT], DX_PLAYTYPE_BACK, TRUE);
	}
}

void Blockforblock::Draw()
{
	if (startflag) {
		//if (CheckInCam()) {
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);

#ifdef DEBUG
			rect.Draw(*Camera);
#endif
		//}
	}
}

bool Blockforblock::HitCheck(Rect rect)
{
	if (startflag) {
		if (CheckRectRect(this->rect, rect)) {
			//もし当たっていたらプレイヤーをはじく
			if (usingP->Xmovingflag) {
				//x移動でぶつかった
				usingP->vx = 0;
				usingP->KnuckledX(this->rect);
			}
			else {
				//y移動でぶつかった
				usingP->vy = 0;
				usingP->KnuckledY(this->rect);
				usingP->Animation(STAND);
				usingP->Jump();

				if (usingP->keypressed)
					usingP->vx *= 0.9;			//キーが押されているときの横速度減衰率
				else
					usingP->vx *= 0.6;			//キーが押されていないときの横速度減衰率
			}
			return true;
		}
	}
	return false;
}

