#include "Blockforblock.h"

int Blockforblock::PicHandle = 0;
bool Blockforblock::startflag = false;
bool Blockforblock::liveflag = true;

Blockforblock::Blockforblock(int x, int y, int fx)
{
	this->x = x;
	this->y = y;
	this->fx = fx;
	startflag = false;
	liveflag = true;
}

Blockforblock::~Blockforblock()
{
}

void Blockforblock::Motion(double frametime)
{
	if (usingP->x > fx)startflag = true;
	if (liveflag == false)deathflag = true;
}

void Blockforblock::Draw()
{
	if (startflag) {
		//if (CheckInCam()) {
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);

#ifdef DEBUG
			rect.Draw(*Camera);
#endif
		//}
	}
}

bool Blockforblock::HitCheck(Rect rect)
{
	if (startflag) {
		if (CheckRectRect(this->rect, rect)) {
			//�����������Ă�����v���C���[���͂���
			if (usingP->Xmovingflag) {
				//x�ړ��łԂ�����
				usingP->vx = 0;
				usingP->KnuckledX(this->rect);
			}
			else {
				//y�ړ��łԂ�����
				usingP->vy = 0;
				usingP->KnuckledY(this->rect);
				usingP->Animation(STAND);
				usingP->Jump();

				if (usingP->keypressed)
					usingP->vx *= 0.9;			//�L�[��������Ă���Ƃ��̉����x������
				else
					usingP->vx *= 0.6;			//�L�[��������Ă��Ȃ��Ƃ��̉����x������
			}
			return true;
		}
	}
	return false;
}

