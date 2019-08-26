#include"Turtle.h"

int Turtle::PicTurtleHandle = 0;
int Turtle::PicShellHandle[] = { 0,0,0,0 };

Turtle::Turtle(int x, int y)
{
	//�����蔻��ʒu�Z�b�g
	this->x = x;
	this->y = y;


	GetGraphSize(PicTurtleHandle, &cir.x, &cir.y);

	//�������ς�
	cir.x = cir.x / 2;
	cir.y = cir.y / 2 + 3;

	velocity = TURTLE_MOVESPEED;	//���x���Z�b�g
	formflag = 0;
}

Turtle::~Turtle() {

}

void Turtle::Motion(double frametime) {
	if (CheckInCam()) {
		//�A�j���[�V�����؂�ւ�
		if (animation < TURTLE_TURNTIME) {
			animation += frametime * 1000;
		}
		else {
			animation -= TURTLE_TURNTIME;
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
		//����
		if (formflag == 0) {
			int hitface = 0x0000;

			//�ړ��������]
			if (vecX + velocity * frametime > TURTLE_MOVEWIDTH / 2 || vecX + velocity * frametime < -TURTLE_MOVEWIDTH / 2) {
				velocity = -velocity;
			}
			vecX += velocity * frametime;
			x += velocity * frametime;

			hitface = stepCircle_x(cir, frametime);
			if ((hitface & RIGHT) || (hitface & LEFT)) {
				velocity = -velocity;
			}

			hitface = stepCircle_y(cir, frametime);		//y�����̎��Ԃ�i�߂�
			if ((hitface & BOTTOM) || (hitface & TOP)) {
				vy = 0.0;
			}
		}
		//�����Ă�
		else if (formflag == 1) {
			velocity = 0;
			int hitface = 0x0000;
			hitface = stepCircle_x(cir, frametime);
			hitface = stepCircle_y(cir, frametime);
			if ((hitface & BOTTOM) || (hitface & TOP)) {
				vy = 0;
			}
			//�摜��top��
			index = 0;
		}

	}
	//��]��
	if (formflag == 2) {
		int hitface = 0x0000;

		if (dflag == true)
			shellvelocity = -TURTLE_SHELLSPEED;
		else
			shellvelocity = TURTLE_SHELLSPEED;

		x += shellvelocity * frametime;
		hitface = stepCircle_x(cir, frametime);
		if ((hitface & RIGHT) || (hitface & LEFT)) {
			//shellvelocity = -shellvelocity;
			dflag = !dflag;
		}


		hitface = stepCircle_y(cir, frametime);		//y�����̎��Ԃ�i�߂�
		if ((hitface & BOTTOM) || (hitface & TOP)) {
			vy = 0.0;
			//ay = 0.0;
		}
	}
	//���������Ƃ��Ɏ��ʂ悤�ɂ���
	if (y > HEIGHT)
		deathflag = true;
}

void Turtle::Draw() {
	if (CheckInCam()) {
		if (formflag == 0) {
			if (velocity <= 0)
				DrawGraph(RelativePosX(), RelativePosY(), PicTurtleHandle, TRUE);
			else
				DrawTurnGraph(RelativePosX(), RelativePosY(), PicTurtleHandle, TRUE);

		}
		else {
			if (velocity < 0)
				DrawGraph(RelativePosX(), RelativePosY(), PicShellHandle[(index + 3) % 4], TRUE);
			else
				DrawGraph(RelativePosX(), RelativePosY(), PicShellHandle[index], TRUE);

		}
#ifdef DEBUG
		cir.Draw(*Camera);
#endif
	}

}

bool Turtle::HitCheck(Rect rect) {
	if (CheckCircleRect(cir, rect)) {
		//�v���C���[���������Ă��āA�v���C���[�̉��������ɂ������Ă����玩��������Ńv���C���[�Ƀ_���[�W�͓���Ȃ�
		if (HitFaceCircleRect(this->cir, rect) & BOTTOM && usingP->Ymovingflag && !((HitFaceCircleRect(this->cir, rect) & TOP))) { // && usingP->vy > 0) {
			//�ォ�炠�����Ă��邩(�������łȂ���)
			if (usingP->vy > 0) {
				//�v���C���[���ォ��Ԃ������̂Ńn�C�W�����v���������
				waittime = 0;

				//���̌`�ԂɈړ�
				formflag++;
				if (formflag >= 3) {		//�����A�����Ă�����]���Ă���A�~�߂�
					formflag = 1;
					//�摜��top��
					index = 0;
					
				}

				//�����蔻��傫���ύX
				this->cir = Circle(SHELL_RADIUS, &this->x, &this->y);
				GetGraphSize(PicShellHandle[index], &this->cir.x, &this->cir.y);
				//�����ς�
				this->cir.x /= 2;
				this->cir.y = this->cir.y / 2 + 3;

				//��������E���炠������
				if (usingP->x + usingP->rect.x + usingP->rect.sizeX / 2 >= x + this->cir.x) {
					dflag = true;
					//formflag++;
				}
				else {
					dflag = false;
					//formflag++;
				}

				//�v���C���[���͂���
				usingP->Knuckled(this->cir);
				waittime = 0;
				usingP->Animation(JUMP);
				//�n�C�W�����v�\�ɂ���
				if (usingP->now_key & PAD_INPUT_10) {

					usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
					PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
					waittime = KILLHIGHJUMPTIME;
				}

				PlaySoundMem(Sound::sounds[SOUND_ENEMYTREAD], DX_PLAYTYPE_BACK);
				usingP->vy = -KILLJUMP;
			}
			else {//�������Ɉړ��������Ƃœ������Ă���̂�
				HitPlayer();
			}
		}
		//���E����Ԃ������p�^�[��
		else {
			//����
			if (formflag == 0) {
				HitPlayer();
			}
			//��]��
			else if (formflag == 2) {
				HitPlayer();
			}
			//�����₫
			else {
				//�v���C���[���͂���
				usingP->Knuckled(this->cir);
				//�E�����炠������
				if (usingP->x + usingP->rect.x + usingP->rect.sizeX / 2 >= x + this->cir.x) {
					dflag = true;
					formflag++;
				}
				else {
					dflag = false;
					formflag++;
				}
			}
		}
		return true;
	}
	else
		return false;
}

void Turtle::HitPlayer() {
	usingP->Damage(TURTLE_HITDAMAGE, ENEMYMATCHLESSTIME);
}