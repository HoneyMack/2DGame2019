<<<<<<< HEAD
//ï¿½}ï¿½bï¿½vï¿½Í”zï¿½ï¿½Æ‚ï¿½ï¿½ÄŽï¿½ï¿½ï¿½
#pragma once
#include "DxLib.h"
#define DEBUG			//ï¿½ï¿½ï¿½ï¿½ï¿½è”»ï¿½ï¿½ï¿½`ï¿½æ‚³ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½È‚ï¿½ï¿½Æ‚ï¿½ï¿½ÍƒRï¿½ï¿½ï¿½ï¿½ï¿½gï¿½Aï¿½Eï¿½g



//stageï¿½ÖŒW
#define	TIME_STAGE1_1 500000 //ï¿½cï¿½èŽžï¿½ï¿½(ms)
#define	TIME_STAGE2_1 500000 //ï¿½cï¿½èŽžï¿½ï¿½(ms)
#define	TIME_STAGE1_1R 500000 //ï¿½cï¿½èŽžï¿½ï¿½(ms)
#define	TIME_STAGE2_1R 500000 //ï¿½cï¿½èŽžï¿½ï¿½(ms)
#define TIME_STAGE1_3R 500000


//ï¿½wï¿½iï¿½æ‘œ
#define MAPPARTS_X 1000	//ï¿½wï¿½iï¿½æ‘œï¿½Ì‚È‚ï¿½ï¿½ï¿½ï¿½@
#define ACCOUNTFORMAPPARTS 3//ï¿½wï¿½iï¿½æ‘œï¿½pï¿½[ï¿½cï¿½Ì‘ï¿½ï¿½ï¿½

//scoreï¿½ÖŒW
#define SCORE_HP 4
#define SCORE_LIMIT 5
#define SCORE_ENEMY 10
#define SCORE_COIN 30
#define RECODE_NUM_MAX 18			//ï¿½Å‘ï¿½Û—Lï¿½ï¿½ï¿½Rï¿½[ï¿½hï¿½ï¿½

//dot size
#define DOT 32
//window sizeï¿½@ï¿½iï¿½hï¿½bï¿½gï¿½ÅŠï¿½ï¿½ï¿½Ø‚ï¿½ï¿½æ‚¤ï¿½É‚ï¿½ï¿½ï¿½j
#define WIDTH 640
#define HEIGHT 480

//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Zï¿½Ì‚ï¿½ï¿½ß‚Ì‚ï¿½ï¿½ï¿½ï¿½ï¿½
#define FLOW 0.1
#define ZEROEXCEPTION 0.0001	//ï¿½ï¿½ï¿½é”ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Èã¬ï¿½ï¿½ï¿½ï¿½ï¿½È‚ï¿½È‚ï¿½ï¿½æ‚¤ï¿½É‚ï¿½ï¿½ï¿½

//ï¿½dï¿½ï¿½(dot/sec)
#define GRAVITY 1500
#define MAX_VELOCITY 3000	//ï¿½Iï¿½[ï¿½ï¿½ï¿½x
#define PI 3.141592653589793

//ï¿½ï¿½ï¿½ï¿½ï¿½Xï¿½Nï¿½ï¿½ï¿½[ï¿½ï¿½ï¿½Ì‘ï¿½ï¿½x(dot/s)
#define SCROLLSPEED 100


//ï¿½Gï¿½Ìƒ_ï¿½ï¿½ï¿½[ï¿½Wï¿½ÊŠÖŒW
#define WALKENEMY_HITDAMAGE 5		//ï¿½Ô‚Â‚ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ‚ï¿½ï¿½Ìƒ_ï¿½ï¿½ï¿½[ï¿½Wï¿½ï¿½
#define SHOOTLASER_HITDAMAGE 5			//ï¿½ï¿½ï¿½[ï¿½Uï¿½[ï¿½É‚Ô‚Â‚ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ‚ï¿½ï¿½Ìƒ_ï¿½ï¿½ï¿½[ï¿½Wï¿½ï¿½
#define SHOOTENEMY_HITDAMAGE 5
#define BULLETTOWARDPLAYER_HITDAMAGE 7
#define FIREBALL_DAMAGE 10		//ï¿½tï¿½@ï¿½Cï¿½ï¿½ï¿½[ï¿½{ï¿½[ï¿½ï¿½ï¿½É‚ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ‚ï¿½ï¿½Ìƒ_ï¿½ï¿½ï¿½[ï¿½W
#define FALLWALL_BIRDDAMAGE 6			//ï¿½ï¿½ï¿½É‚ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ‚ï¿½ï¿½Ìƒ_ï¿½ï¿½ï¿½[ï¿½W
#define FALLWALL_REDEXAMDAMAGE 10		//ï¿½Ô“_ï¿½É‚ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ‚ï¿½ï¿½Ìƒ_ï¿½ï¿½ï¿½[ï¿½W
#define TURTLE_HITDAMAGE 5
#define GHOST_HITDAMAGE 8					//ï¿½_ï¿½ï¿½ï¿½[ï¿½W
#define THORNBLOCK_HITDAMAGE 12
#define HANMER_HITDAMAGE 8
#define HANMERTHROW_DAMAGE 4
#define GARDENEEL_DAMAGE  4//ï¿½`ï¿½ï¿½ï¿½Aï¿½iï¿½Sï¿½ÉÕ“Ë‚ï¿½ï¿½ï¿½ï¿½Æ‚ï¿½ï¿½Ìƒ_ï¿½ï¿½ï¿½[ï¿½W

//player move speed
#define HITPOINT 50		//ï¿½vï¿½ï¿½ï¿½Cï¿½ï¿½ï¿½[ï¿½ï¿½HP
#define ENEMYMATCHLESSTIME 1000	//ï¿½_ï¿½ï¿½ï¿½[ï¿½Wï¿½ï¿½ï¿½ó‚¯‚ï¿½ï¿½Æ‚ï¿½ï¿½Ì–ï¿½ï¿½Gï¿½ï¿½ï¿½ï¿½(ms)
#define MOVESPEED 200
#define GROUNDBOOSTSPEED 26		//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ï‚È‚ï¿½ï¿½É‚ï¿½ï¿½Ú“ï¿½ï¿½Ê‚Ì‘ï¿½ï¿½ï¿½ï¿½x
#define AIRBOOSTSPEED 12			//ï¿½ó’†‚Å‚Ì‰ï¿½ï¿½Xï¿½sï¿½[ï¿½hï¿½ï¿½ï¿½ï¿½ï¿½x
#define MAXBOOST 280		//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ï‚È‚ï¿½ï¿½É‚ï¿½é‘ï¿½ï¿½ï¿½xï¿½Ìï¿½ï¿½
#define JUMPSPEED 200		//ï¿½Wï¿½ï¿½ï¿½ï¿½ï¿½vï¿½Xï¿½sï¿½[ï¿½h
#define HIGHJUMPSPEED 550	//ï¿½Ç‰ï¿½ï¿½Å‚ï¿½ï¿½ï¿½nï¿½Cï¿½Wï¿½ï¿½ï¿½ï¿½ï¿½vï¿½Xï¿½sï¿½[ï¿½hï¿½ï¿½
#define CANHIGHJUMPTIME 205	//ï¿½nï¿½Cï¿½Wï¿½ï¿½ï¿½ï¿½ï¿½vï¿½Å’ï¿½ï¿½ß‚Å‚ï¿½ï¿½éŽžï¿½ï¿½(ms)


#define KILLHIGHJUMPTIME 100 //ï¿½Gï¿½ð“¥‚ñ‚¾Žï¿½ï¿½ï¿½ï¿½ï¿½nï¿½Cï¿½Wï¿½ï¿½ï¿½ï¿½ï¿½vï¿½ï¿½ï¿½Å‚ï¿½ï¿½éŽžï¿½Ô‚ï¿½ï¿½Kï¿½ï¿½(ms)
#define KILLHIGHJUMPLIMIT 125 //ï¿½Gï¿½ð“¥‚ñ‚¾‚ï¿½ï¿½Æ‚É‚ï¿½ï¿½nï¿½Cï¿½Wï¿½ï¿½ï¿½ï¿½ï¿½vï¿½Å’ï¿½ï¿½ß‚Å‚ï¿½ï¿½éŽžï¿½ï¿½(ms)ï¿½ð§Œï¿½		ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ACANHIGHJUMPTIMEï¿½ï¿½è¬ï¿½ï¿½ï¿½ï¿½ï¿½È‚ï¿½ï¿½Æ‚ï¿½ï¿½ï¿½ï¿½È‚ï¿½
#define KILLJUMP 380		//ï¿½Gï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ‚ï¿½ï¿½Ìï¿½Ö‚ÌƒWï¿½ï¿½ï¿½ï¿½ï¿½vï¿½ï¿½
#define ANIMETIONINTERVAL 400 //ï¿½æ‘œï¿½Ø‚ï¿½Ö‚ï¿½ï¿½ï¿½ï¿½xï¿½imsï¿½j


//walkenemy
#define WALKENEMY_MOVEWIDTH 160		//ï¿½Ú“ï¿½ï¿½ï¿½(dot)
#define WALKENEMY_SIZEX 24			//ï¿½ï¿½ï¿½ï¿½ï¿½è”»ï¿½ï¿½Ì‘å‚«ï¿½ï¿½(dot)
#define WALKENEMY_SIZEY 28			//ï¿½ï¿½ï¿½ï¿½ï¿½è”»ï¿½ï¿½Ì‘å‚«ï¿½ï¿½(dot)
#define WALKENEMY_SPEED 100			//walkï¿½Xï¿½sï¿½[ï¿½h(dot/s)
#define WALKENEMY_KILLCOLLIDERY  5	//ï¿½ï¿½É‚ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ä‚ï¿½ï¿½é‚©

//ShootLaserï¿½ÉŠÖ‚ï¿½ï¿½ï¿½ï¿½`
#define SHOOTLASER_POSX 595				//ï¿½ï¿½ï¿½[ï¿½Uï¿½[ï¿½ï¿½ï¿½Ë‘ï¿½ï¿½uï¿½Ì‰ï¿½Êï¿½ï¿½Xï¿½ï¿½ï¿½W
#define SHOOTLASER_SHOTTIMES 22			//ï¿½ï¿½ï¿½ñƒŒ[ï¿½Uï¿½[ï¿½ï¿½Å‚Â‚ï¿½
#define SHOOTLASER_LASERINTERVAL 1400	//ï¿½ï¿½ï¿½[ï¿½Uï¿½[ï¿½ð”­ŽË‚ï¿½ï¿½ï¿½ÔŠu(ms)
#define SHOOTLASER_MOVEINTERVAL 20		//ï¿½ï¿½ñƒŒ[ï¿½Uï¿½[ï¿½ï¿½Å‚ï¿½ï¿½ï¿½ï¿½ï¿½Éƒfï¿½Bï¿½Xï¿½yï¿½ï¿½ï¿½Tï¿½[ï¿½ï¿½ï¿½ï¿½ï¿½É‚Ç‚ê‚¾ï¿½ï¿½ï¿½Ú“ï¿½ï¿½ï¿½ï¿½é‚©(dot)
#define SHOOTLASER_SHOOTWAITTIME 700			//ï¿½Å‚ï¿½ï¿½ï¿½ï¿½Ì‚ï¿½ï¿½Aï¿½Ç‚ê‚®ï¿½ç‚¢ï¿½Ò‚Â‚ï¿½(ms)
#define SHOOTLASER_WAITTIME 300			//ï¿½fï¿½Bï¿½Xï¿½yï¿½ï¿½ï¿½Tï¿½[ï¿½ï¿½ï¿½Ú“ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ì‚ï¿½ï¿½Aï¿½Ç‚ê‚®ï¿½ç‚¢ï¿½Ò‚Â‚ï¿½(ms)
#define SHOOTLASER_LASERSPEED 1000		//ï¿½ï¿½ï¿½[ï¿½Uï¿½[ï¿½Ì”ï¿½Ô‘ï¿½ï¿½ï¿½(dot/s)

//FlashBlock
#define FLASHBLOCK_SIZEX 32				//ï¿½ï¿½ï¿½ï¿½ï¿½è”»ï¿½ï¿½Ì‘å‚«ï¿½ï¿½
#define FLASHBLOCK_SIZEY 32
#define FLASHBLOCK_FLASHTIME 1000		//ï¿½ï¿½ï¿½ï¿½ï¿½È‚ï¿½ï¿½È‚éŽžï¿½ï¿½(ms)

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
#define SHOOTENEMY_TIMEBFOREFIRING 1000 //ï¿½ï¿½Ê‚É“ï¿½ï¿½ï¿½ï¿½Ä‚ï¿½ï¿½ç‹…ï¿½ð”­ŽË‚ï¿½ï¿½nï¿½ß‚ï¿½Ü‚Å‚ÌŽï¿½ï¿½ï¿½

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
#define FIREBAR_BALL_RADIUS 6  //firebarï¿½ï¿½fireballï¿½Ì”ï¿½ï¿½a
#define FIREBAR_NUMBER 4  //firebarï¿½ï¿½barï¿½Ì–{ï¿½ï¿½
#define FIREBAR_LENGTH 5  //firebarï¿½ï¿½fireballï¿½ÌŒÂï¿½

//FireBall
#define FIREBALL_ANGVEL 90.0*(PI/180.0)  //firebarï¿½ÌŠpï¿½ï¿½ï¿½x

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
#define JUMP_LOWJUMP 350				//ï¿½Î‚Ë‚É‚ï¿½ï¿½Wï¿½ï¿½ï¿½ï¿½ï¿½vï¿½ï¿½
#define JUMP_HIGHJUMP  470				//ï¿½Xï¿½yï¿½[ï¿½Xï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ä‚ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ÌƒWï¿½ï¿½ï¿½ï¿½ï¿½vï¿½ï¿½
#define JUMP_HIGHJUMPLIMIT 170			//ï¿½Åï¿½ï¿½nï¿½Cï¿½Wï¿½ï¿½ï¿½ï¿½ï¿½vï¿½Ì’ï¿½ï¿½ï¿½	ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ACANHIGHJUMPTIMEï¿½ï¿½è¬ï¿½ï¿½ï¿½ï¿½ï¿½È‚ï¿½ï¿½Æ‚ï¿½ï¿½ï¿½ï¿½È‚ï¿½
#define JUMP_CANHIGHJUMP 100			//HIGHJUMPï¿½Â”\ï¿½È”Íˆï¿½
#define JUMP_ANGULARVELOCITY 2*PI *1.8	//(rad/s)
#define JUMP_DECREMENT 1.00 //ï¿½Î‚Ë‚ÌUï¿½ï¿½ï¿½Ì‘ï¿½ï¿½ï¿½ï¿½ï¿½
#define JUMP_EXTENSION 14 //(dot)
//#define JUMP_LOW_EXTENSION 20 //(dot)
//#define JUMP_HIGH_EXTENSION 50 //(dot)


//fallwall
#define FALLWALL_WAITFORDOWN 1000		//ï¿½Ô“_ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ä‚ï¿½ï¿½ç‰ºï¿½~ï¿½Ò‚ï¿½(ms)
#define FALLWALL_WAITFORUP	1000		//ï¿½ã¸ï¿½Ü‚ï¿½ï¿½iï¿½ï¿½ï¿½ï¿½ï¿½j
//#define FALLWALL_BIRDFALLINGTIME 3000	//ï¿½ï¿½ï¿½ï¿½ï¿½Ô“_ï¿½ï¿½ï¿½Æ‚ï¿½Ì‚É—vï¿½ï¿½ï¿½éŽžï¿½Ôiï¿½ï¿½ï¿½ï¿½ï¿½j(MS)
//#define FALLWALL_BIRDRISINGTIME 3000	//ï¿½ï¿½ï¿½ï¿½ï¿½Ô“_ï¿½ï¿½ï¿½Æ‚ï¿½ï¿½ï¿½ï¿½Ì‚ï¿½ï¿½ÌAï¿½oï¿½ï¿½Ì‚É—vï¿½ï¿½ï¿½éŽžï¿½ï¿½(MS)
#define FALLWALL_BIRDSPEED 200			//ï¿½ï¿½ï¿½ÌˆÚ“ï¿½ï¿½Xï¿½sï¿½[ï¿½h
#define FALLWALL_FALLSPEED 300//ï¿½ï¿½ï¿½Ä—ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½x(dot/s)

#define FALLWALL_ANIMATIONTURNTIME 200	//ï¿½pï¿½^ï¿½pï¿½^ï¿½ÌŠÔŠu(MS)

//Coin
#define COIN_MATCHLESSTIME 1000		//(ms)
#define COIN_REVERSETIME 1000		//ï¿½ï¿½ï¿½]ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ÔŠu(ms)

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
#define TURTLE_TURNTIME 60 //ï¿½ï¿½]ï¿½Ì‰æ‘œï¿½ï¿½Rï¿½}ï¿½ï¿½\ï¿½ï¿½ï¿½ï¿½ï¿½éŽžï¿½Ôimsï¿½j

//TurtleWithWing
#define TURTLEWITHWING_PERIODICTIME 5000 //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ì‚É—vï¿½ï¿½ï¿½éŽžï¿½ï¿½(ms)
#define TURTLEWITHWING_MOVEMENT 35 //ï¿½Uï¿½ï¿½(dot)


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
#define THROWING_ANGLE_MAX PI/180 * 85		//ï¿½Å‘ï¿½p
#define THROWING_ANGLE_MIN PI/180 * 10		//ï¿½Åï¿½ï¿½p

#define HANMERTHROW_TURNTIME 200 //ï¿½Aï¿½jï¿½ï¿½ï¿½[ï¿½Vï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ø‚ï¿½Ö‚ï¿½éŽžï¿½ï¿½

//Hanmer
//#define HANMER_SIZEX 10
//#define HANMER_SIZEY 10
#define HANMER_RADIUS 5
#define HANMER_ANGVEL PI/180 * 360 //20ï¿½ï¿½/s

//ghost
#define GHOST_DISPLAYSIZEX 56
#define GHOST_DISPLAYSIZEY 36
#define GHOST_CHARASIZEX 28
#define GHOST_CHARASIZEY 30					
#define GHOST_MOVESPEED 20					//ï¿½vï¿½ï¿½ï¿½Cï¿½ï¿½ï¿½[ï¿½Éiï¿½Þ‘ï¿½ï¿½ï¿½
#define GHOST_ANGVEL 90.0*(PI/180.0)		//ï¿½pï¿½Uï¿½ï¿½ï¿½ï¿½
#define GHOST_MOVEWIDTH 60		//ï¿½Uï¿½ï¿½ï¿½Ì—hï¿½ê•
#define GHOST_TRANSPARENCY 50  //ï¿½Ç‚Ì‚ï¿½ï¿½ç‚¢ï¿½ï¿½ï¿½ï¿½ï¿½É‚ï¿½ï¿½é‚©0:ï¿½ï¿½ï¿½ï¿½ï¿½@250:ï¿½sï¿½ï¿½ï¿½ï¿½
#define GHOST_TURNTIME 300	//ï¿½tï¿½ï¿½ï¿½bï¿½Vï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Äˆï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Þ‚Ü‚ï¿½

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
#define FENCE_SIZE 32  //ï¿½ï¿½ï¿½ï¿½ï¿½`ï¿½Å’ï¿½`
#define FENCE_PLAYERMOVESPEED 100 //ï¿½vï¿½ï¿½ï¿½Cï¿½ï¿½ï¿½[ï¿½ÌˆÚ“ï¿½ï¿½ï¿½ï¿½xï¿½wï¿½ï¿½
#define FENCE_LOWJUMPSPEED 200		//LOWï¿½Wï¿½ï¿½ï¿½ï¿½ï¿½vï¿½Ìï¿½ï¿½ï¿½ï¿½wï¿½ï¿½

//Ship
#define SHIP_SIZEX 96
#define SHIP_SIZEY 64
#define SHIP_MOVESPEED 100


//SeaWeed(ï¿½Cï¿½ï¿½)
#define SEAWEED_SIZEX 32 //ï¿½Cï¿½ï¿½ï¿½Ì‰æ‘œï¿½Ì‘å‚«ï¿½ï¿½
#define SEAWEED_SIZEY 32 //ï¿½Cï¿½ï¿½ï¿½Ì‰æ‘œï¿½Ì‘å‚«ï¿½ï¿½
#define SEAWEED_TOTALPICTURES 5 //ï¿½æ‘œï¿½Ì‘ï¿½ï¿½ï¿½
#define SEAWEED_SWITCHTIME 1000 //1ï¿½æ‘œï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ì•\ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½(ms/ï¿½æ‘œ)

//GardenEel(ï¿½`ï¿½ï¿½ï¿½Aï¿½iï¿½S)
#define GARDENEEL_SIZEX 10 //ï¿½`ï¿½ï¿½ï¿½Aï¿½iï¿½Sï¿½Ì‰æ‘œï¿½Tï¿½Cï¿½Y
#define GARDENEEL_SIZEY 32
#define GARDENEEL_HIDINGTIME 1000 //ï¿½yï¿½É‰Bï¿½ï¿½Ä‚ï¿½ï¿½ï¿½iï¿½ï¿½ï¿½ï¿½ï¿½ï¿½È‚ï¿½ï¿½jï¿½ï¿½ï¿½ï¿½(ms)
#define GARDENEEL_RISINGTIME 500 //ï¿½ï¿½Éã¸ï¿½ï¿½ï¿½Ä‚ï¿½ï¿½éŽžï¿½ï¿½(ms)
#define GARDENEEL_HOLDINGTIME 3000 //ï¿½ã¸ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ÄLï¿½Ñ‚Ä‚ï¿½ï¿½ï¿½ï¿½Ô‚ÌŽï¿½ï¿½ï¿½(ms)
#define GARDENEEL_FALLINGTIME 1000 //ï¿½ï¿½ï¿½É‰ï¿½ï¿½~ï¿½ï¿½ï¿½Ä‚ï¿½ï¿½éŽžï¿½ï¿½(ms)

//Sea(ï¿½C)
#define SEA_SIZEX 32
#define SEA_SIZEY 32
#define SEA_TRANSPARENCY 150	//ï¿½ï¿½ï¿½Ì“ï¿½ï¿½ï¿½ï¿½xï¿½wï¿½ï¿½
#define SEA_FIRSTDIVE_SPEED_DECAY 0.5	//ï¿½ï¿½ï¿½ß‚ÄŠCï¿½É“ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ì‘ï¿½ï¿½xï¿½ï¿½ï¿½ï¿½ï¿½iï¿½ï¿½ï¿½ï¿½ï¿½_ï¿½È‰ï¿½ï¿½j
#define SEA_GRAVITY 1200	//ï¿½Cï¿½Ì’ï¿½ï¿½Ìdï¿½ï¿½
//#define SEA_PLAYERMOVESPEED 70	//ï¿½ï¿½ï¿½ï¿½ï¿½Å‚ÌˆÚ“ï¿½ï¿½ï¿½ï¿½x
//#define SEA_BOOSTSPEED 14
#define SEA_MOVESPEED 100	
#define SEA_LOWJUMPSPEED 120
#define SEA_MAXVY 100	//ï¿½ï¿½ï¿½ï¿½ï¿½Å‚Ì—ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½xï¿½ÌÅ‘ï¿½l
#define SEA_WAVESPEEDX 30 //ï¿½gï¿½É‚ï¿½ï¿½ï¿½Äƒvï¿½ï¿½ï¿½Cï¿½ï¿½ï¿½[ï¿½É—^ï¿½ï¿½ï¿½ï¿½ï¿½é‘¬ï¿½x
#define SEA_WAVESPEEDDOWN 30
#define SEA_WAVESPEEDUP 50


//ï¿½`ï¿½ï¿½Tï¿½Cï¿½Y(ï¿½zï¿½ï¿½ÌŒÂï¿½)
#define VIEW_WIDTH_INDEX	WIDTH/DOT
#define VIEW_HEIGHT_INDEX	HEIGHT/DOT

//ï¿½ï¿½ï¿½ï¿½ï¿½è”»ï¿½ï¿½pï¿½Ìƒtï¿½ï¿½ï¿½O ï¿½ï¿½ï¿½ï¿½4ï¿½rï¿½bï¿½gï¿½ÅAï¿½Ç‚Æ‚Ì”ï¿½ï¿½ï¿½B
#define RIGHTTOP 0b0001
#define LEFTTOP 0b0010
#define RIGHTBOTTOM 0b0100
#define LEFTBOTTOM 0b1000
#define TOP 0b0011
#define BOTTOM 0b1100
#define RIGHT 0b0101
#define LEFT 0b1010

//ï¿½Nï¿½ï¿½ï¿½Xï¿½Ì‘Oï¿½ï¿½ï¿½éŒ¾
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

 //ï¿½vï¿½ï¿½ï¿½gï¿½^ï¿½Cï¿½vï¿½éŒ¾
bool InKeyTrigger(int key, int CheckKey);		//when key pressed, return true once    not while
bool CheckRectRect(Rect rect1, Rect rect2);		//ï¿½ï¿½Â‚Ì’ï¿½ï¿½ï¿½ï¿½`ï¿½ï¿½ï¿½dï¿½È‚ï¿½ï¿½Ä‚ï¿½ï¿½é‚©
bool CheckPointRect( double vecX, double vecY ,Rect rect);	//rectï¿½É“_vectorï¿½ï¿½ï¿½Ü‚Ü‚ï¿½Ä‚ï¿½ï¿½é‚©
bool CheckCircleCircle(Circle cir1,Circle cir2);//ï¿½ï¿½Â‚Ì‰~ï¿½ï¿½ï¿½dï¿½È‚ï¿½ï¿½Ä‚ï¿½ï¿½é‚©
bool CheckPointCircle(double vecX,double vecY,Circle cir);	//ï¿½ï¿½ï¿½ï¿½_(vecX,vecY)ï¿½ï¿½,ï¿½~ï¿½ÉŠÜ‚Ü‚ï¿½Ä‚ï¿½ï¿½é‚©
bool CheckCircleRect(Circle cir, Rect rect);	//ï¿½~ï¿½Æ’ï¿½ï¿½ï¿½ï¿½`ï¿½ï¿½ï¿½dï¿½È‚ï¿½ï¿½Ä‚ï¿½ï¿½é‚©
int HitFaceRectRect(Rect rect1, Rect rect2);	//ï¿½ï¿½Â‚Ì’ï¿½ï¿½ï¿½ï¿½`ï¿½Ådï¿½È‚ï¿½ï¿½Ä‚ï¿½ï¿½é•”ï¿½ï¿½ï¿½ï¿½Ô‚ï¿½(rect2ï¿½ï¿½ï¿½ï¿½{ï¿½Æ‚ï¿½ï¿½Äã‰ºï¿½ï¿½ï¿½E)
int HitFaceCircleRect(Circle cir, Rect rect);	//Circleï¿½Æ’ï¿½ï¿½ï¿½ï¿½`ï¿½Ådï¿½È‚ï¿½ï¿½Ä‚ï¿½ï¿½é•”ï¿½ï¿½ï¿½ï¿½Ô‚ï¿½(rectï¿½ï¿½ï¿½ï¿½{ï¿½Æ‚ï¿½ï¿½Äã‰ºï¿½ï¿½ï¿½E)(cirï¿½ï¿½rectï¿½Æ‚Ý‚Äï¿½ï¿½ï¿½)
int HitFaceCircleCircle(Circle cir1,Circle cir2);	//ï¿½Qï¿½Â‚Ì‰~ï¿½Ådï¿½È‚ï¿½ï¿½Ä‚ï¿½ï¿½é•”ï¿½ï¿½ï¿½ï¿½Ô‚ï¿½(cir2ï¿½ï¿½ï¿½ï¿½{ï¿½Æ‚ï¿½ï¿½Äã‰ºï¿½ï¿½ï¿½E)(cirï¿½ï¿½rectï¿½Æ‚Ý‚Äï¿½ï¿½ï¿½)
Rect ChangeCircleToRect(Circle cir);	//Circleï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ÆˆÍ‚Þ’ï¿½ï¿½ï¿½ï¿½`ï¿½ï¿½ï¿½ì¬




//ï¿½Eï¿½Bï¿½ï¿½ï¿½hï¿½Eï¿½Ø‚ï¿½Ö‚ï¿½ï¿½p
enum {
	STARTWINDOW, GAMESELECTWINDOW, GAMEPLAYWINDOW,GAMEPAUSEWINDOW, GAMEOVERWINDOW,GAMECLEARWINDOW,RANKINGWINDOW
};
//ï¿½}ï¿½bï¿½vï¿½æ‘œï¿½p
enum {
	GROUND = 1, TOGE, BLOCK_STONE, BLOCK_ICE, BLOCK_WOOD, MAP_MAX
};
//ï¿½æ‘œï¿½Ç—ï¿½ï¿½p
enum {
	PLAYER,WALKENEMY
};
//ï¿½vï¿½ï¿½ï¿½Cï¿½ï¿½ï¿½[ï¿½hï¿½Ø‘ï¿½
enum {
	CROSSKEYANDJUMP,FORCEHORIZONTALSCROLL
};

//ï¿½vï¿½ï¿½ï¿½Cï¿½ï¿½ï¿½[ï¿½æ‘œï¿½Ø‚ï¿½Ö‚ï¿½ï¿½p
enum {
	STAND,RUN,JUMP,ROPE,FENCE
};


//ï¿½Tï¿½Eï¿½ï¿½ï¿½hï¿½Ç—ï¿½ï¿½p
enum {
	SOUND_FLASHBLOCK, SOUND_PLAYERJUMP,SOUND_PLAYERSKILL,SOUND_PLAYERJUMPMINI,SOUND_LASERSHOT,SOUND_DAMAGE,SOUND_ENEMYSHOOT,SOUND_JUMPSPRING,SOUND_JUMPSPRINGMINI,SOUND_ROPEJUMP,SOUND_ENEMYTREAD,SOUND_COIN,SOUND_STAGESTART,SOUND_STAGE1_1,SOUND_STAGE1_2,SOUND_STAGE1_3,SOUND_MAX
};
=======
//ƒ}ƒbƒv‚Í”z—ñ‚Æ‚µ‚ÄŽ‚Â
#pragma once
#include "DxLib.h"
#define DEBUG			//‚ ‚½‚è”»’è‚ð•`‰æ‚³‚¹‚½‚­‚È‚¢‚Æ‚«‚ÍƒRƒƒ“ƒgƒAƒEƒg



//stageŠÖŒW
#define	TIME_STAGE1_1 500000 //Žc‚èŽžŠÔ(ms)
#define	TIME_STAGE2_1 500000 //Žc‚èŽžŠÔ(ms)
#define	TIME_STAGE1_1R 500000 //Žc‚èŽžŠÔ(ms)
#define	TIME_STAGE2_1R 500000 //Žc‚èŽžŠÔ(ms)
#define TIME_STAGE1_3R 500000


//”wŒi‰æ‘œ
#define MAPPARTS_X 1000	//”wŒi‰æ‘œ‚Ì‚È‚ª‚³@
#define ACCOUNTFORMAPPARTS 3//”wŒi‰æ‘œƒp[ƒc‚Ì‘”

//scoreŠÖŒW
#define SCORE_HP 4
#define SCORE_LIMIT 5
#define SCORE_ENEMY 10
#define SCORE_COIN 30
#define RECODE_NUM_MAX 18			//Å‘å•Û—LƒŒƒR[ƒh”

//dot size
#define DOT 32
//window size@iƒhƒbƒg‚ÅŠ„‚èØ‚ê‚é‚æ‚¤‚É‚·‚éj
#define WIDTH 640
#define HEIGHT 480

//•¨—‰‰ŽZ‚Ì‚½‚ß‚Ì‚¤‚©‚µ
#define FLOW 0.1
#define ZEROEXCEPTION 0.0001	//Š„‚é”‚ª‚±‚êˆÈã¬‚³‚­‚È‚ç‚È‚¢‚æ‚¤‚É‚·‚é

//d—Í(dot/sec)
#define GRAVITY 1500
#define MAX_VELOCITY 3000	//I’[‘¬“x
#define PI 3.141592653589793

//‹­§ƒXƒNƒ[ƒ‹‚Ì‘¬“x(dot/s)
#define SCROLLSPEED 100


//“G‚Ìƒ_ƒ[ƒW—ÊŠÖŒW
#define WALKENEMY_HITDAMAGE 5		//‚Ô‚Â‚©‚Á‚½‚Æ‚«‚Ìƒ_ƒ[ƒW—Ê
#define SHOOTLASER_HITDAMAGE 5			//ƒŒ[ƒU[‚É‚Ô‚Â‚©‚Á‚½‚Æ‚«‚Ìƒ_ƒ[ƒW—Ê
#define SHOOTENEMY_HITDAMAGE 5
#define BULLETTOWARDPLAYER_HITDAMAGE 7
#define FIREBALL_DAMAGE 10		//ƒtƒ@ƒCƒ„[ƒ{[ƒ‹‚É‚ ‚½‚Á‚½‚Æ‚«‚Ìƒ_ƒ[ƒW
#define FALLWALL_BIRDDAMAGE 6			//’¹‚É‚ ‚½‚Á‚½‚Æ‚«‚Ìƒ_ƒ[ƒW
#define FALLWALL_REDEXAMDAMAGE 10		//Ô“_‚É‚ ‚½‚Á‚½‚Æ‚«‚Ìƒ_ƒ[ƒW
#define TURTLE_HITDAMAGE 5
#define GHOST_HITDAMAGE 8					//ƒ_ƒ[ƒW
#define THORNBLOCK_HITDAMAGE 12
#define HANMER_HITDAMAGE 8
#define HANMERTHROW_DAMAGE 4
#define GARDENEEL_DAMAGE  4//ƒ`ƒ“ƒAƒiƒS‚ÉÕ“Ë‚µ‚½‚Æ‚«‚Ìƒ_ƒ[ƒW

//player move speed
#define HITPOINT 50		//ƒvƒŒƒCƒ„[‚ÌHP
#define ENEMYMATCHLESSTIME 1000	//ƒ_ƒ[ƒW‚ðŽó‚¯‚½‚Æ‚«‚Ì–³“GŽžŠÔ(ms)
#define MOVESPEED 200
#define GROUNDBOOSTSPEED 26		//‰Ÿ‚µ‚Á‚Ï‚È‚µ‚É‚æ‚éˆÚ“®—Ê‚Ì‘‰Á“x
#define AIRBOOSTSPEED 12			//‹ó’†‚Å‚Ì‰¡ƒXƒs[ƒh‰Á‘¬“x
#define MAXBOOST 280		//‰Ÿ‚µ‚Á‚Ï‚È‚µ‚É‚æ‚é‘‰Á“x‚ÌãŒÀ
#define JUMPSPEED 200		//ƒWƒƒƒ“ƒvƒXƒs[ƒh
#define HIGHJUMPSPEED 550	//’Ç‰Á‚Å‚«‚éƒnƒCƒWƒƒƒ“ƒvƒXƒs[ƒh—Ê
#define CANHIGHJUMPTIME 205	//ƒnƒCƒWƒƒƒ“ƒv‚Å’²ß‚Å‚«‚éŽžŠÔ(ms)


#define KILLHIGHJUMPTIME 100 //“G‚ð“¥‚ñ‚¾Žž‚©‚çƒnƒCƒWƒƒƒ“ƒv‚ª‚Å‚«‚éŽžŠÔ‚ð‹K’è(ms)
#define KILLHIGHJUMPLIMIT 125 //“G‚ð“¥‚ñ‚¾‚±‚Æ‚É‚æ‚éƒnƒCƒWƒƒƒ“ƒv‚Å’²ß‚Å‚«‚éŽžŠÔ(ms)‚ð§ŒÀ		‚à‚µ‚©‚µ‚½‚çACANHIGHJUMPTIME‚æ‚è¬‚³‚­‚È‚¢‚Æ‚¢‚¯‚È‚¢
#define KILLJUMP 380		//“G‚ð‚½‚¨‚µ‚½‚Æ‚«‚Ìã‚Ö‚ÌƒWƒƒƒ“ƒv—Ê
#define ANIMETIONINTERVAL 400 //‰æ‘œØ‚è‘Ö‚¦‘¬“ximsj


//walkenemy
#define WALKENEMY_MOVEWIDTH 160		//ˆÚ“®•(dot)
#define WALKENEMY_SIZEX 24			//‚ ‚½‚è”»’è‚Ì‘å‚«‚³(dot)
#define WALKENEMY_SIZEY 28			//‚ ‚½‚è”»’è‚Ì‘å‚«‚³(dot)
#define WALKENEMY_SPEED 100			//walkƒXƒs[ƒh(dot/s)
#define WALKENEMY_KILLCOLLIDERY  5	//ã‚É‚ ‚½‚Á‚Ä‚¢‚é‚©

//ShootLaser‚ÉŠÖ‚·‚é’è‹`
#define SHOOTLASER_POSX 595				//ƒŒ[ƒU[”­ŽË‘•’u‚Ì‰æ–Êã‚ÌXÀ•W
#define SHOOTLASER_SHOTTIMES 22			//‰½‰ñƒŒ[ƒU[‚ð‘Å‚Â‚©
#define SHOOTLASER_LASERINTERVAL 1400	//ƒŒ[ƒU[‚ð”­ŽË‚·‚éŠÔŠu(ms)
#define SHOOTLASER_MOVEINTERVAL 20		//ˆê‰ñƒŒ[ƒU[‚ð‘Å‚Á‚½Œã‚ÉƒfƒBƒXƒyƒ“ƒT[‚ð‰º‚É‚Ç‚ê‚¾‚¯ˆÚ“®‚·‚é‚©(dot)
#define SHOOTLASER_SHOOTWAITTIME 700			//‘Å‚Á‚½‚Ì‚¿A‚Ç‚ê‚®‚ç‚¢‘Ò‚Â‚©(ms)
#define SHOOTLASER_WAITTIME 300			//ƒfƒBƒXƒyƒ“ƒT[‚ðˆÚ“®‚³‚¹‚½‚Ì‚¿A‚Ç‚ê‚®‚ç‚¢‘Ò‚Â‚©(ms)
#define SHOOTLASER_LASERSPEED 1000		//ƒŒ[ƒU[‚Ì”ò‚Ô‘¬‚³(dot/s)

//FlashBlock
#define FLASHBLOCK_SIZEX 32				//‚ ‚½‚è”»’è‚Ì‘å‚«‚³
#define FLASHBLOCK_SIZEY 32
#define FLASHBLOCK_FLASHTIME 1000		//Œ©‚¦‚È‚­‚È‚éŽžŠÔ(ms)

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
#define SHOOTENEMY_TIMEBFOREFIRING 1000 //‰æ–Ê‚É“ü‚Á‚Ä‚©‚ç‹…‚ð”­ŽË‚µŽn‚ß‚é‚Ü‚Å‚ÌŽžŠÔ

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
#define FIREBAR_BALL_RADIUS 6  //firebar‚Ìfireball‚Ì”¼Œa
#define FIREBAR_NUMBER 4  //firebar‚Ìbar‚Ì–{”
#define FIREBAR_LENGTH 5  //firebar‚Ìfireball‚ÌŒÂ”

//FireBall
#define FIREBALL_ANGVEL 90.0*(PI/180.0)  //firebar‚ÌŠp‘¬“x

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
#define JUMP_LOWJUMP 350				//‚Î‚Ë‚É‚æ‚éƒWƒƒƒ“ƒv—Ê
#define JUMP_HIGHJUMP  470				//ƒXƒy[ƒX‚ð‰Ÿ‚µ‚Ä‚¢‚½Žž‚ÌƒWƒƒƒ“ƒv—Ê
#define JUMP_HIGHJUMPLIMIT 170			//Å‚ƒnƒCƒWƒƒƒ“ƒv‚Ì’²®	‚à‚µ‚©‚µ‚½‚çACANHIGHJUMPTIME‚æ‚è¬‚³‚­‚È‚¢‚Æ‚¢‚¯‚È‚¢
#define JUMP_CANHIGHJUMP 100			//HIGHJUMP‰Â”\‚È”ÍˆÍ
#define JUMP_ANGULARVELOCITY 2*PI *1.8	//(rad/s)
#define JUMP_DECREMENT 1.00 //‚Î‚Ë‚ÌU•‚Ì‘‰Á—¦
#define JUMP_EXTENSION 14 //(dot)
//#define JUMP_LOW_EXTENSION 20 //(dot)
//#define JUMP_HIGH_EXTENSION 50 //(dot)


//fallwall
#define FALLWALL_WAITFORDOWN 1000		//Ô“_‚ª—Ž‚¿‚Ä‚©‚ç‰º~‘Ò‚¿(ms)
#define FALLWALL_WAITFORUP	1000		//ã¸‚Ü‚¿i‚‚“j
//#define FALLWALL_BIRDFALLINGTIME 3000	//’¹‚ªÔ“_‚ð‚Æ‚é‚Ì‚É—v‚·‚éŽžŠÔi—Ž‰ºj(MS)
//#define FALLWALL_BIRDRISINGTIME 3000	//’¹‚ªÔ“_‚ð‚Æ‚Á‚½‚Ì‚¿‚ÌA“o‚é‚Ì‚É—v‚·‚éŽžŠÔ(MS)
#define FALLWALL_BIRDSPEED 200			//’¹‚ÌˆÚ“®ƒXƒs[ƒh
#define FALLWALL_FALLSPEED 300//“šˆÄ—Ž‰º‘¬“x(dot/s)

#define FALLWALL_ANIMATIONTURNTIME 200	//ƒpƒ^ƒpƒ^‚ÌŠÔŠu(MS)

//Coin
#define COIN_MATCHLESSTIME 1000		//(ms)
#define COIN_REVERSETIME 1000		//”½“]‚³‚¹‚éŠÔŠu(ms)

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
#define TURTLE_TURNTIME 60 //‰ñ“]‚Ì‰æ‘œˆêƒRƒ}‚ð•\Ž¦‚·‚éŽžŠÔimsj

//TurtleWithWing
#define TURTLEWITHWING_PERIODICTIME 5000 //ˆêŽü‚·‚é‚Ì‚É—v‚·‚éŽžŠÔ(ms)
#define TURTLEWITHWING_MOVEMENT 35 //U•(dot)


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
#define THROWING_ANGLE_MAX PI/180 * 85		//Å‘åŠp
#define THROWING_ANGLE_MIN PI/180 * 10		//Å¬Šp

#define HANMERTHROW_TURNTIME 200 //ƒAƒjƒ[ƒVƒ‡ƒ“‚ªØ‚è‘Ö‚í‚éŽžŠÔ

//Hanmer
//#define HANMER_SIZEX 10
//#define HANMER_SIZEY 10
#define HANMER_RADIUS 5
#define HANMER_ANGVEL PI/180 * 360 //20‹/s

//ghost
#define GHOST_DISPLAYSIZEX 56
#define GHOST_DISPLAYSIZEY 36
#define GHOST_CHARASIZEX 28
#define GHOST_CHARASIZEY 30					
#define GHOST_MOVESPEED 20					//ƒvƒŒƒCƒ„[‚Éi‚Þ‘¬‚³
#define GHOST_ANGVEL 90.0*(PI/180.0)		//ŠpU“®”
#define GHOST_MOVEWIDTH 60		//U“®‚Ì—h‚ê•
#define GHOST_TRANSPARENCY 50  //‚Ç‚Ì‚­‚ç‚¢“§–¾‚É‚·‚é‚©0:“§–¾@250:•s“§–¾
#define GHOST_TURNTIME 300	//ƒtƒ‰ƒbƒVƒ…‚ª‚½‚©‚ê‚Äˆø‚Áž‚Þ‚Ü‚Å

//thornblock
#define THORNBLOCK_SIZEX 28
#define THORNBLOCK_SIZEY 28
#define THORNBLOCK_TRANSPARENCY 10

//fence
#define FENCE_SIZE 32  //³•ûŒ`‚Å’è‹`
#define FENCE_PLAYERMOVESPEED 100 //ƒvƒŒƒCƒ„[‚ÌˆÚ“®‘¬“xŽw’è
#define FENCE_LOWJUMPSPEED 200		//LOWƒWƒƒƒ“ƒv‚Ì‚‚³Žw’è

//Ship
#define SHIP_SIZEX 96
#define SHIP_SIZEY 64
#define SHIP_MOVESPEED 100


//SeaWeed(ŠC‘”)
#define SEAWEED_SIZEX 32 //ŠC‘”‚Ì‰æ‘œ‚Ì‘å‚«‚³
#define SEAWEED_SIZEY 32 //ŠC‘”‚Ì‰æ‘œ‚Ì‘å‚«‚³
#define SEAWEED_TOTALPICTURES 5 //‰æ‘œ‚Ì‘”
#define SEAWEED_SWITCHTIME 1000 //1‰æ‘œ‚ ‚½‚è‚Ì•\Ž¦ŽžŠÔ(ms/‰æ‘œ)

//GardenEel(ƒ`ƒ“ƒAƒiƒS)
#define GARDENEEL_SIZEX 10 //ƒ`ƒ“ƒAƒiƒS‚Ì‰æ‘œƒTƒCƒY
#define GARDENEEL_SIZEY 32
#define GARDENEEL_HIDINGTIME 1000 //“y‚É‰B‚ê‚Ä‚¢‚éi“–‚½‚ç‚È‚¢jŽžŠÔ(ms)
#define GARDENEEL_RISINGTIME 500 //ã‚Éã¸‚µ‚Ä‚¢‚éŽžŠÔ(ms)
#define GARDENEEL_HOLDINGTIME 3000 //ã¸‚µ‚«‚Á‚ÄL‚Ñ‚Ä‚¢‚éó‘Ô‚ÌŽžŠÔ(ms)
#define GARDENEEL_FALLINGTIME 1000 //‰º‚É‰º~‚µ‚Ä‚¢‚éŽžŠÔ(ms)


//•`‰æƒTƒCƒY(”z—ñ‚ÌŒÂ”)
#define VIEW_WIDTH_INDEX	WIDTH/DOT
#define VIEW_HEIGHT_INDEX	HEIGHT/DOT

//‚ ‚½‚è”»’è—p‚Ìƒtƒ‰ƒO ‰ºˆÊ4ƒrƒbƒg‚ÅA•Ç‚Æ‚Ì”»’èB
#define RIGHTTOP 0b0001
#define LEFTTOP 0b0010
#define RIGHTBOTTOM 0b0100
#define LEFTBOTTOM 0b1000
#define TOP 0b0011
#define BOTTOM 0b1100
#define RIGHT 0b0101
#define LEFT 0b1010

//ƒNƒ‰ƒX‚Ì‘O•ûéŒ¾
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

 //ƒvƒƒgƒ^ƒCƒvéŒ¾
bool InKeyTrigger(int key, int CheckKey);		//when key pressed, return true once    not while
bool CheckRectRect(Rect rect1, Rect rect2);		//“ñ‚Â‚Ì’·•ûŒ`‚ªd‚È‚Á‚Ä‚¢‚é‚©
bool CheckPointRect( double vecX, double vecY ,Rect rect);	//rect‚É“_vector‚ªŠÜ‚Ü‚ê‚Ä‚¢‚é‚©
bool CheckCircleCircle(Circle cir1,Circle cir2);//“ñ‚Â‚Ì‰~‚ªd‚È‚Á‚Ä‚¢‚é‚©
bool CheckPointCircle(double vecX,double vecY,Circle cir);	//‚ ‚é“_(vecX,vecY)‚Í,‰~‚ÉŠÜ‚Ü‚ê‚Ä‚¢‚é‚©
bool CheckCircleRect(Circle cir, Rect rect);	//‰~‚Æ’·•ûŒ`‚ªd‚È‚Á‚Ä‚¢‚é‚©
int HitFaceRectRect(Rect rect1, Rect rect2);	//“ñ‚Â‚Ì’·•ûŒ`‚Åd‚È‚Á‚Ä‚¢‚é•”•ª‚ð•Ô‚·(rect2‚ðŠî–{‚Æ‚µ‚Äã‰º¶‰E)
int HitFaceCircleRect(Circle cir, Rect rect);	//Circle‚Æ’·•ûŒ`‚Åd‚È‚Á‚Ä‚¢‚é•”•ª‚ð•Ô‚·(rect‚ðŠî–{‚Æ‚µ‚Äã‰º¶‰E)(cir‚ðrect‚Æ‚Ý‚Äˆ—)
int HitFaceCircleCircle(Circle cir1,Circle cir2);	//‚Q‚Â‚Ì‰~‚Åd‚È‚Á‚Ä‚¢‚é•”•ª‚ð•Ô‚·(cir2‚ðŠî–{‚Æ‚µ‚Äã‰º¶‰E)(cir‚ðrect‚Æ‚Ý‚Äˆ—)
Rect ChangeCircleToRect(Circle cir);	//Circle‚ð‚®‚é‚Á‚ÆˆÍ‚Þ’·•ûŒ`‚ðì¬




//ƒEƒBƒ“ƒhƒEØ‚è‘Ö‚¦—p
enum {
	STARTWINDOW, GAMESELECTWINDOW, GAMEPLAYWINDOW,GAMEPAUSEWINDOW, GAMEOVERWINDOW,GAMECLEARWINDOW,RANKINGWINDOW
};
//ƒ}ƒbƒv‰æ‘œ—p
enum {
	GROUND = 1, TOGE, BLOCK_STONE, BLOCK_ICE, BLOCK_WOOD, MAP_MAX
};
//‰æ‘œŠÇ——p
enum {
	PLAYER,WALKENEMY
};
//ƒvƒŒƒCƒ‚[ƒhØ‘Ö
enum {
	CROSSKEYANDJUMP,FORCEHORIZONTALSCROLL
};

//ƒvƒŒƒCƒ„[‰æ‘œØ‚è‘Ö‚¦—p
enum {
	STAND,RUN,JUMP,ROPE,FENCE
};


//ƒTƒEƒ“ƒhŠÇ——p
enum {
	SOUND_FLASHBLOCK, SOUND_PLAYERJUMP,SOUND_PLAYERSKILL,SOUND_PLAYERJUMPMINI,SOUND_LASERSHOT,SOUND_DAMAGE,SOUND_ENEMYSHOOT,SOUND_JUMPSPRING,SOUND_JUMPSPRINGMINI,SOUND_ROPEJUMP,SOUND_ENEMYTREAD,SOUND_COIN,SOUND_STAGESTART,SOUND_STAGE1_1,SOUND_STAGE1_2,SOUND_STAGE1_3,SOUND_MAX
};
>>>>>>> parent of 6027140... Merge branch 'MakePenguin' of https://github.com/HoneyMack/2DGame2019 into MakePenguin
