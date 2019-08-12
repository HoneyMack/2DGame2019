#pragma once
#include"FireBall.h"

class FireBar :public Object, public Mob
{
public:
	static int PicHandle;			//中心ブロック画像
	FireBar(int set_x, int set_y);
	FireBar(int set_x, int set_y, int length, int number);  //firebarの長さ本数を指定
	FireBar(int set_x, int set_y, double speed);  //firebarの速さを指定　角速度がspeed*PI/180になります　デフォルトでspeedは90です
	FireBar(int set_x, int set_y, bool direction);  //firebarの回転の向きを指定　falseで通常と反対方向を向きます　true,falseと小文字で宣言してください(大文字だとint型と判断されてしまうため)
	FireBar(int set_x, int set_y, int set_angle);  //firebarの位相角を指定　弧度法ではなく度数法で宣言してください
	FireBar(int set_x, int set_y, double set_speed, bool direction, int length, int number, int set_angle);  //すべて指定 度数法で宣言してください
	
	~FireBar();

	Rect rect = Rect(30, 30, &this->x, &this->y);

	FireBall *fireball;

	void Motion(double frametime);
	void Draw();

	bool HitCheck(Rect rect);
	void HitPlayer();

};