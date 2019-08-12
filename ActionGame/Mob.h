#pragma once
#include "define.h"
#include "Rect.h"

class Mob
{
public:
	static Mob *first, *last;
	Mob *former, *next;	//�C���X�^���X�̍��ɗp����
	bool deathflag = false;	//���񂾂��Fyes-> true
	static	int killedenemy;						//�|���ꂽ�G�̐�

	virtual void Motion(double frametime) = 0;	//����&����
	virtual void Draw() = 0;		//�`��
	virtual void AddDraw() {};			//�ǉ��ŕ`��
	virtual bool HitCheck(Rect rect) { return false; };	//Player->Enemy �������Ă��邩�𒲂ׂ�B�f�t�H���g�͂����蔻��͎����Ȃ�, �v���C���[����Ă΂��̂͂�������
	virtual void HitPlayer() {};						//�v���C���[�ɂԂ����Ă������̏������L�q

	bool HasNext();								//���̗v�f�����邩�B
	static void AllDelete(Mob* mob);				//�C���X�^���X�̍������ׂď����B
	virtual void ChainMaker();		//�C���X�^���X�̍��ɒǉ��B���ꂼ��̓G�̃R���X�g���N�^���ɋL�q���Ă��������B
	virtual void ChainCutter();		//�C���X�^���X�̍������菜���B���ꂼ��̓G�̃f�X�g���N�^���ɋL�q���Ă��������B

	Mob();
	virtual ~Mob();
};

