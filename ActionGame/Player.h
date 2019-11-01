#pragma once
#include "define.h"
#include "Sound.h"
#include "Map.h"
#include "Rect.h"
#include "Circle.h"

class Mob;	//�O���錾

class Player
{
private:
	int index = 0;			//�A�j���[�V�����p
	int motion = 0;			//�L�����N�^�[�𓮂������߂ɗp����
public:
	static int PicHandle[];						//�摜������ stand,run,jump,fance,swim
	Rect rect = Rect(25,25,&this->x,&this->y);	//�����蔻�������
	Map *map;			//�ʒu�ړ��̂��߂ɂ��̎��X�̃}�b�v��������
	Rect *Camera;		//�J�����̈ʒu������

	double x, y;			//���W
	double vx, vy;			//���x
	double ax, ay;			//�����x
	int now_key = 0;		//�L�[���͏��𓾂�
	int HP = HITPOINT;					//�v���C���[��HP

	double matchlesstime = 0;//�v���C���[�̖��G�o�ߎ��Ԃ�ێ�
	double highjumpcounter = 0;	//�n�C�W�����v���\���ێ�

	int  directionflag = 0;		//�w��Ȃ��@ = 0�E�����[��1,������ ->2
	bool matchlessflag = false;		//���G���ǂ���
	bool keypressed;		//�\���L�[��������Ă��邩
	bool Xmovingflag = false;	//����x���W�̈ړ����������Ă��邩
	bool Ymovingflag = false;	//����y���W�̈ړ����������Ă��邩
	bool fenceflag = false;		//�t�F���X�̏�ɂ�����
	bool seaflag = false;		//�C�̒��ɂ��邩

	Player();
	Player(double dx, double dy, double dvx, double dvy, double dax, double day);
	Player(const Player &p);					//�R�s�[�R���X�g���N�^
	Player& operator=(const Player& p);			//������Z�q�̃I�[�o�[���[�h
	~Player();

	Player nextPosX(double frametime);		//���ɐi�񂾎���X�����݂̂̏���Ԃ�
	Player nextPosY(double frametime);		//���ɐi�񂾎���Y�����݂̂̏���Ԃ�
	Player nextPosAll(double frametime);	//���ɐi�񂾎��̏���Ԃ�
	void stepPosX(double frametime);		//X�����̂ݐi��
	void stepPosY(double frametime);		//Y�����̂ݐi��
	void stepPosAll(double frametime);		//���̍��W�ɐi��

	int CheckMapNum(Player P, int vecX, int vecY);		//�v���C���[������}�b�v�̕ϐ��̒��g��Ԃ�

	//����4�r�b�g�ŁA�ǂƂ̔���
	int stepRect_x(Rect rect, double frametime);//�}�b�v��̃u���b�N�ƂԂ����Ă�����Ԃ���Ȃ��悤�ɖ߂��Ȃ���x�����̎��Ԃ�i�߂�B�@
	int stepRect_y(Rect rect, double frametime);//�}�b�v��̃u���b�N�ƂԂ����Ă�����Ԃ���Ȃ��悤�ɖ߂��Ȃ���y�����̎��Ԃ�i�߂�B

	//void ForceHorizontalScrollMotion(double frametime);			//�������X�N���[���̓���
	//void CrossKeyAndJumpMotion(double frametime);				//�\���ł̓���
	void Motion(double frametime);								//�v���C���[�̓���
	void Animation(int action);									//�A�j���[�V�����̕�����L�q�A�ɂȂ����߂̊֐�

	void MatchLessProcess(double frametime);					//���G����
	bool CrossKeyInput();										//�\���L�[�ɂ��v���C���[�̑���
	void Jump();												//�W�����v����
	void Jump(int jump);												//�W�����v����

	void Draw();												//�`��
	void Reset();												//�J�����̒����ɖ߂�

	bool HitCheck(Rect rect);									//Enemy->Player�����`rect���Ԃ����Ă��邩�B�v���C���[�̌`���ς��Ες��
	bool HitCheck(Circle cir);									////Enemy->Player �~cir���Ԃ����Ă��邩�B�v���C���[�̌`���ς��Ες��
	void EnemysHitCheck(Mob *mob);								//�G�̐擪�A�h���X�̃|�C���^��n���������蔻��{���������Ă����

	bool Damage(int damage,int matchlesstime);					//�_���[�W���󂯂邽�߂̃C���^�[�t�F�[�X(�_���[�W��,���G����(ms) �߂�l�̓_���[�W����������true

	void Knuckled(Circle cir);									//circle���v���C���[�Ɛڂ���悤�ɂ���
	void Knuckled(Rect rect, int face);							//rect�Ƀv���C���[��face����������
	int KnuckledX(Rect rect);									//rect�Əd�Ȃ�Ȃ��悤�Ƀv���C���[���͂������ �߂�l�͓������Ă����� rect���������Ƃ��蔲����\������
	int KnuckledY(Rect rect);									//rect�Əd�Ȃ�Ȃ��悤�Ƀv���C���[���͂������
};

