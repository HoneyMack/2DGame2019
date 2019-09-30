#include "Mob.h"
Mob* Mob::first = nullptr;
Mob* Mob::last = nullptr;
int Mob::killedenemy = 0;
Mob::Mob()
{
	ChainMaker();
}


Mob::~Mob()
{
	ChainCutter();
}

bool Mob::HasNext() {
	if (this->next != nullptr)
		return true;
	else
		return false;
}

void Mob::AllDelete() {
	AllDelete(first);
	first = nullptr;
}

void Mob::AllDelete(Mob* mob) {
	while (mob != nullptr) {
		Mob* nextmob = mob->next;
		delete mob;
		mob = nextmob;
	}
}

void Mob::ChainMaker() 
{
	if (first == nullptr)		//��������Ȃ�������first�ɓ����
		first = this;
	else {					//�ЂƂO�ɗv�f�������
		former = last;			//������肢�����O�ɍ��ꂽMob��ێ�
		former->next = this;
	}
	last = this;			//�Ō�����X�V
	next = nullptr;			//�����������̂͂Ȃ�
}
void Mob::ChainCutter() 
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