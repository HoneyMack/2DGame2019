#include "Crab.h"

int Crab::PicHandle = 0;

Crab::Crab(int x, int y)
{
	this->x = centerX = x;
	this->y = y;

	velocity = CRAB_SPEED;

	//�e�̏�����
	for (int i = 0; i < CRAB_BULLETS; i++) {
		BTP[i] = new BulletTowardPlayer(x, y);
		BTP[i]->ay = 0;
		BTP[i]->picflag = false;
	}

	

	//�����蔻����摜�̒��S��	�摜���m�肵����m�F����
	GetGraphSize(PicHandle, &rect.x, &rect.y);
	rect.x /= 2;
	rect.y /= 2;
	rect.x -= rect.sizeX / 2;
	rect.y -= rect.sizeY / 2 - 2;
}

Crab::~Crab()
{
	for (int i = 0; i < CRAB_BULLETS; i++) {
		delete BTP[i];
	}
}

void Crab::Motion(double frametime)
{
	//��{�͉��ړ�
	//�e��ShootEnemy���Q�l�ɂ��ď���ɑł��グ�鏈����ǉ�
	if (CheckInCam()) {
		int hitface = 0x0000;
		
		//�w�肵�����̖��тŉ����ړ�����@�[�ɗ����甽�]
		if (vecX + velocity * frametime > CRAB_MOVEWIDTH / 2 || vecX + velocity * frametime < -CRAB_MOVEWIDTH / 2) {
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

		hitface = stepRect_y(rect, frametime);
		if ((hitface & BOTTOM) || (hitface & TOP)) {
			vy = 0.0;
		}

		//����ł���
		pasttime += frametime;
		if (pasttime * 1000 - CRAB_TIMEBFOREFIRING > bulletcounter * CRAB_FIRINGSPEED
			&& bulletcounter < CRAB_BULLETS) {
			//�������˂܂ŏ\���ɑ҂��Ă�����
			BTP[bulletcounter]->x = x;
			BTP[bulletcounter]->y = y;

			BTP[bulletcounter]->vx = 0;
			BTP[bulletcounter]->vy = -BUBBLE_SPEED;

			bulletcounter++;

			//�T�E���h���������������������
		}
		if (pasttime * 1000 > CRAB_INTERVAL) {
			bulletcounter = 0;
			pasttime = 0;
		}
	}
	else {
		//�J�����O�@���ԃ��Z�b�g
		pasttime = 0.0;
	}
	//�e�̍X�V
	for (int i = 0; i < bulletcounter; i++)
		BTP[i]->Motion(frametime);
}

void Crab::Draw()
{
	if (CheckInCam()) {
		if(velocity <= 0)
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
		else
			DrawTurnGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
#ifdef DEBUG
		rect.Draw(*Camera);
#endif			
	}
	//�e�̕`�揈��
	for (int i = 0; i < bulletcounter; i++) {
		BTP[i]->Draw();
	}
}

bool Crab::HitCheck(Rect rect)
{
	//return false;
	bool returnflag = false;
	if (CheckInCam()) {
		if (CheckRectRect(this->rect, rect)) {
			usingP->Damage(CRAB_HITDAMAGE, ENEMYMATCHLESSTIME);
			returnflag = true;
		}
	}
	for (int i = 0; i < bulletcounter; i++) {
		//�e�ƂԂ����Ă��邩
		if (CheckCircleRect(*BTP[i]->cir, rect)) {
			returnflag = true;
			usingP->Damage(BUBBLE_HITDAMAGE, ENEMYMATCHLESSTIME);
		}

		return returnflag;
	}
}
