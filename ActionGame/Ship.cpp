#include "Ship.h"

int Ship::PicHandle = 0;

Ship::Ship(int x, int y, double set_angle)
{
	this->x = x;
	this->y = y;
	angle = set_angle;
	if (angle >= 360) {	//����Ȃ���������Ȃ��@�ꉞ
		int i = angle / 360;
		angle -= 360 * i;
	}
	angle = 360 - angle;	//windows��ł̊p�x�w��ɍ��킹�鏈��
	angle *= PI / 180;	//���W�A���֕ϊ�
	vx = SHIP_MOVESPEED * cos(angle);
	vy = SHIP_MOVESPEED * sin(angle);

	ay = 0;

	//�摜�����܂����炱�̏������������B
	GetGraphSize(PicHandle, &rect.x, &rect.y);
	rect.x /= 2;
	rect.y /= 2;
	//rect.y = 0;
	rect.x -= rect.sizeX / 2;
	rect.y -= rect.sizeY / 2 - 4;
}

Ship::~Ship()
{
}

void Ship::Motion(double frametime)
{
	if (CheckInCam()) {
		startflag = true;
		stepPosAll(frametime);
		if (y >= HEIGHT || y <= 0)
			deathflag = true;	//y�͈̔͂𒴂��������
	}
	else if (startflag) {
		deathflag = true;	//��ʓ��ɓ��蓮�����Ă����ʊO�ɏo�������
		//����܂����H	�܂��������玞�Ԏw�������
	}
}

void Ship::Draw()
{
	if (CheckInCam()) {
		DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);

#ifdef DEBUG
		rect.Draw(*Camera);
#endif // DEBUG

	}
}

bool Ship::HitCheck(Rect rect)
{
	////return false;
	//if (CheckRectRect(rect, this->rect)) {
	//	if (usingP->Xmovingflag) {
	//		//x
	//		usingP->vx = 0;
	//		usingP->KnuckledX(this->rect);
	//		return true;
	//	}
	//	else if (usingP->vy < 0) {
	//		usingP->vy = 0;
	//		usingP->Knuckled(this->rect, TOP);
	//		return true;
	//	}
	//	//else if (HitFaceRectRect(rect, this->rect) & TOP && usingP->vy > 0 && usingP->Ymovingflag && !(HitFaceRectRect(rect, this->rect) & BOTTOM)) {
	//	else{	
	//		HitPlayer();
	//		return true;
	//	}
	//	/*else
	//		return false;*/
	//}
	if (CheckRectRect(rect, this->rect)) {
		if (HitFaceRectRect(rect, this->rect) & TOP && !(HitFaceRectRect(rect,this->rect) & BOTTOM)) {
			HitPlayer();
			unsigned int a = HitFaceRectRect(rect, this->rect);
			return true;
		}
		else if (usingP->Xmovingflag) {
			//x
			usingP->vx = 0;
			usingP->KnuckledX(this->rect);
			return true;
		}
		else if (usingP->vy < 0) {
			usingP->vy = 0;
			usingP->Knuckled(this->rect, TOP);
			return true;
		}
		else return false;
	}
	return false;
}

void Ship::HitPlayer()
{
	//�ォ�瓖���������v���C���[��e��
	if (usingP->Ymovingflag == true) {
		if (usingP->vy > 0) {
			//�㏸�Ɖ��~�Ńv���C���[�̑��x��ς���
			if (angle*180/PI < 180)
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
