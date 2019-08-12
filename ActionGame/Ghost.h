#include"Object.h"
#include"Mob.h"
#include"Rect.h"




class Ghost :public Mob,public Object
{
public:
	static int PicHandle[3];

	int index = 0;	//アニメーション用
	int  animation = 0; //アニメーション用
	double angvel=GHOST_ANGVEL, angle = -PI / 2;				//各振動数、角度
	double vecY = 0;
	double speed = GHOST_MOVESPEED;								//プレイヤーに近づく速さ
	double movewidth = GHOST_MOVEWIDTH;							//振動の揺れ幅

	double dx, dy;
	double length;

	Rect display = Rect(GHOST_DISPLAYSIZEX, GHOST_DISPLAYSIZEY, &this->x, &this->y);
	Rect chara = Rect(GHOST_CHARASIZEX,GHOST_CHARASIZEY, &this->x, &this->y);

	Ghost(int x, int y);
	~Ghost();
	
	void Motion(double frametime);
	void Draw();

	bool HitCheck(Rect rect);
	void HitPlayer();
};
