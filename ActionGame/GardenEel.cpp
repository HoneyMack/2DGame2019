#include "GardenEel.h"
#include "Stage.h"
int GardenEel::PicHandle = 0; //�`���A�i�S�摜�n���h���ێ�


GardenEel::GardenEel(int _x, int _y, int _initPhase) {
	initX = x = _x;
	initY = y = _y;
	initPhase = _initPhase;

	//�����蔻��̈ʒu���������\��(�摜����)
}

void GardenEel::Motion(double ftime) {
	if (CheckInCam() || CheckInCam(x + GARDENEEL_SIZEX, y)) {
		//���݂̈ʒu���v�Z�����
		int time = (GARDENEEL_HIDINGTIME + GARDENEEL_RISINGTIME + GARDENEEL_HOLDINGTIME + GARDENEEL_FALLINGTIME) - (Stage::limit + initPhase) % (GARDENEEL_HIDINGTIME + GARDENEEL_RISINGTIME + GARDENEEL_HOLDINGTIME + GARDENEEL_FALLINGTIME);
		if (time < GARDENEEL_HIDINGTIME) y = initY; //�����Ȃ��悤��
		else if (time < GARDENEEL_HIDINGTIME + GARDENEEL_RISINGTIME) {
			//���������^���ŏ㏸
			time -= GARDENEEL_HIDINGTIME;
			y = initY - (int)(GARDENEEL_SIZEY * (double)time / GARDENEEL_RISINGTIME);
		}
		else if (time < GARDENEEL_HIDINGTIME + GARDENEEL_RISINGTIME + GARDENEEL_HOLDINGTIME) {
			y = initY - GARDENEEL_SIZEY;
		}
		else {
			time -= GARDENEEL_HIDINGTIME + GARDENEEL_RISINGTIME + GARDENEEL_HOLDINGTIME;
			y = initY - (int)(GARDENEEL_SIZEY * (1.0 - (double)time / GARDENEEL_FALLINGTIME));
		}
	}
}

void GardenEel::Draw() {
	//�`���A�i�S�������ł��ʂ��Ă�����`��
	if (CheckInCam() || CheckInCam(x + GARDENEEL_SIZEX, y)) {
		//���݈ʒu���珉���ʒu�܂ŕ`��
		DrawRectGraph(RelativePosX(), RelativePosY(), 0, 0, GARDENEEL_SIZEX, initY - y, PicHandle, TRUE);
	}
#ifdef DEBUG
	//collider.Draw(*Camera);
#endif 
}

bool GardenEel::HitCheck(Rect rect) {
	//�����蔻�蓯�m���Փ˂��Ă��邩�AHidingTime���ł͂Ȃ�
	if (CheckRectRect(rect, collider)
		&& (Stage::limit + initPhase) % (GARDENEEL_HIDINGTIME + GARDENEEL_RISINGTIME + GARDENEEL_FALLINGTIME + GARDENEEL_HOLDINGTIME)
		> GARDENEEL_HIDINGTIME) {
		HitPlayer();
		return true;
	}
	return false;
}

void GardenEel::HitPlayer() {
	usingP->Damage(GARDENEEL_DAMAGE, ENEMYMATCHLESSTIME);
}