#include "UpDownObject.h"
int UpDownObject::PicHandle = 0;

UpDownObject::UpDownObject(int set_x, int set_y)
{
	movewidth = UPDOWN_OB_MOVEWIDTH;
	angvel = UPDOWN_OB_ANGVEL;
	x = set_x;
	y = set_y;	

	GetGraphSize(PicHandle, &rect.x, &rect.y);
	rect.x /= 2;
	rect.y /= 2;
	rect.x -= rect.sizeX / 2;
	rect.y -= rect.sizeY / 2 + 1;
}

UpDownObject::~UpDownObject()
{
}

void UpDownObject::Motion(double frametime) {
	if (CheckInCam()) {
		//リフトの動作
		if (angle >= 2 * PI) {
			angle = 0;
		}

		vecY = (movewidth / 2)*(sin(angle));

		angle += angvel*frametime;

		y += vecY;

		//プレイヤーと当たっているかチェックー＞当たっていたらプレイヤーをはじく
		if (usingP->HitCheck(rect)) {
				usingP->KnuckledY(rect);
		}
	}
}

void UpDownObject::Draw()
{
	if (CheckInCam()) {

		
#ifdef DEBUG
		rect.Draw(*Camera);		//あたり判定描画
#endif
		DrawGraph(RelativePosX(), RelativePosY(),PicHandle,TRUE);
		y -= vecY;
	}
}

bool UpDownObject::HitCheck(Rect rect) {
	//UpDownObjectのあたり判定を変えると変わる
	if (CheckRectRect(rect, this->rect)) {	//当たっているか
		HitPlayer();
		return true;
	}
	else
		return false;
}

void UpDownObject::HitPlayer() {
	//ここでは当たっていたらプレイヤーをはじく
	//プレイヤーがx方向に移動して当たったのと、y方向に移動して当たったのとで処理を別ける
	if (usingP->Xmovingflag == true) {
		//usingP->KnuckledX(rect);

		if (usingP->vx > 0) {
			usingP->Knuckled(rect, RIGHT);
		}
		else
			usingP->Knuckled(rect, LEFT);
		
		usingP->vx = 0;		//横にあたっているのでx速さ０に
	}
	if (usingP->Ymovingflag == true) {
		
		if (usingP->vy > 0) {
			usingP->Knuckled(rect, BOTTOM);
			usingP->vy = 0;		//上下で当たっているのでy速さ0に
			usingP->Animation(STAND);
			usingP->Jump();
			if (usingP->keypressed)
				usingP->vx *= 0.9;			//キーが押されているときの横速度減衰率
			else
				usingP->vx *= 0.6;			//キーが押されていないときの横速度減衰率
		}		
		else {
			usingP->Knuckled(rect, TOP);
			usingP->Animation(STAND);
			usingP->vy = 0;		//上下で当たっているのでy速さ0に
		}
		

		//if (usingP->KnuckledY(rect) == BOTTOM)	//プレイヤーの底にぶつかっていたらジャンプを可能に
		//	usingP->Jump();
		////x方向速度減少を発生
		//if (usingP->keypressed)
		//	usingP->vx *= 0.9;			//キーが押されているときの横速度減衰率
		//else
		//	usingP->vx *= 0.6;			//キーが押されていないときの横速度減衰率
	}
}


