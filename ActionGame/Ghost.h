#include"Object.h"
#include"Mob.h"
#include"Rect.h"




class Ghost :public Mob,public Object
{
public:
	static int PicHandle[3];

	int index = 0;	//�A�j���[�V�����p
	int  animation = 0; //�A�j���[�V�����p
	double angvel=GHOST_ANGVEL, angle = -PI / 2;				//�e�U�����A�p�x
	double vecY = 0;
	double speed = GHOST_MOVESPEED;								//�v���C���[�ɋ߂Â�����
	double movewidth = GHOST_MOVEWIDTH;							//�U���̗h�ꕝ

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
