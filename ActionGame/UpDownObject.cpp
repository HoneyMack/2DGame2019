#include "UpDownObject.h"
int UpDownObject::PicHandle = 0;

UpDownObject::UpDownObject(int set_x, int set_y)
{
	movewidth = UPDOWN_OB_MOVEWIDTH;
	angvel = UPDOWN_OB_ANGVEL;
	x = set_x;
	y = set_y;	

	GetGraphSize(PicHandle, &rect.x, &rect.y);
	rect.x /= 2;
	rect.y /= 2;
	rect.x -= rect.sizeX / 2;
	rect.y -= rect.sizeY / 2 + 1;
}

UpDownObject::~UpDownObject()
{
}

void UpDownObject::Motion(double frametime) {
	if (CheckInCam()) {
		//���t�g�̓���
		if (angle >= 2 * PI) {
			angle = 0;
		}

		vecY = (movewidth / 2)*(sin(angle));

		angle += angvel*frametime;

		y += vecY;

		//�v���C���[�Ɠ������Ă��邩�`�F�b�N�[���������Ă�����v���C���[���͂���
		if (usingP->HitCheck(rect)) {
				usingP->KnuckledY(rect);
		}
	}
}

void UpDownObject::Draw()
{
	if (CheckInCam()) {

		
#ifdef DEBUG
		rect.Draw(*Camera);		//�����蔻��`��
#endif
		DrawGraph(RelativePosX(), RelativePosY(),PicHandle,TRUE);
		y -= vecY;
	}
}

bool UpDownObject::HitCheck(Rect rect) {
	//UpDownObject�̂����蔻���ς���ƕς��
	if (CheckRectRect(rect, this->rect)) {	//�������Ă��邩
		HitPlayer();
		return true;
	}
	else
		return false;
}

void UpDownObject::HitPlayer() {
	//�����ł͓������Ă�����v���C���[���͂���
	//�v���C���[��x�����Ɉړ����ē��������̂ƁAy�����Ɉړ����ē��������̂Ƃŏ�����ʂ���
	if (usingP->Xmovingflag == true) {
		//usingP->KnuckledX(rect);

		if (usingP->vx > 0) {
			usingP->Knuckled(rect, RIGHT);
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
		

		//if (usingP->KnuckledY(rect) == BOTTOM)	//�v���C���[�̒�ɂԂ����Ă�����W�����v���\��
		//	usingP->Jump();
		////x�������x�����𔭐�
		//if (usingP->keypressed)
		//	usingP->vx *= 0.9;			//�L�[��������Ă���Ƃ��̉����x������
		//else
		//	usingP->vx *= 0.6;			//�L�[��������Ă��Ȃ��Ƃ��̉����x������
	}
}


