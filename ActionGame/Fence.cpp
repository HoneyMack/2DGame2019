#include "Fence.h"
Fence* Fence::first = nullptr;
Fence* Fence::last = nullptr;

int Fence::PicHandle = 0;

Fence::Fence(int x,int y)
{
	this->x = x;
	this->y = y;

	ChainMaker();
}

Fence::~Fence()
{
	ChainCutter();
}

void Fence::Draw() {
	if (CheckInCam(x + rect.sizeX,y) || CheckInCam(x, y)) {
#ifdef DEBUG
		rect.Draw(*Camera);
#endif
		DrawGraph(RelativePosX(),RelativePosY(),PicHandle,TRUE);
	}
}

void Fence::AllDelete() {
	AllDelete(first);
	first = nullptr;
}

void Fence::AllDelete(Fence* mob) {
	while (mob != nullptr) {
		Fence* nextmob = mob->next;
		delete mob;
		mob = nextmob;
	}
}

void Fence::ChainMaker()
{
	if (first == nullptr)		//��������Ȃ�������first�ɓ����
		first = this;
	else {					//�ЂƂO�ɗv�f�������
		former = last;			//������肢�����O�ɍ��ꂽFence��ێ�
		former->next = this;
	}
	last = this;			//�Ō�����X�V
	next = nullptr;			//�����������̂͂Ȃ�
}
void Fence::ChainCutter()
{
	//�I�u�W�F�N�g�̍�������Ȃ��悤�ɂ��邽�߂̏���
	//�v�f���܂��ʂɂ��鎞
	if (last != first) {
		if (this == last) {				//this == �Ō���Ȃ�
			last = former;					//�Ō���̍X�V
			former->next = nullptr;			//�Ō����next��null��
		}
		else if (this == first) {			//�őO����������
			next->former = nullptr;			//�őO�ɂȂ����former��null��
			first = next;					//�őO�̍X�V
		}
		else {	//�^�񒆂ɂ�����̂���������
			former->next = this->next;
		}
	}
	else {	//�C���X�^���X��������Ȃ��Ƃ��̏���
		last = first = nullptr;
	}
}

bool Fence::HasNext() {
	if (this->next != nullptr)
		return true;
	else
		return false;
}

int Fence::HitCheckReturnFace(Rect rect) {
	//�X�̂����蔻��
	return HitFaceRectRect(this->rect, rect);
}

int Fence::PlayerHitCheck(Rect rect) {
	//�������Ă��邩�i�ǂ��̖ʂɁj��Ԃ�����
	int hitface = 0;

	//�擪�����
	if (first != nullptr) {
		Fence *fence = first;

		if (fence != nullptr) {		//�C���X�^���X��ێ����Ă��邩
			while (true) {			//�C���X�^���X�����ׂă`�F�b�N����܂Ń��[�v
				if (fence->HitCheckReturnFace(rect) != 0) {
					//�v���C���[�̂����蔻���n���āA���X����Ă��炤
					hitface = hitface | fence->HitCheckReturnFace(rect);
				}
				//�`�揈��
				fence->Draw();

				if (fence->HasNext())	//���̃C���X�^���X����������
					fence = fence->next;
				else
					break;			//���������烋�[�v�𔲂���
			}
		}
	}
	return hitface;
}