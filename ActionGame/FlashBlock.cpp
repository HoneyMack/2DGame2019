#include "FlashBlock.h"
#include "Ghost.h"
int FlashBlock::PicHandle = 0;
bool FlashBlock::flashingflag = false;

FlashBlock::FlashBlock(int x, int y)
{
	this->x = x;
	this->y = y;
}

FlashBlock::~FlashBlock()
{
}

void FlashBlock::Motion(double frametime) {
	if (CheckInCam()) {
		//時間を累積
		if (hitflag == true) {
			hittime += frametime;
			flashingflag = true;
		}
			
		//判定の消失条件
		if (hittime * 1000 > FLASHBLOCK_FLASHTIME)
			hitflag = false;
	}
}

void FlashBlock::Draw() {
	if (CheckInCam()) {
		if (hitflag == true) {
			//判定が残っているときは画面を真っ白に
			DrawBox(0, 0, Camera->sizeX + Camera->x, Camera->sizeY + Camera->y, 0xFFFFFF, TRUE);		//真っ白
			
		}
	}
	else {
		hitflag = false;
	}
#ifdef DEBUG
		rect.Draw(*Camera);//あたり判定	仮設
#endif
}

void FlashBlock::AddDraw() {
	if (CheckInCam()) {
		//画面内のときは画像を表示
		DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);	//画像描画
	}
}

bool FlashBlock::HitCheck(Rect rect) {
	if (CheckRectRect(this->rect, rect)) {
		//もし当たっていたらプレイヤーをはじく
		if (usingP->Xmovingflag) {
			//x移動でぶつかった
			usingP->vx = 0;
			usingP->KnuckledX(this->rect);
		}
		else {
			//y移動でぶつかった
			usingP->vy = 0;
			usingP->KnuckledY(this->rect);
			usingP->Animation(STAND);
			usingP->Jump();

			if (usingP->keypressed)
				usingP->vx *= 0.9;			//キーが押されているときの横速度減衰率
			else
				usingP->vx *= 0.6;			//キーが押されていないときの横速度減衰率
		}

		//当たっていたらフラグを立ち上げ＋時間累積を初期化
		if (hitflag == false) {
			hitflag = true;
			hittime = 0.0;
			PlaySoundMem(Sound::sounds[SOUND_FLASHBLOCK], DX_PLAYTYPE_BACK);//音を鳴らす
		}
		return true;
	}

	return false;
}
