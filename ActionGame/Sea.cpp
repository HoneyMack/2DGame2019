#include "Sea.h"

Sea* Sea::first = nullptr;
Sea* Sea::last = nullptr;

int Sea::PicHandle = 0;

Sea::Sea(int x, int y)
{
	this->x = x;
	this->y = y;
	
	ChainMaker();
}

Sea::~Sea()
{
	ChainCutter();
}

void Sea::ChainMaker()
{
	if (first == nullptr) 
		first = this;
	else {
		former = last;
		former->next = this;
	}
	last = this;
	next = nullptr;
}

void Sea::ChainCutter()
{
	if (last != first) {
		if (this == last) {
			last = former;
			former->next = nullptr;
		}
		else if (this == first) {
			next->former = nullptr;
			first = next;
		}
		else {
			former->next = this->next;
		}
	}
	else {
		last = first = nullptr;
	}
}

bool Sea::HasNext()
{
	if (this->next != nullptr)
		return true;
	else
		return false;
}

int Sea::HitCheckReturnSea(Rect rect)
{	//ŒÂX‚Ì“–‚½‚è”»’è
	return HitFaceRectRect(this->rect,rect);
}

void Sea::AllDelete()
{
	AllDelete(first);
	first = nullptr;
}

void Sea::AllDelete(Sea* sea)
{
	while (sea != nullptr) {
		Sea* nextsea = sea->next;
		delete sea;
		sea = nextsea;
	}
}

void Sea::Draw()
{
	if (CheckInCam(x + rect.sizeX, y) || CheckInCam(x, y)) {
#ifdef DEBUG
		rect.Draw(*Camera);
#endif
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, SEA_TRANSPARENCY);
		DrawGraph(RelativePosX(), RelativePosY(), PicHandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

int Sea::PlayerHitCheck(Rect rect)
{
	//return 0;
	int hitface = 0;

	if (first != nullptr) {
		Sea* sea = first;

		if (sea != nullptr) {
			while (true) {
				if (sea->HitCheckReturnSea(rect) != 0) {
					hitface = hitface | sea->HitCheckReturnSea(rect);
				}
				sea->Draw();

				if (sea->HasNext())
					sea = sea->next;
				else
					break;
			}
		}
	}
	return hitface;
}
