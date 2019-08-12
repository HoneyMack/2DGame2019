#include "Coin.h"

int Coin::hadcoins = 0;
int Coin::PicHandle[] = { 0,0 };

Coin::Coin(int x, int y)
{
	this->x = x;
	this->y = y;
	rect = new Rect(20,20,&this->x,&this->y);	//�����蔻��Z�b�g
	//�R�C���̒����ɂ����蔻��̒��������킹��
	GetGraphSize(PicHandle[0], &rect->x, &rect->y);
	rect->x /= 2;
	rect->y /= 2;
	rect->x -= rect->sizeX / 2;
	rect->y -= rect->sizeY / 2 ;
}


Coin::~Coin()
{
	delete rect;
}

void Coin::Motion(double frametime) {
	//animation�p
	animation += (int)(frametime * 1000);

	//�v���C���[���X�L���𔭓��ł��邩�̕��򏈗�
	int key = Object::usingP->now_key;
	
	if (InKeyTrigger(key,PAD_INPUT_4) && hadcoins >= 10) {//A�L�[
		//���G����
		if (Object::usingP->Damage(0, COIN_MATCHLESSTIME)) {		//���������ꂽ��
			hadcoins -= 10;
			PlaySoundMem(Sound::sounds[SOUND_PLAYERSKILL], DX_PLAYTYPE_BACK);
		}
	}
	//if (InKeyTrigger(key , PAD_INPUT_2)&& hadcoins >= 50) {//X�L�[
	//	//�G��|
	//}
	//if (InKeyTrigger(key , PAD_INPUT_1)&& hadcoins >= 100) {//Z�L�[
	//	//
	//}
}

void Coin::Draw() {
	static int turn = 0;
	if (Object::CheckInCam(x,y) && appear) {
		if (animation >= COIN_REVERSETIME) {
			turn = (turn + 1) % 2;
			animation -= COIN_REVERSETIME;
		}
		DrawGraph(x - Object::Camera->x,y - Object::Camera->y,PicHandle[turn],TRUE);
#ifdef DEBUG
		rect->Draw(*Object::Camera);
#endif
	}
}

bool Coin::HitCheck(Rect rect) {
	if (appear) {
		if (CheckRectRect(*this->rect, rect)) {
			hadcoins++;
			PlaySoundMem(Sound::sounds[SOUND_COIN], DX_PLAYTYPE_BACK);
			appear = false;

			return true;
		}
		else 
			return false;
	}
	else
		return false;
}