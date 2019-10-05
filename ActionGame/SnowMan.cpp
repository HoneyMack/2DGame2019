#include "SnowMan.h"

int SnowMan::PicHandle = 0;
int SnowBall::PicHandle = 0;



SnowBall::SnowBall(int _x, int _y) {
	x = _x;
	y = _y;
}

void SnowBall::Motion(double ftime) {
	//��ʓ��ɂ���Ƃ��A��������
	if (CheckInCam()) {
		int hitface = stepCircle_x(cir, ftime);
		//�ǂɏՓ˂��Ă�����E��
		if ((hitface & RIGHT) || (hitface & LEFT)) deathflag = true;

		//�ړ��ʂɉ����ċ�����]
		angle += (vx * ftime) / (SNOWBALL_RADIUS);

		hitface = stepCircle_y(cir, ftime);		//y�����̎��Ԃ�i�߂�
		if ((hitface & BOTTOM) || (hitface & TOP)) {
			vy = 0.0;
		}
		//�������Ă����ʂ悤�ɂ���
		if (y > HEIGHT)
			deathflag = true;
	}
	else {
		//��ʊO�ɏo����E��
		deathflag = true;
	}
}

void SnowBall::Draw() {
	//��ʓ��ɂ���Ƃ��A��������
	if (CheckInCam()) {
		DrawRotaGraph(RelativePosX(), RelativePosY(), 1.0, angle, PicHandle, TRUE);
	}
}

bool SnowBall::HitCheck(Rect rect) {
	if (CheckCircleRect(this->cir, rect)) {
		Object::usingP->Damage(SNOWBALL_DAMAGE, ENEMYMATCHLESSTIME);
		return true;
	}
	return false;
}

SnowMan::SnowMan(int _x, int _y,bool _direction) {
	x = _x;
	y = _y;
	direction = _direction;
	ballSetFlag = true;
	counter = 0;
	ball = new SnowBall(x, y); //�v�ʒu�C��
}

void SnowMan::Motion(double ftime) {
	//��ʓ��ɂ���Ƃ��A��������
	if (CheckInCam()) {
		counter += ftime * 1000;
		//�n�C�W�����v�p�t���O
		
		if (waittime < KILLHIGHJUMPTIME) {
			waittime += ftime * 1000;
			//�n�C�W�����v�\�ɂ���
			if (usingP->now_key & PAD_INPUT_10) {
				usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
				PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
				waittime = KILLHIGHJUMPTIME;
			}
		}
		

		//�ړ�
		int hitface = stepRect_x(rect, ftime);
		hitface = stepRect_y(rect, ftime);		//y�����̎��Ԃ�i�߂�
		if ((hitface & BOTTOM) || (hitface & TOP)) {
			vy = 0.0;
		}

		if (ball->deathflag) {
			//������������ł���i��ʊO�ł���j�Ȃ玩���̂Ƃ���ɖ߂��A�ʂ̑��x0,�����Ԃ点��
			ball->x = x;
			ball->y = y; //�ʒu�v�C��
			ball->vx = 0;
			ball->deathflag = false;
			ballSetFlag = true;
		}
		//������x�]�������ԂɂȂ��Ă��āA���{�[�����đ��U�ς݂ł���Γ]����
		if (counter > SNOWMAN_THROWINTERVAL && ballSetFlag) {
			ballSetFlag = false;
			if (direction) ball->vx = -SNOWBALL_VELOCITY;
			else ball->vx = SNOWBALL_VELOCITY;
			counter -= SNOWMAN_THROWINTERVAL;
		}
	}
}

void SnowMan::Draw() {
	//��ʓ��ɂ���Ƃ��A��������
	if (CheckInCam()) {
		DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE); //������`��
	}
}

bool SnowMan::HitCheck(Rect rect) {
	if (CheckRectRect(rect, this->rect)) {
		//�v���C���[���������Ă��āA�����̏�ɂ������Ă����玩��������Ńv���C���[�Ƀ_���[�W�͓���Ȃ�
		if (HitFaceRectRect(rect, this->rect) & TOP && usingP->vy > 0 && usingP->Ymovingflag && !(HitFaceRectRect(rect, this->rect) & BOTTOM)) {
			killedenemy++;
			PlaySoundMem(Sound::sounds[SOUND_ENEMYTREAD], DX_PLAYTYPE_BACK);
			deathflag = true;
			ball->deathflag = true;//�ʂ���\����
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
			usingP->Damage(SNOWMAN_DAMAGE, ENEMYMATCHLESSTIME);
		return true;
	}
	else
		return false;
}
