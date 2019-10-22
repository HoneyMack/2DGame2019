//�}�b�v�͔z��Ƃ��Ď���
#pragma once
#include "DxLib.h"
#define DEBUG			//�����蔻���`�悳�������Ȃ��Ƃ��̓R�����g�A�E�g



//stage�֌W
#define	TIME_STAGE1_1 500000 //�c�莞��(ms)
#define	TIME_STAGE2_1 500000 //�c�莞��(ms)
#define	TIME_STAGE1_1R 500000 //�c�莞��(ms)
#define	TIME_STAGE2_1R 500000 //�c�莞��(ms)
#define TIME_STAGE1_3R 500000


//�w�i�摜
#define MAPPARTS_X 1000	//�w�i�摜�̂Ȃ����@
#define ACCOUNTFORMAPPARTS 3//�w�i�摜�p�[�c�̑���

//score�֌W
#define SCORE_HP 4
#define SCORE_LIMIT 5
#define SCORE_ENEMY 10
#define SCORE_COIN 30
#define RECODE_NUM_MAX 18			//�ő�ۗL���R�[�h��

//dot size
#define DOT 32
//window size�@�i�h�b�g�Ŋ���؂��悤�ɂ���j
#define WIDTH 640
#define HEIGHT 480

//�������Z�̂��߂̂�����
#define FLOW 0.1
#define ZEROEXCEPTION 0.0001	//���鐔������ȏ㏬�����Ȃ�Ȃ��悤�ɂ���

//�d��(dot/sec)
#define GRAVITY 1500
#define MAX_VELOCITY 3000	//�I�[���x
#define PI 3.141592653589793

//�����X�N���[���̑��x(dot/s)
#define SCROLLSPEED 100


//�G�̃_���[�W�ʊ֌W
#define WALKENEMY_HITDAMAGE 5		//�Ԃ������Ƃ��̃_���[�W��
#define SHOOTLASER_HITDAMAGE 5			//���[�U�[�ɂԂ������Ƃ��̃_���[�W��
#define SHOOTENEMY_HITDAMAGE 5
#define BULLETTOWARDPLAYER_HITDAMAGE 7
#define FIREBALL_DAMAGE 10		//�t�@�C���[�{�[���ɂ��������Ƃ��̃_���[�W
#define FALLWALL_BIRDDAMAGE 6			//���ɂ��������Ƃ��̃_���[�W
#define FALLWALL_REDEXAMDAMAGE 10		//�ԓ_�ɂ��������Ƃ��̃_���[�W
#define TURTLE_HITDAMAGE 5
#define GHOST_HITDAMAGE 8					//�_���[�W
#define THORNBLOCK_HITDAMAGE 12
#define HANMER_HITDAMAGE 8
#define HANMERTHROW_DAMAGE 4
#define GARDENEEL_DAMAGE  4//�`���A�i�S�ɏՓ˂����Ƃ��̃_���[�W

//player move speed
#define HITPOINT 50		//�v���C���[��HP
#define ENEMYMATCHLESSTIME 1000	//�_���[�W���󂯂��Ƃ��̖��G����(ms)
#define MOVESPEED 200
#define GROUNDBOOSTSPEED 26		//�������ςȂ��ɂ��ړ��ʂ̑����x
#define AIRBOOSTSPEED 12			//�󒆂ł̉��X�s�[�h�����x
#define MAXBOOST 280		//�������ςȂ��ɂ�鑝���x�̏��
#define JUMPSPEED 200		//�W�����v�X�s�[�h
#define HIGHJUMPSPEED 550	//�ǉ��ł���n�C�W�����v�X�s�[�h��
#define CANHIGHJUMPTIME 205	//�n�C�W�����v�Œ��߂ł��鎞��(ms)


#define KILLHIGHJUMPTIME 100 //�G�𓥂񂾎�����n�C�W�����v���ł��鎞�Ԃ��K��(ms)
#define KILLHIGHJUMPLIMIT 125 //�G�𓥂񂾂��Ƃɂ��n�C�W�����v�Œ��߂ł��鎞��(ms)�𐧌�		������������ACANHIGHJUMPTIME��菬�����Ȃ��Ƃ����Ȃ�
#define KILLJUMP 380		//�G�����������Ƃ��̏�ւ̃W�����v��
#define ANIMETIONINTERVAL 400 //�摜�؂�ւ����x�ims�j


//walkenemy
#define WALKENEMY_MOVEWIDTH 160		//�ړ���(dot)
#define WALKENEMY_SIZEX 24			//�����蔻��̑傫��(dot)
#define WALKENEMY_SIZEY 28			//�����蔻��̑傫��(dot)
#define WALKENEMY_SPEED 100			//walk�X�s�[�h(dot/s)
#define WALKENEMY_KILLCOLLIDERY  5	//��ɂ������Ă��邩

//ShootLaser�Ɋւ����`
#define SHOOTLASER_POSX 595				//���[�U�[���ˑ��u�̉�ʏ��X���W
#define SHOOTLASER_SHOTTIMES 22			//���񃌁[�U�[��ł�
#define SHOOTLASER_LASERINTERVAL 1400	//���[�U�[�𔭎˂���Ԋu(ms)
#define SHOOTLASER_MOVEINTERVAL 20		//��񃌁[�U�[��ł�����Ƀf�B�X�y���T�[�����ɂǂꂾ���ړ����邩(dot)
#define SHOOTLASER_SHOOTWAITTIME 700			//�ł����̂��A�ǂꂮ�炢�҂�(ms)
#define SHOOTLASER_WAITTIME 300			//�f�B�X�y���T�[���ړ��������̂��A�ǂꂮ�炢�҂�(ms)
#define SHOOTLASER_LASERSPEED 1000		//���[�U�[�̔�ԑ���(dot/s)

//FlashBlock
#define FLASHBLOCK_SIZEX 32				//�����蔻��̑傫��
#define FLASHBLOCK_SIZEY 32
#define FLASHBLOCK_FLASHTIME 1000		//�����Ȃ��Ȃ鎞��(ms)

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
#define SHOOTENEMY_TIMEBFOREFIRING 1000 //��ʂɓ����Ă��狅�𔭎˂��n�߂�܂ł̎���

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
#define FIREBAR_BALL_RADIUS 6  //firebar��fireball�̔��a
#define FIREBAR_NUMBER 4  //firebar��bar�̖{��
#define FIREBAR_LENGTH 5  //firebar��fireball�̌�

//FireBall
#define FIREBALL_ANGVEL 90.0*(PI/180.0)  //firebar�̊p���x

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
#define JUMP_LOWJUMP 350				//�΂˂ɂ��W�����v��
#define JUMP_HIGHJUMP  470				//�X�y�[�X�������Ă������̃W�����v��
#define JUMP_HIGHJUMPLIMIT 170			//�ō��n�C�W�����v�̒���	������������ACANHIGHJUMPTIME��菬�����Ȃ��Ƃ����Ȃ�
#define JUMP_CANHIGHJUMP 100			//HIGHJUMP�\�Ȕ͈�
#define JUMP_ANGULARVELOCITY 2*PI *1.8	//(rad/s)
#define JUMP_DECREMENT 1.00 //�΂˂̐U���̑�����
#define JUMP_EXTENSION 14 //(dot)
//#define JUMP_LOW_EXTENSION 20 //(dot)
//#define JUMP_HIGH_EXTENSION 50 //(dot)


//fallwall
#define FALLWALL_WAITFORDOWN 1000		//�ԓ_�������Ă��牺�~�҂�(ms)
#define FALLWALL_WAITFORUP	1000		//�㏸�܂��i�����j
//#define FALLWALL_BIRDFALLINGTIME 3000	//�����ԓ_���Ƃ�̂ɗv���鎞�ԁi�����j(MS)
//#define FALLWALL_BIRDRISINGTIME 3000	//�����ԓ_���Ƃ����̂��́A�o��̂ɗv���鎞��(MS)
#define FALLWALL_BIRDSPEED 200			//���̈ړ��X�s�[�h
#define FALLWALL_FALLSPEED 300//���ė������x(dot/s)

#define FALLWALL_ANIMATIONTURNTIME 200	//�p�^�p�^�̊Ԋu(MS)

//Coin
#define COIN_MATCHLESSTIME 1000		//(ms)
#define COIN_REVERSETIME 1000		//���]������Ԋu(ms)

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
#define TURTLE_TURNTIME 60 //��]�̉摜��R�}��\�����鎞�ԁims�j

//TurtleWithWing
#define TURTLEWITHWING_PERIODICTIME 5000 //�������̂ɗv���鎞��(ms)
#define TURTLEWITHWING_MOVEMENT 35 //�U��(dot)


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
#define THROWING_ANGLE_MAX PI/180 * 85		//�ő�p
#define THROWING_ANGLE_MIN PI/180 * 10		//�ŏ��p

#define HANMERTHROW_TURNTIME 200 //�A�j���[�V�������؂�ւ�鎞��

//Hanmer
//#define HANMER_SIZEX 10
//#define HANMER_SIZEY 10
#define HANMER_RADIUS 5
#define HANMER_ANGVEL PI/180 * 360 //20��/s

//ghost
#define GHOST_DISPLAYSIZEX 56
#define GHOST_DISPLAYSIZEY 36
#define GHOST_CHARASIZEX 28
#define GHOST_CHARASIZEY 30					
#define GHOST_MOVESPEED 20					//�v���C���[�ɐi�ޑ���
#define GHOST_ANGVEL 90.0*(PI/180.0)		//�p�U����
#define GHOST_MOVEWIDTH 60		//�U���̗h�ꕝ
#define GHOST_TRANSPARENCY 50  //�ǂ̂��炢�����ɂ��邩0:�����@250:�s����
#define GHOST_TURNTIME 300	//�t���b�V����������Ĉ������ނ܂�

//Polarbear
#define PBSIZEX 32
#define PBSIZEY 32
#define PB_SPEED 100
#define PB_MOVEWIDTH 160
#define PB_HITDAMAGE 5

//thornblock
#define THORNBLOCK_SIZEX 28
#define THORNBLOCK_SIZEY 28
#define THORNBLOCK_TRANSPARENCY 10

//fence
#define FENCE_SIZE 32  //�����`�Œ�`
#define FENCE_PLAYERMOVESPEED 100 //�v���C���[�̈ړ����x�w��
#define FENCE_LOWJUMPSPEED 200		//LOW�W�����v�̍����w��

//Ship
#define SHIP_SIZEX 96
#define SHIP_SIZEY 64
#define SHIP_MOVESPEED 100


//SeaWeed(�C��)
#define SEAWEED_SIZEX 32 //�C���̉摜�̑傫��
#define SEAWEED_SIZEY 32 //�C���̉摜�̑傫��
#define SEAWEED_TOTALPICTURES 5 //�摜�̑���
#define SEAWEED_SWITCHTIME 1000 //1�摜������̕\������(ms/�摜)

//GardenEel(�`���A�i�S)
#define GARDENEEL_SIZEX 10 //�`���A�i�S�̉摜�T�C�Y
#define GARDENEEL_SIZEY 32
#define GARDENEEL_HIDINGTIME 1000 //�y�ɉB��Ă���i������Ȃ��j����(ms)
#define GARDENEEL_RISINGTIME 500 //��ɏ㏸���Ă��鎞��(ms)
#define GARDENEEL_HOLDINGTIME 3000 //�㏸�������ĐL�тĂ����Ԃ̎���(ms)
#define GARDENEEL_FALLINGTIME 1000 //���ɉ��~���Ă��鎞��(ms)

//Sea(�C)
#define SEA_SIZEX 32
#define SEA_SIZEY 32
#define SEA_TRANSPARENCY 150	//���̓����x�w��
#define SEA_FIRSTDIVE_SPEED_DECAY 0.5	//���߂ĊC�ɓ��������̑��x�����i�����_�ȉ��j
#define SEA_GRAVITY 1200	//�C�̒��̏d��
//#define SEA_PLAYERMOVESPEED 70	//�����ł̈ړ����x
//#define SEA_BOOSTSPEED 14
#define SEA_MOVESPEED 100	
#define SEA_LOWJUMPSPEED 120
#define SEA_MAXVY 100	//�����ł̗������x�̍ő�l
#define SEA_WAVESPEEDX 30 //�g�ɂ���ăv���C���[�ɗ^�����鑬�x
#define SEA_WAVESPEEDDOWN 30
#define SEA_WAVESPEEDUP 50


//�`��T�C�Y(�z��̌�)
#define VIEW_WIDTH_INDEX	WIDTH/DOT
#define VIEW_HEIGHT_INDEX	HEIGHT/DOT

//�����蔻��p�̃t���O ����4�r�b�g�ŁA�ǂƂ̔���B
#define RIGHTTOP 0b0001
#define LEFTTOP 0b0010
#define RIGHTBOTTOM 0b0100
#define LEFTBOTTOM 0b1000
#define TOP 0b0011
#define BOTTOM 0b1100
#define RIGHT 0b0101
#define LEFT 0b1010

//�N���X�̑O���錾
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

 //�v���g�^�C�v�錾
bool InKeyTrigger(int key, int CheckKey);		//when key pressed, return true once    not while
bool CheckRectRect(Rect rect1, Rect rect2);		//��̒����`���d�Ȃ��Ă��邩
bool CheckPointRect( double vecX, double vecY ,Rect rect);	//rect�ɓ_vector���܂܂�Ă��邩
bool CheckCircleCircle(Circle cir1,Circle cir2);//��̉~���d�Ȃ��Ă��邩
bool CheckPointCircle(double vecX,double vecY,Circle cir);	//����_(vecX,vecY)��,�~�Ɋ܂܂�Ă��邩
bool CheckCircleRect(Circle cir, Rect rect);	//�~�ƒ����`���d�Ȃ��Ă��邩
int HitFaceRectRect(Rect rect1, Rect rect2);	//��̒����`�ŏd�Ȃ��Ă��镔����Ԃ�(rect2����{�Ƃ��ď㉺���E)
int HitFaceCircleRect(Circle cir, Rect rect);	//Circle�ƒ����`�ŏd�Ȃ��Ă��镔����Ԃ�(rect����{�Ƃ��ď㉺���E)(cir��rect�Ƃ݂ď���)
int HitFaceCircleCircle(Circle cir1,Circle cir2);	//�Q�̉~�ŏd�Ȃ��Ă��镔����Ԃ�(cir2����{�Ƃ��ď㉺���E)(cir��rect�Ƃ݂ď���)
Rect ChangeCircleToRect(Circle cir);	//Circle��������ƈ͂ޒ����`���쐬




//�E�B���h�E�؂�ւ��p
enum {
	STARTWINDOW, GAMESELECTWINDOW, GAMEPLAYWINDOW,GAMEPAUSEWINDOW, GAMEOVERWINDOW,GAMECLEARWINDOW,RANKINGWINDOW
};
//�}�b�v�摜�p
enum {
	GROUND = 1, TOGE, BLOCK_STONE, BLOCK_ICE, BLOCK_WOOD, MAP_MAX
};
//�摜�Ǘ��p
enum {
	PLAYER,WALKENEMY
};
//�v���C���[�h�ؑ�
enum {
	CROSSKEYANDJUMP,FORCEHORIZONTALSCROLL
};

//�v���C���[�摜�؂�ւ��p
enum {
	STAND,RUN,JUMP,ROPE,FENCE
};


//�T�E���h�Ǘ��p
enum {
	SOUND_FLASHBLOCK, SOUND_PLAYERJUMP,SOUND_PLAYERSKILL,SOUND_PLAYERJUMPMINI,SOUND_LASERSHOT,SOUND_DAMAGE,SOUND_ENEMYSHOOT,SOUND_JUMPSPRING,SOUND_JUMPSPRINGMINI,SOUND_ROPEJUMP,SOUND_ENEMYTREAD,SOUND_COIN,SOUND_STAGESTART,SOUND_STAGE1_1,SOUND_STAGE1_2,SOUND_STAGE1_3,SOUND_MAX
};
