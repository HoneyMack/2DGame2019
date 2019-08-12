#include"Object.h"
#include"Rect.h"
#include"Mob.h"
#include"define.h"

class ThornBlock :public Object, public Mob
{
public:
	static int PicHandle;

	Rect rect = Rect(THORNBLOCK_SIZEX, THORNBLOCK_SIZEY, &this->x, &this->y);
	
	ThornBlock(int x, int y);
	~ThornBlock();

	void Motion(double frametime);
	void Draw();
	bool HitCheck(Rect rect);
	void HitPlayer();
};