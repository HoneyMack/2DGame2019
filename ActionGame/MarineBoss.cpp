#include "MarineBoss.h"

int MarineBoss::PicHandle[] = { 0,0 };

MarineBoss::MarineBoss(int sx, int sy, int fx)
{
	this->x = sx;
	this->y = sy;

	this->fx = fx;
	this->tx = sx;

	for (int i = 0; i < BOSS_UNI_CNT; i++) {
		UNI[i] = new Urchin(x,-40);
	}

	rect.x = 5;
	rect.y = 7;

	startflag = false;
	velocity = BOSS_MOVESPEED;
	unitime = BOSS_UNITIME_FIRST;	//�E�j�𗎂Ƃ����Ԃ�ݒ�
}

MarineBoss::~MarineBoss()
{
	for (int i = 0; i < BOSS_UNI_CNT; i++) {
		UNI[i]->~Urchin();
	}
}

void MarineBoss::Motion(double frametime)
{
	if (Blockforblock::startflag) 
		
		startflag = true;
		//�n�C�W�����v�p�t���O
		if (waittime < KILLHIGHJUMPTIME) {
			waittime += frametime * 1000;
			//�n�C�W�����v�\�ɂ���
			if (usingP->now_key & PAD_INPUT_10) {
				usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
				PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
				waittime = KILLHIGHJUMPTIME;
			}
		}
		switch (stats)
		{
		case 0:
			//�������ĂȂ��A���̍s����I��
			if (startflag) {
				stats = rnd() % 3 + 1;
				cnttime = 0;
			}
			break;
		case 1:
			//�������ɉ��ړ�
			velocity = -BOSS_MOVESPEED;
			x += velocity * frametime;
			if (x <= fx) {	//�s���͈͂̍��[�ɓ��B
				stats = 4;	//�E�����։��ړ��ɕύX
				cnttime = 0;
			}
			break;
		case 2:
			//������
			if (HardeningFlag == false) {
				//���A�d��������
				HardeningFlag = true;
			}
			cnttime++;
			if (cnttime >= BOSS_HARDTIME) {
				HardeningFlag = false;	//�d��������
				stats = 6;	//�s����̑҂����Ԃֈڍs
				cnttime = 0;
			}
			break;
		case 3:
			//�E�j���Ƃ�
			//�p�T�E���h�ǉ�
			if (Uniflag == false) {
				Uniflag = true;

			}
			cnttime++;
			if ((int)cnttime % BOSS_UNI_INTERVAL == 0) {
				//�E�j�𗎂Ƃ�������ǉ�
				UNI[unicnt]->x = (rnd() % (tx - fx)) + fx + BOSS_SIZEX;
				UNI[unicnt]->y = 1;
				unicnt++;
			}
			if (cnttime >= unitime) {
				cnttime = 0;
				stats = 6;
				unicnt = 0;
				
			}
			break;
		case 4:
			//�E�����ړ�
			velocity = BOSS_MOVESPEED;
			x += velocity * frametime;
			if (x >= tx) {
				stats = 6;
				cnttime = 0;
			}
			break;
		case 5:
			//�E�j���Ƃ�+�d����
			//�p�T�E���h�ǉ�
			if (HardeningFlag == false) {
				HardeningFlag = true;
			}
			cnttime++;
			if ((int)cnttime % BOSS_UNI_INTERVAL == 0) {
				//�E�j�𗎂Ƃ�������ǉ�
				UNI[unicnt]->x = (rnd() % (tx - fx)) + fx + BOSS_SIZEX;
				UNI[unicnt]->y = 1;
				unicnt++;
			}
			if (cnttime >= BOSS_HARDTIME) {
				HardeningFlag = false;	//�d��������
				stats = 6;	//�s����̑҂����Ԃֈڍs
				cnttime = 0;
				unicnt = 0;
				
			}
			break;
		case 6:
			//�s����wait����
			cnttime++;
			if (cnttime >= BOSS_ACTION_INTERVAL) {
				cnttime = 0;
				stats = 0;
			}
		default:
			break;
		}


		int hitface = 0x0000;
		hitface = stepRect_y(rect, frametime);		//y�����̎��Ԃ�i�߂�
		if ((hitface & BOTTOM) || (hitface & TOP)) {
			vy = 0.0;
		}
		for (int i = 0; i < BOSS_UNI_CNT; i++) {
			UNI[i]->Motion(frametime);
		}
	
	//���������Ƃ��Ɏ��ʂ悤�ɂ���
	if (y > HEIGHT)
		deathflag = true;
}

void MarineBoss::Draw()
{
#ifdef DEBUG
		rect.Draw(*Camera);
#endif
	if (CheckInCam()) {
		if (stats == 0 || stats == 1 || stats == 3 || stats == 6)	//����������
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle[0], TRUE);
		else if (stats == 4)
			DrawTurnGraph(RelativePosX(), RelativePosY(), PicHandle[0], TRUE);
		else if (stats == 2 || stats == 5) {
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle[0], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, SEA_TRANSPARENCY);
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle[1], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		for (int i = 0; i < BOSS_UNI_CNT; i++) {
			UNI[i]->Draw();
		}

	}
}

bool MarineBoss::HitCheck(Rect rect)
{
	//return false;
	if (CheckRectRect(rect, this->rect)) {
		//�v���C���[���������Ă��āA�����̏�ɂ������Ă����玩��������Ńv���C���[�Ƀ_���[�W�͓���Ȃ�
		if (HitFaceRectRect(rect, this->rect) & TOP && usingP->vy > 0 && usingP->Ymovingflag && !(HitFaceRectRect(rect, this->rect) & BOTTOM)) {
			//killedenemy++;
			PlaySoundMem(Sound::sounds[SOUND_ENEMYTREAD], DX_PLAYTYPE_BACK);
			//deathflag = true;
			if (stats != 2 && stats != 5) {
				hp--;	//hp�����炷
				stats = 5;
				cnttime = 0;
			}
			if (hp <= 0) {
				Blockforblock::liveflag = false;
				deathflag = true;	//hp���O�Ȃ玀�S
			}
			//usingP->vx -= BOSS_DROPED_VX;
			if (usingP->x < this->x+BOSS_SIZEX/2)usingP->vx -= BOSS_DROPED_VX;
			else usingP->vx += BOSS_DROPED_VX;
			usingP->vy -= BOSS_DROPED_VY;
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
	else {
		for (int i = 0; i < BOSS_UNI_CNT; i++) {
			//�E�j�̓����蔻��
			if (CheckCircleRect(*UNI[i]->cir, rect)) {
				usingP->Damage(BOSS_UNI_HITDAMAGE, ENEMYMATCHLESSTIME);
				return true;
			}
		}
	}
		return false;
}

void MarineBoss::HitPlayer()
{
	usingP->Damage(BOSS_HITDAMAGE, ENEMYMATCHLESSTIME);
}
