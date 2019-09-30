#include "TurtleWithWing.h"
#include "Stage.h"
#include <math.h>

int TurtleWithWing::PicHandleWing = 0;

TurtleWithWing::TurtleWithWing(int _x, int _y, int _initPhase) {
	initX = x = _x;
	initY = y = _y;
	initPhase = _initPhase;

	turtle = new Turtle(x, y);
	isWithWing = true;
}

TurtleWithWing::~TurtleWithWing() {
}

void TurtleWithWing::Motion(double ftime) {
	if (CheckInCam()) {
		//�H��Ԃ̂Ƃ��́A�㉺�Ɉړ��i�P�U���j
		if (isWithWing) {
			//�H�̏�Ԃ�turtle�����܂ꂽ��A�����Ԃ点�A�p�^�p�^������
			if (turtle->formflag == 1) {
				turtle->formflag = 0;//�^�R�̌`���߂�
				isWithWing = false;
			}

			//�㉺�Ɉړ����Aturtle�𖳗���蓮����
			turtle->y = y = initY + TURTLEWITHWING_MOVEMENT * sin(2.0 * PI *
				((double)((Stage::limit + initPhase) % (TURTLEWITHWING_PERIODICTIME)) / TURTLEWITHWING_PERIODICTIME));
			turtle->x = x;
			turtle->vy = 0; //���R�����𖳌���
		}
	}
}

void TurtleWithWing::Draw() {
	if (CheckInCam()) {
		if (isWithWing) {
			//�H��`��(�v�C��)
			DrawGraph(RelativePosX(), RelativePosY(), PicHandleWing, TRUE);
		}
	}
}
