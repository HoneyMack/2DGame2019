//マップは配列として持つ
#pragma once
#include "DxLib.h"
//#define DEBUG			//あたり判定を描画させたくないときはコメントアウト



//stage関係
#define	TIME_STAGE1_1 500000 //残り時間(ms)
#define	TIME_STAGE2_1 500000 //残り時間(ms)
#define	TIME_STAGE1_1R 500000 //残り時間(ms)
#define	TIME_STAGE2_1R 500000 //残り時間(ms)
#define TIME_STAGE1_3R 500000

#define TIME_STAGE_SNOW 500000


//背景画像
#define MAPPARTS_X 1000	//背景画像のながさ　
#define ACCOUNTFORMAPPARTS 3//背景画像パーツの総数

//score関係
#define SCORE_HP 4
#define SCORE_LIMIT 5
#define SCORE_ENEMY 10
#define SCORE_COIN 30
#define RECODE_NUM_MAX 18			//最大保有レコード数

//dot size
#define DOT 32
//window size　（ドットで割り切れるようにする）
#define WIDTH 640
#define HEIGHT 480

//物理演算のためのうかし
#define FLOW 0.1
#define ZEROEXCEPTION 0.0001	//割る数がこれ以上小さくならないようにする

//重力(dot/sec)
#define GRAVITY 1500
#define MAX_VELOCITY 3000	//終端速度
#define PI 3.141592653589793

//強制スクロールの速度(dot/s)
#define SCROLLSPEED 100


//敵のダメージ量関係
#define WALKENEMY_HITDAMAGE 5		//ぶつかったときのダメージ量
#define SHOOTLASER_HITDAMAGE 5			//レーザーにぶつかったときのダメージ量
#define SHOOTENEMY_HITDAMAGE 5
#define BULLETTOWARDPLAYER_HITDAMAGE 7
#define FIREBALL_DAMAGE 10		//ファイヤーボールにあたったときのダメージ
#define FALLWALL_BIRDDAMAGE 6			//鳥にあたったときのダメージ
#define FALLWALL_REDEXAMDAMAGE 10		//赤点にあたったときのダメージ
#define TURTLE_HITDAMAGE 5
#define GHOST_HITDAMAGE 8					//ダメージ
#define THORNBLOCK_HITDAMAGE 12
#define HANMER_HITDAMAGE 8
#define HANMERTHROW_DAMAGE 4
#define GARDENEEL_DAMAGE  4//チンアナゴに衝突したときのダメージ
#define SNOWBALL_DAMAGE 5 //ボールに衝突したときのダメージ
#define SNOWMAN_DAMAGE 5 //ゆきだるまに衝突したときのダメージ


//player move speed
#define HITPOINT 50		//プレイヤーのHP
#define ENEMYMATCHLESSTIME 1000	//ダメージを受けたときの無敵時間(ms)
#define GROUNDBOOSTSPEED 26		//押しっぱなしによる移動量の増加度
#define AIRBOOSTSPEED 12			//空中での横スピード加速度
#define MAXBOOST 280		//押しっぱなしによる増加度の上限
#define JUMPSPEED 200		//ジャンプスピード
#define HIGHJUMPSPEED 550	//追加できるハイジャンプスピード量
#define CANHIGHJUMPTIME 205	//ハイジャンプで調節できる時間(ms)


#define KILLHIGHJUMPTIME 100 //敵を踏んだ時からハイジャンプができる時間を規定(ms)
#define KILLHIGHJUMPLIMIT 125 //敵を踏んだことによるハイジャンプで調節できる時間(ms)を制限		もしかしたら、CANHIGHJUMPTIMEより小さくないといけない
#define KILLJUMP 380		//敵をたおしたときの上へのジャンプ量
#define ANIMETIONINTERVAL 400 //画像切り替え速度（ms）

#define ONICEFRICTION 0.985 //アイスの上の摩擦
#define ONICEBOOSTSPEED 6 //アイスの上にいるときの移動速度増加度


//walkenemy
#define WALKENEMY_MOVEWIDTH 160		//移動幅(dot)
#define WALKENEMY_SIZEX 24			//あたり判定の大きさ(dot)
#define WALKENEMY_SIZEY 28			//あたり判定の大きさ(dot)
#define WALKENEMY_SPEED 100			//walkスピード(dot/s)
#define WALKENEMY_KILLCOLLIDERY  5	//上にあたっているか

//ShootLaserに関する定義
#define SHOOTLASER_POSX 595				//レーザー発射装置の画面上のX座標
#define SHOOTLASER_SHOTTIMES 22			//何回レーザーを打つか
#define SHOOTLASER_LASERINTERVAL 1400	//レーザーを発射する間隔(ms)
#define SHOOTLASER_MOVEINTERVAL 20		//一回レーザーを打った後にディスペンサーを下にどれだけ移動するか(dot)
#define SHOOTLASER_SHOOTWAITTIME 700			//打ったのち、どれぐらい待つか(ms)
#define SHOOTLASER_WAITTIME 300			//ディスペンサーを移動させたのち、どれぐらい待つか(ms)
#define SHOOTLASER_LASERSPEED 1000		//レーザーの飛ぶ速さ(dot/s)

//FlashBlock
#define FLASHBLOCK_SIZEX 32				//あたり判定の大きさ
#define FLASHBLOCK_SIZEY 32
#define FLASHBLOCK_FLASHTIME 1000		//見えなくなる時間(ms)

//UpDownObject
#define UPDOWN_OB_MOVEWIDTH 80
#define UPDOWN_OB_SIZEX 60
#define UPDOWN_OB_SIZEY 10
#define UPDOWN_OB_ANGVEL 90.0*(PI/180.0)

//ShootEnemy
#define SHOOTENEMY_SIZEX 10
#define SHOOTENEMY_SIZEY 22
#define SHOOTENEMY_MOVEWIDTH 500
#define SHOOTENEMY_MOVESPEED 140
#define SHOOTENEMY_FIRINGSPEED 100
#define SHOOTENEMY_TIMEBFOREFIRING 1000 //画面に入ってから球を発射し始めるまでの時間

#define SHOOTENEMY_INTERVAL 5000
#define SHOOTENEMY_BULLETS 3



//BulletTowardPlayer
#define BULLETTOWARDPLAYER_RADIUS 10
#define BULLETTOWARDPLAYER_SPEED 300

//Lift
#define LIFT_SIZEX 60
#define LIFT_SIZEY 20
#define LIFT_MOVESPEED 100

//FireBar
#define FIREBAR_BALL_RADIUS 6  //firebarのfireballの半径
#define FIREBAR_NUMBER 4  //firebarのbarの本数
#define FIREBAR_LENGTH 5  //firebarのfireballの個数

//FireBall
#define FIREBALL_ANGVEL 90.0*(PI/180.0)  //firebarの角速度

//Rope
#define ROPE_SIZEX 5
#define ROPE_SIZEY 100
#define ROPE_FIXTURE_SIZEX 32
#define ROPE_FIXTURE_SIZEY 32
#define ROPE_JUMPSPEED 400
#define ROPE_LOWJUMP 200
#define ROPE_HIGHJUMP 400
#define ROPE_UPDOWN 150	//(ms)

//Jump
#define JUMP_TIME	1000
#define JUMP_LOWJUMP 350				//ばねによるジャンプ量
#define JUMP_HIGHJUMP  470				//スペースを押していた時のジャンプ量
#define JUMP_HIGHJUMPLIMIT 170			//最高ハイジャンプの調整	もしかしたら、CANHIGHJUMPTIMEより小さくないといけない
#define JUMP_CANHIGHJUMP 100			//HIGHJUMP可能な範囲
#define JUMP_ANGULARVELOCITY 2*PI *1.8	//(rad/s)
#define JUMP_DECREMENT 1.00 //ばねの振幅の増加率
#define JUMP_EXTENSION 14 //(dot)
//#define JUMP_LOW_EXTENSION 20 //(dot)
//#define JUMP_HIGH_EXTENSION 50 //(dot)


//fallwall
#define FALLWALL_WAITFORDOWN 1000		//赤点が落ちてから下降待ち(ms)
#define FALLWALL_WAITFORUP	1000		//上昇まち（ｍｓ）
//#define FALLWALL_BIRDFALLINGTIME 3000	//鳥が赤点をとるのに要する時間（落下）(MS)
//#define FALLWALL_BIRDRISINGTIME 3000	//鳥が赤点をとったのちの、登るのに要する時間(MS)
#define FALLWALL_BIRDSPEED 200			//鳥の移動スピード
#define FALLWALL_FALLSPEED 300//答案落下速度(dot/s)

#define FALLWALL_ANIMATIONTURNTIME 200	//パタパタの間隔(MS)

//Coin
#define COIN_MATCHLESSTIME 1000		//(ms)
#define COIN_REVERSETIME 1000		//反転させる間隔(ms)

//Turtle
#define TURTLE_MOVESPEED 30
#define TURTLE_RADIUS 12
//#define TURTLE_SIZEX 30
//#define TURTLE_SIZEY 30
#define TURTLE_MOVEWIDTH 160
#define TURTLE_SHELLSPEED 300
#define SHELL_RADIUS 12
//#define SHELL_SIZEX 30
//#define SHELL_SIZEY 30
#define TURTLE_TURNTIME 60 //回転の画像一コマを表示する時間（ms）

//TurtleWithWing
#define TURTLEWITHWING_PERIODICTIME 5000 //一周するのに要する時間(ms)
#define TURTLEWITHWING_MOVEMENT 35 //振幅(dot)


//HanmerThrow
#define HANMERTHROW_SIZEX 26
#define HANMERTHROW_SIZEY 50
#define HANMERTHROW_MOVESPEED 50
#define HANMERTHROW_MOVEWIDTH 160

#define THROW_HANMERS 3
#define THROWINTERVAL 3000
#define THROWINGSPEED 800
#define HANMERTHROW_GRAVITY 300
//#define THROWING_WIDTH 300
//#define THROWING_ANGLE PI/3
#define THROWING_ANGLE_MAX PI/180 * 85		//最大角
#define THROWING_ANGLE_MIN PI/180 * 10		//最小角

#define HANMERTHROW_TURNTIME 200 //アニメーションが切り替わる時間

//Hanmer
//#define HANMER_SIZEX 10
//#define HANMER_SIZEY 10
#define HANMER_RADIUS 5
#define HANMER_ANGVEL PI/180 * 360 //20°/s

//ghost
#define GHOST_DISPLAYSIZEX 56
#define GHOST_DISPLAYSIZEY 36
#define GHOST_CHARASIZEX 28
#define GHOST_CHARASIZEY 30					
#define GHOST_MOVESPEED 20					//プレイヤーに進む速さ
#define GHOST_ANGVEL 90.0*(PI/180.0)		//角振動数
#define GHOST_MOVEWIDTH 60		//振動の揺れ幅
#define GHOST_TRANSPARENCY 50  //どのくらい透明にするか0:透明　250:不透明
#define GHOST_TURNTIME 300	//フラッシュがたかれて引っ込むまで

//Polarbear
#define PBSIZEX 32
#define PBSIZEY 32
#define PB_SPEED 100
#define PB_MOVEWIDTH 160
#define PB_HITDAMAGE 5

//Penguin
#define PENGUIN_MOVEWIDTH 160
#define PENGUIN_HITDAMAGE 4
#define PENGUIN_SLIDINGSPEED 300	//滑ってる時の速度
#define PENGUIN_WALKINGSPEED 100	//歩いてる時の速度
#define PENGUIN_SEARCHINGAREA 200
#define PENGUIN_CHANGEDISTANCE_WIDTH 80	//この距離以上離れたらプレイヤー側に向きを変える

//thornblock
#define THORNBLOCK_SIZEX 28
#define THORNBLOCK_SIZEY 28
#define THORNBLOCK_TRANSPARENCY 10

//fence
#define FENCE_SIZE 32  //正方形で定義
#define FENCE_PLAYERMOVESPEED 100 //プレイヤーの移動速度指定
#define FENCE_LOWJUMPSPEED 200		//LOWジャンプの高さ指定

//Ship
#define SHIP_SIZEX 96
#define SHIP_SIZEY 20
#define SHIP_MOVESPEED 100


//SeaWeed(海藻)
#define SEAWEED_SIZEX 32 //海藻の画像の大きさ
#define SEAWEED_SIZEY 32 //海藻の画像の大きさ
#define SEAWEED_TOTALPICTURES 5 //画像の総数
#define SEAWEED_SWITCHTIME 1000 //1画像あたりの表示時間(ms/画像)

//GardenEel(チンアナゴ)
#define GARDENEEL_SIZEX 10 //チンアナゴの画像サイズ
#define GARDENEEL_SIZEY 32
#define GARDENEEL_HIDINGTIME 1000 //土に隠れている（当たらない）時間(ms)
#define GARDENEEL_RISINGTIME 500 //上に上昇している時間(ms)
#define GARDENEEL_HOLDINGTIME 3000 //上昇しきって伸びている状態の時間(ms)
#define GARDENEEL_FALLINGTIME 1000 //下に下降している時間(ms)

//Sea(?C)
#define SEA_SIZEX 32
#define SEA_SIZEY 32
#define SEA_TRANSPARENCY 150	//透明度
#define SEA_FIRSTDIVE_SPEED_DECAY 0.5	//最初に海に入った時の速度減衰
#define SEA_GRAVITY 1200	//海の中の重力
//#define SEA_PLAYERMOVESPEED 70	//????????????x
//#define SEA_BOOSTSPEED 14
#define SEA_MOVESPEED 100	
#define SEA_LOWJUMPSPEED 120
#define SEA_MAXVY 100	//海の中の最高速度
#define SEA_WAVESPEEDX 30 //ｘ方向速度（波）
#define SEA_WAVESPEEDDOWN 30
#define SEA_WAVESPEEDUP 50
#define SEA_SWITCHTIME 500



//SnowMan（雪だるま）
#define SNOWMAN_SIZEX 20
#define SNOWMAN_SIZEY 40
#define SNOWMAN_THROWINTERVAL 3000 //球を転がす間隔(ms)
#define SNOWBALL_RADIUS 15
#define SNOWBALL_VELOCITY 300//玉の速度(dot/s) 


//描画サイズ(配列の個数)
#define VIEW_WIDTH_INDEX	WIDTH/DOT
#define VIEW_HEIGHT_INDEX	HEIGHT/DOT

//あたり判定用のフラグ 下位4ビットで、壁との判定。
#define RIGHTTOP 0b0001
#define LEFTTOP 0b0010
#define RIGHTBOTTOM 0b0100
#define LEFTBOTTOM 0b1000
#define TOP 0b0011
#define BOTTOM 0b1100
#define RIGHT 0b0101
#define LEFT 0b1010

//クラスの前方宣言
class Player;
class WalkEnemy;
class ShootLaser;
class FlashBlock;
class UpDownObject;
class Mob;
class Object;
class Map;
class Rect;
class Circle;

 //プロトタイプ宣言
bool InKeyTrigger(int key, int CheckKey);		//when key pressed, return true once    not while
bool CheckRectRect(Rect rect1, Rect rect2);		//二つの長方形が重なっているか
bool CheckPointRect( double vecX, double vecY ,Rect rect);	//rectに点vectorが含まれているか
bool CheckCircleCircle(Circle cir1,Circle cir2);//二つの円が重なっているか
bool CheckPointCircle(double vecX,double vecY,Circle cir);	//ある点(vecX,vecY)は,円に含まれているか
bool CheckCircleRect(Circle cir, Rect rect);	//円と長方形が重なっているか
int HitFaceRectRect(Rect rect1, Rect rect2);	//二つの長方形で重なっている部分を返す(rect2を基本として上下左右)
int HitFaceCircleRect(Circle cir, Rect rect);	//Circleと長方形で重なっている部分を返す(rectを基本として上下左右)(cirをrectとみて処理)
int HitFaceCircleCircle(Circle cir1,Circle cir2);	//２つの円で重なっている部分を返す(cir2を基本として上下左右)(cirをrectとみて処理)
Rect ChangeCircleToRect(Circle cir);	//Circleをぐるっと囲む長方形を作成




//ウィンドウ切り替え用
enum {
	STARTWINDOW, GAMESELECTWINDOW, GAMEPLAYWINDOW,GAMEPAUSEWINDOW, GAMEOVERWINDOW,GAMECLEARWINDOW,RANKINGWINDOW
};
//マップ画像用
enum {
	GROUND = 1, TOGE, BLOCK_STONE, BLOCK_ICE, BLOCK_WOOD, MAP_MAX
};
//画像管理用
enum {
	PLAYER,WALKENEMY
};
//プレイモード切替
enum {
	CROSSKEYANDJUMP,FORCEHORIZONTALSCROLL
};

//プレイヤー画像切り替え用
enum {
	STAND,RUN,JUMP,ROPE,FENCE,SWIM
};


//サウンド管理用
enum {
	SOUND_FLASHBLOCK, SOUND_PLAYERJUMP,SOUND_PLAYERSKILL,SOUND_PLAYERJUMPMINI,SOUND_LASERSHOT,SOUND_DAMAGE,SOUND_ENEMYSHOOT,SOUND_JUMPSPRING,SOUND_JUMPSPRINGMINI,SOUND_ROPEJUMP,SOUND_ENEMYTREAD,SOUND_COIN,SOUND_STAGESTART, SOUND_STAGE_TUTO, SOUND_STAGE_SNOW, SOUND_STAGE_SEA, SOUND_STAGE_SKY,
	SOUND_STAGE1_1,SOUND_STAGE1_2,SOUND_STAGE1_3,
	SOUND_BOSS,SOUND_BOSS_DEFEAT,SOUND_HEALING,SOUND_UNI,SOUND_MAX
};
