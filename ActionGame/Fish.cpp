#include "Fish.h"

//行動限界まで行ってプレイヤーを追いかける状態だと反復横跳びする。要修正

int Fish::PicHandle = 0;

Fish::Fish(int x, int y)
{
	//当たり判定位置セット
	this->x = x;
	this->y = y;

	//重力を無効に
	ay = 0;
	rect.x = 3;
	rect.y = 5;
	rect.sizeX = 25;
	rect.sizeY = 25;

	fx = x;
	fy = y;

	velocityX = FISH_SPEED;	//速度セット
	velocityY = 0;
}

Fish::~Fish()
{
}

void Fish::Motion(double frametime)
{
	double angle;
	if (CheckInCam()) {
		int hitface = 0x0000;



		//プレイヤーとの距離が一定以下であれば追いかける
		//プレイヤーが範囲外に出たら追いかけないようにする。範囲恥での反復横跳び防止
		if (((x - usingP->x) * (x - usingP->x) + (usingP->y - y) * (usingP->y - y)) < FISH_CHASE_DISTANCE * FISH_CHASE_DISTANCE
			&& (fx + FISH_MOVEWIDTH / 2 > usingP->x) && (fx - FISH_MOVEWIDTH / 2 < usingP->x)) {
			chasing = true;	//追いかけフラグセット

			//プレイヤーとfishとの角度を計算する
			//angle = atan((usingP->y - y) / (x - usingP->x));	//0除算　要修正
			if (x - usingP->x < ZEROEXCEPTION)
				angle = atan((usingP->y - y) / ZEROEXCEPTION);
			else
				angle = atan((usingP->y - y) / (x - usingP->x));	//0除算　要修正


			angle *= 180. / PI;
			//if (angle < 0)angle *= -1;

			//プレイヤーとの角度が限界角度以上であった場合限界角度として進む方向を変更
			if (angle >= FISH_LIMIT_ANGLE) {
				velocityX = FISH_SPEED * cos(FISH_LIMIT_ANGLE * PI / 180.);
				velocityY = FISH_SPEED * sin(FISH_LIMIT_ANGLE * PI / 180.);
			}
			else if (angle <= -FISH_LIMIT_ANGLE) {
				velocityX = FISH_SPEED * cos(-FISH_LIMIT_ANGLE * PI / 180.);
				velocityY = FISH_SPEED * sin(-FISH_LIMIT_ANGLE * PI / 180.);
			}
			//プレイヤーとの角度が小さければプレイヤーを追いかける
			else {
				velocityX = FISH_SPEED * cos(angle * PI / 180.);	//ここで勝手に設定すると壁を突き抜けるかもしれない。突き抜けたら修正する。
				velocityY = FISH_SPEED * sin(angle * PI / 180.);
			}
			if (usingP->x < x || velocityX < 0)
				velocityX = -velocityX;
			/*if (usingP->y < y || velocityY < 0)
				velocityY = -velocityY;*/
		}
		//プレイヤーとの距離が離れている場合は横移動
		else if (chasing == true) {
			chasing = false;
			velocityX = FISH_SPEED;
			velocityY = 0;
		}

		/*if (vecX + velocityX * frametime > FISH_MOVEWIDTH / 2) || vecX + velocityX * frametime < -FISH_MOVEWIDTH / 2) {

		velocityX = -velocityX;
		}*/

		if ((fx + FISH_MOVEWIDTH / 2 < x) || (fx - FISH_MOVEWIDTH / 2 > x)){
		velocityX = -velocityX;

		}

		vecX += velocityX * frametime;
		//x += velocityX * frametime;
		vx = velocityX;

		hitface = stepRect_x(rect, frametime);
		if ((hitface & RIGHT) || (hitface & LEFT)) {
			velocityX = -velocityX;
		}

		//y += velocityY * frametime;
		vy = velocityY;

		//vy = velocityY;
		//stepPosY(frametime);


		hitface = stepRect_y(rect, frametime);		//y方向の時間を進める
		//if ((hitface & BOTTOM) || (hitface & TOP)) {
		//	vy = 0.0;
		//	velocityY = 0;
		//}
		//y += velocityY * frametime;
		
	}
}

void Fish::Draw()
{
	if (CheckInCam()) {
		//反復横跳び防止
		if (velocityX <= 0 || (usingP->x - x < 5 && usingP->x - x > -5))
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
		else
			DrawTurnGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
#ifdef DEBUG
		rect.Draw(*Camera);
#endif			

	}
}

bool Fish::HitCheck(Rect rect)
{
	if (CheckRectRect(rect, this->rect)) {
		HitPlayer();
		return true;
	}
	else
		return false;
}

void Fish::HitPlayer()
{
	usingP->Damage(FISH_HITDAMAGE, ENEMYMATCHLESSTIME);
}




