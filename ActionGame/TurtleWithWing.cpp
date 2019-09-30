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
		//羽状態のときは、上下に移動（単振動）
		if (isWithWing) {
			//羽の状態でturtleが踏まれたら、生き返らせ、パタパタを解除
			if (turtle->formflag == 1) {
				turtle->formflag = 0;//タコの形状を戻す
				isWithWing = false;
			}

			//上下に移動し、turtleを無理やり動かす
			turtle->y = y = initY + TURTLEWITHWING_MOVEMENT * sin(2.0 * PI *
				((double)((Stage::limit + initPhase) % (TURTLEWITHWING_PERIODICTIME)) / TURTLEWITHWING_PERIODICTIME));
			turtle->x = x;
			turtle->vy = 0; //自由落下を無効に
		}
	}
}

void TurtleWithWing::Draw() {
	if (CheckInCam()) {
		if (isWithWing) {
			//羽を描画(要修正)
			DrawGraph(RelativePosX(), RelativePosY(), PicHandleWing, TRUE);
		}
	}
}
