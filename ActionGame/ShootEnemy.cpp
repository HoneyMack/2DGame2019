#include "ShootEnemy.h"

int ShootEnemy::PicHandle = 0;

ShootEnemy::ShootEnemy(int x, int y)
{
	this->x = centerX = x;
	this->y = y;

	velocity = SHOOTENEMY_MOVESPEED;

	//�e�̏�����
	for (int i = 0; i < SHOOTENEMY_BULLETS; i++) {
		BTP[i] = new BulletTowardPlayer(x, y);
		BTP[i]->ay = 0;	//�d�͂�0��
	}
	//�����蔻����摜�̒��S��
	GetGraphSize(PicHandle, &rect.x, &rect.y);
	rect.x /= 2;
	rect.y /= 2;
	rect.x -= rect.sizeX / 2;
	rect.y -= rect.sizeY / 2 - 2;

}


ShootEnemy::~ShootEnemy()
{
	for (int i = 0; i < SHOOTENEMY_BULLETS; i++)
		delete BTP[i];
}

void ShootEnemy::Motion(double frametime) {
	//�J�������ł��邩�ǂ���
	if (CheckInCam()) {
		//�n�C�W�����v�p�t���O
		if (waittime < KILLHIGHJUMPTIME) {
			waittime += frametime * 1000;
			//�n�C�W�����v�\�ɂ���
			if (InKeyTrigger(usingP->now_key, PAD_INPUT_10)) {
				usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
				PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
				waittime = KILLHIGHJUMPTIME;
			}
		}
		int hitface = 0x0000;

		//�w�肵�����̒��ŉ����ړ������邽�߂ɁA�[�ɗ����瑬�x�𔽓]
		if (vecX + velocity * frametime > SHOOTENEMY_MOVEWIDTH / 2 || vecX + velocity * frametime < -SHOOTENEMY_MOVEWIDTH / 2) {
			velocity = -velocity;
		}

		//�ړ��ʍX�V
		vecX += velocity * frametime;
		//���ۂ̈ʒu�X�V
		x = centerX + vecX;

		hitface = stepRect_x(rect, frametime);
		if ((hitface & RIGHT) || (hitface & LEFT)) {
			velocity = -velocity;
		}


		hitface = stepRect_y(rect, frametime);		//y�����̎��Ԃ�i�߂�
		if ((hitface & BOTTOM) || (hitface & TOP)) {
			vy = 0.0;
		}

		//����ł���
		pasttime += frametime;
		if (pasttime * 1000 - SHOOTENEMY_TIMEBFOREFIRING > bulletcounter * SHOOTENEMY_FIRINGSPEED
			&& bulletcounter < SHOOTENEMY_BULLETS) {
			//�������˂܂ŏ\���҂��Ă�����
			//�e���v���C���[�Ɍ����鏈��
			BTP[bulletcounter]->x = x;
			BTP[bulletcounter]->y = y;

			double dx = usingP->x - x + 5, dy = usingP->y - y + 10;
			double length = sqrt(dx * dx + dy * dy);
			//�[�����Z��O
			if (length < ZEROEXCEPTION)
				length = ZEROEXCEPTION;
			BTP[bulletcounter]->vx = dx / length * BULLETTOWARDPLAYER_SPEED;
			BTP[bulletcounter]->vy = dy / length * BULLETTOWARDPLAYER_SPEED;

			bulletcounter++;
			PlaySoundMem(Sound::sounds[SOUND_ENEMYSHOOT], DX_PLAYTYPE_BACK);
		}
		//���̔��˂Ɉڂ�
		if (pasttime * 1000 > SHOOTENEMY_INTERVAL) {
			bulletcounter = 0;
			pasttime = 0;
		}
	}
	else {
		//�J�����̊O�̏ꍇ�͎��Ԃ����Z�b�g
		pasttime = 0.0;
	}
	//�e�̍X�V
	for (int i = 0; i < bulletcounter; i++)
		BTP[i]->Motion(frametime);
	//���������Ƃ��Ɏ��ʂ悤�ɂ���
	if (y > HEIGHT)
		deathflag = true;
}

void ShootEnemy::Draw() {
	if (CheckInCam()) {
		//if(!usingP->HitCheck(cir)) //�f�o�b�O�p
		if (velocity <= 0)
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
		else
			DrawTurnGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
#ifdef DEBUG
		rect.Draw(*Camera);
#endif			
	}
	//�e�̕`��
	for (int i = 0; i < bulletcounter; i++)
		BTP[i]->Draw();
}

bool ShootEnemy::HitCheck(Rect rect) {
	bool returnflag = false;
	if (CheckInCam()) {
		//�G�ƂԂ����Ă��邩
		if (CheckRectRect(this->rect, rect)) {
			//�v���C���[���������Ă��āA�����̏�ɂ������Ă����玩��������Ńv���C���[�Ƀ_���[�W�͓���Ȃ�
			if (HitFaceRectRect(rect, this->rect) & TOP && usingP->vy > 0 && usingP->Ymovingflag && !(HitFaceRectRect(rect, this->rect) & BOTTOM)) {
				deathflag = true;
				PlaySoundMem(Sound::sounds[SOUND_ENEMYTREAD], DX_PLAYTYPE_BACK);
				killedenemy++;
				usingP->Animation(JUMP);
				waittime = 0;
				//�n�C�W�����v�\�ɂ���
				if (usingP->now_key & PAD_INPUT_10) {
					usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
					PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
					waittime = KILLHIGHJUMPTIME;
				}
				usingP->vy = -KILLJUMP;

			}
			else
				usingP->Damage(SHOOTENEMY_HITDAMAGE, ENEMYMATCHLESSTIME);
			returnflag = true;
		}
	}
	for (int i = 0; i < bulletcounter; i++) {
		//�e�ƂԂ����Ă��邩
		if (CheckCircleRect(*BTP[i]->cir, rect)) {
			returnflag = true;
			usingP->Damage(BULLETTOWARDPLAYER_HITDAMAGE, ENEMYMATCHLESSTIME);
		}
	}
	return returnflag;
}
