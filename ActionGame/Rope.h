#pragma once
#include "Object.h"
#include "Mob.h"
#include "define.h"
#include "Player.h"


class Rope : public Object, public Mob
{
public:
	static int rope_PicHandle;			//���[�v�摜
	static int fixture_PicHandle;		//�Œ��摜
	static int FsizeX, FsizeY;			//�Œ��̉摜�̑傫��

	int ropelen;					//���[�v�̒�����ێ�
	int ropenum;					//���{�̃��[�v���g�p���邩
	Rect fixture = Rect(ROPE_FIXTURE_SIZEX, ROPE_FIXTURE_SIZEY, &this->x, &this->y);			//�Œ��
	Rect rope = Rect(ROPE_SIZEX, ROPE_SIZEY, &this->x, &this->y);				//���[�v
	bool catchflag;		//�����[�v�ɂ���ł��邩

	double invalidation = 100;		//�W�����v��ɓ����蔻��̖��������Ԃ�ݒ肷��
					
	bool hitflag = false;

	Rope(int x, int y,int ropenum);		//�R���X�g���N�^
	~Rope();

	void Motion(double frametime);
	bool HitCheck(Rect rect);	//Player->Enemy�@�����蔻��
	void Draw();
};
