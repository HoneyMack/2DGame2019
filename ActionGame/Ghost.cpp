#include"Ghost.h"
#include <math.h>
#include "FlashBlock.h"

int Ghost::PicHandle[] = { 0,0,0 };

Ghost::Ghost(int x, int y){
	this->x = x;
	this->y = y;

	GetGraphSize(PicHandle[0], &display.x, &display.y);

	display.x /= 2;
	//display.y /= 2;
	display.x -= display.sizeX / 2;
	//display.y -= display.sizeY / 2 - 2;
	display.y = 0;

	//体のあたり判定を画像の中心に
	GetGraphSize(PicHandle[0], &chara.x, &chara.y);
	chara.x /= 2;
	chara.y /= 2;
	chara.x -= chara.sizeX / 2;
	chara.y -= chara.sizeY / 2 - 8;

	ay = 0;	
}

Ghost::~Ghost(){

}

void Ghost::Motion(double frametime){
	//カメラ内に入っていてかつプレイヤーがこちらを向いていない,マジックナンバーに注意
	if (CheckInCam() &&(( usingP->x -x> 0 && usingP->directionflag == 1) || (usingP->x - x< 0 && usingP->directionflag == 2))){
		//一度動かした分を戻す
		y += vecY;

		angle += angvel*frametime;
		if (angle >= 2 * PI){
			angle = 0;
		}
		//往復分
		vecY = (movewidth / 2)*(sin(angle));

		dx = usingP->x - x;
		dy = y - usingP->y;
		length = sqrt((double)(dx*dx + dy*dy));
		//ゼロ除算例外
		if (length< ZEROEXCEPTION)
			length = ZEROEXCEPTION;

		vx = dx / length*GHOST_MOVESPEED;
		vy = -dy / length*GHOST_MOVESPEED;

		stepPosAll(frametime);
		/*stepRect_x(display, frametime);
		stepRect_y(display, frametime);*/

		//画面下に落ちないようにする
		if (y - vecY >= HEIGHT)
			vecY = y - HEIGHT;
		//画面上に出ないようにする処理
		if (y - vecY <= 0)
			vecY = y;
			
		y -= vecY;
		//フラッシュ中ではなかったなら
		if (!FlashBlock::flashingflag) {
			if (animation >0) {
				animation -= frametime * 1000;
				index = 1;
			}
			else {
				animation = 0;
				index = 0;
			}
		}
		else {//フラッシュ中
			animation += frametime * 1000;	//アニメーション
			if (animation < GHOST_TURNTIME)
				index = 1;
			else {
				index = 2;
				animation = GHOST_TURNTIME;
			}
				
		}
	}

}

void Ghost::Draw(){
	if (CheckInCam()){
#ifdef DEBUG
		display.Draw(*Camera);
		chara.Draw(*Camera);
#endif
		if (!FlashBlock::flashingflag)
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, GHOST_TRANSPARENCY);
		DrawGraph(RelativePosX(), RelativePosY(), PicHandle[index], TRUE);

		if (!FlashBlock::flashingflag)
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

	}
}

bool Ghost::HitCheck(Rect rect){
	bool flag = false;
	if (!FlashBlock::flashingflag) {	//もし薄くなっていたら体のあたり判定をする
		if(CheckRectRect(rect, this->display)){
			HitPlayer();
			flag = true;
		}
	}
	if (CheckRectRect(rect, this->display) ){
		HitPlayer();
		flag = true;
	}

	return flag;
}

void Ghost::HitPlayer(){
	usingP->Damage(GHOST_HITDAMAGE, ENEMYMATCHLESSTIME);
}