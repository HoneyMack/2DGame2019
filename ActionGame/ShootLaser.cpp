#include "ShootLaser.h"

int ShootLaser::PicHandle_laser = 0;
int ShootLaser::PicHandle_dispenser = 0;


ShootLaser::ShootLaser(int x) :Object(), laserX() {
	//���[�U�[�̑傫���̏�����
	for (int i = 0; i < SHOOTLASER_SHOTTIMES; i++) {
		laser[i] = new Rect(384, 12, &this->x, &this->y);	//���[�U�[�̑傫��x = 384,y = 12
	}
	this->x = x;
}


ShootLaser::~ShootLaser()
{
}

void ShootLaser::Shoot(double ftime) {
	timecount += ftime;
	//���Ԉ��ȏ�o��& ���˂��鋅���𒴂��Ă��Ȃ���
	if (timecount * 1000 >= SHOOTLASER_LASERINTERVAL * shotcount && shotcount < SHOOTLASER_SHOTTIMES) {
		laserX[shotcount] = SHOOTLASER_POSX + 164;	//-�̓��[�U�[�����˂���Ă���悤�Ɍ����邽��
		laser[shotcount]->y = shotcount*SHOOTLASER_MOVEINTERVAL + 15; //+�̓I�t�Z�b�g

		//�����o��
		PlaySoundMem(Sound::sounds[SOUND_LASERSHOT], DX_PLAYTYPE_BACK);
		shotcount++;
	}
	else {	//�Ԃ̎���
		//�܂����̔��ˈʒu�ɂ��Ă��Ȃ��Ȃ�ǉ�
		if (y < SHOOTLASER_MOVEINTERVAL * shotcount && timecount *1000> SHOOTLASER_LASERINTERVAL * (shotcount-1) + SHOOTLASER_SHOOTWAITTIME)
			y += (double)SHOOTLASER_MOVEINTERVAL / (SHOOTLASER_LASERINTERVAL - SHOOTLASER_WAITTIME- SHOOTLASER_SHOOTWAITTIME) * ftime * 1000; //�f�B�X�y���T�[�𓮂���
	}
}

void ShootLaser::Motion(double ftime) {
	if (CheckInCam() && !startflag && onceflag) {	//��ʂɉf������t���O��true��
		startflag = true;
		onceflag = false;
		timecount = 0.0;
	}
	if (startflag == true) {
		Shoot(ftime);
		//���˂��ꂽ���[�U�[�݂̂��ړ�
		for (int i = 0; i < shotcount; i++) {
			laserX[i] -= SHOOTLASER_LASERSPEED*ftime;
		}
		//�����Ō�̃��[�U�[����ʊO�ɏo���珉����
		if (shotcount == SHOOTLASER_SHOTTIMES && laserX[SHOOTLASER_SHOTTIMES - 1] - Camera->x < 0)
			Reset();
	}

}

void ShootLaser::Draw() {
	if (startflag == true) {
		//���˂��ꂽ���[�U�[�݂̂�`��
		for (int i = 0; i < shotcount; i++) {
			DrawGraph(laserX[i], laser[i]->y +2, PicHandle_laser, TRUE);
			
#ifdef DEBUG
			Rect drect = *laser[i];//�����蔻��`��
			drect.y = SHOOTLASER_MOVEINTERVAL* i + Camera->y - y + 18;
			drect.x = laserX[i] + Camera->x - x;
			drect.Draw(*Camera);
#endif
			
		}
		//�f�B�X�y���T�[�̕`��
		if (shotcount < SHOOTLASER_SHOTTIMES)	//�Ō�𔭎˂���܂�
			DrawGraph(SHOOTLASER_POSX, y, PicHandle_dispenser, TRUE);
	}
}

bool ShootLaser::HitCheck(Rect rect) {
	if (startflag == true) {
		//���˂��ꂽ���[�U�[�݂̂𔻒�Ώۂ�
		for (int i = 0; i < shotcount; i++) {
			Rect drect = *laser[i];
			drect.y = SHOOTLASER_MOVEINTERVAL* i + Camera->y - y + 18;
			drect.x = laserX[i] + Camera->x - x;
			if (CheckRectRect(drect, rect)) {
				HitPlayer();
				return true;
			}
		}
	}
	return false;
}

void ShootLaser::HitPlayer() {
	usingP->Damage(SHOOTLASER_HITDAMAGE,ENEMYMATCHLESSTIME);
}

void ShootLaser::Reset() {
	shotcount = 0;
	y = 0;
	startflag = false;
}