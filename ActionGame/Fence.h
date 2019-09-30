#pragma once
#include "Object.h"
#include "Rect.h"


//�t�F���X��� �g���Ƃ��͕����g���Ď���

class Fence:public Object
{
public:
	static Fence *first, *last;
	Fence *former, *next;	//�C���X�^���X�̍��ɗp����

	static int PicHandle;		//�摜�ێ�
	//static bool anyprocessed;	//���̏����Ŋ��ɂق��̃t�F���X����������Ă��邩

	Rect rect = Rect(FENCE_SIZE,FENCE_SIZE,&this->x,&this->y);		//�����蔻��
	Fence(int x,int y);
	~Fence();
	
	void Draw();
	bool HasNext();						//���̗v�f�����邩�B
	int HitCheckReturnFace(Rect rect);			//rect�� �������Ă��邩�𒲂ׂ�B �߂�l��rect�𒆐S�Ƃ��ē���������
	static void AllDelete();
	static void AllDelete(Fence *fence);
	void ChainMaker();		//�C���X�^���X�̍��ɒǉ��B
	void ChainCutter();		//�C���X�^���X�̍������菜���B

	static int PlayerHitCheck(Rect rect);	// �v���C���[����Ă΂��̂͂�������//�v���C���[�̂����蔻���n��//�������Ă���߂񂪌���I�ł���ꍇ�������ʂ��o��
};

