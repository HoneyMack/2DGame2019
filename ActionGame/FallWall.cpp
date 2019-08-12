#include "FallWall.h"
int FallWall::RedExamPicHandle = 0;
int FallWall::BirdPicHandle[] = {0,0};

RedExam::RedExam(int sizeX, int sizeY,int x, int y) {
	this->x = x;
	this->y = y;

	rect = new Rect(sizeX, sizeY, &this->x, &this->y);
	//画像とあたり判定の調整
	GetGraphSize(FallWall::RedExamPicHandle, &rect->x, &rect->y);
	rect->x /= 2;
	rect->y /= 2;
	rect->x -= rect->sizeX / 2;
	rect->y -= rect->sizeY / 2;
}

RedExam::~RedExam() {
	delete rect;
}

FallWall::FallWall(int x,int y)
{
	this->x = x;
	this->y = y;
	index =motionanima = birdanima = 0;

	//初期位置保持
	startY = y;
	//フラグリセット
	fallflag = descendflag = ascendflag = false;

	//インスタンス確保
	bird = new Rect(24,28,&this->x,&this->y);
	redexam = new RedExam(40,40,x,y + 30);	//画像との兼ね合いで変更
	//birdあたり判定と画像調整
	GetGraphSize(BirdPicHandle[0],&bird->x,&bird->y);
	//アニメーション画像(fly2)の大きさを保持
	GetGraphSize(BirdPicHandle[1], &picdsize[0][1],&picdsize[1][1]);
	picdsize[0][1] = -(picdsize[0][1]-  bird->x ) /2;
	picdsize[1][1] = -(picdsize[1][1] - bird->y) ;

	bird->x /= 2;
	bird->y /= 2;
	bird->x -= bird->sizeX / 2;
	bird->y -= bird->sizeY / 2;
	//鳥と解答用紙のずれを修正
	redexam->x -= (redexam->rect->sizeX - bird->sizeX) / 2 -1;
	redexam->startY = redexam->y;//初期位置修正

	//重力を切る
	ay = redexam->ay = 0;
}


FallWall::~FallWall()
{
	delete bird;
	delete redexam;
}

void FallWall::Motion(double ftime) {
	if (CheckInCam()) {
		//ハイジャンプ用フラグ
		if (waittime < KILLHIGHJUMPTIME) {
			waittime += ftime * 1000;
			//ハイジャンプ可能にする
			if (InKeyTrigger(usingP->now_key, PAD_INPUT_10)) {
				usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
				PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
				waittime = KILLHIGHJUMPTIME;
			}
		}
		//アニメーション用
		birdanima += (int)(ftime * 1000);
		//飛行モーション切り替えるタイミングがやってきたら
		if (birdanima > FALLWALL_ANIMATIONTURNTIME) {
			birdanima -= FALLWALL_ANIMATIONTURNTIME;
			//アニメーション切り替え
			index = (index + 1) % 2;
		}
		//落としている最中か
		if (descendflag || ascendflag || fallflag) {
			//計測用
			motionanima += (int)(ftime * 1000);
			if (fallflag) {
				//答案落下
				//マップのブロックについたら止まる
				if (redexam->stepRect_y(*redexam->rect, ftime)) {
					fallflag = false;
					descendflag = true;
					vy = FALLWALL_BIRDSPEED;
					motionanima = 0;
				}
			}
			//鳥が降りる処理
			if (descendflag && motionanima > FALLWALL_WAITFORDOWN) {
				//鳥の時間を進める
				stepPosY(ftime);
				//答案を拾えるところまできたら
				if (y - startY > redexam->y - redexam->startY) {
					descendflag = false;
					ascendflag = true;
					motionanima = 0;
					//上に
					vy = -vy;
					redexam->vy = vy;
				}
			}
			//鳥が上に上がる処理
			if (ascendflag && motionanima > FALLWALL_WAITFORUP) {
				//鳥と答案の時間を進める
				stepPosY(ftime);
				redexam->stepPosY(ftime);
				//元に戻ったら
				if (y - startY <0) {
					y = startY;
					redexam->y = redexam->startY;
					ascendflag = false;
					motionanima = 0;
				}
			}
				
		}
	}
	//落下したときに死ぬようにする
	if (y > HEIGHT)
		deathflag = true;
}

void FallWall::Draw() {
	if (CheckInCam()) {

		//赤点・鳥画像表示
		DrawGraph(redexam->RelativePosX(), redexam->RelativePosY(),RedExamPicHandle,TRUE);
		DrawGraph(RelativePosX()+ picdsize[0][index], RelativePosY() + picdsize[1][index],BirdPicHandle[index],TRUE);
#ifdef DEBUG
		//あたり判定描画
		bird->Draw(*Camera);
		redexam->rect->Draw(*Camera);
#endif
	}
}

bool FallWall::HitCheck(Rect rect) {
	//あたり判定用
	bool flag = false;

	//鳥あたり判定
	if (CheckRectRect(*this->bird, rect))
	{
		//鳥を踏んだら消す
		if (HitFaceRectRect(rect, *this->bird) & TOP && usingP->vy > 0 && usingP->Ymovingflag && !(HitFaceRectRect(rect, *this->bird) & BOTTOM)) {
			killedenemy++;
			PlaySoundMem(Sound::sounds[SOUND_ENEMYTREAD], DX_PLAYTYPE_BACK);
			deathflag = true;
			usingP->Animation(JUMP);
			waittime = 0;
			//ハイジャンプ可能にする
			if (usingP->now_key& PAD_INPUT_10) {
				usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
				PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
				waittime = KILLHIGHJUMPTIME;
			}
			usingP->vy = -KILLJUMP;
		}
		else {
			//上以外からぶつかったのでダメージ
			usingP->Damage(FALLWALL_BIRDDAMAGE,ENEMYMATCHLESSTIME);
		}
		flag = true;	//当たったので
	}

	//落下物あたり判定
	if (CheckRectRect(*this->redexam->rect, rect)) {
		//ぶつかったのでダメージ (はじきはしない)
		usingP->Damage(FALLWALL_REDEXAMDAMAGE, ENEMYMATCHLESSTIME);
	}

	//プレイヤーが落下地点に入っているか(左、右、下)
	if (rect.x + rect.sizeX + *rect.gx > redexam->x + redexam->rect->x &&  *rect.gx + rect.x < redexam->x + redexam->rect->x + redexam->rect->sizeX && *rect.gy  + rect.y >redexam->y + redexam->rect->y + redexam->rect->sizeY) {
		//落ち始める
		if (!(fallflag||ascendflag ||descendflag)) {
			fallflag = true;
			redexam->vy = FALLWALL_FALLSPEED;	//落下速度指定
		}
	}
	return flag;
}
