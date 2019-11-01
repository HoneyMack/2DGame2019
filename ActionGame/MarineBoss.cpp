#include "MarineBoss.h"

int MarineBoss::PicHandle[] = { 0,0 };

MarineBoss::MarineBoss(int sx, int sy, int fx)
{
	this->x = sx;
	this->y = sy;

	this->fx = fx;
	this->tx = sx;

	for (int i = 0; i < BOSS_UNI_CNT; i++) {
		UNI[i] = new Urchin(x,-40);
	}

	rect.x = 5;
	rect.y = 7;

	startflag = false;
	velocity = BOSS_MOVESPEED;
	unitime = BOSS_UNITIME_FIRST;	//ウニを落とす時間を設定
}

MarineBoss::~MarineBoss()
{
	for (int i = 0; i < BOSS_UNI_CNT; i++) {
		UNI[i]->~Urchin();
	}
}

void MarineBoss::Motion(double frametime)
{
	if (Blockforblock::startflag) 
		
		startflag = true;
		//ハイジャンプ用フラグ
		if (waittime < KILLHIGHJUMPTIME) {
			waittime += frametime * 1000;
			//ハイジャンプ可能にする
			if (usingP->now_key & PAD_INPUT_10) {
				usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
				PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
				waittime = KILLHIGHJUMPTIME;
			}
		}
		switch (stats)
		{
		case 0:
			//何もしてない、次の行動を選択
			if (startflag) {
				stats = rnd() % 3 + 1;
				cnttime = 0;
			}
			break;
		case 1:
			//左方向に横移動
			velocity = -BOSS_MOVESPEED;
			x += velocity * frametime;
			if (x <= fx) {	//行動範囲の左端に到達
				stats = 4;	//右方向へ横移動に変更
				cnttime = 0;
			}
			break;
		case 2:
			//高質化
			if (HardeningFlag == false) {
				//今、硬質化した
				HardeningFlag = true;
			}
			cnttime++;
			if (cnttime >= BOSS_HARDTIME) {
				HardeningFlag = false;	//硬質化解除
				stats = 6;	//行動後の待ち時間へ移行
				cnttime = 0;
			}
			break;
		case 3:
			//ウニ落とし
			//用サウンド追加
			if (Uniflag == false) {
				Uniflag = true;

			}
			cnttime++;
			if ((int)cnttime % BOSS_UNI_INTERVAL == 0) {
				//ウニを落とす処理を追加
				UNI[unicnt]->x = (rnd() % (tx - fx)) + fx + BOSS_SIZEX;
				UNI[unicnt]->y = 1;
				unicnt++;
			}
			if (cnttime >= unitime) {
				cnttime = 0;
				stats = 6;
				unicnt = 0;
				
			}
			break;
		case 4:
			//右方向移動
			velocity = BOSS_MOVESPEED;
			x += velocity * frametime;
			if (x >= tx) {
				stats = 6;
				cnttime = 0;
			}
			break;
		case 5:
			//ウニ落とし+硬質化
			//用サウンド追加
			if (HardeningFlag == false) {
				HardeningFlag = true;
			}
			cnttime++;
			if ((int)cnttime % BOSS_UNI_INTERVAL == 0) {
				//ウニを落とす処理を追加
				UNI[unicnt]->x = (rnd() % (tx - fx)) + fx + BOSS_SIZEX;
				UNI[unicnt]->y = 1;
				unicnt++;
			}
			if (cnttime >= BOSS_HARDTIME) {
				HardeningFlag = false;	//硬質化解除
				stats = 6;	//行動後の待ち時間へ移行
				cnttime = 0;
				unicnt = 0;
				
			}
			break;
		case 6:
			//行動間wait時間
			cnttime++;
			if (cnttime >= BOSS_ACTION_INTERVAL) {
				cnttime = 0;
				stats = 0;
			}
		default:
			break;
		}


		int hitface = 0x0000;
		hitface = stepRect_y(rect, frametime);		//y方向の時間を進める
		if ((hitface & BOTTOM) || (hitface & TOP)) {
			vy = 0.0;
		}
		for (int i = 0; i < BOSS_UNI_CNT; i++) {
			UNI[i]->Motion(frametime);
		}
	
	//落下したときに死ぬようにする
	if (y > HEIGHT)
		deathflag = true;
}

void MarineBoss::Draw()
{
#ifdef DEBUG
		rect.Draw(*Camera);
#endif
	if (CheckInCam()) {
		if (stats == 0 || stats == 1 || stats == 3 || stats == 6)	//左向き正常
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle[0], TRUE);
		else if (stats == 4)
			DrawTurnGraph(RelativePosX(), RelativePosY(), PicHandle[0], TRUE);
		else if (stats == 2 || stats == 5) {
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle[0], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, SEA_TRANSPARENCY);
			DrawGraph(RelativePosX(), RelativePosY(), PicHandle[1], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		for (int i = 0; i < BOSS_UNI_CNT; i++) {
			UNI[i]->Draw();
		}

	}
}

bool MarineBoss::HitCheck(Rect rect)
{
	//return false;
	if (CheckRectRect(rect, this->rect)) {
		//プライヤーが落下してきて、自分の上にあたっていたら自分が死んでプレイヤーにダメージは入らない
		if (HitFaceRectRect(rect, this->rect) & TOP && usingP->vy > 0 && usingP->Ymovingflag && !(HitFaceRectRect(rect, this->rect) & BOTTOM)) {
			//killedenemy++;
			PlaySoundMem(Sound::sounds[SOUND_ENEMYTREAD], DX_PLAYTYPE_BACK);
			//deathflag = true;
			if (stats != 2 && stats != 5) {
				hp--;	//hpを減らす
				stats = 5;
				cnttime = 0;
			}
			if (hp <= 0) {
				Blockforblock::liveflag = false;
				deathflag = true;	//hpが０なら死亡
			}
			//usingP->vx -= BOSS_DROPED_VX;
			if (usingP->x < this->x+BOSS_SIZEX/2)usingP->vx -= BOSS_DROPED_VX;
			else usingP->vx += BOSS_DROPED_VX;
			usingP->vy -= BOSS_DROPED_VY;
			usingP->Knuckled(this->rect, BOTTOM);

			waittime = 0;
			//ハイジャンプ可能にする
			usingP->Animation(JUMP);
			if (usingP->now_key & PAD_INPUT_10) {

				usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
				PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
				waittime = KILLHIGHJUMPTIME;
				//usingP->vy = -JUMPSPEED;
			}
			usingP->vy = -KILLJUMP;
		}
		else
			HitPlayer();


		return true;
	}
	else {
		for (int i = 0; i < BOSS_UNI_CNT; i++) {
			//ウニの当たり判定
			if (CheckCircleRect(*UNI[i]->cir, rect)) {
				usingP->Damage(BOSS_UNI_HITDAMAGE, ENEMYMATCHLESSTIME);
				return true;
			}
		}
	}
		return false;
}

void MarineBoss::HitPlayer()
{
	usingP->Damage(BOSS_HITDAMAGE, ENEMYMATCHLESSTIME);
}
