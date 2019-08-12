#pragma once
#include <vector>
#include "define.h"
#include "Rect.h"

using namespace std;

class Map
{
private:
	int numX, numY;
public:
	static int PicHandle[];						//�摜�ێ�
	vector<vector<int> > m_map;					//�`�悷��}�b�v�̏��

	Map();										//�R���X�g���N�^
	Map(int lenX);								//�R���X�g���N�^
	~Map();										//�f�X�g���N�^

	void setNum(int x, int y);					//�ϐ�numX = x,numY = y�ɃZ�b�g (�z�񂠂ӂ��h�����߂̕ی�)
	void setArray();							//�z��̒�����numX,numY�ɃZ�b�g
	void resetMap();							//�}�b�v�̗v�f��0�ŏ�����
	void setFrame();							//�v���C���[�����ӂ�Ȃ��悤�ɊO�g�����

	int getNumX();								//numX��Ԃ�
	int getNumY();								//numY��Ԃ�

	int PosInfo(int x,int y);	//x,y���W�̃u���b�N�̃i���o�[��Ԃ�
	void Draw(Rect *Camera);
};

//�}�b�v�ł̗v�f�ԍ��ɒ���
int ReturnMapIndex(double x);