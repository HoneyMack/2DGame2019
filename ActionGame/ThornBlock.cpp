#include"ThornBlock.h"
#include"FlashBlock.h"

int ThornBlock::PicHandle = 0;

ThornBlock::ThornBlock(int x, int y){
	this->x = x;
	this->y = y;

	//�����蔻����摜�̒��S��
	GetGraphSize(PicHandle, &rect.x, &rect.y);
	rect.x /= 2;
	rect.y /= 2;
	rect.x -= rect.sizeX / 2;
	rect.y -= rect.sizeY / 2;
}

ThornBlock::~ThornBlock()
{

}

void ThornBlock::Motion(double frametime){

}

void ThornBlock::Draw(){
	if (CheckInCam()){
		if (!FlashBlock::flashingflag)			//true == �����Ɂ@== �t���b�V����������Ă��Ȃ�
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, THORNBLOCK_TRANSPARENCY);
		DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
		if (!FlashBlock::flashingflag)
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#ifdef DEBUG
		rect.Draw(*Camera);
#endif
	}
}

bool ThornBlock::HitCheck(Rect rect){
	if (CheckRectRect(this->rect, rect)){

		//�����������Ă�����v���C���[���͂���
		if (usingP->Xmovingflag){
			//x
			usingP->vx = 0;
			usingP->KnuckledX(this->rect);
		}
		else{
			//y
			
			if (usingP->vy > 0)
					usingP->Knuckled(this->rect,BOTTOM);
			else 
				usingP->Knuckled(this->rect, TOP);
			usingP->vy = 0;
			usingP->Animation(STAND);
			usingP->Jump();

			if (usingP->keypressed)
				usingP->vx *= 0.9;			//�L�[��������Ă���Ƃ��̉����x������
			else
				usingP->vx *= 0.6;			//�L�[��������Ă��Ȃ��Ƃ��̉����x������
		}
		HitPlayer();
		return true;
	}
	return false;
}

void ThornBlock::HitPlayer(){
	usingP->Damage(THORNBLOCK_HITDAMAGE, ENEMYMATCHLESSTIME);
}