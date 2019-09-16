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
		vx = -KILLER_MOVESPEED;

	ay = 0;

	//�摜�����܂����炱�̏�����������
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
			//�n�C�W�����v�\�ɂ���
			if (usingP->now_key & PAD_INPUT_10) {
				usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
				PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
				waittime = KILLHIGHJUMPTIME;
			}
		}

		int hitface = 0x0000;

		//stepPosAll(frametime);
		hitface = stepRect_x(rect, frametime);
		if ((hitface & RIGHT) || (hitface & LEFT)) {
			deathflag = true;	//�I�u�W�F�N�g�ɂԂ������玀�S
		}
		
	}
	//else if (startflag) {
	//	deathflag = true;	//��x�`�悳�ꂽ�̂���ʊO�ɏo���玀�S
	//}
}

void Killer::Draw()
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

bool Killer::HitCheck(Rect rect)
{
	if (CheckRectRect(rect, this->rect)) {
		//�v���C���[���������Ă��āA�����̏�ɂ������Ă����玩��������Ńv���C���[�Ƀ_���[�W�͓���Ȃ�
		if (HitFaceRectRect(rect, this->rect) & TOP && usingP->vy > 0 && usingP->Ymovingflag && !(HitFaceRectRect(rect, this->rect) & BOTTOM)) {
			killedenemy++;
			PlaySoundMem(Sound::sounds[SOUND_ENEMYTREAD], DX_PLAYTYPE_BACK);
			deathflag = true;
			usingP->Knuckled(this->rect, BOTTOM);

			waittime = 0;
			//�n�C�W�����v�\�ɂ���
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

void Killer::HitPlayer()
{
	usingP->Damage(KILLER_HITDAMAGE, ENEMYMATCHLESSTIME);
}
