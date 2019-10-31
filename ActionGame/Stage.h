#pragma once

#include "Player.h"
#include "WalkEnemy.h"
#include "Penguin.h"
#include "FlashBlock.h"
#include "ShootLaser.h"
#include "UpDownObject.h"
#include "ShootEnemy.h"
#include "FireBar.h"
#include "Lift.h"
#include "Ship.h"
#include "Rope.h"
#include "Jump.h"
#include "Coin.h"
#include "FallWall.h"
#include "Turtle.h"
#include "TurtleWithWing.h"
#include "HanmerThrow.h"
#include "Ghost.h"
#include "Fish.h"
#include "Crab.h"
#include "ThornBlock.h"
#include "MarineBoss.h"
#include "Fence.h"
#include "Sea.h"
#include "SeaWeed.h"
#include "Polarbear.h"  //new
#include "HealingItem.h"
#include "GardenEel.h"
#include "SnowMan.h"
#include "Map.h"
#include "Rect.h"
#include "Object.h"
#include "define.h"



//?øΩw?øΩi?øΩÊëúÔøΩ?øΩ?øΩ?øΩ»ÇÔøΩ?øΩ∆Éo?øΩO

class Stage
{
public:
	int mode = CROSSKEYANDJUMP;		//?øΩv?øΩ?øΩ?øΩC?øΩ?øΩ?øΩ[?øΩh
	static	int limit;						//?øΩc?øΩËéûÔøΩ?øΩ
	Rect* Camera;					//?øΩ`?øΩ?øΩÕàÕéw?øΩ?øΩp?øΩ?øΩ`?øΩÃóp?øΩ?øΩ
	Player* usingP;					//?øΩv?øΩ?øΩ?øΩC?øΩ?øΩ?øΩ[
	Map* usingM;					//?øΩ}?øΩb?øΩv
	int mapparts[ACCOUNTFORMAPPARTS];	//?øΩw?øΩi?øΩÊëúÔøΩÃíf?øΩ?øΩ

	Stage();
	~Stage();

	void AllUpdate(double frametime);
	void AllDraw();

	void AllReset();

	void Update(double frametime);//mob?øΩC?øΩ?øΩ?øΩX?øΩ^?øΩ?øΩ?øΩX?øΩÃÉ|?øΩC?øΩ?øΩ?øΩ^?øΩ?øΩn?øΩ?øΩ?øΩ∆ìn?øΩ?øΩ?øΩ?øΩMob?øΩÃèÔøΩ?øΩ?øΩ?øΩ?øΩ?øΩ?øΩ?øΩƒÇÔøΩ?øΩ?øΩ?øΩ
	void Draw();					//mob?øΩC?øΩ?øΩ?øΩX?øΩ^?øΩ?øΩ?øΩX?øΩÃÉ|?øΩC?øΩ?øΩ?øΩ^?øΩ?øΩn?øΩ?øΩ?øΩ∆ìn?øΩ?øΩ?øΩ?øΩMob?øΩÃï`?øΩ?øΩ?øΩ?øΩ?øΩ?øΩƒÇÔøΩ?øΩ?øΩ?øΩ
	void AddDraw();							//mob?øΩC?øΩ?øΩ?øΩX?øΩ^?øΩ?øΩ?øΩX?øΩÃÉ|?øΩC?øΩ?øΩ?øΩ^?øΩ?øΩn?øΩ?øΩ?øΩ∆ìn?øΩ?øΩ?øΩ?øΩMob?øΩÃï`?øΩ?øΩ(?øΩ«âÔøΩ)?øΩ?øΩ?øΩ?øΩ?øΩƒÇÔøΩ?øΩ?øΩ?øΩ
};