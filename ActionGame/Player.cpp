#include "Player.h"
#include "Stage.h"

int Player::PicHandle[] = { 0,0,0 ,0};

static bool befKeys[62];	//一戸前の入力保持用

Player::Player()
{
	rect.sizeX = 20;//あたり判定の大きさ調整
	rect.sizeY = 30;
	rect.x = 6;				//位置調整
	rect.y = 0;

	//hp
	HP = HITPOINT;

	//プレイヤーの座標
	x = WIDTH / 2;
	y = HEIGHT / 2;
	ay = GRAVITY;
	vx = vy = ax = 0;
}

Player::Player(double dx, double dy, double dvx, double dvy, double dax, double day) {
	////プレイヤーあたり判定作成
	//rect = new Rect(50, 50);

	x = dx;
	y = dy;
	vx = dvx;
	vy = dvy;
	ax = dax;
	ay = day;
}
Player::Player(const Player &p) {
	rect = p.rect;
	map = p.map;
	Camera = p.Camera;

	x = p.x;
	y = p.y;
	vx = p.vx;
	vy = p.vy;
	ax = p.ax;
	ay = p.ay;
}
Player& Player::operator=(const Player& p) {
	this->rect = p.rect;
	this->map = p.map;
	this->Camera = p.Camera;

	this->x = p.x;
	this->y = p.y;
	this->vx = p.vx;
	this->vy = p.vy;
	this->ax = p.ax;
	this->ay = p.ay;

	return *this;
}

Player::~Player()
{
	//delete rect;
}

void Player::Motion(double frametime) {
	now_key = GetJoypadInputState(DX_INPUT_KEY_PAD1);		//キー入力処理

	int hitface = Fence::PlayerHitCheck(rect);//プレイヤーのあたり判定を渡す
	if (hitface != 0) {		//当たっているか
		if (fenceflag == false) {			//初めてフェンスに乗ったら
			vx = vy = ax = ay = 0;
			fenceflag = true;
			
		}
		//ロープにつかんでいてジャンプ中どうか
		if (vy < 0) {
			vy += GRAVITY * frametime;
		}
		else {
			vy = 0;
		
		}
		Animation(FENCE);
		//上下左右移動
		if (now_key &(PAD_INPUT_UP | PAD_INPUT_DOWN)) {
			if (now_key & PAD_INPUT_UP) 
					vy = -FENCE_PLAYERMOVESPEED;
			else
				vy = FENCE_PLAYERMOVESPEED;	
		}
			
			
		if (now_key & (PAD_INPUT_LEFT | PAD_INPUT_RIGHT)) {
			if (now_key & PAD_INPUT_LEFT) {
				vx = -FENCE_PLAYERMOVESPEED;
				directionflag = 2;		//左向き
			}
				
			else {
				vx = FENCE_PLAYERMOVESPEED;
				directionflag = 1;		//右向き
			}
		}
		else {
			vx = 0;
			//directionflag = 0;			//どこも向かない
		}
		Jump(FENCE_LOWJUMPSPEED);

		//もし、自分の底しか当たっていなかったら立たせる
		if (hitface == BOTTOM)
			Animation(STAND);
	}
	else if (Sea::PlayerHitCheck(rect)) {
		if (seaflag == false) {
			//初めて海の中に入った
			vx *= SEA_FIRSTDIVE_SPEED_DECAY;
			vy *= SEA_FIRSTDIVE_SPEED_DECAY;
			ay = SEA_GRAVITY;
			seaflag = true;
		}
		Animation(FENCE);		//アニメーションをフェンスで仮置き（泳ぎモーションが完成したら差し替え）
		//左右移動
		if (now_key & (PAD_INPUT_LEFT | PAD_INPUT_RIGHT)) {
			if (now_key & PAD_INPUT_LEFT) {
				vx = -SEA_MOVESPEED;
				directionflag = 2;		//左向き
				/*if (vx < -SEA_MOVESPEED)
					vx = -SEA_MOVESPEED;*/
			}

			else {
				vx = SEA_MOVESPEED;
				//directionflag = 1;		//右向き
				//if (vx > SEA_MOVESPEED)
				//	vx = SEA_MOVESPEED;
			}
		}
		else {
			vx *= 0.5;
			//directionflag = 0;			//どこも向かない
		}
		if (vy > SEA_MAXVY) {
			vy = SEA_MAXVY;	//水中での下方への速度制限
		}

		hitface = Sea::PlayerHitCheck(rect);
		if (hitface & 0b0001) vx -= SEA_WAVESPEEDX;
		if (hitface & 0b0010) vx += SEA_WAVESPEEDX;
		if (hitface & 0b0100) vy += SEA_WAVESPEEDY;
		if (hitface & 0b1000) vy -= SEA_WAVESPEEDY;
		//ax = 750;
		
		Jump(SEA_LOWJUMPSPEED);
	}
	else {
		if (fenceflag == true || seaflag == true) {
			ay = GRAVITY;
			fenceflag = false;
			seaflag = false;
		}
		keypressed = CrossKeyInput();				//キー入力
		//directionflag = 0;
	}{
		
		motion += frametime * 1000;					//アニメーション用時間累積(ms)
		//ハイジャンプ処理
		if (highjumpcounter * 1000 < CANHIGHJUMPTIME) {

			if (now_key & PAD_INPUT_10) {
				//キーが押されているので速度を追加
				vy -= 1000.0* HIGHJUMPSPEED / CANHIGHJUMPTIME * frametime;
			}
			else {
				//キーが一度でも離されたら受け付けなくする
				highjumpcounter = CANHIGHJUMPTIME;
			}
			highjumpcounter += frametime;	//ハイジャンプ用時間累積
		}


		int hitface = 0x0000;						//ぶつかっている壁の位置を記憶
		hitface = stepRect_x(rect, frametime);		//x方向の時間を進める
		//壁に当たったら速度０
		if (hitface & RIGHT || hitface & LEFT) {
			vx = 0.0;
		}

		hitface = stepRect_y(rect, frametime);		//y方向の時間を進める

		//地面にあたっていたら
		if (hitface &BOTTOM) {
			vy = 0.0;
			Animation(STAND);
			Jump();
			if (keypressed && seaflag == false)	//海中でこの処理が働かないように変更
				vx *= 0.9;			//プレイヤー地面にいてキーが押されているときの横速度減衰率
			else
				vx *= 0.6;			//プレイヤーが地面にいてキーが押されていないときの横速度減衰率
		}
		else if (hitface & TOP) {
			vy = 0.0;

		}
		//右端、左端落ちないように
		if (x < -rect.x)
			x = -rect.x;
		else if (x + rect.sizeY + rect.x > map->getNumX() * DOT)
			x = map->getNumX() * DOT - rect.sizeY - rect.x;

		MatchLessProcess(frametime);
	}
}


void Player::MatchLessProcess(double frametime) {
	//無敵処理
	if (matchlessflag) {
		//無敵時間中はダメージ無効
		if (matchlesstime >= 0)
			matchlesstime -= frametime * 1000;
		else {
			matchlessflag = false;
		}
	}
}

void Player::Animation(int action) {
	//条件によるアニメーションの変化の分岐処理	
	switch (action) {
	case STAND:
		//ジャンプしていたまたは横移動していなかったら元に戻す
		if (index == 2 || !keypressed)
			index = 0;
		break;
	case RUN:
		//アニメーションを切り替えるrun <->stand （ジャンプ中でない）
		if (motion > ANIMETIONINTERVAL && index != 2) {
			index = (index + 1) % 2;
			motion = 0;
		}
		break;
	case JUMP:
		index = 2;
		break;
	case ROPE:
		//ジャンプしていたら
		if (vy < 0)
			index = 2;	//jumpとする
		else
			index = 1;	//runとする
		break;
	case FENCE:
		//移動しているときこれ
		index = 3;
		break;
	}
}
bool Player::CrossKeyInput() {
	bool keypressed = false;	//キー入力があったらtrueを返す

	//右に速度追加
	if (now_key &PAD_INPUT_RIGHT) {
		//プレイヤーのいるところで分岐
		if ((index == 1 || index == 0))
			vx += GROUNDBOOSTSPEED;
		else
			vx += AIRBOOSTSPEED;

		if (vx > MAXBOOST)
			vx = MAXBOOST;
		keypressed = true;
		directionflag = 1;
	}
	//左に速度追加(地面にいるときだけ)
	if (now_key &PAD_INPUT_LEFT) {
		//プレイヤーのいるところで分岐
		if ((index == 1 || index == 0))
			vx -= GROUNDBOOSTSPEED;
		else
			vx -= AIRBOOSTSPEED;

		if (vx < -MAXBOOST)
			vx = -MAXBOOST;
		keypressed = true;

		directionflag = 2;
	}
	if (keypressed)
		Animation(RUN);

	if (!keypressed) {
		vx *= 0.98;
	}
	return keypressed;
}

void Player::Jump() {
	//地面にいるときだけジャンプ可
	if (InKeyTrigger(now_key, PAD_INPUT_10)) {
		PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
		vy = -JUMPSPEED;
		//ハイジャンプができるように
		highjumpcounter = 0;
		Animation(JUMP);
	}
}

void Player::Jump(int jump) {
	//地面にいるときだけジャンプ可
	if (InKeyTrigger(now_key, PAD_INPUT_10)) {
		PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
		vy = -jump;
		//ハイジャンプができるように
		highjumpcounter = 0;
		Animation(JUMP);
	}
}

void Player::Draw() {
	int Px = x - Camera->x, Py = y - Camera->y;		//Screen上の座標
	if (matchlessflag)
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);		//透明度指定

	//右が押されているか
	if (now_key &PAD_INPUT_RIGHT) {
		DrawGraph(Px, Py, PicHandle[index], TRUE);
		
	}
		
	//左が押されているか
	else if (now_key &PAD_INPUT_LEFT)
		DrawTurnGraph(Px, Py, PicHandle[index], TRUE);
	//右に速度を持っているか
	else if (vx > 0.001 || directionflag == 1)
		DrawGraph(Px, Py, PicHandle[index], TRUE);
	//左に速度を持っているか
	else if (vx < -0.001 || directionflag == 2)
		DrawTurnGraph(Px, Py, PicHandle[index], TRUE);
	else//押してもいないし速度も持っていない
		DrawGraph(Px, Py, PicHandle[0], TRUE);


	if (matchlessflag)
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//透明度をオフ

#ifdef DEBUG
	if (matchlessflag == false)
		rect.Draw(*Camera);	//仮設
#endif
}


//プレイヤーの形が変わったら変わる
bool Player::HitCheck(Rect rect) {
	if (CheckRectRect(rect, this->rect)) {
		return true;
	}
	else
		return false;
}

bool Player::HitCheck(Circle cir) {
	if (CheckCircleRect(cir, this->rect)) {
		return true;
	}
	else
		return false;
}
void Player::EnemysHitCheck(Mob *mob) {

	if (mob != nullptr) {		//インスタンスを保持しているか
		while (true) {			//インスタンスをすべてチェックするまでループ
			if (mob->deathflag == false)
				mob->HitCheck(rect);	//プレイヤーのあたり判定を渡して、諸々やってもらう

			if (mob->HasNext())	//次のインスタンスがあったら
				mob = mob->next;
			else
				break;			//無かったらループを抜ける
		}
	}
}

//動くために必要なもの
Player Player::nextPosX(double frametime) {
	Player ob = *this;
	ob.stepPosX(frametime);
	return ob;
}
Player Player::nextPosY(double frametime) {
	Player ob = *this;
	ob.stepPosY(frametime);
	return ob;
}
Player Player::nextPosAll(double frametime) {
	Player ob = *this;
	ob.stepPosAll(frametime);
	return ob;
}
void Player::stepPosX(double frametime) {
	x += vx *frametime + ax * frametime * frametime / 2;
	vx += ax * frametime;
}
void Player::stepPosY(double frametime) {
	y += vy *frametime + ay * frametime*frametime / 2;
	vy += ay *frametime;
}
void Player::stepPosAll(double frametime) {
	x += vx *frametime + ax * frametime * frametime / 2;
	y += vy *frametime + ay * frametime*frametime / 2;
	vx += ax * frametime;
	vy += ay *frametime;
}

int Player::CheckMapNum(Player P, int vecX, int vecY) {
	return map->PosInfo((int)P.x + vecX, (int)P.y + vecY);
}

int Player::stepRect_x(Rect rect, double frametime) {
	//プレイヤーを動かしていることをあらわす。
	Xmovingflag = true;

	int hitface = 0;
	Player ob_next;

	//X方向に移動させた（時間を進めた）ときの位置を知る
	ob_next = nextPosX(frametime);

	ob_next.x += rect.x;	//相対位置を追加して正しいあたり判定の位置を見る
	ob_next.y += rect.y;

	//まず何か所でぶつかってるか知る
	if (CheckMapNum(ob_next, 0, 0) > 0)			hitface = hitface | LEFTTOP;		//左上
	if (CheckMapNum(ob_next, rect.sizeX, 0) > 0)		hitface = hitface | RIGHTTOP;	//右上
	if (CheckMapNum(ob_next, 0, rect.sizeY) > 0)		hitface = hitface | LEFTBOTTOM;	//左下
	if (CheckMapNum(ob_next, rect.sizeX, rect.sizeY) > 0)	hitface = hitface | RIGHTBOTTOM;	//右下

	//物体がDOTよりも大きいときのための処理
	for (int i = 1; i <= (rect.sizeY - 1) / (DOT - 2); i++) {
		if (CheckMapNum(ob_next, 0, (DOT - 2) * i) > 0)			hitface = hitface | LEFT;		//左
		if (CheckMapNum(ob_next, rect.sizeX, (DOT - 2) * i) > 0)			hitface = hitface | RIGHT;		//右
	}

	stepPosX(frametime);			//X方向の時間を進める

									//重なったところだけ戻す
	if (hitface &RIGHTTOP || hitface & RIGHTBOTTOM) {
		x = ReturnMapIndex(x + rect.sizeX + rect.x)* DOT - rect.sizeX - FLOW - rect.x;	//右の壁ぎりぎりまで移動
	}
	else if (hitface & LEFTTOP || hitface & LEFTBOTTOM) {
		x = (ReturnMapIndex(x + rect.x) + 1)* DOT + FLOW * 2 - rect.x;	//左の壁ぎりぎりまで移動
	}


	//あたり判定
	EnemysHitCheck(Mob::first);
	//移動終了
	Xmovingflag = false;

	return hitface;
}
int Player::stepRect_y(Rect rect, double frametime) {

	//移動開始
	Ymovingflag = true;

	int hitface = 0;
	Player ob_next;

	//X方向に移動させた（時間を進めた）ときの位置を知る
	ob_next = nextPosY(frametime);

	ob_next.x += rect.x;	//相対位置を追加して、rectのいちとプレイヤーの位置を合わせる
	ob_next.y += rect.y;

	//まず何か所でぶつかってるか知る
	if (CheckMapNum(ob_next, 0, 0) > 0)			hitface = hitface | LEFTTOP;		//左上
	if (CheckMapNum(ob_next, rect.sizeX, 0) > 0)		hitface = hitface | RIGHTTOP;	//右上
	if (CheckMapNum(ob_next, 0, rect.sizeY) > 0)		hitface = hitface | LEFTBOTTOM;	//左下
	if (CheckMapNum(ob_next, rect.sizeX, rect.sizeY) > 0)	hitface = hitface | RIGHTBOTTOM;	//右下

																					//物体がDOTよりも大きいときのための処理。DOT-2の間隔でマップのブロックと当たっているかを確認する。
	for (int i = 1; i <= (rect.sizeX - 1) / (DOT - 2); i++) {
		if (CheckMapNum(ob_next, (DOT - 2) * i, 0) > 0)			hitface = hitface | TOP;		//上
		if (CheckMapNum(ob_next, (DOT - 2) * i, rect.sizeY) > 0)		hitface = hitface | BOTTOM;		//下
	}

	stepPosY(frametime);		//Y方向の時間を進める
								//重なっていたら戻す
	if (hitface  &LEFTTOP || hitface & RIGHTTOP) {
		y = (ReturnMapIndex(y + rect.y) + 1) * DOT + FLOW - rect.y;	//上の壁ぎりぎりまで移動
	}
	else if (hitface & LEFTBOTTOM || hitface & RIGHTBOTTOM) {
		y = ReturnMapIndex(y + rect.sizeY + rect.y) * DOT - rect.sizeY - FLOW - rect.y;	//下の壁ぎりぎりまで移動
	}

	//あたり判定
	EnemysHitCheck(Mob::first);
	//移動終了
	Ymovingflag = false;

	return hitface;
}

bool Player::Damage(int damage, int matchlesstime) {
	//無敵でなかったら
	if (!matchlessflag) {
		//敵によるダメージなら
		if (matchlesstime == ENEMYMATCHLESSTIME && damage != 0)
			PlaySoundMem(Sound::sounds[SOUND_DAMAGE], DX_PLAYTYPE_BACK);
		HP -= damage;
		this->matchlesstime = matchlesstime;
		matchlessflag = true;
		return true;
	}
	else
		return false;
}

//プレイヤーの形が変われば変わる
void Player::Knuckled(Circle cir) {
	if (CheckCircleRect(cir, this->rect)) {
		int move = 1;		//調整する移動量
		//x方向での移動で
		if (Xmovingflag) {
			if (vx > 0)
				move *= -1;
			while (CheckCircleRect(cir, this->rect)) {
				x += move;
			}
		}
		//y方向の移動で
		else
		{
			if (vy > 0)
				move *= -1;
			while (CheckCircleRect(cir, this->rect)) {
				y += move;
			}
		}
	}
}

void Player::Knuckled(Rect rect, int face) {
	if (face == RIGHT) {
		x = *rect.gx + rect.x - (this->rect.x + this->rect.sizeX) - FLOW;
	}
	else if (face == LEFT) {
		x = *rect.gx + rect.x + rect.sizeX - this->rect.x + FLOW;
	}
	else if (face == TOP) {
		y = *rect.gy + rect.y + rect.sizeY - this->rect.y + FLOW;
	}
	else if (face == BOTTOM) {
		y = *rect.gy + rect.y - (this->rect.y + this->rect.sizeY) - FLOW;
	}
}

//プレイヤーの形が変われば変わる
int Player::KnuckledX(Rect rect) {
	int hitface = HitFaceRectRect(rect, this->rect);	//自分のどこにぶつかっているか
	if (hitface &RIGHT) {
		x = *rect.gx + rect.x - (this->rect.x + this->rect.sizeX) - FLOW;
		return RIGHT;
	}
	else if (hitface & LEFT) {
		x = *rect.gx + rect.x + rect.sizeX - this->rect.x + FLOW;
		return LEFT;
	}
	return 0;
}

//プレイヤーの形が変われば変わる
int Player::KnuckledY(Rect rect) {
	int hitface = HitFaceRectRect(rect, this->rect);
	if (hitface &TOP) {
		y = *rect.gy + rect.y + rect.sizeY - this->rect.y + FLOW;
		return TOP;
	}
	else if (hitface & BOTTOM) {
		y = *rect.gy + rect.y - (this->rect.y + this->rect.sizeY) - FLOW;
		return BOTTOM;
	}
	return 0;
}

void Player::Reset() {
	x = WIDTH / 2;
	y = HEIGHT / 2;
	vx = 0;
	vy = 0;
	//加速度を治す
	ay = GRAVITY;
	ax = 0;

	HP = HITPOINT;

	//無敵を解除する
	matchlessflag = false;
	matchlesstime = 0;
}

//when key pressed, return true once    not while
bool InKeyTrigger(int key, int CheckKey) {
	int count = 0;
	unsigned int i = (unsigned)CheckKey;
	while (i > 1) {
		i = i >> 1;
		count++;
	}
	if (key & CheckKey) {
		if (befKeys[count] == false) {
			befKeys[count] = true;
			return true;
		}
		befKeys[count] = true;
		return false;
	}
	befKeys[count] = false;
	return false;
}