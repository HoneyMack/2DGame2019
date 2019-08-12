#include"Hanmer.h"

int Hanmer::PicHandle = 0;

Hanmer::Hanmer(int x, int y):Object() {
	this->x = x;
	this->y = y;
	cir = new  Circle(HANMER_RADIUS, &this->x, &this->y);

	GetGraphSize(PicHandle, &cir->x, &cir->y);

	//���������K�v����
	cir->x /= 2;
	cir->y /= 2;

}

Hanmer::~Hanmer() {
	delete cir;
}

void Hanmer::Motion(double frametime) {
	if (CheckInCam()) {
		//�{�[����]�p
		angle += HANMER_ANGVEL * frametime;
		if (angle >= 2 * PI)
			angle -= 2 * PI;


	
	}	
	stepPosAll(frametime);
	//���������Ƃ��Ɏ��ʂ悤�ɂ���
	if (y > HEIGHT)
		deathflag = true;
}

void Hanmer::Draw() {
	if (CheckInCam()) {
		DrawRotaGraph(RelativePosX() + cir->x, RelativePosY() + cir->y, 1.0, angle, PicHandle, TRUE, FALSE);
		//DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
#ifdef DEBUG
		cir->Draw(*Camera);
#endif
	}
}

bool Hanmer::HitCheck(Rect rect) {
	if (CheckCircleRect(*cir,rect)) {
		HitPlayer();
		return true;
	}
	else
		return false;
}

void Hanmer::HitPlayer() {
	usingP->Damage(HANMER_HITDAMAGE, ENEMYMATCHLESSTIME);
}