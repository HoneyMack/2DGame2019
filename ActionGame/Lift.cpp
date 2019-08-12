#include"Lift.h"

int Lift::PicDownHandle = 0;
int Lift::PicUpHandle = 0;

Lift::Lift(int set_x, int set_y,bool set_direction) :Object()
{
	x = set_x;
	y = set_y;
	vy = LIFT_MOVESPEED;
	direction = set_direction;
	if (direction == FALSE)
		vy *= -1;
	
	ay = 0;

	GetGraphSize(PicDownHandle, &rect.x, &rect.y);
	rect.x /= 2;
	rect.y /= 2;
	//rect.y = 0;
	rect.x -= rect.sizeX / 2;
	rect.y -= rect.sizeY / 2 - 4;
}


Lift::~Lift()
{
}

void Lift::Motion(double frametime)
{
	if (dropflag == 1) {   //�v���C���[����x���t�g�𓥂ނƗ����J�n
		//y+= LIFT_MOVESPEED;
		stepPosY(frametime);
		if (y >= HEIGHT||y<=0)
			deathflag = true;  //���܂ŉ������������
	}
}

void Lift::Draw()
{
	if (CheckInCam()) {
#ifdef DEBUG
		rect.Draw(*Camera);		//�����蔻��`��
#endif
		if(direction){
		DrawGraph(RelativePosX(),RelativePosY(),PicDownHandle,TRUE);
		}
		else {
			DrawGraph(RelativePosX(), RelativePosY(), PicUpHandle, TRUE);
		}
		}
}

bool Lift::HitCheck(Rect rect)
{
	if (CheckRectRect(rect, this->rect)) {
		//�v���C���[���������Ă��āA�����̏�ɂ��������璵�˕Ԃ�
		if (HitFaceRectRect(rect, this->rect) & TOP && usingP->vy > 0 && usingP->Ymovingflag && !(HitFaceRectRect(rect, this->rect) & BOTTOM)) {
			HitPlayer();
			dropflag = 1;  //�v���C���[�������̏�ɓ��������痎���J�n�i�����t���O�����P�j
			return true;
		}
		else
			return false;
	}
	return false;
}

void Lift::HitPlayer()
{
	//�ォ�瓖���������v���C���[��e��
	if (usingP->Ymovingflag == true) {
		if (usingP->vy > 0) {
			//�㏸�Ɖ��~�Ńv���C���[�̑��x��ς���
			if (direction == 1)
				usingP->vy = vy;
			else
				usingP->vy = 0;

			usingP->Knuckled(rect, BOTTOM);
			usingP->Animation(STAND);
			usingP->Jump();

			if (usingP->keypressed)
				usingP->vx *= 0.9;			//�L�[��������Ă���Ƃ��̉����x������
			else
				usingP->vx *= 0.6;			//�L�[��������Ă��Ȃ��Ƃ��̉����x������
		}
	}
}