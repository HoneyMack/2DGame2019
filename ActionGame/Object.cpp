#include "Object.h"

Map* Object::map = nullptr;
Rect* Object::Camera = nullptr;
Player* Object::usingP = nullptr;

Object::Object() {
	vx = vy = ax = 0;
	ay = GRAVITY;
}
Object::Object(double dx, double dy, double dvx, double dvy, double dax, double day) {
	x = dx;
	y = dy;
	vx = dvx;
	vy = dvy;
	ax = dax;
	ay = day;
}

Object::~Object()
{
}

Object Object::nextPosX(double ftime) {
	Object ob;
	ob.x = vx * ftime + ax * ftime* ftime / 2 + x;
	ob.y = y;
	ob.vx = vx + ax * ftime;
	ob.vy = vy;

	if (ob.vx > MAX_VELOCITY)
		ob.vx = MAX_VELOCITY;
	else if (ob.vx < -MAX_VELOCITY)
		ob.vx = -MAX_VELOCITY;
	return ob;
}
Object Object::nextPosY(double ftime) {
	Object ob;
	ob.x = x;
	ob.y = vy * ftime + ay * ftime*ftime / 2 + y;
	ob.vx = vx;
	ob.vy = vy + ay * ftime;

	if (ob.vy > MAX_VELOCITY)
		ob.vy = MAX_VELOCITY;
	else if (ob.vy < -MAX_VELOCITY)
		ob.vy = -MAX_VELOCITY;
	return ob;
}
Object Object::nextPosAll(double ftime) {
	Object ob;
	ob.x = vx * ftime + ax * ftime* ftime / 2 + x;
	ob.y = vy * ftime + ay * ftime*ftime / 2 + y;
	ob.vx = vx + ax * ftime;
	ob.vy = vy + ay * ftime;

	if (ob.vx > MAX_VELOCITY)
		ob.vx = MAX_VELOCITY;
	else if (ob.vx < -MAX_VELOCITY)
		ob.vx = -MAX_VELOCITY;

	if (ob.vy > MAX_VELOCITY)
		ob.vy = MAX_VELOCITY;
	else if (ob.vy < -MAX_VELOCITY)
		ob.vy = -MAX_VELOCITY;
	return ob;
}

void Object::stepPosX(double ftime) {
	x += vx *ftime + ax * ftime * ftime / 2;
	vx += ax * ftime;
	if (vx > MAX_VELOCITY)
		vx = MAX_VELOCITY;
	else if (vx < -MAX_VELOCITY)
		vx = -MAX_VELOCITY;
}
void Object::stepPosY(double ftime) {
	y += vy *ftime + ay * ftime*ftime / 2;
	vy += ay *ftime;

	if (vy > MAX_VELOCITY)
		vy = MAX_VELOCITY;
	else if (vy < -MAX_VELOCITY)
		vy = -MAX_VELOCITY;
}
void Object::stepPosAll(double ftime) {
	x += vx *ftime + ax * ftime * ftime / 2;
	y += vy *ftime + ay * ftime*ftime / 2;
	vx += ax * ftime;
	vy += ay *ftime;

	if (vx > MAX_VELOCITY)
		vx = MAX_VELOCITY;
	else if (vx < -MAX_VELOCITY)
		vx = -MAX_VELOCITY;

	if (vy > MAX_VELOCITY)
		vy = MAX_VELOCITY;
	else if (vy < -MAX_VELOCITY)
		vy = -MAX_VELOCITY;
}

int Object::stepRect_x(Rect rect, double ftime) {
	int hitface = 0;
	Object ob_next;

	//X�����Ɉړ��������i���Ԃ�i�߂��j�Ƃ��̈ʒu��m��
	ob_next = nextPosX(ftime);

	ob_next.x += rect.x;	//���Έʒu��ǉ����Đ����������蔻��̈ʒu������
	ob_next.y += rect.y;

	//�܂��������łԂ����Ă邩�m��
	if (CheckMapNum(ob_next, 0, 0) > 0)			hitface = hitface | LEFTTOP;		//����
	if (CheckMapNum(ob_next, rect.sizeX, 0) > 0)		hitface = hitface | RIGHTTOP;	//�E��
	if (CheckMapNum(ob_next, 0, rect.sizeY) > 0)		hitface = hitface | LEFTBOTTOM;	//����
	if (CheckMapNum(ob_next, rect.sizeX, rect.sizeY) > 0)	hitface = hitface | RIGHTBOTTOM;	//�E��

	//���̂�DOT�����傫���Ƃ��̂��߂̏���
	for (int i = 1; i <= (rect.sizeY - 1) / (DOT - 2); i++) {
		if (CheckMapNum(ob_next, 0, (DOT - 2) * i) > 0)			hitface = hitface | LEFT;		//��
		if (CheckMapNum(ob_next, rect.sizeX, (DOT - 2) * i) > 0)			hitface = hitface | RIGHT;		//�E
	}

	stepPosX(ftime);			//X�����̎��Ԃ�i�߂�

	//�d�Ȃ����Ƃ��낾���߂�
	if (hitface &RIGHTTOP || hitface & RIGHTBOTTOM) {
		x = ReturnMapIndex(x + rect.sizeX + rect.x)* DOT - rect.sizeX - FLOW - rect.x;	//�E�̕ǂ��肬��܂ňړ�
	}
	else if (hitface & LEFTTOP || hitface & LEFTBOTTOM) {
		x = (ReturnMapIndex(x + rect.x) + 1)* DOT + FLOW * 2 - rect.x;	//���̕ǂ��肬��܂ňړ�
	}

	return hitface;
}
int Object::stepRect_y(Rect rect, double ftime) {
	int hitface = 0;
	Object ob_next;

	//X�����Ɉړ��������i���Ԃ�i�߂��j�Ƃ��̈ʒu��m��
	ob_next = nextPosY(ftime);

	ob_next.x += rect.x;	//���Έʒu��ǉ����Đ����������蔻��̈ʒu������
	ob_next.y += rect.y;

	//�܂��������łԂ����Ă邩�m��
	if (CheckMapNum(ob_next, 0, 0) > 0)			hitface = hitface | LEFTTOP;		//����
	if (CheckMapNum(ob_next, rect.sizeX, 0) > 0)		hitface = hitface | RIGHTTOP;	//�E��
	if (CheckMapNum(ob_next, 0, rect.sizeY) > 0)		hitface = hitface | LEFTBOTTOM;	//����
	if (CheckMapNum(ob_next, rect.sizeX, rect.sizeY) > 0)	hitface = hitface | RIGHTBOTTOM;	//�E��

	//���̂�DOT�����傫���Ƃ��̂��߂̏���
	for (int i = 1; i <= (rect.sizeX - 1) / (DOT - 2); i++) {
		if (CheckMapNum(ob_next, (DOT - 2) * i, 0) > 0)			hitface = hitface | TOP;		//��
		if (CheckMapNum(ob_next, (DOT - 2) * i, rect.sizeY) > 0)		hitface = hitface | BOTTOM;		//��
	}

	stepPosY(ftime);		//Y�����̎��Ԃ�i�߂�
	//�d�Ȃ��Ă�����߂�
	if (hitface  &LEFTTOP || hitface & RIGHTTOP) {
		y = (ReturnMapIndex(y + rect.y) + 1) * DOT + FLOW - rect.y;	//��̕ǂ��肬��܂ňړ�
	}
	else if (hitface & LEFTBOTTOM || hitface & RIGHTBOTTOM) {
		y = ReturnMapIndex(y + rect.sizeY + rect.y) * DOT - rect.sizeY - FLOW - rect.y;	//���̕ǂ��肬��܂ňړ�
	}
	return hitface;
}
int Object::stepCircle_x(Circle cir, double ftime) {
	//�O��������ƈ͂ސ����`���쐬�����A�̓���
	//�����`�쐬
	Rect rect = ChangeCircleToRect(cir);

	return stepRect_x(rect,ftime);

}
int Object::stepCircle_y(Circle cir, double ftime) {

	Rect rect = ChangeCircleToRect(cir);
	return stepRect_y(rect, ftime);
}

int Object::CheckMapNum(Object Ob, int vecX, int vecY) {
	return map->PosInfo((int)Ob.x + vecX, (int)Ob.y + vecY);
}

bool Object::CheckInCam() {
	if (Camera->x <= x && Camera->x + Camera->sizeX >= x && Camera->y <= y && Camera->y + Camera->sizeY >= y)
		return true;
	else
		return false;
}
bool Object::CheckInCam(double x, double y) {
	if (Camera->x <= x && Camera->x + Camera->sizeX >= x && Camera->y <= y && Camera->y + Camera->sizeY >= y)
		return true;
	else
		return false;
}

bool Object::CheckInCam(int x, int y) {
	if (Camera->x <= x && Camera->x + Camera->sizeX >= x && Camera->y <= y && Camera->y + Camera->sizeY >= y)
		return true;
	else
		return false;
}

double Object::RelativePosX() {
	return x - Camera->x;
}
double Object::RelativePosY() {
	return y - Camera->y;
}



bool CheckRectRect(Rect rect1, Rect rect2) {
	if (!(*rect1.gx + rect1.x - (*rect2.gx + rect2.sizeX + rect2.x) > 0 || 
		rect2.x + *rect2.gx - (*rect1.gx + rect1.x + rect1.sizeX) > 0 || 
		*rect1.gy + rect1.y - (*rect2.gy + rect2.sizeY + rect2.y) > 0 || 
		*rect2.gy + rect2.y - (*rect1.gy + rect1.sizeY + rect1.y) > 0)) {
		return true;
	}
	else {
		return false;
	}
}
bool CheckPointRect( double vecX, double vecY,Rect rect) {
	if (*rect.gx + rect.x <= vecX && *rect.gx + rect.x + rect.sizeX >= vecX &&*rect.gy + rect.y <= vecY &&*rect.gy + rect.y + rect.sizeY >= vecY)
		return true;
	else
		return false;
}

bool CheckCircleCircle(Circle cir1,Circle cir2) {
	if ((*cir1.gx +cir1.x - cir2.x - *cir2.gx)*(*cir1.gx + cir1.x - cir2.x - *cir2.gx) + (cir1.y +*cir1.gy - cir2.y - *cir2.gy ) * (cir1.y + *cir1.gy - cir2.y - *cir2.gy) <= (cir1.radius + cir2.radius)*(cir1.radius + cir2.radius))
		return true;
	else
		return false;
}
bool CheckPointCircle(double vecX, double vecY, Circle cir) {
	if ((cir.x  + *cir.gx- vecX)* (cir.x  + *cir.gx - vecX) + (cir.y + *cir.gy - vecY)*(cir.y  + *cir.gy - vecY) <= cir.radius *cir.radius)
		return true;
	else
		return false;
}
Rect ChangeCircleToRect(Circle cir) {
	//�O��������ƈ͂ސ����`���쐬�����A�̓���
	//�����`�쐬
	Rect rect(cir.radius * 2, cir.radius * 2, cir.gx, cir.gy);
	rect.x = -cir.radius + cir.x;
	rect.y = -cir.radius + cir.y;
	return rect;
}

bool CheckCircleRect(Circle cir,Rect rect) {
	
	//������\���̂���͈�
	Rect rect1(rect.sizeX,rect.sizeY,rect.gx,rect.gy),rect2(rect.sizeX, rect.sizeY, rect.gx, rect.gy);

	rect1.sizeX += 2 * cir.radius;
	rect2.sizeY += 2 * cir.radius;
	rect1.x -= cir.radius;
	rect2.y -= cir.radius;

	//�ꍇ��������
	if (CheckPointRect(cir.x + *cir.gx, cir.y + *cir.gy, rect1)|| CheckPointRect(cir.x + *cir.gx, cir.y + *cir.gy, rect2)) {
		return true;
	}
	else {
		if (CheckPointCircle(rect.x + *rect.gx, rect.y + *rect.gy, cir) || CheckPointCircle(rect.x + *rect.gx + rect.sizeX, rect.y + *rect.gy, cir)
			|| CheckPointCircle(rect.x + *rect.gx, rect.y + *rect.gy + rect.sizeY, cir) || CheckPointCircle(rect.x + *rect.gx + rect.sizeX, rect.y + *rect.gy + rect.sizeY, cir))
			return true;
		else
			return false;
	}
}
int HitFaceRectRect(Rect rect1, Rect rect2) {
	int hitface = 0;
	if (CheckPointRect( *rect2.gx + rect2.x, *rect2.gy + rect2.y, rect1))			hitface = hitface | LEFTTOP;		//����
	if (CheckPointRect(*rect2.gx + rect2.x + rect2.sizeX, *rect2.gy + rect2.y, rect1))		hitface = hitface | RIGHTTOP;	//�E��
	if (CheckPointRect( *rect2.gx + rect2.x, *rect2.gy + rect2.y + rect2.sizeY, rect1))		hitface = hitface | LEFTBOTTOM;	//����
	if (CheckPointRect( *rect2.gx + rect2.x + rect2.sizeX, *rect2.gy + rect2.y + rect2.sizeY, rect1))	hitface = hitface | RIGHTBOTTOM;	//�E��

																																			//rect2 ����rect1�������傫���ꍇ�̗�O����
	if (rect1.sizeX < rect2.sizeX) {
		int part = rect1.sizeX-2;
		for (int i = 1; part * i < rect2.sizeX; i++) {
			if (CheckPointRect(*rect2.gx + rect2.x + part * i, *rect2.gy + rect2.y, rect1))			hitface = hitface | TOP;		//��
			if (CheckPointRect(*rect2.gx + rect2.x + part* i, *rect2.gy + rect2.y + rect2.sizeY, rect1))		hitface = hitface | BOTTOM;	//��
		}
	}

	//rect2 �c��rect1�c�����傫���ꍇ�̗�O����
	if (rect1.sizeY < rect2.sizeY) {
		int part = rect1.sizeY -2;
		for (int i = 1; part* i < rect2.sizeY; i++) {
			if (CheckPointRect(*rect2.gx + rect2.x + rect2.sizeX, *rect2.gy + rect2.y + part* i, rect1))	hitface = hitface | RIGHT;		//�E
			if (CheckPointRect(*rect2.gx + rect2.x, *rect2.gy + rect2.y + part * i, rect1))		hitface = hitface | LEFT;	//��
		}
	}

	return hitface;
}
int HitFaceCircleRect(Circle cir,Rect rect) {
	int hitface = 0;
	//�������Ă��邩
	if (CheckCircleRect(cir, rect)) {
		//�㉺�E���̂ǂꂩ�𒷕��`���m�̔���Ƃ��ċ^���I�ɍs��
		hitface = HitFaceRectRect(ChangeCircleToRect(cir),rect);
	}

	return hitface;
}

int HitFaceCircleCircle(Circle cir1,Circle cir2) {
	int hitface = 0;
	//�������Ă��邩
	if (CheckCircleCircle(cir1, cir2)) {
		//�㉺�E���̂ǂꂩ�𒷕��`���m�̔���Ƃ��ċ^���I�ɍs��
		hitface = HitFaceRectRect(ChangeCircleToRect(cir1), ChangeCircleToRect(cir1));
	}

	return hitface;
}