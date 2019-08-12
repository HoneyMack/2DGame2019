#include "FallWall.h"
int FallWall::RedExamPicHandle = 0;
int FallWall::BirdPicHandle[] = {0,0};

RedExam::RedExam(int sizeX, int sizeY,int x, int y) {
	this->x = x;
	this->y = y;

	rect = new Rect(sizeX, sizeY, &this->x, &this->y);
	//�摜�Ƃ����蔻��̒���
	GetGraphSize(FallWall::RedExamPicHandle, &rect->x, &rect->y);
	rect->x /= 2;
	rect->y /= 2;
	rect->x -= rect->sizeX / 2;
	rect->y -= rect->sizeY / 2;
}

RedExam::~RedExam() {
	delete rect;
}

FallWall::FallWall(int x,int y)
{
	this->x = x;
	this->y = y;
	index =motionanima = birdanima = 0;

	//�����ʒu�ێ�
	startY = y;
	//�t���O���Z�b�g
	fallflag = descendflag = ascendflag = false;

	//�C���X�^���X�m��
	bird = new Rect(24,28,&this->x,&this->y);
	redexam = new RedExam(40,40,x,y + 30);	//�摜�Ƃ̌��ˍ����ŕύX
	//bird�����蔻��Ɖ摜����
	GetGraphSize(BirdPicHandle[0],&bird->x,&bird->y);
	//�A�j���[�V�����摜(fly2)�̑傫����ێ�
	GetGraphSize(BirdPicHandle[1], &picdsize[0][1],&picdsize[1][1]);
	picdsize[0][1] = -(picdsize[0][1]-  bird->x ) /2;
	picdsize[1][1] = -(picdsize[1][1] - bird->y) ;

	bird->x /= 2;
	bird->y /= 2;
	bird->x -= bird->sizeX / 2;
	bird->y -= bird->sizeY / 2;
	//���Ɖ𓚗p���̂�����C��
	redexam->x -= (redexam->rect->sizeX - bird->sizeX) / 2 -1;
	redexam->startY = redexam->y;//�����ʒu�C��

	//�d�͂�؂�
	ay = redexam->ay = 0;
}


FallWall::~FallWall()
{
	delete bird;
	delete redexam;
}

void FallWall::Motion(double ftime) {
	if (CheckInCam()) {
		//�n�C�W�����v�p�t���O
		if (waittime < KILLHIGHJUMPTIME) {
			waittime += ftime * 1000;
			//�n�C�W�����v�\�ɂ���
			if (InKeyTrigger(usingP->now_key, PAD_INPUT_10)) {
				usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
				PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
				waittime = KILLHIGHJUMPTIME;
			}
		}
		//�A�j���[�V�����p
		birdanima += (int)(ftime * 1000);
		//��s���[�V�����؂�ւ���^�C�~���O������Ă�����
		if (birdanima > FALLWALL_ANIMATIONTURNTIME) {
			birdanima -= FALLWALL_ANIMATIONTURNTIME;
			//�A�j���[�V�����؂�ւ�
			index = (index + 1) % 2;
		}
		//���Ƃ��Ă���Œ���
		if (descendflag || ascendflag || fallflag) {
			//�v���p
			motionanima += (int)(ftime * 1000);
			if (fallflag) {
				//���ė���
				//�}�b�v�̃u���b�N�ɂ�����~�܂�
				if (redexam->stepRect_y(*redexam->rect, ftime)) {
					fallflag = false;
					descendflag = true;
					vy = FALLWALL_BIRDSPEED;
					motionanima = 0;
				}
			}
			//�����~��鏈��
			if (descendflag && motionanima > FALLWALL_WAITFORDOWN) {
				//���̎��Ԃ�i�߂�
				stepPosY(ftime);
				//���Ă��E����Ƃ���܂ł�����
				if (y - startY > redexam->y - redexam->startY) {
					descendflag = false;
					ascendflag = true;
					motionanima = 0;
					//���
					vy = -vy;
					redexam->vy = vy;
				}
			}
			//������ɏオ�鏈��
			if (ascendflag && motionanima > FALLWALL_WAITFORUP) {
				//���Ɠ��Ă̎��Ԃ�i�߂�
				stepPosY(ftime);
				redexam->stepPosY(ftime);
				//���ɖ߂�����
				if (y - startY <0) {
					y = startY;
					redexam->y = redexam->startY;
					ascendflag = false;
					motionanima = 0;
				}
			}
				
		}
	}
	//���������Ƃ��Ɏ��ʂ悤�ɂ���
	if (y > HEIGHT)
		deathflag = true;
}

void FallWall::Draw() {
	if (CheckInCam()) {

		//�ԓ_�E���摜�\��
		DrawGraph(redexam->RelativePosX(), redexam->RelativePosY(),RedExamPicHandle,TRUE);
		DrawGraph(RelativePosX()+ picdsize[0][index], RelativePosY() + picdsize[1][index],BirdPicHandle[index],TRUE);
#ifdef DEBUG
		//�����蔻��`��
		bird->Draw(*Camera);
		redexam->rect->Draw(*Camera);
#endif
	}
}

bool FallWall::HitCheck(Rect rect) {
	//�����蔻��p
	bool flag = false;

	//�������蔻��
	if (CheckRectRect(*this->bird, rect))
	{
		//���𓥂񂾂����
		if (HitFaceRectRect(rect, *this->bird) & TOP && usingP->vy > 0 && usingP->Ymovingflag && !(HitFaceRectRect(rect, *this->bird) & BOTTOM)) {
			killedenemy++;
			PlaySoundMem(Sound::sounds[SOUND_ENEMYTREAD], DX_PLAYTYPE_BACK);
			deathflag = true;
			usingP->Animation(JUMP);
			waittime = 0;
			//�n�C�W�����v�\�ɂ���
			if (usingP->now_key& PAD_INPUT_10) {
				usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
				PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
				waittime = KILLHIGHJUMPTIME;
			}
			usingP->vy = -KILLJUMP;
		}
		else {
			//��ȊO����Ԃ������̂Ń_���[�W
			usingP->Damage(FALLWALL_BIRDDAMAGE,ENEMYMATCHLESSTIME);
		}
		flag = true;	//���������̂�
	}

	//�����������蔻��
	if (CheckRectRect(*this->redexam->rect, rect)) {
		//�Ԃ������̂Ń_���[�W (�͂����͂��Ȃ�)
		usingP->Damage(FALLWALL_REDEXAMDAMAGE, ENEMYMATCHLESSTIME);
	}

	//�v���C���[�������n�_�ɓ����Ă��邩(���A�E�A��)
	if (rect.x + rect.sizeX + *rect.gx > redexam->x + redexam->rect->x &&  *rect.gx + rect.x < redexam->x + redexam->rect->x + redexam->rect->sizeX && *rect.gy  + rect.y >redexam->y + redexam->rect->y + redexam->rect->sizeY) {
		//�����n�߂�
		if (!(fallflag||ascendflag ||descendflag)) {
			fallflag = true;
			redexam->vy = FALLWALL_FALLSPEED;	//�������x�w��
		}
	}
	return flag;
}
