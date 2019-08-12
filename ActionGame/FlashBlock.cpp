#include "FlashBlock.h"
#include "Ghost.h"
int FlashBlock::PicHandle = 0;
bool FlashBlock::flashingflag = false;

FlashBlock::FlashBlock(int x, int y)
{
	this->x = x;
	this->y = y;
}

FlashBlock::~FlashBlock()
{
}

void FlashBlock::Motion(double frametime) {
	if (CheckInCam()) {
		//���Ԃ�ݐ�
		if (hitflag == true) {
			hittime += frametime;
			flashingflag = true;
		}
			
		//����̏�������
		if (hittime * 1000 > FLASHBLOCK_FLASHTIME)
			hitflag = false;
	}
}

void FlashBlock::Draw() {
	if (CheckInCam()) {
		if (hitflag == true) {
			//���肪�c���Ă���Ƃ��͉�ʂ�^������
			DrawBox(0, 0, Camera->sizeX + Camera->x, Camera->sizeY + Camera->y, 0xFFFFFF, TRUE);		//�^����
			
		}
	}
	else {
		hitflag = false;
	}
#ifdef DEBUG
		rect.Draw(*Camera);//�����蔻��	����
#endif
}

void FlashBlock::AddDraw() {
	if (CheckInCam()) {
		//��ʓ��̂Ƃ��͉摜��\��
		DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);	//�摜�`��
	}
}

bool FlashBlock::HitCheck(Rect rect) {
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

		//�������Ă�����t���O�𗧂��グ�{���ԗݐς�������
		if (hitflag == false) {
			hitflag = true;
			hittime = 0.0;
			PlaySoundMem(Sound::sounds[SOUND_FLASHBLOCK], DX_PLAYTYPE_BACK);//����炷
		}
		return true;
	}

	return false;
}
