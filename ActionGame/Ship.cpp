#include "Ship.h"

int Ship::PicHandle = 0;

Ship::Ship(int x, int y, double set_angle)
{
	this->x = x;
	this->y = y;
	angle = set_angle;
	if (angle >= 360) {	//いらないかもしれない　一応
		int i = angle / 360;
		angle -= 360 * i;
	}
	angle = 360 - angle;	//windows上での角度指定に合わせる処理
	angle *= PI / 180;	//ラジアンへ変換
	vx = SHIP_MOVESPEED * cos(angle);
	vy = SHIP_MOVESPEED * sin(angle);

	ay = 0;

	//画像が決まったらこの処理を見直す。
	GetGraphSize(PicHandle, &rect.x, &rect.y);
	rect.x /= 2;
	rect.y /= 2;
	//rect.y = 0;
	rect.x -= rect.sizeX / 2;
	rect.y -= rect.sizeY / 2 - 4;
}

Ship::~Ship()
{
}

void Ship::Motion(double frametime)
{
	if (CheckInCam()) {
		startflag = true;
		stepPosAll(frametime);
		if (y >= HEIGHT || y <= 0)
			deathflag = true;	//yの範囲を超えたら消滅
	}
	else if (startflag) {
		deathflag = true;	//画面内に入り動かしてから画面外に出たら消滅
		//これまずい？	まずかったら時間指定を入れる
	}
}

void Ship::Draw()
{
	if (CheckInCam()) {
		DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);

#ifdef DEBUG
		rect.Draw(*Camera);
#endif // DEBUG

	}
}

bool Ship::HitCheck(Rect rect)
{
	////return false;
	//if (CheckRectRect(rect, this->rect)) {
	//	if (usingP->Xmovingflag) {
	//		//x
	//		usingP->vx = 0;
	//		usingP->KnuckledX(this->rect);
	//		return true;
	//	}
	//	else if (usingP->vy < 0) {
	//		usingP->vy = 0;
	//		usingP->Knuckled(this->rect, TOP);
	//		return true;
	//	}
	//	//else if (HitFaceRectRect(rect, this->rect) & TOP && usingP->vy > 0 && usingP->Ymovingflag && !(HitFaceRectRect(rect, this->rect) & BOTTOM)) {
	//	else{	
	//		HitPlayer();
	//		return true;
	//	}
	//	/*else
	//		return false;*/
	//}
	if (CheckRectRect(rect, this->rect)) {
		if (HitFaceRectRect(rect, this->rect) & TOP && !(HitFaceRectRect(rect,this->rect) & BOTTOM)) {
			HitPlayer();
			unsigned int a = HitFaceRectRect(rect, this->rect);
			return true;
		}
		else if (usingP->Xmovingflag) {
			//x
			usingP->vx = 0;
			usingP->KnuckledX(this->rect);
			return true;
		}
		else if (usingP->vy < 0) {
			usingP->vy = 0;
			usingP->Knuckled(this->rect, TOP);
			return true;
		}
		else return false;
	}
	return false;
}

void Ship::HitPlayer()
{
	//上から当たった時プレイヤーを弾く
	if (usingP->Ymovingflag == true) {
		if (usingP->vy > 0) {
			//上昇と下降でプレイヤーの速度を変える
			if (angle*180/PI < 180)
				usingP->vy = vy;
			else
				usingP->vy = 0;

			usingP->Knuckled(rect, BOTTOM);
			usingP->Animation(STAND);
			usingP->Jump();

			if (usingP->keypressed)
				usingP->vx *= 0.9;			//キーが押されているときの横速度減衰率
			else
				usingP->vx *= 0.6;			//キーが押されていないときの横速度減衰率
		}
	}
}
