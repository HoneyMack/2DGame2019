#include "Rope.h"

int Rope::rope_PicHandle = 0;
int Rope::fixture_PicHandle = 0;
int Rope::FsizeX = 0;
int Rope::FsizeY = 0;

Rope::Rope(int x, int y,int ropenum)
{
	this->x = x;
	this->y = y;
	this->ropenum = ropenum;
	//画像合わせ
	GetGraphSize(rope_PicHandle, &rope.x, &ropelen);
	rope.x /= 2;
	rope.x -= rope.sizeX / 2;

	ropelen--;	//微調整
	rope.sizeY = ropenum *ropelen - 15;

	GetGraphSize(fixture_PicHandle, &FsizeX, &FsizeY);

	
	//サイズ合わせ
	fixture.sizeX = 20;
	fixture.sizeY = 18;
	//位置合わせ
	fixture.x = (rope.sizeX/2 + rope.x ) - fixture.sizeX/2;
	fixture.y -= fixture.sizeY + 4;

	catchflag = false;
}

Rope::~Rope()
{
}

void Rope::Motion(double frametime)
{
	//プレイヤーがロープ上にいるか
	if (usingP->HitCheck(rope)) {
		////つかんで初めての処理か
		//if (!catchflag) {
		//	usingP->vy = 0;
		//	usingP->ay = 0;
		//	catchflag = true;
		//}
		//ロープにつかんでいてジャンプ中どうか
		if (vy < 0  && catchflag) {
			usingP->y += vy* frametime;
			vy += GRAVITY * frametime;
			//もし固定部分にあたってしまっていたら
			if (usingP->HitCheck(fixture)){	
				usingP->y -= vy* frametime;
				vy = 0;
			}
		}	
		//ロープ上下移動
		if (usingP->now_key & PAD_INPUT_UP)
			usingP->y -= ROPE_UPDOWN * frametime;
		if (usingP->now_key & PAD_INPUT_DOWN)
			usingP->y += ROPE_UPDOWN * frametime;
		
	}
	else {
		//初めてロープから離れたか
		if (catchflag == true) {
			//ロープから初めて離れたときのジャンプ量で分岐
			if (vy < 0) {
				if (vy < -2*ROPE_JUMPSPEED / 3)	usingP->vy -= ROPE_HIGHJUMP - ROPE_JUMPSPEED * (vy / ROPE_JUMPSPEED);		//半分より上
				else 					usingP->vy -= ROPE_LOWJUMP - ROPE_JUMPSPEED * (vy / ROPE_JUMPSPEED);	//半分より下
			}
			usingP->ay = GRAVITY;
		}
		catchflag = false;
	}
}

bool Rope::HitCheck(Rect rope)
{
	//当たっているか
	if (CheckRectRect(rope, this->rope)|| CheckRectRect(rope, this->fixture)) {
		//ロープをつかんでいるか
		if (CheckRectRect(rope, this->rope)) {
			//つかんで初めての処理か
       			if (!catchflag) {
				usingP->vy = 0;
				usingP->ay = 0;
				catchflag = true;
			}
			//ロープをつかんでいるときの左右移動制限
			if (usingP->keypressed) {
				usingP->vx *= 0.75;
			}
			else {
				usingP->vx *= 0.60;
			}
			//ロープをつかんでいてかつキーが押されていたらジャンプ可能
			if (InKeyTrigger(usingP->now_key, PAD_INPUT_10)) {
				PlaySoundMem(Sound::sounds[SOUND_ROPEJUMP], DX_PLAYTYPE_BACK);
				vy = -ROPE_JUMPSPEED;
			}
			//アニメーションを行う
			usingP->Animation(ROPE);
			//ロープにつかんだので登り続けないようにする
			usingP->highjumpcounter = CANHIGHJUMPTIME;
		}
		//固定具にぶつかっているか
		if (CheckRectRect(rope, this->fixture)) {
			//ロープをつかんでいないか
			if (!CheckRectRect(rope, this->rope)) {
				//左右移動をしていたか
				if (usingP->Xmovingflag == true) {
					//usingP->KnuckledX(rect);
					if (usingP->vx > 0) {
						usingP->Knuckled(fixture, RIGHT);
					}
					else
						usingP->Knuckled(fixture, LEFT);

					usingP->vx = 0;		//横にあたっているのでx速さ０に
				}
			}
			//上下移動をしていたか
			if (usingP->Ymovingflag == true) {

				if (usingP->vy > 0) {
					usingP->Knuckled(fixture, BOTTOM);
					usingP->vy = 0;		//上下で当たっているのでy速さ0に
					usingP->Animation(STAND);		//アニメーション

					usingP->Jump();
					if (usingP->keypressed)
						usingP->vx *= 0.9;			//キーが押されているときの横速度減衰率
					else
						usingP->vx *= 0.6;			//キーが押されていないときの横速度減衰率
				}
				else {
					usingP->Knuckled(fixture, TOP);
					usingP->vy = 0;		//上下で当たっているのでy速さ0に
				}
			}
		}
		return true;
	}
	else
		return false;
}

void Rope::Draw(){
	if (CheckInCam()) {
		for(int i = 0; i < ropenum;i++)
			DrawGraph(RelativePosX() , RelativePosY() + i *ropelen, rope_PicHandle, TRUE);				//ロープ
		
		DrawGraph(RelativePosX() +(rope.sizeX / 2 + rope.x) - FsizeX /2, RelativePosY() - FsizeY +6, fixture_PicHandle, TRUE);		//固定具
#ifdef DEBUG
		fixture.Draw(*Camera);
		rope.Draw(*Camera);
#endif
	}
}
