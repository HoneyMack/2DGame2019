#include "HealingItem.h"

int HealingItem::PicHandle[] = { 0,0,0 };

HealingItem::HealingItem(int x, int y)
{
	this->x = x;
	this->y = y;
	
	PicNum = rnd() % 3;
}

HealingItem::~HealingItem()
{
}

void HealingItem::Motion(double frametime)
{
}

void HealingItem::Draw()
{
	if (CheckInCam()) {
		DrawGraph(RelativePosX(), RelativePosY(), PicHandle[PicNum], TRUE);

#ifdef DEBUG
		rect.Draw(*Camera);
#endif // DEBUG
	}
}

bool HealingItem::HitCheck(Rect rect)
{
	//return false;
	if (CheckInCam()) {
		if (CheckRectRect(this->rect, rect)) {
			HitPlayer();
			return true;
		}
	}
	return false;

}

void HealingItem::HitPlayer()
{
	usingP->HP += HEALING_POINT;
	deathflag = true;
}
