#include "Penguin.h"

int Penguin::PicHandle = 0;

Penguin::Penguin(int x,int y)
{
	this->x = x;
	this->y = y;
	
	GetGraphSize(PicHandle, &rect.x, &rect.y);
	rect.x /= 2;
	rect.y /= 2;
	rect.x -= rect.sizeX / 2;
	rect.y -= rect.sizeY / 2 - 2;

	velocity = PENGUIN_MOVESPEED;
}


Penguin::~Penguin()
{
}

void Penguin::Motion(double frametime)
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

		if (vecX + velocity * frametime > PENGUIN_MOVEWIDTH / 2 || vecX + velocity * frametime < -PENGUIN_MOVEWIDTH) {
			velocity = -velocity;
		}

		vecX += velocity * frametime;

		x += velocity * frametime;

		hitface = stepRect_x(rect, frametime);
		if ((hitface & RIGHT) || (hitface & LEFT)) {
			velocity = -velocity;
		}

		hitface = stepRect_y(rect, frametime);
		if ((hitface & BOTTOM) || (hitface & TOP)) {
			vy = 0.0;
		}
		animation += frametime * 1000;


		if (y > HEIGHT)
			deathflag = true;
	}
	
	
}

void Penguin::Draw()
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

bool Penguin::HitCheck(Rect rect)
{
	//return false;
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
}

void Penguin::HitPlayer()
{
	usingP->Damage(PENGUIN_HITDAMAGE, ENEMYMATCHLESSTIME);
}
