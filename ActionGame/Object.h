#pragma once

#include "define.h"
#include "Map.h"
#include "DxLib.h"
#include "Player.h"
#include "Circle.h"

class Object
{
public:
	static Map *map;		//�}�b�v�̏�������
	static Rect *Camera;	//�J������������
	static Player *usingP;	//�v���C���[��������

	double x, y;			//���W
	double vx, vy;			//���x
	double ax, ay;			//�����x

	Object();		
	Object(double dx, double dy, double dvx, double dvy, double dax, double day);
	virtual ~Object();

	Object nextPosX(double frametime);		//���ɐi�񂾎���X�����݂̂̏���Ԃ�
	Object nextPosY(double frametime);		//���ɐi�񂾎���Y�����݂̂̏���Ԃ�
	Object nextPosAll(double frametime);	//���ɐi�񂾎��̏���Ԃ�
	void stepPosX(double frametime);		//X�����̂ݐi��
	void stepPosY(double frametime);		//Y�����̂ݐi��
	void stepPosAll(double frametime);		//���̍��W�ɐi��

	int stepRect_x(Rect rect, double frametime);					//�}�b�v��̃u���b�N�ƂԂ����Ă�����Ԃ���Ȃ��悤�ɖ߂��Ȃ���x�����̎��Ԃ�i�߂�B
	int stepRect_y(Rect rect, double frametime);					//�}�b�v��̃u���b�N�ƂԂ����Ă�����Ԃ���Ȃ��悤�ɖ߂��Ȃ���y�����̎��Ԃ�i�߂�B
	int stepCircle_x(Circle cir, double frametime);					//�}�b�v��̃u���b�N�ƂԂ����Ă�����Ԃ���Ȃ��悤�ɖ߂��Ȃ���x�����̎��Ԃ�i�߂�B(�߂�����Rect�ƈꏏ�ɂ���)
	int stepCircle_y(Circle cir, double frametime);					//�}�b�v��̃u���b�N�ƂԂ����Ă�����Ԃ���Ȃ��悤�ɖ߂��Ȃ���y�����̎��Ԃ�i�߂�B(�߂�����Rect�ƈꏏ�ɂ���)

	int CheckMapNum(Object Ob, int vecX, int vecY);	//�I�u�W�F�N�g�{�x�N�g���̈ʒu�̃}�b�v�ԍ���Ԃ�

	//bool CheckHitPlayer(Rect rect);				//�����`rect���v���C���[�ƂԂ����Ă��邩

	bool CheckInCam();								//�`����ɃI�u�W�F�N�g�����邩�B
static 	bool CheckInCam(double x, double y);			//�`��̈撆��x,y�͊܂܂�Ă��邩
static 	bool CheckInCam(int x, int y);			//�`��̈撆��x,y�͊܂܂�Ă��邩

	double RelativePosX();							//�X�N���[�������W
	double RelativePosY();							//�X�N���[�������W
};