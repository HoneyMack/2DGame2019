
#include "Stage.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>


#define STAGENUM 7
using namespace std;

//ランキングデータ保持用	テキストの保存形式:名前、残りタイム、敵の撃破数、残りHP、コイン
struct rankdata {
	string name;
	int limit, killedene, hp, coin;
};


//クラスインスタンス作成
Stage stage;

//関数　プロトタイプ宣言
void GameControl();
void StartWindow();
int  GameSelectWindow();		//選択したステージの整理番号を返す
void GamePlayWindow();
void GamePauseWindow();
void GameOverWindow();
void GameClearWindow(int selectedstage);	//選択したステージの整理番号を渡す
void RankingWindow();

void RankingWrite(string txtname, rankdata rankdata);		//txtnameのファイルにrnkdtを書き込む
rankdata* RankingRead(string txtname, int* index);					//txtnameのファイルのデータを読み込んで戻り値として渡す 配列の要素数を引数に渡す

//ステージのオブジェクト生成
void CreateStage1_1();
void CreateStage2_1();
void CreateStage1_1R();
void CreateStage1_2R();
void CreateStage1_3R();
void CreateStage_MiniGame1();			//タイムを競うミニゲーム
void CreateStage_Sea();	
void CreateStage_Snow();
void CreateStage_Sky();
void CreateStage_Tutorial();


//メニュー切り替え用フラグ
int window = STARTWINDOW;

//キー入力関係
int now_key;		//今のフレームの状態を保持
bool befKeys[62];	//一戸前の入力保持用


//マップ名保持
//string stagename[] = { "stage1_1R" ,"stage1_2R","stage1_3R","snow_stage","SeaStage","TEST1","TEST2" };
string stagename[] = { "Tutorial","snow_stage","SeaStage","SkyStage(MiniGame)","stage1_1R","stage1_2R","stage1_3R" };

//背景画像指定
int stage1_1Back[ACCOUNTFORMAPPARTS];
int stage1_2Back[ACCOUNTFORMAPPARTS];
int stage1_3Back[ACCOUNTFORMAPPARTS];
int stage_Snow[1];
int stage_Sea[1];
int stage_Sky[1];
int stage_tutorial[1];

//ゴールバー
int goalPicHandle;


//use to calcurate frametime 
int beftime, curtime;
float frametime;

//スタート画面の文字
int strWidth, strLen;

int HPfont;				//HP表示用フォントハンドル保持
int rankfont_1, rankfont_2, rankfont_3;			//ランク表示用フォント
int Pausefont;							//ポーズフォント


//int picture;

char *str = "";

HWND hWnd;


int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lp, int nC)
{

	ChangeWindowMode(TRUE), SetGraphMode(WIDTH, HEIGHT, 32);

	if (DxLib_Init() == -1) return -1;

	SetDrawScreen(DX_SCREEN_BACK);

	beftime = GetNowCount() & INT_MAX;


	//フォントセット
	HPfont = CreateFontToHandle("メイリオ", 16, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	rankfont_1 = CreateFontToHandle("メイリオ", 16, 9, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	rankfont_2 = CreateFontToHandle("メイリオ", 16, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	rankfont_3 = CreateFontToHandle("メイリオ", 16, 7, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	Pausefont = CreateFontToHandle("Ravie", 32, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//背景画像
	//picture = LoadGraph("pictures/background.png");

	//Mob画像をセット
	Player::PicHandle[0] = LoadGraph("pictures/player.png");
	Player::PicHandle[1] = LoadGraph("pictures/boy_run.png");
	Player::PicHandle[2] = LoadGraph("pictures/boy_jump.png");
	Player::PicHandle[3] = LoadGraph("pictures/fence_motion.png");
	Player::PicHandle[4] = LoadGraph("pictures/player_swim.png");

	WalkEnemy::PicHandle[0] = LoadGraph("pictures/walkenemy_animation/anime1.png");
	WalkEnemy::PicHandle[1] = LoadGraph("pictures/walkenemy_animation/anime2.png");
	WalkEnemy::PicHandle[2] = LoadGraph("pictures/walkenemy_animation/anime3.png");
	WalkEnemy::PicHandle[3] = LoadGraph("pictures/walkenemy_animation/anime4.png");
	WalkEnemy::PicHandle[4] = LoadGraph("pictures/walkenemy_animation/anime5.png");
	WalkEnemy::PicHandle[5] = LoadGraph("pictures/walkenemy_animation/anime6.png");
	WalkEnemy::PicHandle[6] = LoadGraph("pictures/walkenemy_animation/anime7.png");
	WalkEnemy::PicHandle[7] = LoadGraph("pictures/walkenemy_animation/anime8.png");
	FlashBlock::PicHandle = LoadGraph("pictures/block_flash.png");
	ShootLaser::PicHandle_dispenser = LoadGraph("pictures/raser_app.png");
	ShootLaser::PicHandle_laser = LoadGraph("pictures/raser.png");
	ShootEnemy::PicHandle = LoadGraph("pictures/enemy_gun.png");
	BulletTowardPlayer::PicHandle[0] = LoadGraph("pictures/bullet.png");
	BulletTowardPlayer::PicHandle[1] = LoadGraph("pictures/bullet.png");
	FireBall::PicHandle = LoadGraph("pictures/fireball.png");
	FireBar::PicHandle = LoadGraph("pictures/firebar_center.png");
	UpDownObject::PicHandle = LoadGraph("pictures/lift.png");
	Lift::PicDownHandle = LoadGraph("pictures/lift_down.png");
	Lift::PicUpHandle = LoadGraph("pictures/lift_up.png");
	Rope::rope_PicHandle = LoadGraph("pictures/rope.png");
	Rope::fixture_PicHandle = LoadGraph("pictures/rope_fixation.png");
	Coin::PicHandle[0] = LoadGraph("pictures/coin.png");
	Coin::PicHandle[1] = LoadGraph("pictures/coin_reverse.png");
	Jump::PicHandle = LoadGraph("pictures/spring.png");
	Jump::PicHandle_extended = LoadGraph("pictures/spring_ext.png");
	FallWall::BirdPicHandle[0] = LoadGraph("pictures/fallwall_fly1.png");
	FallWall::BirdPicHandle[1] = LoadGraph("pictures/fallwall_fly2.png");
	FallWall::RedExamPicHandle = LoadGraph("pictures/fall_wall_block.png");
	Turtle::PicTurtleHandle = LoadGraph("pictures/octopus.png");
	Turtle::PicShellHandle[0] = LoadGraph("pictures/takoyaki_top.png");
	Turtle::PicShellHandle[1] = LoadGraph("pictures/takoyaki_right.png");
	Turtle::PicShellHandle[2] = LoadGraph("pictures/takoyaki_left.png");
	Turtle::PicShellHandle[3] = LoadGraph("pictures/takoyaki_back.png");
	TurtleWithWing::PicHandleWing = LoadGraph("pictures/takoyaki_wing.png"); //Debug用仮画像
	HanmerThrow::PicHandle[0] = LoadGraph("pictures/HanmerThrow_1.png");
	HanmerThrow::PicHandle[1] = LoadGraph("pictures/HanmerThrow_2.png");
	HanmerThrow::PicHandle[2] = LoadGraph("pictures/HanmerThrow_3.png");
	Hanmer::PicHandle = LoadGraph("pictures/ballonly.png");
	Ghost::PicHandle[0] = LoadGraph("pictures/ghost_3.png");
	Ghost::PicHandle[1] = LoadGraph("pictures/ghost_2.png");
	Ghost::PicHandle[2] = LoadGraph("pictures/ghost_1.png");
	ThornBlock::PicHandle = LoadGraph("pictures/thornblock.png");
	Fence::PicHandle = LoadGraph("pictures/fence.png");

	Fish::PicHandle = LoadGraph("pictures/fish.png");	//魚仮画像セット
	Crab::PicHandle = LoadGraph("pictures/crab.png");	//カニ画像仮セット
	Ship::PicHandle = LoadGraph("pictures/Ship.png");	//デバック用仮画像セット

	Polarbear::PicHandle = LoadGraph("pictures/polarbear.png");

	SeaWeed::PicHandles[0] = LoadGraph("pictures/seaweed_animation/seaweed0.png");//Debug用仮画像		atodehattyuu
	SeaWeed::PicHandles[1] = LoadGraph("pictures/seaweed_animation/seaweed1.png");//Debug用仮画像
	SeaWeed::PicHandles[2] = LoadGraph("pictures/seaweed_animation/seaweed2.png");//Debug用仮画像
	SeaWeed::PicHandles[3] = LoadGraph("pictures/seaweed_animation/seaweed3.png");//Debug用仮画像
	SeaWeed::PicHandles[4] = LoadGraph("pictures/seaweed_animation/seaweed4.png");//Debug用仮画像

	SnowMan::PicHandle = LoadGraph("pictures/SnowMan.png");//Debug?ｿｽp?ｿｽ?ｿｽ?ｿｽ鞫?						atodehattyuu
	SnowBall::PicHandle = LoadGraph("pictures/SnowBall.png");//Debug?ｿｽp?ｿｽ?ｿｽ?ｿｽ鞫?					atodehattyuu


	GardenEel::PicHandle = LoadGraph("pictures/GardenEel.png"); //Debug用仮画像
	Sea::PicHandle = LoadGraph("pictures/Sea.png");

	Penguin::PicHandle[0] = LoadGraph("pictures/penguin_walk.png");
	Penguin::PicHandle[1] = LoadGraph("pictures/penguin_sliding.png");

	Eel::PicHandle = LoadGraph("pictures/eel.png");
	Killer::PicHandle = LoadGraph("pictures/Killer.png");

	MarineBoss::PicHandle[0] = LoadGraph("pictures/marine_boss2_2.png");
	MarineBoss::PicHandle[1] = LoadGraph("pictures/barrier.png");										//atode
	Urchin::PicHandle = LoadGraph("pictures/bullet.png");

	Blockforblock::PicHandle = LoadGraph("pictures/block_wood.png");

	HealingItem::PicHandle[0] = LoadGraph("pictures/HealingItem0.png");
	HealingItem::PicHandle[1] = LoadGraph("pictures/HealingItem1.png");
	HealingItem::PicHandle[2] = LoadGraph("pictures/HealingItem2.png");


	//Fence::PicHandle = LoadGraph("pictures/block_stone.png");

	//マップ画像をセット
	Map::PicHandle[GROUND] = LoadGraph("pictures/ground.png");
	Map::PicHandle[TOGE] = LoadGraph("pictures/toge.png");
	Map::PicHandle[BLOCK_STONE] = LoadGraph("pictures/block_stone.png");
	Map::PicHandle[BLOCK_ICE] = LoadGraph("pictures/block_ice.png");
	Map::PicHandle[BLOCK_WOOD] = LoadGraph("pictures/block_wood.png");

	//背景画像をセット
	stage1_1Back[0] = LoadGraph("pictures/background/stage1_1/background_1.jpg");
	stage1_1Back[1] = LoadGraph("pictures/background/stage1_1/background_2.jpg");
	stage1_1Back[2] = LoadGraph("pictures/background/stage1_1/background_3.jpg");
	stage1_2Back[0] = LoadGraph("pictures/background/stage1_2/background_1.jpg");
	stage1_2Back[1] = LoadGraph("pictures/background/stage1_2/background_2.jpg");
	stage1_2Back[2] = LoadGraph("pictures/background/stage1_2/background_3.jpg");
	stage1_3Back[0] = LoadGraph("pictures/background/stage1_3/background_1.jpg");
	stage1_3Back[1] = LoadGraph("pictures/background/stage1_3/background_2.jpg");
	stage1_3Back[2] = LoadGraph("pictures/background/stage1_3/background_3.jpg");
	stage_Snow[0] = LoadGraph("pictures/background/Snow_background.png");
	stage_Sea[0] = LoadGraph("pictures/background/Sea_background.JPG");
	stage_Sky[0] = LoadGraph("pictures/background/Sky_background.png");
	//浜辺の画像追加


	//ゴール
	goalPicHandle = LoadGraph("pictures/goal_line.png");

	//サウンドをセット
	Sound::sounds[SOUND_FLASHBLOCK] = LoadSoundMem("sounds/flashblock.mp3");
	Sound::sounds[SOUND_PLAYERJUMP] = LoadSoundMem("sounds/jump.mp3");
	Sound::sounds[SOUND_LASERSHOT] = LoadSoundMem("sounds/lasershot.mp3");
	Sound::sounds[SOUND_PLAYERSKILL] = LoadSoundMem("sounds/player_skill.mp3");
	Sound::sounds[SOUND_PLAYERJUMPMINI] = LoadSoundMem("sounds/jump_mini.mp3");
	Sound::sounds[SOUND_DAMAGE] = LoadSoundMem("sounds/damage.mp3");
	Sound::sounds[SOUND_ENEMYSHOOT] = LoadSoundMem("sounds/shoot.mp3");
	Sound::sounds[SOUND_JUMPSPRING] = LoadSoundMem("sounds/jump_spring.mp3");
	Sound::sounds[SOUND_JUMPSPRINGMINI] = LoadSoundMem("sounds/jump_spring_mini.mp3");
	Sound::sounds[SOUND_ENEMYTREAD] = LoadSoundMem("sounds/enemy_tread.mp3");
	Sound::sounds[SOUND_COIN] = LoadSoundMem("sounds/coin.mp3");
	Sound::sounds[SOUND_ROPEJUMP] = LoadSoundMem("sounds/rope.mp3");
	Sound::sounds[SOUND_UNI] = LoadSoundMem("sounds/rakka.mp3");
	Sound::sounds[SOUND_HEALING] = LoadSoundMem("sounds/kaifuku.mp3");
	Sound::sounds[SOUND_BOSS_DEFEAT] = LoadSoundMem("sounds/defeat.mp3");
	Sound::sounds[SOUND_STAGE_SNOW] = LoadSoundMem("sounds/action_snow.mp3");
	Sound::sounds[SOUND_STAGE_TUTO] = LoadSoundMem("sounds/actio_tuto.mp3");
	Sound::sounds[SOUND_STAGE_SEA] = LoadSoundMem("sounds/action_marine.mp3");
	Sound::sounds[SOUND_BOSS] = LoadSoundMem("sounds/action_marine_boss.mp3");
	Sound::sounds[SOUND_STAGE_SKY] = LoadSoundMem("sounds/action_ship.mp3");

	ChangeVolumeSoundMem(255 * 50 / 100, Sound::sounds[SOUND_LASERSHOT]);//音量調整

	while (ProcessMessage() == 0 && ScreenFlip() == 0 && ClearDrawScreen() == 0)
	{
		clsDx();
		GameControl();
		//printfDx("%f::", frametime);
	}
	//メモリをすべて解放
	stage.AllReset();

	DxLib_End();

	return 0;
}

void GameControl() {
	//選択されたステージの番号を保持
	static int selectedstage = 0;
	//calcurate frametime
	curtime = GetNowCount() & INT_MAX;
	frametime = (float)(curtime - beftime) / 1000.0f;
	beftime = curtime;

	now_key = GetJoypadInputState(DX_INPUT_KEY_PAD1);						//キー入力処理

	switch (window) {
	case STARTWINDOW:
		StartWindow();
		break;
	case GAMESELECTWINDOW:
		//音を停止
		StopSoundMem(Sound::sounds[selectedstage + SOUND_STAGESTART + 1]);
		selectedstage = GameSelectWindow();
		break;
	case GAMEPLAYWINDOW:
		GamePlayWindow();
		break;
	case GAMEPAUSEWINDOW:
		GamePauseWindow();
		break;
	case GAMEOVERWINDOW:
		GameOverWindow();

		break;
	case GAMECLEARWINDOW:
		GameClearWindow(selectedstage);
		break;
	case RANKINGWINDOW:
		RankingWindow();
		break;
	}
}

void StartWindow() {

	str = "Press Any Key To Play";
	strLen = strlen(str);
	strWidth = GetDrawStringWidth(str, strLen);

	//ちょうど中央に描画されるようにするための処理
	DrawString((WIDTH - strWidth) / 2, 400, str, 0xFFFFFF);

	if (GetJoypadInputState(DX_INPUT_KEY_PAD1)) {
		window = GAMESELECTWINDOW;
	}
}

int GameSelectWindow() {
	static int selectnum = -1;												//選択したマップを記憶しておく。最初に負の数を入れておいて、連続押されを防ぐ
	const int startx = 100, starty = 100, interval = 30;					//一列目の x 座標,y座標,項目の間隔

	//初回連続で入ってしまうので
	if (selectnum == -1) {
		InKeyTrigger(now_key, PAD_INPUT_1);			//キー入力を流す
		InKeyTrigger(now_key, PAD_INPUT_4);
		selectnum = 0;
	}

	if (InKeyTrigger(now_key, PAD_INPUT_DOWN) && selectnum < STAGENUM - 1)					selectnum++;			//何もないところを選択しないように制限
	if (InKeyTrigger(now_key, PAD_INPUT_UP) && selectnum > 0)	selectnum--;

	//選択を強制する
	if (selectnum >= 0)
		DrawString(startx - 30, starty + selectnum * interval, "■", 0xFFFFFF);	//選択している横に■を描画

	//今あるマップ名を描画
	for (int i = 0; i < STAGENUM; i++)
		DrawString(startx, starty + interval * i, stagename[i].c_str(), 0xFFFFFF);

	DrawString(30, 310, "プレイモード:", 0xFFFFFF);
	DrawString(50, 340, "Aキー:強制スクロール + 左右移動(矢印キー) + ジャンプ(スペースキー)", 0xFFFFFF);							//注意書き
	DrawString(50, 370, "Zキー: 左右移動(矢印キー) + ジャンプ(スペースキー)", 0xFFFFFF);
	DrawString(30, 430, "Rキー:ランキング表示へ", 0xFFFFFF);

	//ステージのBGMはメモリバカ食いするので消しておく
	static bool stagesounddeleteflag = false; //ステージの音楽が消されているか
	if (!stagesounddeleteflag) {
		for (int i = SOUND_STAGESTART; i < SOUND_MAX; i++) {
			DeleteSoundMem(Sound::sounds[i]);
		}
		stagesounddeleteflag = true;

		//画像を消去する
		for(int i = 0;i < 3;i++)
		stage.mapparts[i] = 0;
	}
	//選択されたらその番号を返す +(GameSelectWindowに入った瞬間にゲームに入るのを防ぐ)
	if ((InKeyTrigger(now_key, PAD_INPUT_1) || InKeyTrigger(now_key, PAD_INPUT_4))) {
		switch (selectnum) {
		case 0:
			Sound::sounds[SOUND_STAGE_TUTO] = LoadSoundMem("sounds/actio_tuto.mp3");
			CreateStage_Tutorial();
			break;
		case 1:
			Sound::sounds[SOUND_STAGE_SNOW] = LoadSoundMem("sounds/action_snow.mp3");
			//CreateStage1_1R();
			CreateStage_Snow();
			break;
		case 2:
			//CreateStage1_2R();
			Sound::sounds[SOUND_STAGE_SEA] = LoadSoundMem("sounds/action_marine.mp3");
			CreateStage_Sea();
			break;
		case 3:
			//CreateStage1_3R();
			Sound::sounds[SOUND_STAGE_SKY] = LoadSoundMem("sounds/action_ship.mp3");
			CreateStage_Sky();
			break;
		case 4:
			Sound::sounds[SOUND_STAGE1_1] = LoadSoundMem("sounds/stage1-1.mp3");
			//CreateStage_Snow();
			CreateStage1_1R();
			break;
		case 5:
			//CreateStage2_1();
			//CreateSampleBoss();
			Sound::sounds[SOUND_STAGE1_2] = LoadSoundMem("sounds/stage1-2.mp3");
			CreateStage1_2R();
			break;
		case 6:
			//CreateStage1_1();
			Sound::sounds[SOUND_STAGE1_3] = LoadSoundMem("sounds/stage1-3.mp3");
			CreateStage1_3R();
			break;
		}
		if (now_key&PAD_INPUT_4)
			stage.mode = FORCEHORIZONTALSCROLL;
		else {
			stage.mode = CROSSKEYANDJUMP;
		}
		//処理が重くなってしまうので計測リセット
		//calcurate frametime
		curtime = GetNowCount() & INT_MAX;
		frametime = (float)(curtime - beftime) / 1000.0f;
		beftime = curtime;
		window = GAMEPLAYWINDOW;
		stagesounddeleteflag = false;

		//音を再生
		PlaySoundMem(Sound::sounds[selectnum + SOUND_STAGESTART + 1], DX_PLAYTYPE_LOOP, TRUE);
	}
	//ランキング画面へ移動
	if (CheckHitKey(KEY_INPUT_R) == 1) {
		window = RANKINGWINDOW;
	}




	//選択した番号を返す
	return selectnum;
}

void GamePlayWindow() {
	//一定以上のフレームtimeが出てしまった時の例外処理(200ms)
	if (frametime >= 0.2) {
		window = GAMEPAUSEWINDOW;
	}
	else {
		//背景描画
		//DrawGraph(-stage.Camera->x, -stage.Camera->y, picture, TRUE);


		stage.AllUpdate(frametime);
		stage.AllDraw();

		//表示関係描画
		//残りＨＰによって色を変える
		if (stage.usingP->HP >= 10)
			DrawFormatStringToHandle(10, 10, 0x32CCB6, HPfont, "HP:%3d", stage.usingP->HP);
		else
			DrawFormatStringToHandle(10, 10, 0xFF0037, HPfont, "HP:%3d", stage.usingP->HP);

		DrawFormatStringToHandle(90, 10, 0xFFF10F, HPfont, "COIN:%4d", Coin::hadcoins);		//コイン描画

		//残り時間によって色を変える
		if (stage.limit >= 100000)
			DrawFormatStringToHandle(530, 10, 0xFFFFFF, HPfont, "TIME:%3d", stage.limit / 1000);
		else
			DrawFormatStringToHandle(530, 10, 0xFF0037, HPfont, "TIME:%3d", stage.limit / 1000);

		//printfDx("coins:%d , ", Coin::hadcoins);	//所持コイン表示
		//printfDx("HP:%d , ", stage.usingP->HP);	//HP表示
		//printfDx("vy:%f , ", stage.usingP->vy);	//ｙ速度表示

		if (InKeyTrigger(now_key, PAD_INPUT_9)) //ESCキーが押されたら
			window = GAMEPAUSEWINDOW;

		//ゲームオーバー判定(残り時間０、HP０、プレイヤーが落ちる)
		if (stage.limit < 0 || stage.usingP->HP <= 0 || stage.usingP->y >= HEIGHT + DOT) {
			window = GAMEOVERWINDOW;
		}
		//ゴール判定
		if (stage.usingP->x > stage.usingM->getNumX() * DOT - 50) {
			window = GAMECLEARWINDOW;
		}		
		//ゴールバー描画
		DrawGraph(stage.usingM->getNumX()*DOT -stage.Camera->x -100,350,goalPicHandle,TRUE);
	}
}

void GamePauseWindow() {

	str = "ステージに戻る:ESC , ステージ選択に戻る:Z";
	strLen = strlen(str);
	strWidth = GetDrawStringWidth(str, strLen, Pausefont);				//中央描画用
	DrawString((WIDTH - strWidth) / 2, 400, str, 0x00FFFF);

	str = "Pause";
	strLen = strlen(str);
	strWidth = GetDrawStringWidthToHandle(str, strLen, Pausefont);				//中央描画用
	DrawStringToHandle((WIDTH - strWidth) / 2, 200, str, 0xFFFFFF, Pausefont);

	if (InKeyTrigger(now_key, PAD_INPUT_9)) //ESCキーが押されたら
		window = GAMEPLAYWINDOW;
	if (InKeyTrigger(now_key, PAD_INPUT_1)) {//zキーが押されたら
		stage.AllReset();
		window = GAMESELECTWINDOW;
	}
}

void GameOverWindow() {

	str = "GameOver";
	strLen = strlen(str);
	strWidth = GetDrawStringWidthToHandle(str, strLen, Pausefont);				//中央描画用
	DrawStringToHandle((WIDTH - strWidth) / 2, 200, str, 0xFFFFFF, Pausefont);

	str = "選択メニューに戻る:Zキー";
	strLen = strlen(str);
	strWidth = GetDrawStringWidth(str, strLen);				//中央描画用
	DrawString((WIDTH - strWidth) / 2, 300, str, 0x00FFFF);

	if (InKeyTrigger(now_key, PAD_INPUT_1)) {
		stage.AllReset();
		window = GAMESELECTWINDOW;

	}
}
void GameClearWindow(int selectedstage) {
	str = "GAMECLEAR";
	strLen = strlen(str);
	strWidth = GetDrawStringWidth(str, strLen);				//中央描画用
	DrawString((WIDTH - strWidth) / 2, 200, str, 0xFFFFFF);


	//名前を入力させる
	char addname[20 + 1] = {""};
	str = "名前を入力してスコアをランキングに登録します(20文字以内):Enterで決定";

	strLen = strlen(str);
	strWidth = GetDrawStringWidth(str, strLen);				//中央描画用
	DrawString((WIDTH - strWidth) / 2, 300, str, 0xFFFFFF);

	str = "Escキー:登録せずに戻る";
	strLen = strlen(str);
	strWidth = GetDrawStringWidth(str, strLen);				//中央描画用
	DrawString((WIDTH - strWidth) / 2, 400, str, 0xFFFFFF);
	//if (KeyInputSingleCharString((WIDTH - strWidth) / 2, 320, 20, addname, TRUE) == 1) {
	if (KeyInputString((WIDTH - strWidth) / 2, 320, 20, addname, TRUE) == 1) {
		rankdata addrank;
		//新しく追加するスコアを配列に追加
		addrank.name = addname;
		addrank.limit = stage.limit / 1000;
		addrank.killedene = Mob::killedenemy;
		addrank.hp = stage.usingP->HP;
		addrank.coin = Coin::hadcoins;

		RankingWrite(stagename[selectedstage] + ".txt", addrank);
	}
	//入力後セレクトウィンドウに戻る
	stage.AllReset();
	window = GAMESELECTWINDOW;

}

void RankingWindow() {
	static int selectedstage = 0;	//見たいステージ番号を保持
	{
		//string str;
		//ifstream text("test.txt");		//テキスト入手
		////データを一時的保持
		//string name[RECODE_NUM_MAX];
		//int scores[RECODE_NUM_MAX][5];
		////何人いるかをカウント
		//int count = 0;
		//while (getline(text, str) && count < RECODE_NUM_MAX)
		//{
		//	//テキストの保存形式:名前、残りタイム、敵の撃破数、残りHP、コイン,総合
		//	string tmp;
		//	istringstream stream(str);
		//	//名前を取り出す
		//	getline(stream, tmp, ',');
		//	name[count] = tmp;
		//	//スコアを取り出す(4個の要素)
		//	for (int i = 0; i < 4; i++) {
		//		getline(stream, tmp, ',');
		//		scores[count][i] = stoi(tmp);
		//	}
		//	count++;
		//}


		int count = 0;		//配列の要素数を入手
		int scores[RECODE_NUM_MAX];			//総合得点
		rankdata *score = RankingRead(stagename[selectedstage] + ".txt", &count);	//データ保持用

		//総合計算
		for (int i = 0; i < count; i++) {
			scores[i] = SCORE_LIMIT * score[i].limit + SCORE_ENEMY * score[i].killedene + SCORE_HP * score[i].hp + SCORE_COIN * score[i].coin;
		}

		//最初に表示する位置
		int firstx = 20, firsty = 20, interval = 20;
		int rank;	//順位カウント
		//表示
		for (int i = 0; i < count; i++) {
			//順位付け
			rank = 0;
			for (int j = 0; j < count; j++) {
				if (scores[i] < scores[j])
					rank++;
			}
			//順位によって色を変える
			switch (rank + 1) {
			case 1:
				DrawFormatStringToHandle(firstx, firsty + i * interval, 0xFFF10F, rankfont_1, "rank:%2d", rank + 1);						//順位描画
				DrawFormatStringToHandle(firstx + 130, firsty + i * interval, 0xFFF10F, rankfont_1, "NAME:%-20s", score[i].name.c_str());		//名前描画
				DrawFormatStringToHandle(firstx + 450, firsty + i * interval, 0xFFF10F, rankfont_1, "SCORE:%-10d", scores[i]);		//スコア描画
				break;
			case 2:
				DrawFormatStringToHandle(firstx, firsty + i * interval, 0xafafb0, rankfont_2, "rank:%2d", rank + 1);						//順位描画
				DrawFormatStringToHandle(firstx + 130, firsty + i * interval, 0xafafb0, rankfont_2, "NAME:%-20s", score[i].name.c_str());		//名前描画
				DrawFormatStringToHandle(firstx + 450, firsty + i * interval, 0xafafb0, rankfont_2, "SCORE:%-10d", scores[i]);		//スコア描画
				break;
			case 3:
				DrawFormatStringToHandle(firstx, firsty + i * interval, 0xb36b24, rankfont_3, "rank:%2d", rank + 1);						//順位描画
				DrawFormatStringToHandle(firstx + 130, firsty + i * interval, 0xb36b24, rankfont_3, "NAME:%-20s", score[i].name.c_str());		//名前描画
				DrawFormatStringToHandle(firstx + 450, firsty + i * interval, 0xb36b24, rankfont_3, "SCORE:%-10d", scores[i]);		//スコア描画
				break;
			default:
				DrawFormatStringToHandle(firstx, firsty + i * interval, 0xFFFFFF, HPfont, "rank:%2d", rank + 1);						//順位描画
				DrawFormatStringToHandle(firstx + 130, firsty + i * interval, 0xFFFFFF, HPfont, "NAME:%-20s", score[i].name.c_str());		//名前描画
				DrawFormatStringToHandle(firstx + 450, firsty + i * interval, 0xFFFFFF, HPfont, "SCORE:%-10d", scores[i]);		//スコア描画
				break;
			}
		}
	}

	str = "選択メニューに戻る:Zキー";
	strLen = strlen(str);
	strWidth = GetDrawStringWidth(str, strLen);				//中央描画用
	DrawString((WIDTH - strWidth) / 2, 400, str, 0x00FFFF);

	//右左処理
	if (InKeyTrigger(now_key, PAD_INPUT_RIGHT) && selectedstage < STAGENUM - 1) selectedstage++;
	if (InKeyTrigger(now_key, PAD_INPUT_LEFT) && selectedstage > 0) selectedstage--;

	//before,now,nextランキングに移動の描画
	strWidth = GetDrawFormatStringWidth("now:%s", stagename[selectedstage].c_str());				//中央描画用
	DrawFormatString((WIDTH - strWidth) / 2, 430, 0xFFFFFF, "now:%s", stagename[selectedstage].c_str());

	if (selectedstage > 0)
		DrawFormatString(20, 430, 0xffffff, "←before:%s", stagename[selectedstage - 1].c_str());
	if (selectedstage < STAGENUM - 1)
		DrawFormatString(450, 430, 0xffffff, "→next:%s", stagename[selectedstage + 1].c_str());

	//キー入力
	if (InKeyTrigger(now_key, PAD_INPUT_1)) {
		window = GAMESELECTWINDOW;
	}
}

void RankingWrite(string name, rankdata rank) {
	//入出力
	string str;
	ifstream text(name);		//テキスト入手

	//データを一時的保持
	string names[RECODE_NUM_MAX + 1] = {};
	int scores[RECODE_NUM_MAX + 1][5] = {};//テキストの保存形式:名前、残りタイム、敵の撃破数、残りHP、コイン,総合

	//何人いるかをカウント
	int count = 0;

	//一行分読み取り
	while (getline(text, str) && count < RECODE_NUM_MAX)
	{
		//テキストの保存形式:名前、残りタイム、敵の撃破数、残りHP、コイン,総合
		string tmp;
		istringstream stream(str);
		//名前を取り出す
		getline(stream, tmp, ',');
		names[count] = tmp;
		//スコアを取り出す(4個の要素)
		for (int i = 0; i < 4; i++) {
			getline(stream, tmp, ',');
			scores[count][i] = stoi(tmp);
		}
		count++;
	}

	//新しく追加するスコアを配列に追加
	names[count] = rank.name;
	scores[count][0] = rank.limit;
	scores[count][1] = rank.killedene;
	scores[count][2] = rank.hp;
	scores[count][3] = rank.coin;

	//総合計算
	for (int i = 0; i <= count; i++) {
		scores[i][4] = SCORE_LIMIT * scores[i][0] + SCORE_ENEMY * scores[i][1] + SCORE_HP * scores[i][2] + SCORE_COIN * scores[i][3];
	}
	//ソート iが前jが後ろ
	for (int i = 0; i < count; i++) {
		for (int j = i + 1; j <= count; j++) {
			if (scores[i][4] < scores[j][4]) {
				int d_score[5];
				//配列の中身を丸々コピー
				for (int k = 0; k < 5; k++) {
					d_score[k] = scores[i][k];
				}
				//名前入れ替え
				string d_name = names[i];
				names[i] = names[j];
				names[j] = d_name;
				//配列入れ替え
				for (int k = 0; k < 5; k++) {
					scores[i][k] = scores[j][k];
				}
				for (int k = 0; k < 5; k++) {
					scores[j][k] = d_score[k];
				}
			}
		}
	}
	text.close();
	//テキストに出力(ウイルスセキュリティーによって書き込めなくなるので注意)
	ofstream output(name, ios_base::trunc);

	//書き込み
	for (int i = 0; i <= count; i++)
		output << names[i] << ',' << scores[i][0] << ',' << scores[i][1] << ',' << scores[i][2] << ',' << scores[i][3] << ',' << std::endl;

	output.close();
}

rankdata* RankingRead(string name, int *index) {
	//入出力
	string str;
	ifstream text(name);		//テキスト入手

								//データを一時的保持
	string names[RECODE_NUM_MAX] = {};
	int scores[RECODE_NUM_MAX][5] = {};//テキストの保存形式:名前、残りタイム、敵の撃破数、残りHP、コイン,総合

										   //何人いるかをカウント
	int count = 0;

	//一行分読み取り
	while (getline(text, str) && count < RECODE_NUM_MAX)
	{
		//テキストの保存形式:名前、残りタイム、敵の撃破数、残りHP、コイン,総合
		string tmp;
		istringstream stream(str);
		//名前を取り出す
		getline(stream, tmp, ',');
		names[count] = tmp;
		//スコアを取り出す(4個の要素)
		for (int i = 0; i < 4; i++) {
			getline(stream, tmp, ',');
			scores[count][i] = stoi(tmp);
		}
		count++;
	}

	//総合計算
	for (int i = 0; i < count; i++) {
		scores[i][4] = SCORE_LIMIT * scores[i][0] + SCORE_ENEMY * scores[i][1] + SCORE_HP * scores[i][2] + SCORE_COIN * scores[i][3];
	}
	//ソート iが前jが後ろ
	for (int i = 0; i < count - 1; i++) {
		for (int j = i + 1; j < count; j++) {
			if (scores[i][4] < scores[j][4]) {
				int d_score[5];
				//配列の中身を丸々コピー
				for (int k = 0; k < 5; k++) {
					d_score[k] = scores[i][k];
				}
				//名前入れ替え
				string d_name = names[i];
				names[i] = names[j];
				names[j] = d_name;
				//配列入れ替え
				for (int k = 0; k < 5; k++) {
					scores[i][k] = scores[j][k];
				}
				for (int k = 0; k < 5; k++) {
					scores[j][k] = d_score[k];
				}
			}
		}
	}
	text.close();

	//ランキングデータ配列に入れる
	static rankdata rank[RECODE_NUM_MAX];

	for (int i = 0; i < count; i++) {
		rank[i].name = names[i];
		rank[i].limit = scores[i][0];
		rank[i].killedene = scores[i][1];
		rank[i].hp = scores[i][2];
		rank[i].coin = scores[i][3];
	}

	//要素数を渡してあげる
	*index = count;
	return rank;
}

void CreateStage1_1() {
	//stage.usingP->x = 5;
	//stage.usingP->y = 10;
	stage.limit = TIME_STAGE1_1;

	Map firstMap;

	//マップの情報をセット
	//マップの大きさを変更
	firstMap.setNum(10 * firstMap.getNumX(), firstMap.getNumY());

	//地面生成
	for (int i = 0; i < firstMap.getNumX(); i++)
		firstMap.m_map[i][firstMap.getNumY() - 1] = 1;

	//map作成
	//長方形　1*5
	firstMap.m_map[6][5] = 1;
	firstMap.m_map[6][6] = 1;
	firstMap.m_map[6][7] = 1;
	firstMap.m_map[6][8] = 1;
	firstMap.m_map[6][9] = 1;

	//sの字
	firstMap.m_map[4][10] = 1;
	firstMap.m_map[3][10] = 1;
	firstMap.m_map[3][11] = 1;
	firstMap.m_map[2][11] = 1;
	//2の字
	firstMap.m_map[8][10] = 1;
	firstMap.m_map[9][10] = 1;
	firstMap.m_map[9][11] = 1;
	firstMap.m_map[10][11] = 1;

	//正方形 2*2
	firstMap.m_map[17][11] = BLOCK_WOOD;
	firstMap.m_map[17][10] = BLOCK_ICE;
	firstMap.m_map[16][11] = BLOCK_STONE;
	firstMap.m_map[16][10] = GROUND;

	for (int i = 0; i < 5; i++) {
		firstMap.m_map[19 + i * 5][12] = 1;
		firstMap.m_map[19 + i * 5][13] = 1;
	}

	//ステージにセット
	*stage.usingM = firstMap;

	new WalkEnemy(300, 300);
	new WalkEnemy(100, 100);
	new WalkEnemy(200, 200);
	//new ShootLaser(1000);
	new ShootLaser(500);
	new ShootEnemy(300, 300);
	new ShootEnemy(600, 300);
	new UpDownObject(1000, 300);
	new UpDownObject(500, 200);


	new Coin(100, 300);
	new FallWall(400, 200);
	new FallWall(600, 20);
	//バグ座標（610,10）,サイズ（30,40）<-直した
	new Turtle(610, 10);
	for(int i = 0; i< 1;i++)
		new WalkEnemy(730 + i*2, 10);

	//40000個のファイヤーボールを作ると処理が間に合わない。10000ならいけるはず
	new FireBar(1200, 200, 10, 4);


	new Lift(1500, 300, true);
	new Lift(1800, 300, false);
	new Rope(350, 150, 5);
	new Rope(2500, 350, 2);
	new Jump(3200, 400);
	new Jump(3240, 400);
	new Jump(3280, 400);
	new Jump(3320, 400);
	new FlashBlock(DOT * 15, DOT * 10);

}

void CreateStage2_1() {
	stage.limit = TIME_STAGE2_1;
	Map firstMap;
	stage.usingP->x = 320;
	stage.usingP->y = 20;

	//マップの情報をセット
	//マップの大きさを変更
	firstMap.setNum(firstMap.getNumX(), firstMap.getNumY());

	//地面生成
	for (int i = 0; i < firstMap.getNumX(); i++)
		firstMap.m_map[i][firstMap.getNumY() - 1] = BLOCK_STONE;

	//縦棒1*2
	//firstMap.m_map[6][12] = 1;
	//firstMap.m_map[6][13] = 1;

	firstMap.m_map[13][12] = 1;
	firstMap.m_map[13][13] = 1;

	firstMap.m_map[2][firstMap.getNumY() - 1] = 0;

	//ステージにセット
	*stage.usingM = firstMap;

	new Lift(300, 400, true);

	//new Turtle(300, 10);
	//new Jump(300, 400);
	//new HanmerThrow(300, 10, 300);

	//new FlashBlock(DOT * 15, DOT * 10);
	//new FlashBlock(DOT * 12, DOT * 10);
	//new Ghost(300,10);
	//new ThornBlock(300,400);
	//new Ghost(10,10);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			new Fence(DOT *( 6 + i),DOT * (9 + j));
		}
	}

	//new Fence(DOT * 6, DOT * 10);
	//new Fence(DOT * 5, DOT * 11);
	//new Fence(DOT * 5, DOT * 10);
}

void CreateStage1_1R() {
	//背景をセット
	for (int i = 0; i < ACCOUNTFORMAPPARTS; i++) {
		stage.mapparts[i] = stage1_1Back[i];
	}

	stage.limit = TIME_STAGE1_1R;

	Map firstMap;

	//マップの情報をセット
	//マップの大きさを変更
	firstMap.setNum(10 * firstMap.getNumX(), firstMap.getNumY());

	//地面生成
	for (int i = 0; i < firstMap.getNumX(); i++)
		firstMap.m_map[i][firstMap.getNumY() - 1] = 1;

	//マップ作製
	firstMap.m_map[13][11] = BLOCK_WOOD;
	firstMap.m_map[16][11] = BLOCK_WOOD;
	firstMap.m_map[18][11] = BLOCK_WOOD;
	firstMap.m_map[20][11] = BLOCK_WOOD;

	firstMap.m_map[35][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[36][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[37][firstMap.getNumY() - 1] = 0;

	firstMap.m_map[40][9] = BLOCK_WOOD;
	firstMap.m_map[41][9] = BLOCK_WOOD;
	firstMap.m_map[42][9] = BLOCK_WOOD;
	firstMap.m_map[43][9] = BLOCK_WOOD;

	//firstMap.m_map[48][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[49][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[50][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[51][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[52][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[53][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[54][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[55][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[56][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[57][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[58][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[59][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[60][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[61][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[62][firstMap.getNumY() - 1] = 0;


	firstMap.m_map[50][9] = BLOCK_WOOD;
	firstMap.m_map[51][9] = BLOCK_WOOD;
	firstMap.m_map[52][9] = BLOCK_WOOD;
	firstMap.m_map[53][9] = BLOCK_WOOD;
	firstMap.m_map[54][9] = BLOCK_WOOD;
	firstMap.m_map[55][9] = BLOCK_WOOD;

	firstMap.m_map[50][7] = BLOCK_WOOD;
	firstMap.m_map[51][7] = BLOCK_WOOD;
	firstMap.m_map[52][7] = BLOCK_WOOD;
	firstMap.m_map[53][7] = BLOCK_WOOD;
	firstMap.m_map[54][7] = BLOCK_WOOD;
	firstMap.m_map[55][7] = BLOCK_WOOD;

	firstMap.m_map[72][13] = BLOCK_WOOD;
	firstMap.m_map[72][12] = BLOCK_WOOD;

	firstMap.m_map[83][11] = BLOCK_WOOD;
	firstMap.m_map[83][12] = BLOCK_WOOD;
	firstMap.m_map[83][13] = BLOCK_WOOD;

	firstMap.m_map[98][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[99][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[100][firstMap.getNumY() - 1] = 0;

	firstMap.m_map[106][13] = BLOCK_WOOD;
	firstMap.m_map[113][13] = BLOCK_WOOD;

	firstMap.m_map[159][13] = BLOCK_WOOD;


	firstMap.m_map[185][13] = BLOCK_WOOD;

	//マップ加工
	firstMap.m_map[168][14] = 0;
	firstMap.m_map[107][14] = 0;

	//ステージにセット
	*stage.usingM = firstMap;


	new Coin(545, 350);
	new Coin(609, 350);

	new Turtle(DOT * 10, DOT * 13); //debug
	//new Fish(DOT * 10, DOT * 13);	//debug
	//new Crab(DOT * 10, DOT * 4);
	new Ship(DOT * 10, DOT * 4, 0);

	new SeaWeed(DOT * 20, DOT * 10, 3, 4);//debug
	new GardenEel(DOT * 30, DOT * 14);//debug
	new TurtleWithWing(DOT * 35, DOT * 10); //debug

	new WalkEnemy(700, 415);
	new WalkEnemy(1280, 290);

	new ShootEnemy(1248, 415);
	new ShootEnemy(1280, 415);

	new Jump(1500, 415);

	new Coin(1600, 256);
	new Coin(1632, 256);
	new Coin(1664, 256);
	new Coin(1696, 256);
	new Coin(1728, 256);
	new Coin(1760, 256);

	new Rope(1834, 100, 5);

	new Turtle(DOT * 76, DOT * 13);



	new UpDownObject(DOT * 87, DOT * 9);

	new FallWall(DOT * 90, DOT * 4);

	new WalkEnemy(DOT * 93, DOT * 13);

	new ShootEnemy(DOT * 104, DOT * 13);

	new Turtle(DOT * 109, DOT * 13);

	new UpDownObject(DOT * 109, DOT * 9);

	new Jump(DOT * 117, DOT * 13);

	new FireBar(DOT * 125, DOT * 10, 90.0, true, 10, 4, 90);

	new Rope(DOT * 119, DOT * 1, 4);
	new Rope(DOT * 127, DOT * 1, 5);

	new Lift(DOT * 131, DOT * 7, true);

	new ShootLaser(DOT * 131);

	new FireBar(DOT * 138, DOT * 10, 90.0, false, 10, 4, 90);

	new Jump(DOT * 153, DOT * 13);



	new Turtle(DOT * 165, DOT * 13);


	new Turtle(DOT * 172, DOT * 13);

	new Lift(DOT * 188, DOT * 9, true);

	new Lift(DOT * 193, DOT * 7, true);

	new FallWall(DOT * 185, DOT * 2);

	new Coin(DOT * 195, DOT * 5);
	new Coin(DOT * 196, DOT * 4);
	new Coin(DOT * 197, DOT * 3);
	new Coin(DOT * 198, DOT * 3);
	new Coin(DOT * 199, DOT * 4);
	new Coin(DOT * 200, DOT * 5);

	new FlashBlock(DOT * 82, DOT * 11);
	new FlashBlock(DOT * 18, DOT * 8);

	new FlashBlock(DOT * 168, DOT * 14);
	new FlashBlock(DOT * 107, DOT * 14);

	new FlashBlock(DOT * 112, DOT * 13);
	new FlashBlock(DOT * 160, DOT * 13);


}
void CreateStage1_2R() {
	//背景をセット
	for (int i = 0; i < ACCOUNTFORMAPPARTS; i++) {
		stage.mapparts[i] = stage1_2Back[i];
	}

	stage.limit = TIME_STAGE2_1R;

	stage.usingP->x = DOT * 2;
	stage.usingP->y = DOT * 13;

	Map firstMap;

	//マップの情報をセット
	//マップの大きさを変更
	firstMap.setNum(10 * firstMap.getNumX(), firstMap.getNumY());

	//地面生成
	for (int i = 0; i < firstMap.getNumX(); i++)
		firstMap.m_map[i][firstMap.getNumY() - 1] = BLOCK_STONE;

	//ステージ

	firstMap.m_map[0][0] = BLOCK_STONE;
	firstMap.m_map[0][1] = BLOCK_STONE;
	firstMap.m_map[0][2] = BLOCK_STONE;
	firstMap.m_map[0][3] = BLOCK_STONE;
	firstMap.m_map[0][4] = BLOCK_STONE;
	firstMap.m_map[0][5] = BLOCK_STONE;
	firstMap.m_map[0][6] = BLOCK_STONE;
	firstMap.m_map[0][7] = BLOCK_STONE;
	firstMap.m_map[0][8] = BLOCK_STONE;
	firstMap.m_map[0][9] = BLOCK_STONE;
	firstMap.m_map[0][10] = BLOCK_STONE;
	firstMap.m_map[0][11] = BLOCK_STONE;
	firstMap.m_map[0][12] = BLOCK_STONE;
	firstMap.m_map[0][13] = BLOCK_STONE;

	firstMap.m_map[1][10] = BLOCK_STONE;
	firstMap.m_map[2][10] = BLOCK_STONE;
	firstMap.m_map[3][10] = BLOCK_STONE;
	firstMap.m_map[4][10] = BLOCK_STONE;
	firstMap.m_map[5][10] = BLOCK_STONE;
	firstMap.m_map[6][10] = BLOCK_STONE;
	firstMap.m_map[7][10] = BLOCK_STONE;
	firstMap.m_map[8][10] = BLOCK_STONE;
	firstMap.m_map[9][10] = BLOCK_STONE;
	firstMap.m_map[10][10] = BLOCK_STONE;
	firstMap.m_map[11][10] = BLOCK_STONE;
	firstMap.m_map[12][10] = BLOCK_STONE;

	firstMap.m_map[10][firstMap.getNumY() - 1] = 0;

	firstMap.m_map[14][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[15][firstMap.getNumY() - 1] = 0;

	firstMap.m_map[13][11] = BLOCK_STONE;

	firstMap.m_map[15][11] = BLOCK_STONE;

	//firstMap.m_map[1][9] = BLOCK_STONE;
	//firstMap.m_map[2][8] = BLOCK_STONE;

	//firstMap.m_map[13][4] = BLOCK_STONE; //<- とげブロックの代わり
	//firstMap.m_map[14][3] = BLOCK_STONE;
	//firstMap.m_map[14][5] = BLOCK_STONE;
	//firstMap.m_map[15][4] = BLOCK_STONE;

	firstMap.m_map[20][9] = BLOCK_STONE;
	firstMap.m_map[21][9] = BLOCK_STONE;
	firstMap.m_map[22][9] = BLOCK_STONE;
	firstMap.m_map[23][9] = BLOCK_STONE;
	firstMap.m_map[24][9] = BLOCK_STONE;
	firstMap.m_map[25][9] = BLOCK_STONE;
	firstMap.m_map[26][9] = BLOCK_STONE;
	firstMap.m_map[27][9] = BLOCK_STONE;
	firstMap.m_map[28][9] = BLOCK_STONE;
	firstMap.m_map[29][9] = BLOCK_STONE;
	firstMap.m_map[30][9] = BLOCK_STONE;
	firstMap.m_map[31][9] = BLOCK_STONE;
	firstMap.m_map[32][9] = BLOCK_STONE;

	firstMap.m_map[20][5] = BLOCK_STONE;
	firstMap.m_map[21][5] = BLOCK_STONE;
	firstMap.m_map[22][5] = BLOCK_STONE;
	firstMap.m_map[23][5] = BLOCK_STONE;
	firstMap.m_map[24][5] = BLOCK_STONE;
	firstMap.m_map[25][5] = BLOCK_STONE;
	firstMap.m_map[26][5] = BLOCK_STONE;
	firstMap.m_map[27][5] = BLOCK_STONE;
	firstMap.m_map[28][5] = BLOCK_STONE;
	firstMap.m_map[29][5] = BLOCK_STONE;
	firstMap.m_map[30][5] = BLOCK_STONE;
	firstMap.m_map[31][5] = BLOCK_STONE;
	firstMap.m_map[32][5] = BLOCK_STONE;

	firstMap.m_map[30][13] = BLOCK_STONE;
	firstMap.m_map[36][13] = BLOCK_STONE;

	firstMap.m_map[35][9] = BLOCK_STONE;
	firstMap.m_map[36][9] = BLOCK_STONE;
	firstMap.m_map[37][9] = BLOCK_STONE;
	firstMap.m_map[38][9] = BLOCK_STONE;
	firstMap.m_map[39][9] = BLOCK_STONE;
	firstMap.m_map[40][9] = BLOCK_STONE;
	firstMap.m_map[41][9] = BLOCK_STONE;
	firstMap.m_map[42][9] = BLOCK_STONE;
	firstMap.m_map[43][9] = BLOCK_STONE;
	firstMap.m_map[44][9] = BLOCK_STONE;
	firstMap.m_map[45][9] = BLOCK_STONE;
	firstMap.m_map[46][9] = BLOCK_STONE;
	firstMap.m_map[47][9] = BLOCK_STONE;
	firstMap.m_map[48][9] = BLOCK_STONE;
	firstMap.m_map[49][9] = BLOCK_STONE;
	firstMap.m_map[50][9] = BLOCK_STONE;
	firstMap.m_map[51][9] = BLOCK_STONE;
	firstMap.m_map[52][9] = BLOCK_STONE;
	firstMap.m_map[53][9] = BLOCK_STONE;
	firstMap.m_map[54][9] = BLOCK_STONE;
	firstMap.m_map[55][9] = BLOCK_STONE;
	firstMap.m_map[56][9] = BLOCK_STONE;
	firstMap.m_map[57][9] = BLOCK_STONE;
	firstMap.m_map[58][9] = BLOCK_STONE;

	firstMap.m_map[35][5] = BLOCK_STONE;
	firstMap.m_map[36][5] = BLOCK_STONE;
	firstMap.m_map[37][5] = BLOCK_STONE;
	firstMap.m_map[38][5] = BLOCK_STONE;
	firstMap.m_map[39][5] = BLOCK_STONE;
	firstMap.m_map[40][5] = BLOCK_STONE;
	firstMap.m_map[41][5] = BLOCK_STONE;
	firstMap.m_map[42][5] = BLOCK_STONE;
	firstMap.m_map[43][5] = BLOCK_STONE;
	firstMap.m_map[44][5] = BLOCK_STONE;
	firstMap.m_map[45][5] = BLOCK_STONE;
	firstMap.m_map[46][5] = BLOCK_STONE;
	firstMap.m_map[47][5] = BLOCK_STONE;
	firstMap.m_map[48][5] = BLOCK_STONE;
	firstMap.m_map[49][5] = BLOCK_STONE;
	firstMap.m_map[50][5] = BLOCK_STONE;
	firstMap.m_map[51][5] = BLOCK_STONE;
	firstMap.m_map[52][5] = BLOCK_STONE;
	firstMap.m_map[53][5] = BLOCK_STONE;
	firstMap.m_map[54][5] = BLOCK_STONE;
	firstMap.m_map[55][5] = BLOCK_STONE;
	firstMap.m_map[56][5] = BLOCK_STONE;
	//firstMap.m_map[57][5] = BLOCK_STONE;
	firstMap.m_map[58][5] = BLOCK_STONE;

	firstMap.m_map[62][9] = BLOCK_STONE;
	firstMap.m_map[63][9] = BLOCK_STONE;
	firstMap.m_map[64][9] = BLOCK_STONE;
	firstMap.m_map[65][9] = BLOCK_STONE;
	firstMap.m_map[66][9] = BLOCK_STONE;
	firstMap.m_map[67][9] = BLOCK_STONE;
	firstMap.m_map[68][9] = BLOCK_STONE;
	firstMap.m_map[69][9] = BLOCK_STONE;
	firstMap.m_map[70][9] = BLOCK_STONE;
	firstMap.m_map[71][9] = BLOCK_STONE;
	firstMap.m_map[72][9] = BLOCK_STONE;
	firstMap.m_map[73][9] = BLOCK_STONE;
	firstMap.m_map[74][9] = BLOCK_STONE;
	firstMap.m_map[75][9] = BLOCK_STONE;
	firstMap.m_map[76][9] = BLOCK_STONE;
	firstMap.m_map[77][9] = BLOCK_STONE;
	firstMap.m_map[78][9] = BLOCK_STONE;
	firstMap.m_map[79][9] = BLOCK_STONE;
	firstMap.m_map[80][9] = BLOCK_STONE;
	firstMap.m_map[81][9] = BLOCK_STONE;
	firstMap.m_map[82][9] = BLOCK_STONE;
	//firstMap.m_map[83][9] = BLOCK_STONE;
	//firstMap.m_map[84][9] = BLOCK_STONE;
	firstMap.m_map[85][9] = BLOCK_STONE;

	firstMap.m_map[62][5] = BLOCK_STONE;
	firstMap.m_map[63][5] = BLOCK_STONE;
	firstMap.m_map[64][5] = BLOCK_STONE;
	firstMap.m_map[65][5] = BLOCK_STONE;
	firstMap.m_map[66][5] = BLOCK_STONE;
	firstMap.m_map[67][5] = BLOCK_STONE;
	firstMap.m_map[68][5] = BLOCK_STONE;
	firstMap.m_map[69][5] = BLOCK_STONE;
	firstMap.m_map[70][5] = BLOCK_STONE;
	firstMap.m_map[71][5] = BLOCK_STONE;
	firstMap.m_map[72][5] = BLOCK_STONE;
	firstMap.m_map[73][5] = BLOCK_STONE;
	firstMap.m_map[74][5] = BLOCK_STONE;
	firstMap.m_map[75][5] = BLOCK_STONE;
	firstMap.m_map[76][5] = BLOCK_STONE;
	firstMap.m_map[77][5] = BLOCK_STONE;
	firstMap.m_map[78][5] = BLOCK_STONE;
	firstMap.m_map[79][5] = BLOCK_STONE;
	firstMap.m_map[80][5] = BLOCK_STONE;
	firstMap.m_map[81][5] = BLOCK_STONE;
	firstMap.m_map[82][5] = BLOCK_STONE;
	//firstMap.m_map[83][5] = BLOCK_STONE;
	//firstMap.m_map[84][5] = BLOCK_STONE;
	firstMap.m_map[85][5] = BLOCK_STONE;

	firstMap.m_map[83][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[84][firstMap.getNumY() - 1] = 0;

	firstMap.m_map[88][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[89][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[90][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[91][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[92][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[93][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[94][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[95][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[96][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[97][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[98][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[99][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[100][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[101][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[102][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[103][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[104][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[105][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[106][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[107][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[108][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[109][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[110][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[111][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[112][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[113][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[114][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[115][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[116][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[117][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[118][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[119][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[120][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[127][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[128][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[129][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[130][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[131][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[132][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[133][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[134][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[135][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[136][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[137][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[138][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[139][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[140][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[141][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[142][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[143][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[144][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[145][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[146][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[147][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[148][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[149][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[150][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[151][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[152][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[153][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[154][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[155][firstMap.getNumY() - 1] = 0;
	firstMap.m_map[156][firstMap.getNumY() - 1] = 0;

	//ステージにセット
	*stage.usingM = firstMap;

	//MOB
	new Jump(DOT * 15, DOT * 10);

	new WalkEnemy(DOT * 6, DOT * 13);
	new WalkEnemy(DOT * 7, DOT * 13);

	new Coin(DOT, DOT * 5);
	new Coin(DOT, DOT * 6);
	new Coin(DOT, DOT * 7);
	new Coin(DOT, DOT * 8);

	new Coin(DOT * 13, DOT * 3);
	new Coin(DOT * 13, DOT * 5);
	new Coin(DOT * 14, DOT * 4);
	new Coin(DOT * 15, DOT * 3);
	new Coin(DOT * 15, DOT * 5);

	new Coin(DOT * 64, DOT * 6);
	new Coin(DOT * 64, DOT * 7);
	new Coin(DOT * 64, DOT * 8);

	new Coin(DOT * 65, DOT * 6);
	new Coin(DOT * 65, DOT * 7);
	new Coin(DOT * 65, DOT * 8);

	new Coin(DOT * 66, DOT * 6);
	new Coin(DOT * 66, DOT * 7);
	new Coin(DOT * 66, DOT * 8);

	new Coin(DOT * 64, DOT * 11);
	new Coin(DOT * 64, DOT * 12);
	new Coin(DOT * 64, DOT * 13);

	new Coin(DOT * 65, DOT * 11);
	new Coin(DOT * 65, DOT * 12);
	new Coin(DOT * 65, DOT * 13);

	new Coin(DOT * 66, DOT * 11);
	new Coin(DOT * 66, DOT * 12);
	new Coin(DOT * 66, DOT * 13);

	new Rope(DOT * 18, DOT, 7);
	new Rope(DOT * 33, DOT, 7);
	new Rope(DOT * 60, DOT, 7);
	new Rope(DOT * 130, DOT, 7);
	new Rope(DOT * 135, DOT, 7);
	new Rope(DOT * 140, DOT, 7);
	new Rope(DOT * 145, DOT, 7);
	new Rope(DOT * 150, DOT, 7);

	new Turtle(DOT * 33, DOT * 13);

	new HanmerThrow(DOT * 46, DOT * 5, 300);
	//new HanmerThrow(DOT * 48, DOT * 5,300);
	//new HanmerThrow(DOT * 50, DOT * 5,300);
	new HanmerThrow(DOT * 52, DOT * 5, 300);

	new UpDownObject(DOT * 88, DOT * 4);


	new Lift(DOT * 90, DOT * 12, false);
	new Lift(DOT * 94, DOT * 4, true);
	new Coin(DOT * 94, DOT * 8);
	new Coin(DOT * 94, DOT * 7);
	new Coin(DOT * 94, DOT * 6);
	new Lift(DOT * 98, DOT * 12, false);
	new Lift(DOT * 102, DOT * 4, true);
	new Coin(DOT * 102, DOT * 8);
	new Coin(DOT * 102, DOT * 7);
	new Coin(DOT * 102, DOT * 6);
	new Lift(DOT * 102, DOT * 12, false);
	new Lift(DOT * 106, DOT * 5, true);
	new Lift(DOT * 110, DOT * 6, true);
	new Lift(DOT * 114, DOT * 7, true);
	new Lift(DOT * 118, DOT * 8, true);
	new Lift(DOT * 163, DOT * 6, true);
	new Coin(DOT * 163, DOT * 7);
	new Coin(DOT * 164, DOT * 9);
	new Coin(DOT * 163, DOT * 11);
	new Coin(DOT * 164, DOT * 13);

	new Jump(DOT * 165, DOT * 13);
	new Jump(DOT * 170, DOT * 13);
	new Jump(DOT * 175, DOT * 13);
	new Jump(DOT * 194, DOT * 13);
	new Coin(DOT * 195, DOT * 5);
	new Coin(DOT * 197, DOT * 4);
	new Coin(DOT * 199, DOT * 3);

	new FlashBlock(DOT * 14, DOT * 11);
	new FlashBlock(DOT * 14, DOT * 14);
	new FlashBlock(DOT * 15, DOT * 14);

	new FlashBlock(DOT * 35, DOT * 12);
	new FlashBlock(DOT * 57, DOT * 5);

	new FlashBlock(DOT * 83, DOT * 5);
	new FlashBlock(DOT * 84, DOT * 5);
	new FlashBlock(DOT * 83, DOT * 9);
	new FlashBlock(DOT * 84, DOT * 9);
	new FlashBlock(DOT * 83, DOT * 14);
	new FlashBlock(DOT * 84, DOT * 14);
	new FlashBlock(DOT * 123, DOT * 7);
	new FlashBlock(DOT * 124, DOT * 7);
	new FlashBlock(DOT * 158, DOT * 7);
	new FlashBlock(DOT * 159, DOT * 7);

	new ThornBlock(DOT * 13, DOT * 4);
	new ThornBlock(DOT * 14, DOT * 3);
	new ThornBlock(DOT * 14, DOT * 5);
	new ThornBlock(DOT * 15, DOT * 4);

	new ThornBlock(DOT * 1, DOT * 9);
	new ThornBlock(DOT * 2, DOT * 8);

	new ThornBlock(DOT * 22, DOT * 8);
	new ThornBlock(DOT * 22, DOT * 7);
	//new ThornBlock(DOT * 22, DOT * 6);

	new ThornBlock(DOT * 22, DOT * 4);
	new ThornBlock(DOT * 22, DOT * 3);
	new ThornBlock(DOT * 22, DOT * 2);

	new ThornBlock(DOT * 22, DOT * 10);

	new ThornBlock(DOT * 36, DOT * 6);

	new ThornBlock(DOT * 36, DOT * 3);
	new ThornBlock(DOT * 37, DOT * 4);
	new ThornBlock(DOT * 37, DOT * 2);

	new ThornBlock(DOT * 37, DOT * 11);
	new ThornBlock(DOT * 37, DOT * 12);

	new ThornBlock(DOT * 63, DOT);
	new ThornBlock(DOT * 63, DOT * 2);
	new ThornBlock(DOT * 63, DOT * 3);

	new ThornBlock(DOT * 63, DOT * 6);
	new ThornBlock(DOT * 63, DOT * 7);
	new ThornBlock(DOT * 63, DOT * 8);

	new ThornBlock(DOT * 63, DOT * 12);
	new ThornBlock(DOT * 63, DOT * 13);

	new ThornBlock(DOT * 162, DOT * 7);
	new ThornBlock(DOT * 165, DOT * 7);
	new ThornBlock(DOT * 166, DOT * 7);
	new ThornBlock(DOT * 167, DOT * 7);
	new ThornBlock(DOT * 168, DOT * 7);
	new ThornBlock(DOT * 169, DOT * 7);
	new ThornBlock(DOT * 170, DOT * 7);
	new ThornBlock(DOT * 171, DOT * 7);
	new ThornBlock(DOT * 172, DOT * 7);
	new ThornBlock(DOT * 173, DOT * 7);
	new ThornBlock(DOT * 174, DOT * 7);
	new ThornBlock(DOT * 175, DOT * 7);
	new ThornBlock(DOT * 176, DOT * 7);
	new ThornBlock(DOT * 177, DOT * 7);
	new ThornBlock(DOT * 178, DOT * 7);
	new ThornBlock(DOT * 179, DOT * 7);
	new ThornBlock(DOT * 180, DOT * 7);
	new ThornBlock(DOT * 181, DOT * 7);

	new ThornBlock(DOT * 162, DOT * 8);
	new ThornBlock(DOT * 165, DOT * 8);
	new ThornBlock(DOT * 166, DOT * 8);
	new ThornBlock(DOT * 167, DOT * 8);
	new ThornBlock(DOT * 168, DOT * 8);
	new ThornBlock(DOT * 169, DOT * 8);
	new ThornBlock(DOT * 170, DOT * 8);
	new ThornBlock(DOT * 171, DOT * 8);
	new ThornBlock(DOT * 172, DOT * 8);
	new ThornBlock(DOT * 173, DOT * 8);
	new ThornBlock(DOT * 174, DOT * 8);
	new ThornBlock(DOT * 175, DOT * 8);
	new ThornBlock(DOT * 176, DOT * 8);
	new ThornBlock(DOT * 177, DOT * 8);
	new ThornBlock(DOT * 178, DOT * 8);
	new ThornBlock(DOT * 179, DOT * 8);
	new ThornBlock(DOT * 180, DOT * 8);
	new ThornBlock(DOT * 181, DOT * 8);

	new Crab(DOT * 25, DOT * 13);

	new Ghost(DOT * 25, DOT * 7);
	new Ghost(DOT * 25, DOT * 3);
	new Ghost(DOT * 40, DOT * 4);
	new Ghost(DOT * 46, DOT * 13);
	//new Ghost(DOT * 48, DOT * 13);
	//new Ghost(DOT * 50, DOT * 13);
	//new Ghost(DOT * 52, DOT * 13);

	new Ghost(DOT * 68, DOT);
	new Ghost(DOT * 68, DOT * 13);

	new Ghost(DOT * 70, DOT * 7);
	//new Ghost(DOT * 70, DOT * 8);
	//new Ghost(DOT * 71, DOT * 7);
	//new Ghost(DOT * 71, DOT * 8);
	//new Ghost(DOT * 72, DOT * 7);
	new Ghost(DOT * 72, DOT * 8);

	new Ghost(DOT * 109, DOT * 13);
	//new Ghost(DOT * 110, DOT * 13);
	new Ghost(DOT * 111, DOT * 13);

	new Ghost(DOT * 109, DOT * 2);
	//new Ghost(DOT * 110, DOT * 2);
	new Ghost(DOT * 111, DOT * 2);

	new Ghost(DOT * 123, DOT * 13);
	new Ghost(DOT * 124, DOT * 13);

	new Ghost(DOT * 135, DOT * 13);
	new Ghost(DOT * 140, DOT * 13);
	new Ghost(DOT * 145, DOT * 13);

}

void CreateStage1_3R() {
	//背景をセット
	for (int i = 0; i < ACCOUNTFORMAPPARTS; i++) {
		stage.mapparts[i] = stage1_3Back[i];
	}

	stage.usingP->x = DOT * 2;
	stage.usingP->y = DOT * 10;
	//stage.usingP->x = DOT * 256;
	//stage.usingP->y = DOT * 10;
	stage.limit = TIME_STAGE1_3R;

	Map firstMap;

	//マップの情報をセット
	//マップの大きさを変更
	firstMap.setNum(300, firstMap.getNumY());

	//地面生成
	for (int i = 0; i < firstMap.getNumX(); i++)
		firstMap.m_map[i][firstMap.getNumY() - 1] = 1;


	firstMap.m_map[6][11] = 1;
	for (int i = 0; i < 5; i++)
		firstMap.m_map[8 + i][11] = 1;

	for (int i = 0; i < 3; i++) {
		firstMap.m_map[35 + i][13] = 1;
		firstMap.m_map[40 + i][13] = 1;
	}
	for (int i = 0; i < 2; i++) {
		firstMap.m_map[36 + i][12] = 1;
		firstMap.m_map[40 + i][12] = 1;
	}
	firstMap.m_map[37][11] = 1;
	firstMap.m_map[40][11] = 1;
	firstMap.m_map[38][14] = 0;
	firstMap.m_map[39][14] = 0;
	for (int i = 0; i < 12; i += 2) {
		firstMap.m_map[51 + i][3] = 1;
		firstMap.m_map[50 + i][4] = 1;
		firstMap.m_map[49 + i][5] = 1;
		firstMap.m_map[50 + i][6] = 1;
	}
	for (int i = 0; i < 13; i++)
		firstMap.m_map[69 + i][8] = 1;
	/*for (int i = 0; i < 2; i++)
	firstMap.m_map[81][6 - i] = 1;*/
	for (int i = 0; i < 32; i++)
		firstMap.m_map[69 + i][14] = 0;

	for (int i = 0; i < 2; i++) {
		firstMap.m_map[85 + (i * 2)][12] = 1;
		firstMap.m_map[86 + (i * 2)][13] = 1;
	}
	firstMap.m_map[87][14] = 1;
	firstMap.m_map[86][11] = 1;
	for (int i = 0; i < 5; i++) {
		firstMap.m_map[90 + i][9] = 1;
	}
	firstMap.m_map[93][6] = 1;
	for (int i = 0; i < 3; i++)
		firstMap.m_map[89][i + 1] = 1;
	for (int i = 0; i < 2; i++)
		firstMap.m_map[90 + i][4] = 1;
	firstMap.m_map[91][2] = 1;

	for (int i = 0; i < 5; i++)
		firstMap.m_map[92 + i][1] = 1;
	firstMap.m_map[122][10] = 1;
	firstMap.m_map[128][10] = 1;
	firstMap.m_map[125][7] = 1;
	firstMap.m_map[135][10] = 1;
	firstMap.m_map[139][7] = 1;
	firstMap.m_map[142][10] = 1;
	for (int i = 0; i < 100; i++) {
		firstMap.m_map[178 + i][0] = 1;
	}

	for(int i=0;i<40;i++)
		firstMap.m_map[255 + i][3] = 1;

	for (int i = 0; i < 7; i++) {
		firstMap.m_map[290][13] = 1;

	}
	for (int i = 0; i < 6; i++) {
		firstMap.m_map[291][12] = 1;
	}
	for (int i = 0; i < 5; i++) {
		firstMap.m_map[292][11] = 1;
	}
	for (int i = 0; i < 4; i++) {
		firstMap.m_map[293][10] = 1;
	}
	for (int i = 0; i < 3; i++) {
		firstMap.m_map[294][9] = 1;
	}
	for (int i = 0; i < 2; i++) {
		firstMap.m_map[295][8] = 1;
	}
	firstMap.m_map[296][7] = 1;

	//ステージにセット
	*stage.usingM = firstMap;

	

	new ShootEnemy(DOT * 8, DOT * 12);
	new HanmerThrow(DOT * 10, DOT * 9, 250);
	new Coin(DOT * 8, DOT * 8);
	new Coin(DOT * 9, DOT * 7 + 5);
	new Coin(DOT * 10, DOT * 6 + 20);
	new Coin(DOT * 11, DOT * 7 + 5);
	new Coin(DOT * 12, DOT * 8);

	new WalkEnemy(DOT * 20, DOT * 12);
	new HanmerThrow(DOT * 25, DOT * 12, 250);



	for (int i = 0; i < 10; i += 2) {
		new ShootEnemy(DOT * (51 + i), DOT * 4);
		new ShootEnemy(DOT*(50 + i), DOT * 5);
	}

	for (int i = 0; i < 3; i++) {
		new Coin(DOT*(52 + i * 3), DOT * 9);
		new Coin(DOT*(53 + i * 3), DOT * 8);
		new Coin(DOT*(54 + i * 3), DOT * 9);
	}
	for (int i = 0; i < 5; i++) {
		new Jump(DOT*(51 + i * 3), DOT * 13);
	}
	for (int i = 0; i < 6; i++) {
		new FallWall(DOT*(69 + i * 2), DOT);
	}
	for (int i = 0; i < 5; i++)
		new Coin(DOT * (70 + i * 2), DOT * 3);
	//new FlashBlock(DOT * 80, DOT * 5);
	new FallWall(DOT * 81, DOT);

	new Coin(DOT * 82, DOT * 3);
	new Coin(DOT * 83, DOT * 2);
	new Coin(DOT * 84, DOT * 2);
	new Coin(DOT * 85, DOT * 3);
	new Lift(DOT * 86, DOT * 4, true);
	new ShootEnemy(DOT * 86, DOT * 12);
	new ShootEnemy(DOT * 87, DOT * 13);
	new FireBar(DOT * 91, DOT * 6, 90, false, 8, 3, 0);
	new Coin(DOT * 91, DOT * 7 + 16);
	new Coin(DOT * 92, DOT * 7 + 16);
	new Coin(DOT * 93, DOT * 5);
	for (int i = 0; i < 7; i++) {
		new Coin(DOT * (90 + i), 0);
	}
	for (int i = 0; i < 3; i++) {
		new Coin(DOT * 90, DOT*(i + 1));
	}
	new Coin(DOT * 91, DOT * 1);
	new Coin(DOT * 91, DOT * 3);
	new Coin(DOT * 93, DOT * 4);
	new Lift(DOT * 96, DOT * 9, true);
	new Rope(DOT * 98, 0, 4);
	new ShootLaser(DOT * 103);
	new FireBar(DOT * 103 + 16, DOT * 10 - 16, 60, false, 8, 3, 0);
	new WalkEnemy(DOT * 103, DOT * 12);
	new FireBar(DOT * 110 + 16, DOT * 10 - 16, 60, false, 8, 3, 0);
	new FireBar(DOT * 117 + 16, DOT * 10 - 16, 60, false, 8, 2, 0);
	new WalkEnemy(DOT * 117, DOT * 12);
	new FireBar(DOT * 124 + 16, DOT * 10 - 16,60,true, 8, 2,0);

	new FireBar(DOT * 131 + 16, DOT * 10 - 16, 60, false, 8, 4, 0);
	new FireBar(DOT * 138 + 16, DOT * 10 - 16, 60, false, 8, 4, 0);
	new FireBar(DOT * 145 + 16, DOT * 10 - 16, 60, false, 8, 5, 0);
	new FireBar(DOT * 152 + 16, DOT * 10 - 16, 60, false, 8, 5, 0);
	new Coin(DOT * 122, DOT * 9);
	new Coin(DOT * 128, DOT * 9);
	new Coin(DOT * 125, DOT * 6);
	new Coin(DOT * 135, DOT * 9);
	new Coin(DOT * 139, DOT * 6);
	new Coin(DOT * 142, DOT * 9);

	new FireBar(DOT * 159 + 16, DOT * 10 - 16, 60, false, 8, 6, 0);
	new FireBar(DOT * 166 + 16, DOT * 10 - 16, 60, false, 8, 7, 0);
	new FireBar(DOT * 173 + 16, DOT * 10 - 16, 60, false, 8, 8, 0);



	//new Fence(DOT * 180, DOT * 7);
	for (int i = 0; i < 112; i++) {
		for (int j = 1; j < 14; j++) {
			new Fence(DOT*(178 + i), DOT*j);
		}
	}
	for (int i = 0; i < 5; i++) {
		new ShootEnemy(DOT*(185 + i * 4), DOT * 12);
	}
	for (int i = 0; i < 3; i++) {
		new HanmerThrow(DOT*(185 + i * 8), DOT * 12, 460);
	}

	for (int i = 0; i < 3; i++) {
		new FireBar(DOT*(210 + i * 5), DOT*(2 + i * 4), 40, true, 4, 4, 0);
	}
	for (int i = 0; i < 2; i++) {
		new FireBar(DOT*(210 + i * 10), DOT*(10 - i * 8), 40, true, 4, 4, 0);
	}
	for (int i = 0; i < 2; i++) {
		new FireBar(DOT * 215, DOT*(2 + i * 8), 40, false, 4, 4, 0);
	}
	for (int i = 0; i < 2; i++) {
		new FireBar(DOT*(210 + i * 10), DOT * 6, 40, false, 4, 4, 0);
	}
	new FireBar(DOT * 230, DOT * 7, 45, true, 16, 4, 0);
	for (int i = 0; i < 3; i++) {
		new Coin(DOT * 227, DOT*(5 + i));
	}
	for (int i = 0; i < 3; i++) {
		new Coin(DOT * 234, DOT*(5 + i));
	}
	for (int i = 0; i < 3; i++) {
		new Coin(DOT * (229 + i), DOT * 3);
	}
	for (int i = 0; i < 3; i++) {
		new Coin(DOT * (229 + i), DOT * 11);
	}

	for (int i =1; i < 4; i++) {
		new HanmerThrow(DOT*(256 + i * 8), DOT * 1, 250);
		new ShootEnemy(DOT * (258 + i * 8), DOT * 12);

	}
	for (int i = 0; i < 3; i++) {
		new ShootLaser(DOT*(253 + i * 20));
	}


	for (int i = 0; i < 7; i++) {
		new FlashBlock(DOT * 240, DOT*i * 2);  ///////////////////////////

	}
	new FlashBlock(DOT * 249, DOT * 8);  //kkakakakakakka
	new FlashBlock(DOT * 251, DOT * 4);  //
	new FlashBlock(DOT * 251, DOT * 8);  //
	new Ghost(DOT * 38, DOT * 14);

	new Ghost(DOT * 243, DOT * 2);
	new Ghost(DOT * 243, DOT * 13);

	for (int i = 0; i < 6; i++) {
		new ThornBlock(DOT * 246, DOT*(i + 1));
		new ThornBlock(DOT * 246, DOT * (13 - i));
	}
	for (int i = 0; i < 2; i++) {
		new ThornBlock(DOT*(247 + i), DOT * 8);
		new ThornBlock(DOT*(247 + i), DOT * 6);  //////////////////
	}
	new ThornBlock(DOT * 250, DOT * 2);
	new ThornBlock(DOT * 254, DOT * 7);
	for (int i = 0; i < 4; i++) {
		new ThornBlock(DOT * 248, DOT*(5 - i));
	}
	new ThornBlock(DOT * 249, DOT * 2);

	/////////////////////////////////////////////
	for (int i = 0; i < 4; i++) {
		new ThornBlock(DOT*(251 + i), DOT * 2);
	}
	for (int i = 0; i < 5; i++) {
		new ThornBlock(DOT * 254, DOT*(6 - i));
	}

	for (int i = 0; i < 3; i++) {
		new ThornBlock(DOT * 251, DOT*(5 + i));
	}

	for (int i = 0; i < 2; i++) {

		new ThornBlock(DOT * 254, DOT*(8 + i));
	}
	new ThornBlock(DOT * 250, DOT * 8);
	new ThornBlock(DOT * 251, DOT * 9);

	//new Fence(222, 222);
}


void CreateStage_MiniGame1() {
	//値を負として使う(5秒間の説明)
	stage.limit = 5000;

	//new Turtle(300, 10);
	//new Jump(300, 400);


}

void CreateStage_Sea() {
	//背景をセット
	for (int i = 0; i < ACCOUNTFORMAPPARTS; i++) {
		stage.mapparts[i] = stage_Sea[0];
	}

	stage.limit = TIME_STAGE1_1R;

	Map firstMap;

	//マップの情報をセット
	//マップの大きさを変更
	firstMap.setNum(160   , firstMap.getNumY());

	//地面生成
	for (int i = 0; i < 100; i++)
		firstMap.m_map[i][firstMap.getNumY() - 1] = BLOCK_WOOD;

	for (int i = 103; i < 130; i++) {
		firstMap.m_map[i][firstMap.getNumY() - 1] = BLOCK_WOOD;
		firstMap.m_map[i][firstMap.getNumY() - 2] = BLOCK_WOOD;
		firstMap.m_map[i][firstMap.getNumY() - 3] = BLOCK_WOOD;
		/*firstMap.m_map[i][firstMap.getNumY() - 6] = BLOCK_WOOD;
		firstMap.m_map[i][0] = BLOCK_WOOD;*/
		for (int j = 0; j < 10; j++) {
			firstMap.m_map[i][j] = BLOCK_WOOD;
		}

	}
	for (int i = 130; i < 149; i++) {
		firstMap.m_map[i][firstMap.getNumY() - 1] = BLOCK_WOOD;
	}
	for (int i = 0; i < 12; i++) {
		firstMap.m_map[148][i] = BLOCK_WOOD;
	}
	/*for (int i = 12; i < 15; i++) {
		firstMap.m_map[148][i] = BLOCK_WOOD;
	}*/
	for (int i = 149; i < 160; i++) {
		firstMap.m_map[i][11] = BLOCK_WOOD;
		firstMap.m_map[i][14] = BLOCK_WOOD;
	}



	//天井作成
	for (int i = 0; i < 100; i++) {
		firstMap.m_map[i][0] = BLOCK_WOOD;
	}
	

	for (int i = 7; i < 13; i++) {
		firstMap.m_map[i][11] = BLOCK_WOOD;
	}

	for (int i = 56; i < 69; i++) {
		firstMap.m_map[i][7] = BLOCK_WOOD;
		firstMap.m_map[i][10] = BLOCK_WOOD;

	}
	for (int i = 1; i < 7; i++)
	{
		firstMap.m_map[56][i] = BLOCK_WOOD;
		firstMap.m_map[68][i] = BLOCK_WOOD;
	}

	for (int i = 11; i < 15; i++) {
		firstMap.m_map[56][i] = BLOCK_WOOD;
		firstMap.m_map[68][i] = BLOCK_WOOD;
	}



	for (int i = 0; i < 6; i++)
	{
		firstMap.m_map[68 + i][6 - i] = BLOCK_WOOD;
	}
	for (int i = 0; i < 7; i++)
	{
		firstMap.m_map[68 + i][10 - i] = BLOCK_WOOD;
	}
	for (int i = 75; i < 100; i++) {
		firstMap.m_map[i][4] = BLOCK_WOOD;
	}
	for (int i = 4; i < 15; i++) {
		firstMap.m_map[99][i] = BLOCK_WOOD;
	}


	//ステージにセット
	*stage.usingM = firstMap;

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 15; j++) {
			new Sea(DOT * i, DOT * j, 0);

		}
	}
	for (int i = 0; i < 15; i++) {
		for (int j = 100; j < 103; j++) {
			new Sea(DOT * j, DOT * i, 0b0100);
		}
	}

	new Crab(DOT * 4, DOT * 13);
	new Fish(DOT * 17, DOT * 8);


	new SeaWeed(DOT * 20, DOT * 1, 4, 13);
	new Fish(DOT * 28, DOT * 10);
	new Crab(DOT * 35, DOT * 13);
	new Fish(DOT * 37, DOT * 6);
	
	new Eel(DOT * 42, DOT * 9,false);
	new Eel(DOT * 49, DOT * 6, true);
	new Eel(DOT * 85, DOT * 1, false);
	new Fish(DOT * 45, DOT * 11);
	new Crab(DOT * 44, DOT * 13);
	new Crab(DOT * 54, DOT * 13);

	new GardenEel(DOT * 56, DOT * 10, 0);
	new GardenEel(DOT * 60, DOT * 10, 0);
	new GardenEel(DOT * 63, DOT * 10, 0);
	new GardenEel(DOT * 67, DOT * 10, 0);
	new SeaWeed(DOT * 64, DOT * 8, 3, 2);

	new HealingItem(DOT * 128, DOT * 11);

	new Blockforblock(DOT * 129, DOT * 11, DOT * 130);
	new Blockforblock(DOT * 129, DOT * 10, DOT * 130);
	new Blockforblock(DOT * 148, DOT * 13, DOT * 130);
	new Blockforblock(DOT * 148, DOT * 12, DOT * 130);


	new MarineBoss(DOT * 143, DOT*12, DOT * 130);

	for (int i = 0; i < 3; i++)
	{
		new Coin(DOT * (7 + i), DOT * (9 - i));
		new Coin(DOT * (11 + i), DOT * (7 + i));
	}
	new Coin(DOT * 10, DOT * 7);

	for (int i = 25; i < 31; i++) {
		new Coin(DOT* i, DOT * 12);
	}
	for (int i = 45; i < 52; i++) {
		new Coin(DOT * i, DOT * 9);
	}
	new Coin(DOT * 57, DOT * 9);
	new Coin(DOT * 61, DOT * 9);
	new Coin(DOT * 62, DOT * 9);


	//stage.usingP->x = DOT*139;
}



void CreateStage_Snow() {
	//背景をセット
	for (int i = 0; i < ACCOUNTFORMAPPARTS; i++) {
		stage.mapparts[i] = stage_Snow[0];
	}
	stage.limit = TIME_STAGE_SNOW;

	Map firstMap;

	//マップの情報をセット
	//マップの大きさを変更
	firstMap.setNum(10 * firstMap.getNumX(), firstMap.getNumY());

	//地面(氷)生成
	for (int i = 0; i < firstMap.getNumX(); i++)
		firstMap.m_map[i][firstMap.getNumY() - 1] = BLOCK_ICE;


	for (int i = 0; i < 3; i++)
	{
		firstMap.m_map[6 + i][firstMap.getNumY() - 1 - 4] = BLOCK_ICE;
		new Coin(DOT * (6 + i), DOT * (firstMap.getNumY() - 1 - 5));
	}
	new WalkEnemy(DOT * 7, DOT * (firstMap.getNumY() - 1 - 1));

	for (int i = 0; i < 3; i++)
	{
		firstMap.m_map[29 + i][firstMap.getNumY() - 1 - 4] = BLOCK_ICE;
	}
	new WalkEnemy(DOT * 15, DOT * (firstMap.getNumY() - 1 - 2));

	new Polarbear(DOT * 22, DOT * (firstMap.getNumY() - 1 - 2));

	for (int i = 0; i < 7; i++)
	{
		firstMap.m_map[36 + i][firstMap.getNumY() - 1 - 7] = BLOCK_ICE;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
		{
			new Coin(DOT * (40 + i), DOT * (firstMap.getNumY() - 1 - 8 - j));
		}
	}

	new SnowMan(DOT * 39, DOT * (firstMap.getNumY() - 1 - 8), true);
	new Penguin(DOT * 32, DOT * (firstMap.getNumY() - 1 - 1));
	new Penguin(DOT * 46, DOT * (firstMap.getNumY() - 1 - 1));

	for (int i = 0; i < 3; i++)
	{
		for (int j = i; j < 7 - i; j++)
		{
			firstMap.m_map[49 + j][firstMap.getNumY() - 2 - i] = BLOCK_ICE;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		firstMap.m_map[52][firstMap.getNumY() - 1 - i] = 0;
	}

	for (int i = 0; i < 3; i++)
	{
		firstMap.m_map[62 + i][firstMap.getNumY() - 1 - 4] = BLOCK_ICE;
		new Coin(DOT * (62 + i), DOT * (firstMap.getNumY() - 1 - 5));
	}
	new Penguin(DOT * 60, DOT * (firstMap.getNumY() - 1 - 1));
	new Penguin(DOT * 66, DOT * (firstMap.getNumY() - 1 - 1));

	for (int i = 0; i < 3; i++)
	{
		for (int j = i; j < 7 - i; j++)
		{
			firstMap.m_map[71 + j][firstMap.getNumY() - 2 - i] = BLOCK_ICE;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		firstMap.m_map[74][firstMap.getNumY() - 1 - i] = 0;
	}

	new Polarbear(DOT * 80, DOT * (firstMap.getNumY() - 1 - 2));

	for (int i = 0; i < 3; i++)
	{
		firstMap.m_map[82 + i][firstMap.getNumY() - 1 - 4] = BLOCK_ICE;
	}

	new Lift(DOT * 88, DOT * (firstMap.getNumY() - 1 - 8), true);

	for (int i = 0; i < 7; i++)
	{
		firstMap.m_map[92 + i][firstMap.getNumY() - 1 - 10] = BLOCK_ICE;
		for (int j = 0; j < 3; j++)
		{
			new Coin(DOT * (92 + i), DOT * (firstMap.getNumY() - 1 - 11 - j));
		}
	}
	new SnowMan(DOT * 95, DOT * (firstMap.getNumY() - 1 - 2), true);

	for (int i = 0; i < 3; i++)
	{
		firstMap.m_map[106 + i][firstMap.getNumY() - 1 - 4] = BLOCK_ICE;
	}
	new Lift(DOT * 101, DOT * (firstMap.getNumY() - 1 - 8), true);

	new Penguin(DOT * 112, DOT * (firstMap.getNumY() - 1 - 2));

	for (int i = 0; i < 3; i++)
	{
		firstMap.m_map[118 + i][firstMap.getNumY() - 1 - 4] = BLOCK_ICE;
		firstMap.m_map[118 + i][firstMap.getNumY() - 1 - 8] = BLOCK_ICE;
		new Coin(DOT * (118 + i), DOT * (firstMap.getNumY() - 1 - 9));
	}

	new Polarbear(DOT * 122, DOT * (firstMap.getNumY() - 1 - 2));

	//healingItem
	new HealingItem(DOT * 119, DOT * (firstMap.getNumY() - 1 - 5));

	for (int i = 0; i < 3; i++)
	{
		new Coin(DOT * (123 + i), DOT * (firstMap.getNumY() - 1 - 11));
	}
	new Polarbear(DOT * 128, DOT * (firstMap.getNumY() - 1 - 2));

	for (int i = 0; i < 3; i++) {
		for (int j = i; j < 3; j++)
		{
			firstMap.m_map[130 + j][firstMap.getNumY() - 1 - 1 - i] = BLOCK_ICE;
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 6; j++)
		{
			firstMap.m_map[133 + j][firstMap.getNumY() - 1 - 1 - i] = BLOCK_ICE;
		}
	}
	new SnowMan(DOT * 134, DOT * (firstMap.getNumY() - 1 - 5), true);
	for (int i = 3; i < 6; i++) {
		for (int j = i - 3; j < 3; j++)
		{
			firstMap.m_map[136 + j][firstMap.getNumY() - 1 - 1 - i] = BLOCK_ICE;
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 6; j++)
		{
			firstMap.m_map[139 + i][firstMap.getNumY() - 1 - 1 - j] = BLOCK_ICE;
		}
		for (int j = 0; j < 3; j++)
		{
			new Coin(DOT * (139 + i), DOT * (firstMap.getNumY() - 1 - 7 - j));
		}
	}
	firstMap.m_map[142][firstMap.getNumY() - 1 - 3] = BLOCK_ICE;

	new UpDownObject(DOT * 147, DOT * (firstMap.getNumY() - 1 - 7));

	for (int i = 0; i < 3; i++)
	{
		firstMap.m_map[152 + i][firstMap.getNumY() - 1 - 6] = BLOCK_ICE;
	}

	new TurtleWithWing(DOT * 158, DOT * (firstMap.getNumY() - 1 - 8));

	for (int i = 0; i < 3; i++)
	{
		firstMap.m_map[162 + i][firstMap.getNumY() - 1 - 6] = BLOCK_ICE;
	}

	new UpDownObject(DOT * 170, DOT * (firstMap.getNumY() - 1 - 7));

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			firstMap.m_map[178 + i][firstMap.getNumY() - 1 - j] = BLOCK_ICE;
		}
	}
	for (int i = 0; i < 2; i++) {
		new Polarbear(DOT * (145 + i * 12), DOT * (firstMap.getNumY() - 1 - 1));
	}
	new Penguin(DOT * 155, DOT * (firstMap.getNumY() - 1 - 1));

	//ステージにセット
	*stage.usingM = firstMap;
}

void CreateStage_Sky() {

}

void CreateStage_Tutorial() {
	//背景をセット
	for (int i = 0; i < ACCOUNTFORMAPPARTS; i++) {
		stage.mapparts[i] = stage1_1Back[i];
	}

	stage.limit = TIME_STAGE1_1R;

	Map firstMap;

	//マップの情報をセット
	//マップの大きさを変更
	firstMap.setNum(6 * firstMap.getNumX(), firstMap.getNumY());

	//地面生成
	for (int i = 0; i < firstMap.getNumX(); i++)
		firstMap.m_map[i][firstMap.getNumY() - 1] = BLOCK_WOOD;

	//マップ作製
	for (int i = 0; i < 3; i++)
	{
		firstMap.m_map[16 + i][11] = BLOCK_WOOD;
	}
	//マップ作製
	for (int i = 0; i < 3; i++)
	{
		firstMap.m_map[26 + i][11] = BLOCK_WOOD;
	}

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++)
		{
			firstMap.m_map[35 + j][firstMap.getNumY() - 1 - 1 - i] = BLOCK_STONE;
		}
	}

	firstMap.m_map[41][10] = BLOCK_WOOD;
	firstMap.m_map[42][10] = BLOCK_WOOD;
	firstMap.m_map[43][10] = BLOCK_WOOD;
	firstMap.m_map[44][10] = BLOCK_WOOD;

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++)
		{
			firstMap.m_map[60 + j][firstMap.getNumY() - 1 - 1 - i] = BLOCK_STONE;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			firstMap.m_map[63 + i][firstMap.getNumY() - 1 - 1 - j] = BLOCK_STONE;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		firstMap.m_map[71][(firstMap.getNumY() - 1 - 1 - i)] = BLOCK_STONE;
	}

	for (int i = 0; i < 3; i++)
	{
		firstMap.m_map[73][(firstMap.getNumY() - 1 - 1 - i)] = BLOCK_STONE;
	}

	for (int i = 0; i < 3; i++)
	{
		firstMap.m_map[93][(firstMap.getNumY() - 1 - 1 - i)] = BLOCK_STONE;
	}

	//ステージにセット
	*stage.usingM = firstMap;



	for (int i = 0; i < 3; i++)
	{
		new Coin(DOT * (16 + i), DOT * 10);
	}

	for (int i = 0; i < 3; i++)
	{
		new Coin(DOT * (26 + i), DOT * 10);
	}


	new WalkEnemy(500, 415);
	new WalkEnemy(780, 415);

	new ShootEnemy(DOT * 66, 415);

	new Jump(DOT * 33, 415);

	new Coin(1600, 256);
	new Coin(1632, 256);
	new Coin(1664, 256);
	new Coin(1696, 256);
	new Coin(1728, 256);
	new Coin(1760, 256);

	new Rope(1834, 100, 8);

	new Turtle(DOT * 76, DOT * 13);
	new Turtle(DOT * 46, DOT * 13);

	new WalkEnemy(DOT * 75, DOT * 13);

	new UpDownObject(DOT * 87, DOT * 9);

	new FallWall(DOT * 90, DOT * 1);

	new TurtleWithWing(DOT * 100, DOT * 11);

	new FireBar(DOT * 110, DOT * 10, 70.0, false, 5, 2, 90);
}