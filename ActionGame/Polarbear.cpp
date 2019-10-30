#include "Polarbear.h"

int Polarbear::PicHandle = 0;

Polarbear::Polarbear(int x, int y)
{
	//あたり判定位置セット
	this->x = x;
	this->y = y;
	rect.x = 3;
	rect.y = 5;
	rect.sizeX = 25;
	rect.sizeY = 25;

	velocity = PB_SPEED;	//速度をセット

}

Polarbear::~Polarbear()
{
}

void Polarbear::Motion(double frametime)
{
	if (CheckInCam()) {
		//ハイジャンプ用フラグ
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

		if (vecX + velocity * frametime > PB_MOVEWIDTH / 2 || vecX + velocity * frametime < -PB_MOVEWIDTH / 2) {
			velocity = -velocity;
		}

		vecX += velocity * frametime;

		x += velocity * frametime;

		hitface = stepRect_x(rect, frametime);
		if ((hitface & RIGHT) || (hitface & LEFT)) {
			velocity = -velocity;
		}


		hitface = stepRect_y(rect, frametime);		//y方向の時間を進める
		if ((hitface & BOTTOM) || (hitface & TOP)) {
			vy = 0.0;
		}
		/*animation += frametime * 1000;
		if (animation >= 100) {
			index++;
			animation = 0;
		}*/

		/*index = animation % 200;
		if (animation > 1600){
			animation = 0;*/
			//}
	}
	//落下したときに死ぬようにする
	if (y > HEIGHT)
		deathflag = true;
}

void Polarbear::Draw()
{
	if (CheckInCam()) {

		if (velocity <= 0)
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
		else
			DrawTurnGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
#ifdef DEBUG
		rect.Draw(*Camera);
#endif			

	}
}

bool Polarbear::HitCheck(Rect rect)
{
	if (CheckRectRect(rect, this->rect)) {
		//プライヤーが落下してきて、自分の上にあたっていたら自分が死んでプレイヤーにダメージは入らない
		if (HitFaceRectRect(rect, this->rect) & TOP && usingP->vy > 0 && usingP->Ymovingflag && !(HitFaceRectRect(rect, this->rect) & BOTTOM)) {
			killedenemy++;
			PlaySoundMem(Sound::sounds[SOUND_ENEMYTREAD], DX_PLAYTYPE_BACK);
			deathflag = true;
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
			HitPlayer();


		return true;
	}
	else
		return false;
}

void Polarbear::HitPlayer()
{
	usingP->Damage(PB_HITDAMAGE, ENEMYMATCHLESSTIME);
}


