#include"FireBar.h"

int FireBar::PicHandle = 0;

FireBar::FireBar(int set_x, int set_y) {
	x = set_x;
	y = set_y;

	int i, j;
	double angle = 2.0* PI / FIREBAR_NUMBER;		//ファイヤーバー同士の角度指定

	int blockx = 0, blocky = 0;			//中心ブロックの大きさを保持
	GetGraphSize(PicHandle, &blockx, &blocky);

	//ブロックの中心とあたり判定の中心を合わせる
	rect.x += (blockx - rect.sizeX) / 2;
	rect.y += (blocky - rect.sizeY) / 2;

	//先頭だけ保持
	fireball = new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 + blockx / 2, 0, FIREBALL_ANGVEL, true, FIREBAR_LENGTH);

	for (i = 0; i < FIREBAR_NUMBER; i++) {
		for (j = 0; j < FIREBAR_LENGTH; j++) {
			if (i + j != 0)
				new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 * (j + 1) + blockx / 2, angle * i, FIREBALL_ANGVEL, true, FIREBAR_LENGTH);
		}
	}
	//中心ブロックもボールに合わせて平行移動
	rect.x += fireball->cir->x;
	rect.y += fireball->cir->y;
	//rectの中心を回転の中心に
	//	rect.x -= rect.sizeX / 2;
	//	rect.y -= rect.sizeY / 2;
}

FireBar::FireBar(int set_x, int set_y, int length, int number) {
	x = set_x;
	y = set_y;

	int i, j;
	double angle = 2.0*PI / number;		//ファイヤーバー同士の角度指定

	int blockx = 0, blocky = 0;			//中心ブロックの大きさを保持
	GetGraphSize(PicHandle, &blockx, &blocky);

	//ブロックの中心とあたり判定の中心を合わせる
	rect.x += (blockx - rect.sizeX) / 2;
	rect.y += (blocky - rect.sizeY) / 2;

	//先頭だけ保持
	fireball = new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 + blockx / 2, 0, FIREBALL_ANGVEL, true,length);

	for (i = 0; i < number; i++) {
		for (j = 0; j < length; j++) {
			if (i + j != 0)
				new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 * (j + 1) + blockx / 2, angle*i, FIREBALL_ANGVEL, true,length);
		}
	}
	//中心ブロックもボールに合わせて平行移動
	rect.x += fireball->cir->x;
	rect.y += fireball->cir->y;
}

FireBar::FireBar(int set_x, int set_y, double set_speed) {
	x = set_x;
	y = set_y;

	int i, j;
	double angle = 2.0* PI / FIREBAR_NUMBER;		//ファイヤーバー同士の角度算出
	set_speed *= PI / 180.0;						//角速度算出

	int blockx = 0, blocky = 0;			//中心ブロックの大きさを保持
	GetGraphSize(PicHandle, &blockx, &blocky);

	//ブロックの中心とあたり判定の中心を合わせる
	rect.x += (blockx - rect.sizeX) / 2;
	rect.y += (blocky - rect.sizeY) / 2;

	//先頭だけ保持
	fireball = new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 + blockx / 2, 0, set_speed, true, FIREBAR_LENGTH);

	for (i = 0; i < FIREBAR_NUMBER; i++) {
		for (j = 0; j < FIREBAR_LENGTH; j++) {
			if (i + j != 0)
				new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 * (j + 1) + blockx / 2, angle * i, set_speed, true, FIREBAR_LENGTH);
		}
	}
	//中心ブロックもボールに合わせて平行移動
	rect.x += fireball->cir->x;
	rect.y += fireball->cir->y;
}

FireBar::FireBar(int set_x, int set_y, bool direction) {
	x = set_x;
	y = set_y;

	int i, j;
	double angle = 2.0* PI / FIREBAR_NUMBER;	//ファイヤーバー同士の角度指定
	double angvel = FIREBALL_ANGVEL;			//角速度指定

	int blockx = 0, blocky = 0;			//中心ブロックの大きさを保持
	GetGraphSize(PicHandle, &blockx, &blocky);

	//ブロックの中心とあたり判定の中心を合わせる
	rect.x += (blockx - rect.sizeX) / 2;
	rect.y += (blocky - rect.sizeY) / 2;

	//先頭だけ保持
	fireball = new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 + blockx / 2, 0, angvel, direction, FIREBAR_LENGTH);

	for (i = 0; i < FIREBAR_NUMBER; i++) {
		for (j = 0; j < FIREBAR_LENGTH; j++) {
			if (i + j != 0)
				new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 * (j + 1) + blockx / 2, angle * i, angvel, direction, FIREBAR_LENGTH);
		}
	}
	//中心ブロックもボールに合わせて平行移動
	rect.x += fireball->cir->x;
	rect.y += fireball->cir->y;
}

FireBar::FireBar(int set_x, int set_y, int set_angle) {
	x = set_x;
	y = set_y;

	int i, j;
	double phase = set_angle / 180 * PI;			//度数法ー＞ラジアン
	double angle = 2.0* PI / FIREBAR_NUMBER;				//ファイヤーバー同士の角度算出

	int blockx = 0, blocky = 0;			//中心ブロックの大きさを保持
	GetGraphSize(PicHandle, &blockx, &blocky);

	//ブロックの中心とあたり判定の中心を合わせる
	rect.x += (blockx - rect.sizeX) / 2;
	rect.y += (blocky - rect.sizeY) / 2;

	//先頭だけ保持
	fireball = new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 + blockx / 2, phase, FIREBALL_ANGVEL, true, FIREBAR_LENGTH);

	for (i = 0; i < FIREBAR_NUMBER; i++) {
		for (j = 0; j < FIREBAR_LENGTH; j++) {
			if (i + j != 0)
				new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 * (j + 1) + blockx / 2, angle * i + phase, FIREBALL_ANGVEL, true, FIREBAR_LENGTH);
		}
	}
	//中心ブロックもボールに合わせて平行移動
	rect.x += fireball->cir->x;
	rect.y += fireball->cir->y;
}
FireBar::FireBar(int set_x, int set_y, double set_speed, bool direction, int length, int number, int set_angle) {
	x = set_x;
	y = set_y;

	int i, j;

	double phase = set_angle / 180 * PI;			//度数法ー＞ラジアン
	double speed = set_speed*(PI / 180.0);			//角速度指定
	double angle = 2.0* PI / number;				//ファイヤーバー同士の角度算出


	int blockx = 0, blocky = 0;			//中心ブロックの大きさを保持
	GetGraphSize(PicHandle, &blockx, &blocky);

	//ブロックの中心とあたり判定の中心を合わせる
	rect.x += (blockx - rect.sizeX) / 2;
	rect.y += (blocky - rect.sizeY) / 2; 
	

	//先頭のみ保持
	fireball = new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 + blockx / 2, phase, speed, direction,length);

	//ファイヤーボール生成
	for (i = 0; i < number; i++) {
		for (j = 0; j < length; j++) {
			if (i + j != 0)
				new FireBall(x + blockx / 2, y + blocky / 2, FIREBAR_BALL_RADIUS * 2 * (j + 1) + blockx / 2, angle * i + phase, speed, direction,length);
		}
	}
	//中心ブロックもボールに合わせて平行移動
	rect.x += fireball->cir->x;
	rect.y += fireball->cir->y;
}

FireBar::~FireBar() {
}

void FireBar::Motion(double frametime) {


}

void FireBar::Draw() {
	if (CheckInCam()) {
		DrawGraph(RelativePosX() + fireball->cir->x, RelativePosY() + fireball->cir->y, PicHandle, TRUE);
#ifdef DEBUG
		rect.Draw(*Camera);
#endif
	}
}

bool FireBar::HitCheck(Rect rect) {
	if (CheckRectRect(rect, this->rect)) {
		HitPlayer();
		return true;
	}
	else {
		return false;
	}
}

void FireBar::HitPlayer() {
	//ここでは当たっていたらプレイヤーをはじく
	//プレイヤーがx方向に移動して当たったのと、y方向に移動して当たったのとで処理を別ける
	if (usingP->Xmovingflag == true) {
		//usingP->KnuckledX(rect);

		if (usingP->vx > 0) {
			usingP->Knuckled(rect, RIGHT);
			usingP->Jump();
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
	}
}