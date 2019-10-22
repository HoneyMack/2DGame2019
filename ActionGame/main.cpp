
#include "Stage.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>


#define STAGENUM 3
using namespace std;

//�����L���O�f�[�^�ێ��p	�e�L�X�g�̕ۑ��`��:���O�A�c��^�C���A�G�̌��j���A�c��HP�A�R�C��
struct rankdata {
	string name;
	int limit, killedene, hp, coin;
};


//�N���X�C���X�^���X�쐬
Stage stage;

//�֐��@�v���g�^�C�v�錾
void GameControl();
void StartWindow();
int  GameSelectWindow();		//�I�������X�e�[�W�̐����ԍ���Ԃ�
void GamePlayWindow();
void GamePauseWindow();
void GameOverWindow();
void GameClearWindow(int selectedstage);	//�I�������X�e�[�W�̐����ԍ���n��
void RankingWindow();

void RankingWrite(string txtname, rankdata rankdata);		//txtname�̃t�@�C����rnkdt����������
rankdata* RankingRead(string txtname, int* index);					//txtname�̃t�@�C���̃f�[�^��ǂݍ���Ŗ߂�l�Ƃ��ēn�� �z��̗v�f���������ɓn��

//�X�e�[�W�̃I�u�W�F�N�g����
void CreateStage1_1();
void CreateStage2_1();
void CreateStage1_1R();
void CreateStage1_2R();
void CreateStage1_3R();
void CreateStage_MiniGame1();			//�^�C���������~�j�Q�[��


//���j���[�؂�ւ��p�t���O
int window = STARTWINDOW;

//�L�[���͊֌W
int now_key;		//���̃t���[���̏�Ԃ�ێ�
bool befKeys[62];	//��ˑO�̓��͕ێ��p


//�}�b�v���ێ�
string stagename[] = { "stage1_1R" ,"stage1_2R","stage1_3R","TEST1","TEST2" };

//�w�i�摜�w��
int stage1_1Back[ACCOUNTFORMAPPARTS];
int stage1_2Back[ACCOUNTFORMAPPARTS];
int stage1_3Back[ACCOUNTFORMAPPARTS];

//�S�[���o�[
int goalPicHandle;


//use to calcurate frametime 
int beftime, curtime;
float frametime;

//�X�^�[�g��ʂ̕���
int strWidth, strLen;

int HPfont;				//HP�\���p�t�H���g�n���h���ێ�
int rankfont_1, rankfont_2, rankfont_3;			//�����N�\���p�t�H���g
int Pausefont;							//�|�[�Y�t�H���g


//int picture;

char *str = "";

HWND hWnd;


int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lp, int nC)
{

	ChangeWindowMode(TRUE), SetGraphMode(WIDTH, HEIGHT, 32);

	if (DxLib_Init() == -1) return -1;

	SetDrawScreen(DX_SCREEN_BACK);

	beftime = GetNowCount() & INT_MAX;


	//�t�H���g�Z�b�g
	HPfont = CreateFontToHandle("���C���I", 16, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	rankfont_1 = CreateFontToHandle("���C���I", 16, 9, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	rankfont_2 = CreateFontToHandle("���C���I", 16, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	rankfont_3 = CreateFontToHandle("���C���I", 16, 7, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	Pausefont = CreateFontToHandle("Ravie", 32, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//�w�i�摜
	//picture = LoadGraph("pictures/background.png");

	//Mob�摜���Z�b�g
	Player::PicHandle[0] = LoadGraph("pictures/player.png");
	Player::PicHandle[1] = LoadGraph("pictures/boy_run.png");
	Player::PicHandle[2] = LoadGraph("pictures/boy_jump.png");
	Player::PicHandle[3] = LoadGraph("pictures/fence_motion.png");

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
	TurtleWithWing::PicHandleWing = LoadGraph("pictures/takoyaki_wing.png"); //Debug�p���摜
	HanmerThrow::PicHandle[0] = LoadGraph("pictures/HanmerThrow_1.png");
	HanmerThrow::PicHandle[1] = LoadGraph("pictures/HanmerThrow_2.png");
	HanmerThrow::PicHandle[2] = LoadGraph("pictures/HanmerThrow_3.png");
	Hanmer::PicHandle = LoadGraph("pictures/ballonly.png");
	Ghost::PicHandle[0] = LoadGraph("pictures/ghost_3.png");
	Ghost::PicHandle[1] = LoadGraph("pictures/ghost_2.png");
	Ghost::PicHandle[2] = LoadGraph("pictures/ghost_1.png");
	ThornBlock::PicHandle = LoadGraph("pictures/thornblock.png");
	Fence::PicHandle = LoadGraph("pictures/fence.png");

	Fish::PicHandle = LoadGraph("pictures/fish.png");	//�����摜�Z�b�g
	Crab::PicHandle = LoadGraph("pictures/crab.png");	//�J�j�摜���Z�b�g
	Ship::PicHandle = LoadGraph("pictures/Ship.png");	//�f�o�b�N�p���摜�Z�b�g

	Polarbear::PicHandle = LoadGraph("pictures/Ship.png"); //debug�p���摜

	SeaWeed::PicHandles[0] = LoadGraph("pictures/seaweed_animation/seaweed0.png");//Debug�p���摜
	SeaWeed::PicHandles[1] = LoadGraph("pictures/seaweed_animation/seaweed1.png");//Debug�p���摜
	SeaWeed::PicHandles[2] = LoadGraph("pictures/seaweed_animation/seaweed2.png");//Debug�p���摜
	SeaWeed::PicHandles[3] = LoadGraph("pictures/seaweed_animation/seaweed3.png");//Debug�p���摜
	SeaWeed::PicHandles[4] = LoadGraph("pictures/seaweed_animation/seaweed4.png");//Debug�p���摜

	GardenEel::PicHandle = LoadGraph("pictures/GardenEel.png"); //Debug�p���摜
	Sea::PicHandle = LoadGraph("pictures/Sea.png");
	
	Penguin::PicHandle = LoadGraph("pictures/takoyaki_back.png");

	//Fence::PicHandle = LoadGraph("pictures/block_stone.png");

	//�}�b�v�摜���Z�b�g
	Map::PicHandle[GROUND] = LoadGraph("pictures/ground.png");
	Map::PicHandle[TOGE] = LoadGraph("pictures/toge.png");
	Map::PicHandle[BLOCK_STONE] = LoadGraph("pictures/block_stone.png");
	Map::PicHandle[BLOCK_ICE] = LoadGraph("pictures/block_ice.png");
	Map::PicHandle[BLOCK_WOOD] = LoadGraph("pictures/block_wood.png");

	//�w�i�摜���Z�b�g
	stage1_1Back[0] = LoadGraph("pictures/background/stage1_1/background_1.jpg");
	stage1_1Back[1] = LoadGraph("pictures/background/stage1_1/background_2.jpg");
	stage1_1Back[2] = LoadGraph("pictures/background/stage1_1/background_3.jpg");
	stage1_2Back[0] = LoadGraph("pictures/background/stage1_2/background_1.jpg");
	stage1_2Back[1] = LoadGraph("pictures/background/stage1_2/background_2.jpg");
	stage1_2Back[2] = LoadGraph("pictures/background/stage1_2/background_3.jpg");
	stage1_3Back[0] = LoadGraph("pictures/background/stage1_3/background_1.jpg");
	stage1_3Back[1] = LoadGraph("pictures/background/stage1_3/background_2.jpg");
	stage1_3Back[2] = LoadGraph("pictures/background/stage1_3/background_3.jpg");

	//�S�[��
	goalPicHandle = LoadGraph("pictures/goal_line.png");

	//�T�E���h���Z�b�g
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

	ChangeVolumeSoundMem(255 * 50 / 100, Sound::sounds[SOUND_LASERSHOT]);//���ʒ���

	while (ProcessMessage() == 0 && ScreenFlip() == 0 && ClearDrawScreen() == 0)
	{
		clsDx();
		GameControl();
		//printfDx("%f::", frametime);
	}
	//�����������ׂĉ��
	stage.AllReset();

	DxLib_End();

	return 0;
}

void GameControl() {
	//�I�����ꂽ�X�e�[�W�̔ԍ���ێ�
	static int selectedstage = 0;
	//calcurate frametime
	curtime = GetNowCount() & INT_MAX;
	frametime = (float)(curtime - beftime) / 1000.0f;
	beftime = curtime;

	now_key = GetJoypadInputState(DX_INPUT_KEY_PAD1);						//�L�[���͏���

	switch (window) {
	case STARTWINDOW:
		StartWindow();
		break;
	case GAMESELECTWINDOW:
		//�����~
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

	//���傤�ǒ����ɕ`�悳���悤�ɂ��邽�߂̏���
	DrawString((WIDTH - strWidth) / 2, 400, str, 0xFFFFFF);

	if (GetJoypadInputState(DX_INPUT_KEY_PAD1)) {
		window = GAMESELECTWINDOW;
	}
}

int GameSelectWindow() {
	static int selectnum = -1;												//�I�������}�b�v���L�����Ă����B�ŏ��ɕ��̐������Ă����āA�A���������h��
	const int startx = 100, starty = 100, interval = 30;					//���ڂ� x ���W,y���W,���ڂ̊Ԋu

	//����A���œ����Ă��܂��̂�
	if (selectnum == -1) {
		InKeyTrigger(now_key, PAD_INPUT_1);			//�L�[���͂𗬂�
		InKeyTrigger(now_key, PAD_INPUT_4);
		selectnum = 0;
	}

	if (InKeyTrigger(now_key, PAD_INPUT_DOWN) && selectnum < STAGENUM - 1)					selectnum++;			//�����Ȃ��Ƃ����I�����Ȃ��悤�ɐ���
	if (InKeyTrigger(now_key, PAD_INPUT_UP) && selectnum > 0)	selectnum--;

	//�I������������
	if (selectnum >= 0)
		DrawString(startx - 30, starty + selectnum * interval, "��", 0xFFFFFF);	//�I�����Ă��鉡�Ɂ���`��

	//������}�b�v����`��
	for (int i = 0; i < STAGENUM; i++)
		DrawString(startx, starty + interval * i, stagename[i].c_str(), 0xFFFFFF);

	DrawString(30, 310, "�v���C���[�h:", 0xFFFFFF);
	DrawString(50, 340, "A�L�[:�����X�N���[�� + ���E�ړ�(���L�[) + �W�����v(�X�y�[�X�L�[)", 0xFFFFFF);							//���ӏ���
	DrawString(50, 370, "Z�L�[: ���E�ړ�(���L�[) + �W�����v(�X�y�[�X�L�[)", 0xFFFFFF);
	DrawString(30, 430, "R�L�[:�����L���O�\����", 0xFFFFFF);

	//�X�e�[�W��BGM�̓������o�J�H������̂ŏ����Ă���
	static bool stagesounddeleteflag = false; //�X�e�[�W�̉��y��������Ă��邩
	if (!stagesounddeleteflag) {
		for (int i = SOUND_STAGESTART; i < SOUND_MAX; i++) {
			DeleteSoundMem(Sound::sounds[i]);
		}
		stagesounddeleteflag = true;

		//�摜����������
		for(int i = 0;i < 3;i++)
		stage.mapparts[i] = 0;
	}
	//�I�����ꂽ�炻�̔ԍ���Ԃ� +(GameSelectWindow�ɓ������u�ԂɃQ�[���ɓ���̂�h��)
	if ((InKeyTrigger(now_key, PAD_INPUT_1) || InKeyTrigger(now_key, PAD_INPUT_4))) {
		switch (selectnum) {

		case 0:
			Sound::sounds[SOUND_STAGE1_1] = LoadSoundMem("sounds/stage1-1.mp3");
			CreateStage1_1R();
			break;
		case 1:
			CreateStage1_2R();
			Sound::sounds[SOUND_STAGE1_2] = LoadSoundMem("sounds/stage1-2.mp3");
			break;
		case 2:
			CreateStage1_3R();
			Sound::sounds[SOUND_STAGE1_3] = LoadSoundMem("sounds/stage1-3.mp3");
			break;
		case 3:
			CreateStage2_1();
			break;
		case 4:
			CreateStage1_1();
			break;
		}
		if (now_key&PAD_INPUT_4)
			stage.mode = FORCEHORIZONTALSCROLL;
		else {
			stage.mode = CROSSKEYANDJUMP;
		}
		//�������d���Ȃ��Ă��܂��̂Ōv�����Z�b�g
		//calcurate frametime
		curtime = GetNowCount() & INT_MAX;
		frametime = (float)(curtime - beftime) / 1000.0f;
		beftime = curtime;
		window = GAMEPLAYWINDOW;
		stagesounddeleteflag = false;

		//�����Đ�
		PlaySoundMem(Sound::sounds[selectnum + SOUND_STAGESTART + 1], DX_PLAYTYPE_LOOP, TRUE);
	}
	//�����L���O��ʂֈړ�
	if (CheckHitKey(KEY_INPUT_R) == 1) {
		window = RANKINGWINDOW;
	}




	//�I�������ԍ���Ԃ�
	return selectnum;
}

void GamePlayWindow() {
	//���ȏ�̃t���[��time���o�Ă��܂������̗�O����(200ms)
	if (frametime >= 0.2) {
		window = GAMEPAUSEWINDOW;
	}
	else {
		//�w�i�`��
		//DrawGraph(-stage.Camera->x, -stage.Camera->y, picture, TRUE);


		stage.AllUpdate(frametime);
		stage.AllDraw();

		//�\���֌W�`��
		//�c��g�o�ɂ���ĐF��ς���
		if (stage.usingP->HP >= 10)
			DrawFormatStringToHandle(10, 10, 0x32CCB6, HPfont, "HP:%3d", stage.usingP->HP);
		else
			DrawFormatStringToHandle(10, 10, 0xFF0037, HPfont, "HP:%3d", stage.usingP->HP);

		DrawFormatStringToHandle(90, 10, 0xFFF10F, HPfont, "COIN:%4d", Coin::hadcoins);		//�R�C���`��

		//�c�莞�Ԃɂ���ĐF��ς���
		if (stage.limit >= 100000)
			DrawFormatStringToHandle(530, 10, 0xFFFFFF, HPfont, "TIME:%3d", stage.limit / 1000);
		else
			DrawFormatStringToHandle(530, 10, 0xFF0037, HPfont, "TIME:%3d", stage.limit / 1000);

		//printfDx("coins:%d , ", Coin::hadcoins);	//�����R�C���\��
		//printfDx("HP:%d , ", stage.usingP->HP);	//HP�\��
		//printfDx("vy:%f , ", stage.usingP->vy);	//�����x�\��

		if (InKeyTrigger(now_key, PAD_INPUT_9)) //ESC�L�[�������ꂽ��
			window = GAMEPAUSEWINDOW;

		//�Q�[���I�[�o�[����(�c�莞�ԂO�AHP�O�A�v���C���[��������)
		if (stage.limit < 0 || stage.usingP->HP <= 0 || stage.usingP->y >= HEIGHT + DOT) {
			window = GAMEOVERWINDOW;
		}
		//�S�[������
		if (stage.usingP->x > stage.usingM->getNumX() * DOT - 50) {
			window = GAMECLEARWINDOW;
		}		
		//�S�[���o�[�`��
		DrawGraph(stage.usingM->getNumX()*DOT -stage.Camera->x -100,350,goalPicHandle,TRUE);
	}
}

void GamePauseWindow() {

	str = "�X�e�[�W�ɖ߂�:ESC , �X�e�[�W�I���ɖ߂�:Z";
	strLen = strlen(str);
	strWidth = GetDrawStringWidth(str, strLen, Pausefont);				//�����`��p
	DrawString((WIDTH - strWidth) / 2, 400, str, 0x00FFFF);

	str = "Pause";
	strLen = strlen(str);
	strWidth = GetDrawStringWidthToHandle(str, strLen, Pausefont);				//�����`��p
	DrawStringToHandle((WIDTH - strWidth) / 2, 200, str, 0xFFFFFF, Pausefont);

	if (InKeyTrigger(now_key, PAD_INPUT_9)) //ESC�L�[�������ꂽ��
		window = GAMEPLAYWINDOW;
	if (InKeyTrigger(now_key, PAD_INPUT_1)) {//z�L�[�������ꂽ��
		stage.AllReset();
		window = GAMESELECTWINDOW;
	}
}

void GameOverWindow() {

	str = "GameOver";
	strLen = strlen(str);
	strWidth = GetDrawStringWidthToHandle(str, strLen, Pausefont);				//�����`��p
	DrawStringToHandle((WIDTH - strWidth) / 2, 200, str, 0xFFFFFF, Pausefont);

	str = "�I�����j���[�ɖ߂�:Z�L�[";
	strLen = strlen(str);
	strWidth = GetDrawStringWidth(str, strLen);				//�����`��p
	DrawString((WIDTH - strWidth) / 2, 300, str, 0x00FFFF);

	if (InKeyTrigger(now_key, PAD_INPUT_1)) {
		stage.AllReset();
		window = GAMESELECTWINDOW;

	}
}
void GameClearWindow(int selectedstage) {
	str = "GAMECLEAR";
	strLen = strlen(str);
	strWidth = GetDrawStringWidth(str, strLen);				//�����`��p
	DrawString((WIDTH - strWidth) / 2, 200, str, 0xFFFFFF);


	//���O����͂�����
	char addname[20 + 1] = {""};
	str = "���O����͂��ăX�R�A�������L���O�ɓo�^���܂�(20�����ȓ�):Enter�Ō���";
	strLen = strlen(str);
	strWidth = GetDrawStringWidth(str, strLen);				//�����`��p
	DrawString((WIDTH - strWidth) / 2, 300, str, 0xFFFFFF);

	str = "Esc�L�[:�o�^�����ɖ߂�";
	strLen = strlen(str);
	strWidth = GetDrawStringWidth(str, strLen);				//�����`��p
	DrawString((WIDTH - strWidth) / 2, 400, str, 0xFFFFFF);
	//if (KeyInputSingleCharString((WIDTH - strWidth) / 2, 320, 20, addname, TRUE) == 1) {
	if (KeyInputString((WIDTH - strWidth) / 2, 320, 20, addname, TRUE) == 1) {
		rankdata addrank;
		//�V�����ǉ�����X�R�A��z��ɒǉ�
		addrank.name = addname;
		addrank.limit = stage.limit / 1000;
		addrank.killedene = Mob::killedenemy;
		addrank.hp = stage.usingP->HP;
		addrank.coin = Coin::hadcoins;

		RankingWrite(stagename[selectedstage] + ".txt", addrank);
	}
	//���͌�Z���N�g�E�B���h�E�ɖ߂�
	stage.AllReset();
	window = GAMESELECTWINDOW;

}

void RankingWindow() {
	static int selectedstage = 0;	//�������X�e�[�W�ԍ���ێ�
	{
		//string str;
		//ifstream text("test.txt");		//�e�L�X�g����
		////�f�[�^���ꎞ�I�ێ�
		//string name[RECODE_NUM_MAX];
		//int scores[RECODE_NUM_MAX][5];
		////���l���邩���J�E���g
		//int count = 0;
		//while (getline(text, str) && count < RECODE_NUM_MAX)
		//{
		//	//�e�L�X�g�̕ۑ��`��:���O�A�c��^�C���A�G�̌��j���A�c��HP�A�R�C��,����
		//	string tmp;
		//	istringstream stream(str);
		//	//���O�����o��
		//	getline(stream, tmp, ',');
		//	name[count] = tmp;
		//	//�X�R�A�����o��(4�̗v�f)
		//	for (int i = 0; i < 4; i++) {
		//		getline(stream, tmp, ',');
		//		scores[count][i] = stoi(tmp);
		//	}
		//	count++;
		//}


		int count = 0;		//�z��̗v�f�������
		int scores[RECODE_NUM_MAX];			//�������_
		rankdata *score = RankingRead(stagename[selectedstage] + ".txt", &count);	//�f�[�^�ێ��p

		//�����v�Z
		for (int i = 0; i < count; i++) {
			scores[i] = SCORE_LIMIT * score[i].limit + SCORE_ENEMY * score[i].killedene + SCORE_HP * score[i].hp + SCORE_COIN * score[i].coin;
		}

		//�ŏ��ɕ\������ʒu
		int firstx = 20, firsty = 20, interval = 20;
		int rank;	//���ʃJ�E���g
		//�\��
		for (int i = 0; i < count; i++) {
			//���ʕt��
			rank = 0;
			for (int j = 0; j < count; j++) {
				if (scores[i] < scores[j])
					rank++;
			}
			//���ʂɂ���ĐF��ς���
			switch (rank + 1) {
			case 1:
				DrawFormatStringToHandle(firstx, firsty + i * interval, 0xFFF10F, rankfont_1, "rank:%2d", rank + 1);						//���ʕ`��
				DrawFormatStringToHandle(firstx + 130, firsty + i * interval, 0xFFF10F, rankfont_1, "NAME:%-20s", score[i].name.c_str());		//���O�`��
				DrawFormatStringToHandle(firstx + 450, firsty + i * interval, 0xFFF10F, rankfont_1, "SCORE:%-10d", scores[i]);		//�X�R�A�`��
				break;
			case 2:
				DrawFormatStringToHandle(firstx, firsty + i * interval, 0xafafb0, rankfont_2, "rank:%2d", rank + 1);						//���ʕ`��
				DrawFormatStringToHandle(firstx + 130, firsty + i * interval, 0xafafb0, rankfont_2, "NAME:%-20s", score[i].name.c_str());		//���O�`��
				DrawFormatStringToHandle(firstx + 450, firsty + i * interval, 0xafafb0, rankfont_2, "SCORE:%-10d", scores[i]);		//�X�R�A�`��
				break;
			case 3:
				DrawFormatStringToHandle(firstx, firsty + i * interval, 0xb36b24, rankfont_3, "rank:%2d", rank + 1);						//���ʕ`��
				DrawFormatStringToHandle(firstx + 130, firsty + i * interval, 0xb36b24, rankfont_3, "NAME:%-20s", score[i].name.c_str());		//���O�`��
				DrawFormatStringToHandle(firstx + 450, firsty + i * interval, 0xb36b24, rankfont_3, "SCORE:%-10d", scores[i]);		//�X�R�A�`��
				break;
			default:
				DrawFormatStringToHandle(firstx, firsty + i * interval, 0xFFFFFF, HPfont, "rank:%2d", rank + 1);						//���ʕ`��
				DrawFormatStringToHandle(firstx + 130, firsty + i * interval, 0xFFFFFF, HPfont, "NAME:%-20s", score[i].name.c_str());		//���O�`��
				DrawFormatStringToHandle(firstx + 450, firsty + i * interval, 0xFFFFFF, HPfont, "SCORE:%-10d", scores[i]);		//�X�R�A�`��
				break;
			}
		}
	}

	str = "�I�����j���[�ɖ߂�:Z�L�[";
	strLen = strlen(str);
	strWidth = GetDrawStringWidth(str, strLen);				//�����`��p
	DrawString((WIDTH - strWidth) / 2, 400, str, 0x00FFFF);

	//�E������
	if (InKeyTrigger(now_key, PAD_INPUT_RIGHT) && selectedstage < STAGENUM - 1) selectedstage++;
	if (InKeyTrigger(now_key, PAD_INPUT_LEFT) && selectedstage > 0) selectedstage--;

	//before,now,next�����L���O�Ɉړ��̕`��
	strWidth = GetDrawFormatStringWidth("now:%s", stagename[selectedstage].c_str());				//�����`��p
	DrawFormatString((WIDTH - strWidth) / 2, 430, 0xFFFFFF, "now:%s", stagename[selectedstage].c_str());

	if (selectedstage > 0)
		DrawFormatString(20, 430, 0xffffff, "��before:%s", stagename[selectedstage - 1].c_str());
	if (selectedstage < STAGENUM - 1)
		DrawFormatString(450, 430, 0xffffff, "��next:%s", stagename[selectedstage + 1].c_str());

	//�L�[����
	if (InKeyTrigger(now_key, PAD_INPUT_1)) {
		window = GAMESELECTWINDOW;
	}
}

void RankingWrite(string name, rankdata rank) {
	//���o��
	string str;
	ifstream text(name);		//�e�L�X�g����

	//�f�[�^���ꎞ�I�ێ�
	string names[RECODE_NUM_MAX + 1] = {};
	int scores[RECODE_NUM_MAX + 1][5] = {};//�e�L�X�g�̕ۑ��`��:���O�A�c��^�C���A�G�̌��j���A�c��HP�A�R�C��,����

	//���l���邩���J�E���g
	int count = 0;

	//��s���ǂݎ��
	while (getline(text, str) && count < RECODE_NUM_MAX)
	{
		//�e�L�X�g�̕ۑ��`��:���O�A�c��^�C���A�G�̌��j���A�c��HP�A�R�C��,����
		string tmp;
		istringstream stream(str);
		//���O�����o��
		getline(stream, tmp, ',');
		names[count] = tmp;
		//�X�R�A�����o��(4�̗v�f)
		for (int i = 0; i < 4; i++) {
			getline(stream, tmp, ',');
			scores[count][i] = stoi(tmp);
		}
		count++;
	}

	//�V�����ǉ�����X�R�A��z��ɒǉ�
	names[count] = rank.name;
	scores[count][0] = rank.limit;
	scores[count][1] = rank.killedene;
	scores[count][2] = rank.hp;
	scores[count][3] = rank.coin;

	//�����v�Z
	for (int i = 0; i <= count; i++) {
		scores[i][4] = SCORE_LIMIT * scores[i][0] + SCORE_ENEMY * scores[i][1] + SCORE_HP * scores[i][2] + SCORE_COIN * scores[i][3];
	}
	//�\�[�g i���Oj�����
	for (int i = 0; i < count; i++) {
		for (int j = i + 1; j <= count; j++) {
			if (scores[i][4] < scores[j][4]) {
				int d_score[5];
				//�z��̒��g���ہX�R�s�[
				for (int k = 0; k < 5; k++) {
					d_score[k] = scores[i][k];
				}
				//���O����ւ�
				string d_name = names[i];
				names[i] = names[j];
				names[j] = d_name;
				//�z�����ւ�
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
	//�e�L�X�g�ɏo��(�E�C���X�Z�L�����e�B�[�ɂ���ď������߂Ȃ��Ȃ�̂Œ���)
	ofstream output(name, ios_base::trunc);

	//��������
	for (int i = 0; i <= count; i++)
		output << names[i] << ',' << scores[i][0] << ',' << scores[i][1] << ',' << scores[i][2] << ',' << scores[i][3] << ',' << std::endl;

	output.close();
}

rankdata* RankingRead(string name, int *index) {
	//���o��
	string str;
	ifstream text(name);		//�e�L�X�g����

								//�f�[�^���ꎞ�I�ێ�
	string names[RECODE_NUM_MAX] = {};
	int scores[RECODE_NUM_MAX][5] = {};//�e�L�X�g�̕ۑ��`��:���O�A�c��^�C���A�G�̌��j���A�c��HP�A�R�C��,����

										   //���l���邩���J�E���g
	int count = 0;

	//��s���ǂݎ��
	while (getline(text, str) && count < RECODE_NUM_MAX)
	{
		//�e�L�X�g�̕ۑ��`��:���O�A�c��^�C���A�G�̌��j���A�c��HP�A�R�C��,����
		string tmp;
		istringstream stream(str);
		//���O�����o��
		getline(stream, tmp, ',');
		names[count] = tmp;
		//�X�R�A�����o��(4�̗v�f)
		for (int i = 0; i < 4; i++) {
			getline(stream, tmp, ',');
			scores[count][i] = stoi(tmp);
		}
		count++;
	}

	//�����v�Z
	for (int i = 0; i < count; i++) {
		scores[i][4] = SCORE_LIMIT * scores[i][0] + SCORE_ENEMY * scores[i][1] + SCORE_HP * scores[i][2] + SCORE_COIN * scores[i][3];
	}
	//�\�[�g i���Oj�����
	for (int i = 0; i < count - 1; i++) {
		for (int j = i + 1; j < count; j++) {
			if (scores[i][4] < scores[j][4]) {
				int d_score[5];
				//�z��̒��g���ہX�R�s�[
				for (int k = 0; k < 5; k++) {
					d_score[k] = scores[i][k];
				}
				//���O����ւ�
				string d_name = names[i];
				names[i] = names[j];
				names[j] = d_name;
				//�z�����ւ�
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

	//�����L���O�f�[�^�z��ɓ����
	static rankdata rank[RECODE_NUM_MAX];

	for (int i = 0; i < count; i++) {
		rank[i].name = names[i];
		rank[i].limit = scores[i][0];
		rank[i].killedene = scores[i][1];
		rank[i].hp = scores[i][2];
		rank[i].coin = scores[i][3];
	}

	//�v�f����n���Ă�����
	*index = count;
	return rank;
}

void CreateStage1_1() {
	//stage.usingP->x = 5;
	//stage.usingP->y = 10;
	stage.limit = TIME_STAGE1_1;

	Map firstMap;

	//�}�b�v�̏����Z�b�g
	//�}�b�v�̑傫����ύX
	firstMap.setNum(10 * firstMap.getNumX(), firstMap.getNumY());

	//�n�ʐ���
	for (int i = 0; i < firstMap.getNumX(); i++)
		firstMap.m_map[i][firstMap.getNumY() - 1] = 1;

	//map�쐬
	//�����`�@1*5
	firstMap.m_map[6][5] = 1;
	firstMap.m_map[6][6] = 1;
	firstMap.m_map[6][7] = 1;
	firstMap.m_map[6][8] = 1;
	firstMap.m_map[6][9] = 1;

	//s�̎�
	firstMap.m_map[4][10] = 1;
	firstMap.m_map[3][10] = 1;
	firstMap.m_map[3][11] = 1;
	firstMap.m_map[2][11] = 1;
	//2�̎�
	firstMap.m_map[8][10] = 1;
	firstMap.m_map[9][10] = 1;
	firstMap.m_map[9][11] = 1;
	firstMap.m_map[10][11] = 1;

	//�����` 2*2
	firstMap.m_map[17][11] = BLOCK_WOOD;
	firstMap.m_map[17][10] = BLOCK_ICE;
	firstMap.m_map[16][11] = BLOCK_STONE;
	firstMap.m_map[16][10] = GROUND;

	for (int i = 0; i < 5; i++) {
		firstMap.m_map[19 + i * 5][12] = 1;
		firstMap.m_map[19 + i * 5][13] = 1;
	}

	//�X�e�[�W�ɃZ�b�g
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
	//�o�O���W�i610,10�j,�T�C�Y�i30,40�j<-������
	new Turtle(610, 10);
	for(int i = 0; i< 1;i++)
		new WalkEnemy(730 + i*2, 10);

	//40000�̃t�@�C���[�{�[�������Ə������Ԃɍ���Ȃ��B10000�Ȃ炢����͂�
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

	//�}�b�v�̏����Z�b�g
	//�}�b�v�̑傫����ύX
	firstMap.setNum(firstMap.getNumX(), firstMap.getNumY());

	//�n�ʐ���
	for (int i = 0; i < firstMap.getNumX(); i++)
		firstMap.m_map[i][firstMap.getNumY() - 1] = BLOCK_STONE;

	//�c�_1*2
	//firstMap.m_map[6][12] = 1;
	//firstMap.m_map[6][13] = 1;

	firstMap.m_map[13][12] = 1;
	firstMap.m_map[13][13] = 1;

	firstMap.m_map[2][firstMap.getNumY() - 1] = 0;

	//�X�e�[�W�ɃZ�b�g
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
	//�w�i���Z�b�g
	for (int i = 0; i < ACCOUNTFORMAPPARTS; i++) {
		stage.mapparts[i] = stage1_1Back[i];
	}

	stage.limit = TIME_STAGE1_1R;

	Map firstMap;

	//�}�b�v�̏����Z�b�g
	//�}�b�v�̑傫����ύX
	firstMap.setNum(10 * firstMap.getNumX(), firstMap.getNumY());

	//�n�ʐ���
	for (int i = 0; i < firstMap.getNumX(); i++)
		firstMap.m_map[i][firstMap.getNumY() - 1] = 1;

	//�}�b�v�쐻
	//for (int i = 0; i < firstMap.getNumX(); i++)
	//	firstMap.m_map[i][0] = 1;		//debug �V��쐬

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

	//�}�b�v���H
	firstMap.m_map[168][14] = 0;
	firstMap.m_map[107][14] = 0;

	//�X�e�[�W�ɃZ�b�g
	*stage.usingM = firstMap;


	new Coin(545, 350);
	new Coin(609, 350);

	new Turtle(DOT * 10, DOT * 13); //debug
	//new Fish(DOT * 10, DOT * 13);	//debug
	new Crab(DOT * 7, DOT * 4);
	new Ship(DOT * 10, DOT * 4, 0);

	new SeaWeed(DOT * 20, DOT * 10, 3, 4);//debug
	new GardenEel(DOT * 30, DOT * 14);//debug
	new TurtleWithWing(DOT * 35, DOT * 10); //debug

	new Polarbear(DOT * 20, DOT * 3);
	for (int i = 0; i < 30; i++) {			//debug
		for (int j = 1; j < 14; j++) {
			new Sea(DOT *  i, DOT * j,4);
		}
	}
	for (int i = 30; i < 100; i++) {			//debug
		for (int j = 1; j < 14; j++) {
			new Sea(DOT * i, DOT * j, 4);
		}
	}

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
	//�w�i���Z�b�g
	for (int i = 0; i < ACCOUNTFORMAPPARTS; i++) {
		stage.mapparts[i] = stage1_2Back[i];
	}

	stage.limit = TIME_STAGE2_1R;

	stage.usingP->x = DOT * 2;
	stage.usingP->y = DOT * 13;

	Map firstMap;

	//�}�b�v�̏����Z�b�g
	//�}�b�v�̑傫����ύX
	firstMap.setNum(10 * firstMap.getNumX(), firstMap.getNumY());

	//�n�ʐ���
	for (int i = 0; i < firstMap.getNumX(); i++)
		firstMap.m_map[i][firstMap.getNumY() - 1] = BLOCK_STONE;

	//�X�e�[�W

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

	//firstMap.m_map[13][4] = BLOCK_STONE; //<- �Ƃ��u���b�N�̑���
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

	//�X�e�[�W�ɃZ�b�g
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
	//�w�i���Z�b�g
	for (int i = 0; i < ACCOUNTFORMAPPARTS; i++) {
		stage.mapparts[i] = stage1_3Back[i];
	}

	stage.usingP->x = DOT * 2;
	stage.usingP->y = DOT * 10;
	//stage.usingP->x = DOT * 256;
	//stage.usingP->y = DOT * 10;
	stage.limit = TIME_STAGE1_3R;

	Map firstMap;

	//�}�b�v�̏����Z�b�g
	//�}�b�v�̑傫����ύX
	firstMap.setNum(300, firstMap.getNumY());

	//�n�ʐ���
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

	//�X�e�[�W�ɃZ�b�g
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
	//�l�𕉂Ƃ��Ďg��(5�b�Ԃ̐���)
	stage.limit = 5000;

	//new Turtle(300, 10);
	//new Jump(300, 400);


}
