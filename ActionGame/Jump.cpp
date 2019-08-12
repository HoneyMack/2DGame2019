#include "Jump.h"

int Jump::PicHandle = 0;
int Jump::PicHandle_extended = 0;
int Jump::NsizeY = 0;

Jump::Jump(int x, int y)
{
	this->x = x;
	this->y = y;
	//�����蔻�蒲��
	rect.sizeX = 28;
	rect.sizeY = 30;
	//�摜�̒��S�ɂ����蔻���z�u
	GetGraphSize(PicHandle, &rect.x, &rect.y);
	//GetGraphSize(PicHandle_extended, &rect.x, &EsizeY);

	//�m�[�}���T�C�Y��ێ�
	NsizeY = rect.y;

	rect.x /= 2;
	rect.y /= 2;
	rect.x -= rect.sizeX / 2;
	rect.y -= rect.sizeY / 2;

}

Jump::~Jump()
{
}

void Jump::Draw()
{

#ifdef DEBUG
		//�摜�`��
		rect.Draw(*Camera);
		
#endif
	
	if (CheckInCam()) {
		//���_�w��`��
		DrawModiGraph(	RelativePosX(), RelativePosY() + amplitude * sin(radian),
						RelativePosX() + rect.sizeX, RelativePosY() + amplitude * sin(radian),
						RelativePosX() + rect.sizeX,RelativePosY() + rect.sizeY, 
						RelativePosX(), RelativePosY() + rect.sizeY,
						PicHandle, TRUE);
	}
}

void Jump::Motion(double frametime)
{
	if (CheckInCam()) {
		//�΂˂��U�����Ă���		
		if (hitflag == true) {
			//�n�C�W�����v����
			if (InKeyTrigger(usingP->now_key, PAD_INPUT_10) && jumponce) {
				usingP->vy = -JUMP_HIGHJUMP;
				PlaySoundMem(Sound::sounds[SOUND_JUMPSPRING], DX_PLAYTYPE_BACK);
				usingP->highjumpcounter = (CANHIGHJUMPTIME - JUMP_HIGHJUMPLIMIT) / 1000.0;//�n�C�W�����v�ς�
				usingP->Animation(JUMP);
				//�t���O��؂�
				jumponce = false;
			}
				

			//�����蔻���O�t���[���ňړ��������߂�
			rect.y -=amplitude* sin(radian);
			//�p�x��ǉ�
			radian += JUMP_ANGULARVELOCITY * frametime;		
			//����������
			amplitude *= JUMP_DECREMENT;

			//�����蔻��̈ʒu���X�V
			rect.y += amplitude *sin(radian);
		}

		//�΂˂��߂��Ă�����ɂȂ�����~�߂�
		if (radian > PI && hitflag ) {
			hitflag = false;
			radian = 0;

			//�����蔻�肪����Ă��܂��̂Œ���
			rect.y = NsizeY;
			rect.y /= 2;
			rect.y -= rect.sizeY / 2;
		}
	}
}

bool Jump::HitCheck(Rect rect)
{
	if (CheckRectRect(rect, this->rect)) {
		//�΂˂�����Ȉʒu�ɂ��邩
		if(hitflag == false)
			HitPlayer();
		else {
			//�ڐG��ۂ��Ȃ���
			if (usingP->Ymovingflag == true) {
				if (usingP->vy > 0) {
					//�v���C���[���͂���
					usingP->Knuckled(this->rect, BOTTOM);
					usingP->Animation(STAND);

					//�v���C���[���n�ʂ��痣���Ƃ�
					if (radian > PI - 0.6) {
						usingP->vy = -JUMP_LOWJUMP;
						PlaySoundMem(Sound::sounds[SOUND_JUMPSPRINGMINI], DX_PLAYTYPE_BACK);
						usingP->Animation(JUMP);
					}
					else
						usingP->vy = 0;

					if (usingP->keypressed)
						usingP->vx *= 0.3;			//�L�[��������Ă���Ƃ��̉����x������
					else
						usingP->vx *= 0.2;			//�L�[��������Ă��Ȃ��Ƃ��̉����x������
				}
			}
		}
			
		return true;
	}
	else 
		return false;
}

	


void Jump::HitPlayer()
{
	//�v���C���[��x�����Ɉړ����ē��������̂ƁAy�����Ɉړ����ē��������̂Ƃŏ�����ʂ���
	if (usingP->Xmovingflag == true ) {

		if (usingP->vx > 0) {
			usingP->Knuckled(this->rect, RIGHT);
		}
		else
			usingP->Knuckled(this->rect, LEFT);

		usingP->vx = 0;		//���ɂ������Ă���̂�x�����O��
	}
	if (usingP->Ymovingflag == true) {
		if (usingP->vy > 0) {
			//�L�я�Ԃ��Z�b�g
			hitflag = true;
			//�W�����v�t���O���Z�b�g
			jumponce = true;

			//�U�����Z�b�g
			amplitude = JUMP_EXTENSION;
			//�v���C���[���͂���
			usingP->Knuckled(this->rect, BOTTOM);

			usingP->Animation(STAND);
			 usingP->vy = 0;		//��œ������Ă���̂�y����0��

			if (usingP->keypressed)
				usingP->vx *= 0.3;			//�L�[��������Ă���Ƃ��̉����x������
			else
				usingP->vx *= 0.2;			//�L�[��������Ă��Ȃ��Ƃ��̉����x������
		}
		else {
			usingP->Knuckled(rect, TOP);
			usingP->vy = 0;		//���œ������Ă���̂�y����0��
		}
	}
}
