#pragma once
#include "define.h"
#include "Sound.h"
#include "Map.h"
#include "Rect.h"
#include "Circle.h"

class Mob;	//前方宣言

class Player
{
private:
	int index = 0;			//アニメーション用
	int motion = 0;			//キャラクターを動かすために用いる
public:
	static int PicHandle[];						//画像を持つ stand,run,jump,fance,swim
	Rect rect = Rect(25,25,&this->x,&this->y);	//あたり判定を持つ
	Map *map;			//位置移動のためにその時々のマップ情報をもつ
	Rect *Camera;		//カメラの位置を持つ

	double x, y;			//座標
	double vx, vy;			//速度
	double ax, ay;			//加速度
	int now_key = 0;		//キー入力情報を得る
	int HP = HITPOINT;					//プレイヤーのHP

	double matchlesstime = 0;//プレイヤーの無敵経過時間を保持
	double highjumpcounter = 0;	//ハイジャンプが可能か保持

	int  directionflag = 0;		//指定なし　 = 0右向きー＞1,左向き ->2
	bool matchlessflag = false;		//無敵かどうか
	bool keypressed;		//十字キーが押されているか
	bool Xmovingflag = false;	//いまx座標の移動処理をしているか
	bool Ymovingflag = false;	//いまy座標の移動処理をしているか
	bool fenceflag = false;		//フェンスの上にいたか
	bool seaflag = false;		//海の中にいるか

	Player();
	Player(double dx, double dy, double dvx, double dvy, double dax, double day);
	Player(const Player &p);					//コピーコンストラクタ
	Player& operator=(const Player& p);			//代入演算子のオーバーロード
	~Player();

	Player nextPosX(double frametime);		//次に進んだ時のX方向のみの情報を返す
	Player nextPosY(double frametime);		//次に進んだ時のY方向のみの情報を返す
	Player nextPosAll(double frametime);	//次に進んだ時の情報を返す
	void stepPosX(double frametime);		//X方向のみ進む
	void stepPosY(double frametime);		//Y方向のみ進む
	void stepPosAll(double frametime);		//次の座標に進む

	int CheckMapNum(Player P, int vecX, int vecY);		//プレイヤーがいるマップの変数の中身を返す

	//下位4ビットで、壁との判定
	int stepRect_x(Rect rect, double frametime);//マップ上のブロックとぶつかっていたらぶつからないように戻しながらx方向の時間を進める。　
	int stepRect_y(Rect rect, double frametime);//マップ上のブロックとぶつかっていたらぶつからないように戻しながらy方向の時間を進める。

	//void ForceHorizontalScrollMotion(double frametime);			//強制横スクロールの動き
	//void CrossKeyAndJumpMotion(double frametime);				//十字での動き
	void Motion(double frametime);								//プレイヤーの動き
	void Animation(int action);									//アニメーションの分岐を記述、になうための関数

	void MatchLessProcess(double frametime);					//無敵処理
	bool CrossKeyInput();										//十字キーによるプレイヤーの操作
	void Jump();												//ジャンプする
	void Jump(int jump);												//ジャンプする

	void Draw();												//描画
	void Reset();												//カメラの中央に戻す

	bool HitCheck(Rect rect);									//Enemy->Player長方形rectがぶつかっているか。プレイヤーの形が変われば変わる
	bool HitCheck(Circle cir);									////Enemy->Player 円cirがぶつかっているか。プレイヤーの形が変われば変わる
	void EnemysHitCheck(Mob *mob);								//敵の先頭アドレスのポインタを渡すをあたり判定＋処理をしてくれる

	bool Damage(int damage,int matchlesstime);					//ダメージを受けるためのインターフェース(ダメージ量,無敵時間(ms) 戻り値はダメージが入ったらtrue

	void Knuckled(Circle cir);									//circleをプレイヤーと接するようにする
	void Knuckled(Rect rect, int face);							//rectにプレイヤーのfaceをくっつける
	int KnuckledX(Rect rect);									//rectと重ならないようにプレイヤーがはじかれる 戻り値は当たっていた面 rectが小さいとすり抜ける可能性あり
	int KnuckledY(Rect rect);									//rectと重ならないようにプレイヤーがはじかれる
};

