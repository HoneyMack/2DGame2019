#include"Hanmer.h"

int Hanmer::PicHandle = 0;

Hanmer::Hanmer(int x, int y):Object() {
	this->x = x;
	this->y = y;
	cir = new  Circle(HANMER_RADIUS, &this->x, &this->y);

	GetGraphSize(PicHandle, &cir->x, &cir->y);

	//微調整が必要かも
	cir->x /= 2;
	cir->y /= 2;

}

Hanmer::~Hanmer() {
	delete cir;
}

void Hanmer::Motion(double frametime) {
	if (CheckInCam()) {
		//ボール回転用
		angle += HANMER_ANGVEL * frametime;
		if (angle >= 2 * PI)
			angle -= 2 * PI;


	
	}	
	stepPosAll(frametime);
	//落下したときに死ぬようにする
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