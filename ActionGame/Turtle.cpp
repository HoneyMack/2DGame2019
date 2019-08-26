#include"Turtle.h"

int Turtle::PicTurtleHandle = 0;
int Turtle::PicShellHandle[] = { 0,0,0,0 };

Turtle::Turtle(int x, int y)
{
	//あたり判定位置セット
	this->x = x;
	this->y = y;


	GetGraphSize(PicTurtleHandle, &cir.x, &cir.y);

	//微調整済み
	cir.x = cir.x / 2;
	cir.y = cir.y / 2 + 3;

	velocity = TURTLE_MOVESPEED;	//速度をセット
	formflag = 0;
}

Turtle::~Turtle() {

}

void Turtle::Motion(double frametime) {
	if (CheckInCam()) {
		//アニメーション切り替え
		if (animation < TURTLE_TURNTIME) {
			animation += frametime * 1000;
		}
		else {
			animation -= TURTLE_TURNTIME;
			index = (index + 1) % 4;
		}

		//ハイジャンプ用フラグ
		if (waittime < KILLHIGHJUMPTIME) {
			waittime += frametime * 1000;
			//ハイジャンプ可能にする
			if (InKeyTrigger(usingP->now_key, PAD_INPUT_10)) {
				usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
				PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
				waittime = KILLHIGHJUMPTIME;
			}
		}
		//たこ
		if (formflag == 0) {
			int hitface = 0x0000;

			//移動向き反転
			if (vecX + velocity * frametime > TURTLE_MOVEWIDTH / 2 || vecX + velocity * frametime < -TURTLE_MOVEWIDTH / 2) {
				velocity = -velocity;
			}
			vecX += velocity * frametime;
			x += velocity * frametime;

			hitface = stepCircle_x(cir, frametime);
			if ((hitface & RIGHT) || (hitface & LEFT)) {
				velocity = -velocity;
			}

			hitface = stepCircle_y(cir, frametime);		//y方向の時間を進める
			if ((hitface & BOTTOM) || (hitface & TOP)) {
				vy = 0.0;
			}
		}
		//たこ焼き
		else if (formflag == 1) {
			velocity = 0;
			int hitface = 0x0000;
			hitface = stepCircle_x(cir, frametime);
			hitface = stepCircle_y(cir, frametime);
			if ((hitface & BOTTOM) || (hitface & TOP)) {
				vy = 0;
			}
			//画像をtopに
			index = 0;
		}

	}
	//回転中
	if (formflag == 2) {
		int hitface = 0x0000;

		if (dflag == true)
			shellvelocity = -TURTLE_SHELLSPEED;
		else
			shellvelocity = TURTLE_SHELLSPEED;

		x += shellvelocity * frametime;
		hitface = stepCircle_x(cir, frametime);
		if ((hitface & RIGHT) || (hitface & LEFT)) {
			//shellvelocity = -shellvelocity;
			dflag = !dflag;
		}


		hitface = stepCircle_y(cir, frametime);		//y方向の時間を進める
		if ((hitface & BOTTOM) || (hitface & TOP)) {
			vy = 0.0;
			//ay = 0.0;
		}
	}
	//落下したときに死ぬようにする
	if (y > HEIGHT)
		deathflag = true;
}

void Turtle::Draw() {
	if (CheckInCam()) {
		if (formflag == 0) {
			if (velocity <= 0)
				DrawGraph(RelativePosX(), RelativePosY(), PicTurtleHandle, TRUE);
			else
				DrawTurnGraph(RelativePosX(), RelativePosY(), PicTurtleHandle, TRUE);

		}
		else {
			if (velocity < 0)
				DrawGraph(RelativePosX(), RelativePosY(), PicShellHandle[(index + 3) % 4], TRUE);
			else
				DrawGraph(RelativePosX(), RelativePosY(), PicShellHandle[index], TRUE);

		}
#ifdef DEBUG
		cir.Draw(*Camera);
#endif
	}

}

bool Turtle::HitCheck(Rect rect) {
	if (CheckCircleRect(cir, rect)) {
		//プライヤーが落下してきて、プレイヤーの下が自分にあたっていたら自分が死んでプレイヤーにダメージは入らない
		if (HitFaceCircleRect(this->cir, rect) & BOTTOM && usingP->Ymovingflag && !((HitFaceCircleRect(this->cir, rect) & TOP))) { // && usingP->vy > 0) {
			//上からあたっているか(下から上でないか)
			if (usingP->vy > 0) {
				//プレイヤーが上からぶつかったのでハイジャンプ判定をする
				waittime = 0;

				//次の形態に移動
				formflag++;
				if (formflag >= 3) {		//もし、たこ焼きが回転してたら、止める
					formflag = 1;
					//画像をtopに
					index = 0;
					
				}

				//あたり判定大きさ変更
				this->cir = Circle(SHELL_RADIUS, &this->x, &this->y);
				GetGraphSize(PicShellHandle[index], &this->cir.x, &this->cir.y);
				//調整済み
				this->cir.x /= 2;
				this->cir.y = this->cir.y / 2 + 3;

				//中央から右からあたった
				if (usingP->x + usingP->rect.x + usingP->rect.sizeX / 2 >= x + this->cir.x) {
					dflag = true;
					//formflag++;
				}
				else {
					dflag = false;
					//formflag++;
				}

				//プレイヤーをはじく
				usingP->Knuckled(this->cir);
				waittime = 0;
				usingP->Animation(JUMP);
				//ハイジャンプ可能にする
				if (usingP->now_key & PAD_INPUT_10) {

					usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
					PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
					waittime = KILLHIGHJUMPTIME;
				}

				PlaySoundMem(Sound::sounds[SOUND_ENEMYTREAD], DX_PLAYTYPE_BACK);
				usingP->vy = -KILLJUMP;
			}
			else {//下から上に移動したことで当たっているので
				HitPlayer();
			}
		}
		//左右からぶつかったパターン
		else {
			//たこ
			if (formflag == 0) {
				HitPlayer();
			}
			//回転中
			else if (formflag == 2) {
				HitPlayer();
			}
			//たこやき
			else {
				//プレイヤーをはじく
				usingP->Knuckled(this->cir);
				//右側からあたった
				if (usingP->x + usingP->rect.x + usingP->rect.sizeX / 2 >= x + this->cir.x) {
					dflag = true;
					formflag++;
				}
				else {
					dflag = false;
					formflag++;
				}
			}
		}
		return true;
	}
	else
		return false;
}

void Turtle::HitPlayer() {
	usingP->Damage(TURTLE_HITDAMAGE, ENEMYMATCHLESSTIME);
}