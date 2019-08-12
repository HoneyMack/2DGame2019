#include"FireBall.h"

//メモリの無駄がある。もしメモリがいっぱいになったらここを修正する。
int FireBall::PicHandle = 0;

FireBall::FireBall(int set_x, int set_y, int set_radius,double set_angle,double set_angvel,bool set_direction,int max_radius) {  
	direction = set_direction;
	
	angle = set_angle;
	radius = set_radius;
	this->max_radius = max_radius;

	x = radius*cos(angle) + set_x;
	y = radius*sin(angle) + set_y;


	fx = set_x;
	fy = set_y;


	angvel = set_angvel;

	cir = new Circle(FIREBAR_BALL_RADIUS, &this->x, &this->y);
	//写真の大きさを得て中心にそろえる
	GetGraphSize(PicHandle, &cir->x, &cir->y);
	cir->x /= 2;
	cir->y /= 2;
}

FireBall::~FireBall() {
	delete cir;
}

void FireBall::Motion(double frametime) {
	//中心座標でやらんとだめ
//	if (Object::CheckInCam(fx - 2*(max_radius + 2)*FIREBAR_BALL_RADIUS, fy) || Object::CheckInCam(fx + 2*(max_radius + 2)*FIREBAR_BALL_RADIUS, fy)) 
	{
		if (angle >= 2 * PI) {
			angle -= 2 * PI;
		}
		angle += angvel*frametime;

		if (direction) {
			x = radius*cos(angle) + fx;
			y = radius*sin(angle) + fy;
		}
		else {
			x = radius*cos(2 * PI - angle) + fx;
			y = radius*sin(2 * PI - angle) + fy;
		}
	}
}

void FireBall::Draw() {
	if (Object::CheckInCam(x, y)) {
		DrawRotaGraph(x - Object::Camera->x + cir->x, y - Object::Camera->y+ cir->y,1.0,angle*3, PicHandle, TRUE,FALSE);
#ifdef DEBUG
		cir->Draw(*Object::Camera);
#endif
	}
}

bool FireBall::HitCheck(Rect rect) {
	if (CheckCircleRect(*this->cir, rect)) {
		Object::usingP->Damage(FIREBALL_DAMAGE,ENEMYMATCHLESSTIME);	//ダメージ
		return true;
	}
	else
		return false;
}