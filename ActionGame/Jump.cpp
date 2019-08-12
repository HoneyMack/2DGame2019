#include "Jump.h"

int Jump::PicHandle = 0;
int Jump::PicHandle_extended = 0;
int Jump::NsizeY = 0;

Jump::Jump(int x, int y)
{
	this->x = x;
	this->y = y;
	//あたり判定調整
	rect.sizeX = 28;
	rect.sizeY = 30;
	//画像の中心にあたり判定を配置
	GetGraphSize(PicHandle, &rect.x, &rect.y);
	//GetGraphSize(PicHandle_extended, &rect.x, &EsizeY);

	//ノーマルサイズを保持
	NsizeY = rect.y;

	rect.x /= 2;
	rect.y /= 2;
	rect.x -= rect.sizeX / 2;
	rect.y -= rect.sizeY / 2;

}

Jump::~Jump()
{
}

void Jump::Draw()
{

#ifdef DEBUG
		//画像描画
		rect.Draw(*Camera);
		
#endif
	
	if (CheckInCam()) {
		//頂点指定描画
		DrawModiGraph(	RelativePosX(), RelativePosY() + amplitude * sin(radian),
						RelativePosX() + rect.sizeX, RelativePosY() + amplitude * sin(radian),
						RelativePosX() + rect.sizeX,RelativePosY() + rect.sizeY, 
						RelativePosX(), RelativePosY() + rect.sizeY,
						PicHandle, TRUE);
	}
}

void Jump::Motion(double frametime)
{
	if (CheckInCam()) {
		//ばねが振動している		
		if (hitflag == true) {
			//ハイジャンプ判定
			if (InKeyTrigger(usingP->now_key, PAD_INPUT_10) && jumponce) {
				usingP->vy = -JUMP_HIGHJUMP;
				PlaySoundMem(Sound::sounds[SOUND_JUMPSPRING], DX_PLAYTYPE_BACK);
				usingP->highjumpcounter = (CANHIGHJUMPTIME - JUMP_HIGHJUMPLIMIT) / 1000.0;//ハイジャンプ可変に
				usingP->Animation(JUMP);
				//フラグを切る
				jumponce = false;
			}
				

			//あたり判定を前フレームで移動した分戻す
			rect.y -=amplitude* sin(radian);
			//角度を追加
			radian += JUMP_ANGULARVELOCITY * frametime;		
			//減衰させる
			amplitude *= JUMP_DECREMENT;

			//あたり判定の位置を更新
			rect.y += amplitude *sin(radian);
		}

		//ばねが戻ってきたらになったら止める
		if (radian > PI && hitflag ) {
			hitflag = false;
			radian = 0;

			//あたり判定がずれてしまうので直す
			rect.y = NsizeY;
			rect.y /= 2;
			rect.y -= rect.sizeY / 2;
		}
	}
}

bool Jump::HitCheck(Rect rect)
{
	if (CheckRectRect(rect, this->rect)) {
		//ばねが正常な位置にあるか
		if(hitflag == false)
			HitPlayer();
		else {
			//接触を保ちながら
			if (usingP->Ymovingflag == true) {
				if (usingP->vy > 0) {
					//プレイヤーをはじく
					usingP->Knuckled(this->rect, BOTTOM);
					usingP->Animation(STAND);

					//プレイヤーが地面から離れるとき
					if (radian > PI - 0.6) {
						usingP->vy = -JUMP_LOWJUMP;
						PlaySoundMem(Sound::sounds[SOUND_JUMPSPRINGMINI], DX_PLAYTYPE_BACK);
						usingP->Animation(JUMP);
					}
					else
						usingP->vy = 0;

					if (usingP->keypressed)
						usingP->vx *= 0.3;			//キーが押されているときの横速度減衰率
					else
						usingP->vx *= 0.2;			//キーが押されていないときの横速度減衰率
				}
			}
		}
			
		return true;
	}
	else 
		return false;
}

	


void Jump::HitPlayer()
{
	//プレイヤーがx方向に移動して当たったのと、y方向に移動して当たったのとで処理を別ける
	if (usingP->Xmovingflag == true ) {

		if (usingP->vx > 0) {
			usingP->Knuckled(this->rect, RIGHT);
		}
		else
			usingP->Knuckled(this->rect, LEFT);

		usingP->vx = 0;		//横にあたっているのでx速さ０に
	}
	if (usingP->Ymovingflag == true) {
		if (usingP->vy > 0) {
			//伸び状態をセット
			hitflag = true;
			//ジャンプ可フラグをセット
			jumponce = true;

			//振幅をセット
			amplitude = JUMP_EXTENSION;
			//プレイヤーをはじく
			usingP->Knuckled(this->rect, BOTTOM);

			usingP->Animation(STAND);
			 usingP->vy = 0;		//上で当たっているのでy速さ0に

			if (usingP->keypressed)
				usingP->vx *= 0.3;			//キーが押されているときの横速度減衰率
			else
				usingP->vx *= 0.2;			//キーが押されていないときの横速度減衰率
		}
		else {
			usingP->Knuckled(rect, TOP);
			usingP->vy = 0;		//下で当たっているのでy速さ0に
		}
	}
}
