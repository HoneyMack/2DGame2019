#include "Fish.h"

//�s�����E�܂ōs���ăv���C���[��ǂ��������Ԃ��Ɣ��������т���B�v�C��

int Fish::PicHandle = 0;

Fish::Fish(int x, int y)
{
	//�����蔻��ʒu�Z�b�g
	this->x = x;
	this->y = y;

	//�d�͂𖳌���
	ay = 0;
	rect.x = 3;
	rect.y = 5;
	rect.sizeX = 25;
	rect.sizeY = 25;

	fx = x;
	fy = y;

	velocityX = FISH_SPEED;	//���x�Z�b�g
	velocityY = 0;
}

Fish::~Fish()
{
}

void Fish::Motion(double frametime)
{
	double angle;
	if (CheckInCam()) {
		int hitface = 0x0000;



		//�v���C���[�Ƃ̋��������ȉ��ł���Βǂ�������
		//�v���C���[���͈͊O�ɏo����ǂ������Ȃ��悤�ɂ���B�͈͒p�ł̔��������іh�~
		if (((x - usingP->x) * (x - usingP->x) + (usingP->y - y) * (usingP->y - y)) < FISH_CHASE_DISTANCE * FISH_CHASE_DISTANCE
			&& (fx + FISH_MOVEWIDTH / 2 > usingP->x) && (fx - FISH_MOVEWIDTH / 2 < usingP->x)) {
			chasing = true;	//�ǂ������t���O�Z�b�g

			//�v���C���[��fish�Ƃ̊p�x���v�Z����
			//angle = atan((usingP->y - y) / (x - usingP->x));	//0���Z�@�v�C��
			if (x - usingP->x < ZEROEXCEPTION)
				angle = atan((usingP->y - y) / ZEROEXCEPTION);
			else
				angle = atan((usingP->y - y) / (x - usingP->x));	//0���Z�@�v�C��


			angle *= 180. / PI;
			//if (angle < 0)angle *= -1;

			//�v���C���[�Ƃ̊p�x�����E�p�x�ȏ�ł������ꍇ���E�p�x�Ƃ��Đi�ޕ�����ύX
			if (angle >= FISH_LIMIT_ANGLE) {
				velocityX = FISH_SPEED * cos(FISH_LIMIT_ANGLE * PI / 180.);
				velocityY = FISH_SPEED * sin(FISH_LIMIT_ANGLE * PI / 180.);
			}
			else if (angle <= -FISH_LIMIT_ANGLE) {
				velocityX = FISH_SPEED * cos(-FISH_LIMIT_ANGLE * PI / 180.);
				velocityY = FISH_SPEED * sin(-FISH_LIMIT_ANGLE * PI / 180.);
			}
			//�v���C���[�Ƃ̊p�x����������΃v���C���[��ǂ�������
			else {
				velocityX = FISH_SPEED * cos(angle * PI / 180.);	//�����ŏ���ɐݒ肷��ƕǂ�˂������邩������Ȃ��B�˂���������C������B
				velocityY = FISH_SPEED * sin(angle * PI / 180.);
			}
			if (usingP->x < x || velocityX < 0)
				velocityX = -velocityX;
			/*if (usingP->y < y || velocityY < 0)
				velocityY = -velocityY;*/
		}
		//�v���C���[�Ƃ̋���������Ă���ꍇ�͉��ړ�
		else if (chasing == true) {
			chasing = false;
			velocityX = FISH_SPEED;
			velocityY = 0;
		}

		/*if (vecX + velocityX * frametime > FISH_MOVEWIDTH / 2) || vecX + velocityX * frametime < -FISH_MOVEWIDTH / 2) {

		velocityX = -velocityX;
		}*/

		if ((fx + FISH_MOVEWIDTH / 2 < x) || (fx - FISH_MOVEWIDTH / 2 > x)){
		velocityX = -velocityX;

		}

		vecX += velocityX * frametime;
		//x += velocityX * frametime;
		vx = velocityX;

		hitface = stepRect_x(rect, frametime);
		if ((hitface & RIGHT) || (hitface & LEFT)) {
			velocityX = -velocityX;
		}

		//y += velocityY * frametime;
		vy = velocityY;

		//vy = velocityY;
		//stepPosY(frametime);


		hitface = stepRect_y(rect, frametime);		//y�����̎��Ԃ�i�߂�
		//if ((hitface & BOTTOM) || (hitface & TOP)) {
		//	vy = 0.0;
		//	velocityY = 0;
		//}
		//y += velocityY * frametime;
		
	}
}

void Fish::Draw()
{
	if (CheckInCam()) {
		//���������іh�~
		if (velocityX <= 0 || (usingP->x - x < 5 && usingP->x - x > -5))
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
		else
			DrawTurnGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
#ifdef DEBUG
		rect.Draw(*Camera);
#endif			

	}
}

bool Fish::HitCheck(Rect rect)
{
	if (CheckRectRect(rect, this->rect)) {
		HitPlayer();
		return true;
	}
	else
		return false;
}

void Fish::HitPlayer()
{
	usingP->Damage(FISH_HITDAMAGE, ENEMYMATCHLESSTIME);
}




