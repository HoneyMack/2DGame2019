#include"Lift.h"

int Lift::PicDownHandle = 0;
int Lift::PicUpHandle = 0;

Lift::Lift(int set_x, int set_y,bool set_direction) :Object()
{
	x = set_x;
	y = set_y;
	vy = LIFT_MOVESPEED;
	direction = set_direction;
	if (direction == FALSE)
		vy *= -1;
	
	ay = 0;

	GetGraphSize(PicDownHandle, &rect.x, &rect.y);
	rect.x /= 2;
	rect.y /= 2;
	//rect.y = 0;
	rect.x -= rect.sizeX / 2;
	rect.y -= rect.sizeY / 2 - 4;
}


Lift::~Lift()
{
}

void Lift::Motion(double frametime)
{
	if (dropflag == 1) {   //プレイヤーが一度リフトを踏むと落下開始
		//y+= LIFT_MOVESPEED;
		stepPosY(frametime);
		if (y >= HEIGHT||y<=0)
			deathflag = true;  //下まで下がったら消滅
	}
}

void Lift::Draw()
{
	if (CheckInCam()) {
#ifdef DEBUG
		rect.Draw(*Camera);		//あたり判定描画
#endif
		if(direction){
		DrawGraph(RelativePosX(),RelativePosY(),PicDownHandle,TRUE);
		}
		else {
			DrawGraph(RelativePosX(), RelativePosY(), PicUpHandle, TRUE);
		}
		}
}

bool Lift::HitCheck(Rect rect)
{
	if (CheckRectRect(rect, this->rect)) {
		//プレイヤーが落下してきて、自分の上にあったたら跳ね返す
		if (HitFaceRectRect(rect, this->rect) & TOP && usingP->vy > 0 && usingP->Ymovingflag && !(HitFaceRectRect(rect, this->rect) & BOTTOM)) {
			HitPlayer();
			dropflag = 1;  //プレイヤーが自分の上に当たったら落下開始（落下フラグ＝＝１）
			return true;
		}
		else
			return false;
	}
	return false;
}

void Lift::HitPlayer()
{
	//上から当たった時プレイヤーを弾く
	if (usingP->Ymovingflag == true) {
		if (usingP->vy > 0) {
			//上昇と下降でプレイヤーの速度を変える
			if (direction == 1)
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