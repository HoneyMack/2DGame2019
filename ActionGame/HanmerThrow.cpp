#include"HanmerThrow.h"
#include<stdio.h>
#include<time.h>
#include <math.h>

int HanmerThrow::PicHandle[] = { 0,0,0 };

HanmerThrow::HanmerThrow(int x, int y, double iv) {
	this->x = x;
	this->y = y;
	this->iv = iv;

	GetGraphSize(PicHandle[0], &rect.x, &rect.y);

	rect.x /= 2;
	rect.y /= 2;
	rect.x -= rect.sizeX / 2;
	rect.y -= rect.sizeY / 2 - 2;
	velocity = HANMERTHROW_MOVESPEED;
	for (int i = 0; i < THROW_HANMERS; i++) {
		HAnmer[i] = new Hanmer(x, y);
		//�d�͒���
		HAnmer[i]->ay = HANMERTHROW_GRAVITY;
	}
}

HanmerThrow::~HanmerThrow() {
}

void HanmerThrow::Motion(double frametime) {
	if (CheckInCam()) {
		//�A�j���[�V�����؂�ւ�
		if (animation < HANMERTHROW_TURNTIME) {
			animation += frametime * 1000;
		}
		else {
			animation -= HANMERTHROW_TURNTIME;
			index = (index + 1) % 4;
		}
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

		if (vecX + velocity*frametime > HANMERTHROW_MOVEWIDTH / 2 || vecX + velocity*frametime < -HANMERTHROW_MOVEWIDTH / 2) {
			velocity = -velocity;
		}

		vecX += velocity*frametime;
		x += velocity*frametime;;

		hitface = stepRect_x(rect, frametime);
		if ((hitface&RIGHT) || (hitface&LEFT)) {
			velocity = -velocity;
		}

		hitface = stepRect_y(rect, frametime);
		if ((hitface&BOTTOM) || (hitface&TOP)) {
			vy = 0.0;
		}

		pasttime += frametime;
		if (pasttime * 1000 > hanmercounter * THROWINGSPEED && hanmercounter < THROW_HANMERS) {
			//�������˂܂ŏ\���҂��Ă�����
			//�e���v���C���[�Ɍ����鏈��
			if (usingP->x < this->x)
				HAnmer[hanmercounter]->x = x + rect.x;
			else
				HAnmer[hanmercounter]->x = x + rect.x + rect.sizeX ;
			HAnmer[hanmercounter]->y = y + rect.y;
			//�t���O��߂��ĕ\��
			HAnmer[hanmercounter]->deathflag = false;

			//�����n�_���v���C���[��

			double length = HAnmer[hanmercounter]->x - usingP->x;	//��������	
			double height =abs( HAnmer[hanmercounter]->y - usingP->y);	//��������
				
			//�[�����Z��O
			if (abs(length) < ZEROEXCEPTION) {
				if (length > 0)
					length = ZEROEXCEPTION;
				else
					length = -ZEROEXCEPTION;
			}
				
			//double angle = atan(sqrt(HANMERTHROW_GRAVITY * abs(usingP->x - x)) / iv);
			double angle;
			angle = atan2(-iv*(iv + sqrt(iv*iv + 2 * ay*height)), length * ay) + PI /180 * GetRand(5);

			////�p�x����
			//if (angle > THROWING_ANGLE_MAX) {
			//	angle = THROWING_ANGLE_MAX;
			//}
			//if (angle < THROWING_ANGLE_MIN) {
			//	angle = THROWING_ANGLE_MIN;
			//}


			if (usingP->x <= this->x)
				HAnmer[hanmercounter]->vx = -(iv * cos(angle));
			else
				HAnmer[hanmercounter]->vx = iv * cos(angle);

//			if(usingP->y <= this->y )
			HAnmer[hanmercounter]->vx = -(iv * cos(angle));
			HAnmer[hanmercounter]->vy = (iv * sin(angle));



			//HAnmer[hanmercounter]->vx = 200;
			//srand((unsigned int)time(NULL));
			//HAnmer[hanmercounter] = new Hanmer(this->x, this->y, 200);
			//HAnmer[hanmercounter]->ivx = 200;// rand() % THROWING_WIDTH + 1;
			hanmercounter++;
		}

		index = 0;
		//�A�j���[�V��������
		for (int j = 0; j < THROW_HANMERS; j++) {
			for (int i = 0; i < 3; i++) {	//index�̐��ŕύX
				if (HANMERTHROW_TURNTIME *(i + 1) + THROWINGSPEED*j > pasttime * 1000 && pasttime * 1000 >= HANMERTHROW_TURNTIME *i + THROWINGSPEED *j) {
					index = i;
				}
			}
		}

		//���[�`���Ԋu
		if (pasttime * 1000 > THROWINTERVAL) {
			hanmercounter = 0;
			pasttime = 0;
		}

	}
	for (int i = 0; i < hanmercounter; i++)
		HAnmer[i]->Motion(frametime);
	//���������Ƃ��Ɏ��ʂ悤�ɂ���
	if (y > HEIGHT)
		deathflag = true;
}

void HanmerThrow::Draw() {
	if (CheckInCam()) {
		//�v���C���[������
		if (usingP->x - x < 0)	//�v���C���[�����ɂ��邩
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle[index], TRUE);
		else
			DrawTurnGraph(RelativePosX(), RelativePosY(), PicHandle[index], TRUE);
#ifdef DEBUG
		rect.Draw(*Camera);
#endif
	}
}

bool HanmerThrow::HitCheck(Rect rect) {
	if (CheckRectRect(rect, this->rect)) {
		//�v���C���[���������Ă��āA�����̏�ɂ������Ă����玩��������Ńv���C���[�Ƀ_���[�W�͓���Ȃ�
		if (HitFaceRectRect(rect, this->rect) & TOP && usingP->vy > 0 && usingP->Ymovingflag && !(HitFaceRectRect(rect, this->rect) & BOTTOM)) {
			killedenemy++;
			PlaySoundMem(Sound::sounds[SOUND_ENEMYTREAD], DX_PLAYTYPE_BACK);
			deathflag = true;
			usingP->Knuckled(this->rect, BOTTOM);
			usingP->Animation(JUMP);
			waittime = 0;

			//�n�C�W�����v�\�ɂ���
			if (usingP->now_key& PAD_INPUT_10) {
				usingP->Animation(JUMP);
				usingP->highjumpcounter=( CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT)/1000.0;
				PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
				waittime = KILLHIGHJUMPTIME;
			}
			usingP->vy = -KILLJUMP;
			if (usingP->now_key & PAD_INPUT_10)
				usingP->vy = -JUMPSPEED;
		}
		else
			HitPlayer();
		return true;
	}
	else
		return false;
}

void HanmerThrow::HitPlayer() {
	usingP->Damage(HANMERTHROW_DAMAGE, ENEMYMATCHLESSTIME);
}