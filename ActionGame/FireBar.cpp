#include"FireBar.h"

int FireBar::PicHandle = 0;

FireBar::FireBar(int set_x, int set_y) {
	x = set_x;
	y = set_y;

	int i, j;
	double angle = 2.0* PI / FIREBAR_NUMBER;		//�t�@�C���[�o�[���m�̊p�x�w��

	int blockx = 0, blocky = 0;			//���S�u���b�N�̑傫����ێ�
	GetGraphSize(PicHandle, &blockx, &blocky);

	//�u���b�N�̒��S�Ƃ����蔻��̒��S�����킹��
	rect.x += (blockx - rect.sizeX) / 2;
	rect.y += (blocky - rect.sizeY) / 2;

	//�擪�����ێ�
	fireball = new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 + blockx / 2, 0, FIREBALL_ANGVEL, true, FIREBAR_LENGTH);

	for (i = 0; i < FIREBAR_NUMBER; i++) {
		for (j = 0; j < FIREBAR_LENGTH; j++) {
			if (i + j != 0)
				new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 * (j + 1) + blockx / 2, angle * i, FIREBALL_ANGVEL, true, FIREBAR_LENGTH);
		}
	}
	//���S�u���b�N���{�[���ɍ��킹�ĕ��s�ړ�
	rect.x += fireball->cir->x;
	rect.y += fireball->cir->y;
	//rect�̒��S����]�̒��S��
	//	rect.x -= rect.sizeX / 2;
	//	rect.y -= rect.sizeY / 2;
}

FireBar::FireBar(int set_x, int set_y, int length, int number) {
	x = set_x;
	y = set_y;

	int i, j;
	double angle = 2.0*PI / number;		//�t�@�C���[�o�[���m�̊p�x�w��

	int blockx = 0, blocky = 0;			//���S�u���b�N�̑傫����ێ�
	GetGraphSize(PicHandle, &blockx, &blocky);

	//�u���b�N�̒��S�Ƃ����蔻��̒��S�����킹��
	rect.x += (blockx - rect.sizeX) / 2;
	rect.y += (blocky - rect.sizeY) / 2;

	//�擪�����ێ�
	fireball = new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 + blockx / 2, 0, FIREBALL_ANGVEL, true,length);

	for (i = 0; i < number; i++) {
		for (j = 0; j < length; j++) {
			if (i + j != 0)
				new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 * (j + 1) + blockx / 2, angle*i, FIREBALL_ANGVEL, true,length);
		}
	}
	//���S�u���b�N���{�[���ɍ��킹�ĕ��s�ړ�
	rect.x += fireball->cir->x;
	rect.y += fireball->cir->y;
}

FireBar::FireBar(int set_x, int set_y, double set_speed) {
	x = set_x;
	y = set_y;

	int i, j;
	double angle = 2.0* PI / FIREBAR_NUMBER;		//�t�@�C���[�o�[���m�̊p�x�Z�o
	set_speed *= PI / 180.0;						//�p���x�Z�o

	int blockx = 0, blocky = 0;			//���S�u���b�N�̑傫����ێ�
	GetGraphSize(PicHandle, &blockx, &blocky);

	//�u���b�N�̒��S�Ƃ����蔻��̒��S�����킹��
	rect.x += (blockx - rect.sizeX) / 2;
	rect.y += (blocky - rect.sizeY) / 2;

	//�擪�����ێ�
	fireball = new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 + blockx / 2, 0, set_speed, true, FIREBAR_LENGTH);

	for (i = 0; i < FIREBAR_NUMBER; i++) {
		for (j = 0; j < FIREBAR_LENGTH; j++) {
			if (i + j != 0)
				new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 * (j + 1) + blockx / 2, angle * i, set_speed, true, FIREBAR_LENGTH);
		}
	}
	//���S�u���b�N���{�[���ɍ��킹�ĕ��s�ړ�
	rect.x += fireball->cir->x;
	rect.y += fireball->cir->y;
}

FireBar::FireBar(int set_x, int set_y, bool direction) {
	x = set_x;
	y = set_y;

	int i, j;
	double angle = 2.0* PI / FIREBAR_NUMBER;	//�t�@�C���[�o�[���m�̊p�x�w��
	double angvel = FIREBALL_ANGVEL;			//�p���x�w��

	int blockx = 0, blocky = 0;			//���S�u���b�N�̑傫����ێ�
	GetGraphSize(PicHandle, &blockx, &blocky);

	//�u���b�N�̒��S�Ƃ����蔻��̒��S�����킹��
	rect.x += (blockx - rect.sizeX) / 2;
	rect.y += (blocky - rect.sizeY) / 2;

	//�擪�����ێ�
	fireball = new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 + blockx / 2, 0, angvel, direction, FIREBAR_LENGTH);

	for (i = 0; i < FIREBAR_NUMBER; i++) {
		for (j = 0; j < FIREBAR_LENGTH; j++) {
			if (i + j != 0)
				new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 * (j + 1) + blockx / 2, angle * i, angvel, direction, FIREBAR_LENGTH);
		}
	}
	//���S�u���b�N���{�[���ɍ��킹�ĕ��s�ړ�
	rect.x += fireball->cir->x;
	rect.y += fireball->cir->y;
}

FireBar::FireBar(int set_x, int set_y, int set_angle) {
	x = set_x;
	y = set_y;

	int i, j;
	double phase = set_angle / 180 * PI;			//�x���@�[�����W�A��
	double angle = 2.0* PI / FIREBAR_NUMBER;				//�t�@�C���[�o�[���m�̊p�x�Z�o

	int blockx = 0, blocky = 0;			//���S�u���b�N�̑傫����ێ�
	GetGraphSize(PicHandle, &blockx, &blocky);

	//�u���b�N�̒��S�Ƃ����蔻��̒��S�����킹��
	rect.x += (blockx - rect.sizeX) / 2;
	rect.y += (blocky - rect.sizeY) / 2;

	//�擪�����ێ�
	fireball = new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 + blockx / 2, phase, FIREBALL_ANGVEL, true, FIREBAR_LENGTH);

	for (i = 0; i < FIREBAR_NUMBER; i++) {
		for (j = 0; j < FIREBAR_LENGTH; j++) {
			if (i + j != 0)
				new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 * (j + 1) + blockx / 2, angle * i + phase, FIREBALL_ANGVEL, true, FIREBAR_LENGTH);
		}
	}
	//���S�u���b�N���{�[���ɍ��킹�ĕ��s�ړ�
	rect.x += fireball->cir->x;
	rect.y += fireball->cir->y;
}
FireBar::FireBar(int set_x, int set_y, double set_speed, bool direction, int length, int number, int set_angle) {
	x = set_x;
	y = set_y;

	int i, j;

	double phase = set_angle / 180 * PI;			//�x���@�[�����W�A��
	double speed = set_speed*(PI / 180.0);			//�p���x�w��
	double angle = 2.0* PI / number;				//�t�@�C���[�o�[���m�̊p�x�Z�o


	int blockx = 0, blocky = 0;			//���S�u���b�N�̑傫����ێ�
	GetGraphSize(PicHandle, &blockx, &blocky);

	//�u���b�N�̒��S�Ƃ����蔻��̒��S�����킹��
	rect.x += (blockx - rect.sizeX) / 2;
	rect.y += (blocky - rect.sizeY) / 2; 
	

	//�擪�̂ݕێ�
	fireball = new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 + blockx / 2, phase, speed, direction,length);

	//�t�@�C���[�{�[������
	for (i = 0; i < number; i++) {
		for (j = 0; j < length; j++) {
			if (i + j != 0)
				new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 * (j + 1) + blockx / 2, angle * i + phase, speed, direction,length);
		}
	}
	//���S�u���b�N���{�[���ɍ��킹�ĕ��s�ړ�
	rect.x += fireball->cir->x;
	rect.y += fireball->cir->y;
}

FireBar::~FireBar() {
}

void FireBar::Motion(double frametime) {


}

void FireBar::Draw() {
	if (CheckInCam()) {
		DrawGraph(RelativePosX() + fireball->cir->x, RelativePosY() + fireball->cir->y, PicHandle, TRUE);
#ifdef DEBUG
		rect.Draw(*Camera);
#endif
	}
}

bool FireBar::HitCheck(Rect rect) {
	if (CheckRectRect(rect, this->rect)) {
		HitPlayer();
		return true;
	}
	else {
		return false;
	}
}

void FireBar::HitPlayer() {
	//�����ł͓������Ă�����v���C���[���͂���
	//�v���C���[��x�����Ɉړ����ē��������̂ƁAy�����Ɉړ����ē��������̂Ƃŏ�����ʂ���
	if (usingP->Xmovingflag == true) {
		//usingP->KnuckledX(rect);

		if (usingP->vx > 0) {
			usingP->Knuckled(rect, RIGHT);
			usingP->Jump();
		}
		else
			usingP->Knuckled(rect, LEFT);

		usingP->vx = 0;		//���ɂ������Ă���̂�x�����O��
	}
	if (usingP->Ymovingflag == true) {

		if (usingP->vy > 0) {
			usingP->Knuckled(rect, BOTTOM);
			usingP->vy = 0;		//�㉺�œ������Ă���̂�y����0��
			usingP->Animation(STAND);
			usingP->Jump();
			if (usingP->keypressed)
				usingP->vx *= 0.9;			//�L�[��������Ă���Ƃ��̉����x������
			else
				usingP->vx *= 0.6;			//�L�[��������Ă��Ȃ��Ƃ��̉����x������
		}
		else {
			usingP->Knuckled(rect, TOP);
			usingP->Animation(STAND);
			usingP->vy = 0;		//�㉺�œ������Ă���̂�y����0��
		}
	}
}