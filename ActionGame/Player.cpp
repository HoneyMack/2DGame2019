#include "Player.h"
#include "Stage.h"

int Player::PicHandle[] = { 0,0,0 ,0};

static bool befKeys[62];	//��ˑO�̓��͕ێ��p

Player::Player()
{
	rect.sizeX = 20;//�����蔻��̑傫������
	rect.sizeY = 30;
	rect.x = 6;				//�ʒu����
	rect.y = 0;

	//hp
	HP = HITPOINT;

	//�v���C���[�̍��W
	x = WIDTH / 2;
	y = HEIGHT / 2;
	ay = GRAVITY;
	vx = vy = ax = 0;
}

Player::Player(double dx, double dy, double dvx, double dvy, double dax, double day) {
	////�v���C���[�����蔻��쐬
	//rect = new Rect(50, 50);

	x = dx;
	y = dy;
	vx = dvx;
	vy = dvy;
	ax = dax;
	ay = day;
}
Player::Player(const Player &p) {
	rect = p.rect;
	map = p.map;
	Camera = p.Camera;

	x = p.x;
	y = p.y;
	vx = p.vx;
	vy = p.vy;
	ax = p.ax;
	ay = p.ay;
}
Player& Player::operator=(const Player& p) {
	this->rect = p.rect;
	this->map = p.map;
	this->Camera = p.Camera;

	this->x = p.x;
	this->y = p.y;
	this->vx = p.vx;
	this->vy = p.vy;
	this->ax = p.ax;
	this->ay = p.ay;

	return *this;
}

Player::~Player()
{
	//delete rect;
}

void Player::Motion(double frametime) {
	now_key = GetJoypadInputState(DX_INPUT_KEY_PAD1);		//�L�[���͏���

	int hitface = Fence::PlayerHitCheck(rect);//�v���C���[�̂����蔻���n��
	if (hitface != 0) {		//�������Ă��邩
		if (fenceflag == false) {			//���߂ăt�F���X�ɏ������
			vx = vy = ax = ay = 0;
			fenceflag = true;
			
		}
		//���[�v�ɂ���ł��ăW�����v���ǂ���
		if (vy < 0) {
			vy += GRAVITY * frametime;
		}
		else {
			vy = 0;
		
		}
		Animation(FENCE);
		//�㉺���E�ړ�
		if (now_key &(PAD_INPUT_UP | PAD_INPUT_DOWN)) {
			if (now_key & PAD_INPUT_UP) 
					vy = -FENCE_PLAYERMOVESPEED;
			else
				vy = FENCE_PLAYERMOVESPEED;	
		}
			
			
		if (now_key & (PAD_INPUT_LEFT | PAD_INPUT_RIGHT)) {
			if (now_key & PAD_INPUT_LEFT) {
				vx = -FENCE_PLAYERMOVESPEED;
				directionflag = 2;		//������
			}
				
			else {
				vx = FENCE_PLAYERMOVESPEED;
				directionflag = 1;		//�E����
			}
		}
		else {
			vx = 0;
			//directionflag = 0;			//�ǂ��������Ȃ�
		}
		Jump(FENCE_LOWJUMPSPEED);

		//�����A�����̒ꂵ���������Ă��Ȃ������痧������
		if (hitface == BOTTOM)
			Animation(STAND);
	}
	else if (Sea::PlayerHitCheck(rect)) {
		if (seaflag == false) {
			//���߂ĊC�̒��ɓ�����
			vx *= SEA_FIRSTDIVE_SPEED_DECAY;
			vy *= SEA_FIRSTDIVE_SPEED_DECAY;
			ay = SEA_GRAVITY;
			seaflag = true;
		}
		Animation(FENCE);		//�A�j���[�V�������t�F���X�ŉ��u���i�j�����[�V���������������獷���ւ��j
		//���E�ړ�
		if (now_key & (PAD_INPUT_LEFT | PAD_INPUT_RIGHT)) {
			if (now_key & PAD_INPUT_LEFT) {
				vx = -SEA_MOVESPEED;
				directionflag = 2;		//������
				/*if (vx < -SEA_MOVESPEED)
					vx = -SEA_MOVESPEED;*/
			}

			else {
				vx = SEA_MOVESPEED;
				//directionflag = 1;		//�E����
				//if (vx > SEA_MOVESPEED)
				//	vx = SEA_MOVESPEED;
			}
		}
		else {
			vx *= 0.5;
			//directionflag = 0;			//�ǂ��������Ȃ�
		}
		if (vy > SEA_MAXVY) {
			vy = SEA_MAXVY;	//�����ł̉����ւ̑��x����
		}

		hitface = Sea::PlayerHitCheck(rect);
		if (hitface & 0b0001) vx -= SEA_WAVESPEEDX;
		if (hitface & 0b0010) vx += SEA_WAVESPEEDX;
		if (hitface & 0b0100) vy += SEA_WAVESPEEDY;
		if (hitface & 0b1000) vy -= SEA_WAVESPEEDY;
		//ax = 750;
		
		Jump(SEA_LOWJUMPSPEED);
	}
	else {
		if (fenceflag == true || seaflag == true) {
			ay = GRAVITY;
			fenceflag = false;
			seaflag = false;
		}
		keypressed = CrossKeyInput();				//�L�[����
		//directionflag = 0;
	}{
		
		motion += frametime * 1000;					//�A�j���[�V�����p���ԗݐ�(ms)
		//�n�C�W�����v����
		if (highjumpcounter * 1000 < CANHIGHJUMPTIME) {

			if (now_key & PAD_INPUT_10) {
				//�L�[��������Ă���̂ő��x��ǉ�
				vy -= 1000.0* HIGHJUMPSPEED / CANHIGHJUMPTIME * frametime;
			}
			else {
				//�L�[����x�ł������ꂽ��󂯕t���Ȃ�����
				highjumpcounter = CANHIGHJUMPTIME;
			}
			highjumpcounter += frametime;	//�n�C�W�����v�p���ԗݐ�
		}


		int hitface = 0x0000;						//�Ԃ����Ă���ǂ̈ʒu���L��
		hitface = stepRect_x(rect, frametime);		//x�����̎��Ԃ�i�߂�
		//�ǂɓ��������瑬�x�O
		if (hitface & RIGHT || hitface & LEFT) {
			vx = 0.0;
		}

		hitface = stepRect_y(rect, frametime);		//y�����̎��Ԃ�i�߂�

		//�n�ʂɂ������Ă�����
		if (hitface &BOTTOM) {
			vy = 0.0;
			Animation(STAND);
			Jump();
			if (keypressed && seaflag == false)	//�C���ł��̏����������Ȃ��悤�ɕύX
				vx *= 0.9;			//�v���C���[�n�ʂɂ��ăL�[��������Ă���Ƃ��̉����x������
			else
				vx *= 0.6;			//�v���C���[���n�ʂɂ��ăL�[��������Ă��Ȃ��Ƃ��̉����x������
		}
		else if (hitface & TOP) {
			vy = 0.0;

		}
		//�E�[�A���[�����Ȃ��悤��
		if (x < -rect.x)
			x = -rect.x;
		else if (x + rect.sizeY + rect.x > map->getNumX() * DOT)
			x = map->getNumX() * DOT - rect.sizeY - rect.x;

		MatchLessProcess(frametime);
	}
}


void Player::MatchLessProcess(double frametime) {
	//���G����
	if (matchlessflag) {
		//���G���Ԓ��̓_���[�W����
		if (matchlesstime >= 0)
			matchlesstime -= frametime * 1000;
		else {
			matchlessflag = false;
		}
	}
}

void Player::Animation(int action) {
	//�����ɂ��A�j���[�V�����̕ω��̕��򏈗�	
	switch (action) {
	case STAND:
		//�W�����v���Ă����܂��͉��ړ����Ă��Ȃ������猳�ɖ߂�
		if (index == 2 || !keypressed)
			index = 0;
		break;
	case RUN:
		//�A�j���[�V������؂�ւ���run <->stand �i�W�����v���łȂ��j
		if (motion > ANIMETIONINTERVAL && index != 2) {
			index = (index + 1) % 2;
			motion = 0;
		}
		break;
	case JUMP:
		index = 2;
		break;
	case ROPE:
		//�W�����v���Ă�����
		if (vy < 0)
			index = 2;	//jump�Ƃ���
		else
			index = 1;	//run�Ƃ���
		break;
	case FENCE:
		//�ړ����Ă���Ƃ�����
		index = 3;
		break;
	}
}
bool Player::CrossKeyInput() {
	bool keypressed = false;	//�L�[���͂���������true��Ԃ�

	//�E�ɑ��x�ǉ�
	if (now_key &PAD_INPUT_RIGHT) {
		//�v���C���[�̂���Ƃ���ŕ���
		if ((index == 1 || index == 0))
			vx += GROUNDBOOSTSPEED;
		else
			vx += AIRBOOSTSPEED;

		if (vx > MAXBOOST)
			vx = MAXBOOST;
		keypressed = true;
		directionflag = 1;
	}
	//���ɑ��x�ǉ�(�n�ʂɂ���Ƃ�����)
	if (now_key &PAD_INPUT_LEFT) {
		//�v���C���[�̂���Ƃ���ŕ���
		if ((index == 1 || index == 0))
			vx -= GROUNDBOOSTSPEED;
		else
			vx -= AIRBOOSTSPEED;

		if (vx < -MAXBOOST)
			vx = -MAXBOOST;
		keypressed = true;

		directionflag = 2;
	}
	if (keypressed)
		Animation(RUN);

	if (!keypressed) {
		vx *= 0.98;
	}
	return keypressed;
}

void Player::Jump() {
	//�n�ʂɂ���Ƃ������W�����v��
	if (InKeyTrigger(now_key, PAD_INPUT_10)) {
		PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
		vy = -JUMPSPEED;
		//�n�C�W�����v���ł���悤��
		highjumpcounter = 0;
		Animation(JUMP);
	}
}

void Player::Jump(int jump) {
	//�n�ʂɂ���Ƃ������W�����v��
	if (InKeyTrigger(now_key, PAD_INPUT_10)) {
		PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
		vy = -jump;
		//�n�C�W�����v���ł���悤��
		highjumpcounter = 0;
		Animation(JUMP);
	}
}

void Player::Draw() {
	int Px = x - Camera->x, Py = y - Camera->y;		//Screen��̍��W
	if (matchlessflag)
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);		//�����x�w��

	//�E��������Ă��邩
	if (now_key &PAD_INPUT_RIGHT) {
		DrawGraph(Px, Py, PicHandle[index], TRUE);
		
	}
		
	//����������Ă��邩
	else if (now_key &PAD_INPUT_LEFT)
		DrawTurnGraph(Px, Py, PicHandle[index], TRUE);
	//�E�ɑ��x�������Ă��邩
	else if (vx > 0.001 || directionflag == 1)
		DrawGraph(Px, Py, PicHandle[index], TRUE);
	//���ɑ��x�������Ă��邩
	else if (vx < -0.001 || directionflag == 2)
		DrawTurnGraph(Px, Py, PicHandle[index], TRUE);
	else//�����Ă����Ȃ������x�������Ă��Ȃ�
		DrawGraph(Px, Py, PicHandle[0], TRUE);


	if (matchlessflag)
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�����x���I�t

#ifdef DEBUG
	if (matchlessflag == false)
		rect.Draw(*Camera);	//����
#endif
}


//�v���C���[�̌`���ς������ς��
bool Player::HitCheck(Rect rect) {
	if (CheckRectRect(rect, this->rect)) {
		return true;
	}
	else
		return false;
}

bool Player::HitCheck(Circle cir) {
	if (CheckCircleRect(cir, this->rect)) {
		return true;
	}
	else
		return false;
}
void Player::EnemysHitCheck(Mob *mob) {

	if (mob != nullptr) {		//�C���X�^���X��ێ����Ă��邩
		while (true) {			//�C���X�^���X�����ׂă`�F�b�N����܂Ń��[�v
			if (mob->deathflag == false)
				mob->HitCheck(rect);	//�v���C���[�̂����蔻���n���āA���X����Ă��炤

			if (mob->HasNext())	//���̃C���X�^���X����������
				mob = mob->next;
			else
				break;			//���������烋�[�v�𔲂���
		}
	}
}

//�������߂ɕK�v�Ȃ���
Player Player::nextPosX(double frametime) {
	Player ob = *this;
	ob.stepPosX(frametime);
	return ob;
}
Player Player::nextPosY(double frametime) {
	Player ob = *this;
	ob.stepPosY(frametime);
	return ob;
}
Player Player::nextPosAll(double frametime) {
	Player ob = *this;
	ob.stepPosAll(frametime);
	return ob;
}
void Player::stepPosX(double frametime) {
	x += vx *frametime + ax * frametime * frametime / 2;
	vx += ax * frametime;
}
void Player::stepPosY(double frametime) {
	y += vy *frametime + ay * frametime*frametime / 2;
	vy += ay *frametime;
}
void Player::stepPosAll(double frametime) {
	x += vx *frametime + ax * frametime * frametime / 2;
	y += vy *frametime + ay * frametime*frametime / 2;
	vx += ax * frametime;
	vy += ay *frametime;
}

int Player::CheckMapNum(Player P, int vecX, int vecY) {
	return map->PosInfo((int)P.x + vecX, (int)P.y + vecY);
}

int Player::stepRect_x(Rect rect, double frametime) {
	//�v���C���[�𓮂����Ă��邱�Ƃ�����킷�B
	Xmovingflag = true;

	int hitface = 0;
	Player ob_next;

	//X�����Ɉړ��������i���Ԃ�i�߂��j�Ƃ��̈ʒu��m��
	ob_next = nextPosX(frametime);

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

	stepPosX(frametime);			//X�����̎��Ԃ�i�߂�

									//�d�Ȃ����Ƃ��낾���߂�
	if (hitface &RIGHTTOP || hitface & RIGHTBOTTOM) {
		x = ReturnMapIndex(x + rect.sizeX + rect.x)* DOT - rect.sizeX - FLOW - rect.x;	//�E�̕ǂ��肬��܂ňړ�
	}
	else if (hitface & LEFTTOP || hitface & LEFTBOTTOM) {
		x = (ReturnMapIndex(x + rect.x) + 1)* DOT + FLOW * 2 - rect.x;	//���̕ǂ��肬��܂ňړ�
	}


	//�����蔻��
	EnemysHitCheck(Mob::first);
	//�ړ��I��
	Xmovingflag = false;

	return hitface;
}
int Player::stepRect_y(Rect rect, double frametime) {

	//�ړ��J�n
	Ymovingflag = true;

	int hitface = 0;
	Player ob_next;

	//X�����Ɉړ��������i���Ԃ�i�߂��j�Ƃ��̈ʒu��m��
	ob_next = nextPosY(frametime);

	ob_next.x += rect.x;	//���Έʒu��ǉ����āArect�̂����ƃv���C���[�̈ʒu�����킹��
	ob_next.y += rect.y;

	//�܂��������łԂ����Ă邩�m��
	if (CheckMapNum(ob_next, 0, 0) > 0)			hitface = hitface | LEFTTOP;		//����
	if (CheckMapNum(ob_next, rect.sizeX, 0) > 0)		hitface = hitface | RIGHTTOP;	//�E��
	if (CheckMapNum(ob_next, 0, rect.sizeY) > 0)		hitface = hitface | LEFTBOTTOM;	//����
	if (CheckMapNum(ob_next, rect.sizeX, rect.sizeY) > 0)	hitface = hitface | RIGHTBOTTOM;	//�E��

																					//���̂�DOT�����傫���Ƃ��̂��߂̏����BDOT-2�̊Ԋu�Ń}�b�v�̃u���b�N�Ɠ������Ă��邩���m�F����B
	for (int i = 1; i <= (rect.sizeX - 1) / (DOT - 2); i++) {
		if (CheckMapNum(ob_next, (DOT - 2) * i, 0) > 0)			hitface = hitface | TOP;		//��
		if (CheckMapNum(ob_next, (DOT - 2) * i, rect.sizeY) > 0)		hitface = hitface | BOTTOM;		//��
	}

	stepPosY(frametime);		//Y�����̎��Ԃ�i�߂�
								//�d�Ȃ��Ă�����߂�
	if (hitface  &LEFTTOP || hitface & RIGHTTOP) {
		y = (ReturnMapIndex(y + rect.y) + 1) * DOT + FLOW - rect.y;	//��̕ǂ��肬��܂ňړ�
	}
	else if (hitface & LEFTBOTTOM || hitface & RIGHTBOTTOM) {
		y = ReturnMapIndex(y + rect.sizeY + rect.y) * DOT - rect.sizeY - FLOW - rect.y;	//���̕ǂ��肬��܂ňړ�
	}

	//�����蔻��
	EnemysHitCheck(Mob::first);
	//�ړ��I��
	Ymovingflag = false;

	return hitface;
}

bool Player::Damage(int damage, int matchlesstime) {
	//���G�łȂ�������
	if (!matchlessflag) {
		//�G�ɂ��_���[�W�Ȃ�
		if (matchlesstime == ENEMYMATCHLESSTIME && damage != 0)
			PlaySoundMem(Sound::sounds[SOUND_DAMAGE], DX_PLAYTYPE_BACK);
		HP -= damage;
		this->matchlesstime = matchlesstime;
		matchlessflag = true;
		return true;
	}
	else
		return false;
}

//�v���C���[�̌`���ς��Ες��
void Player::Knuckled(Circle cir) {
	if (CheckCircleRect(cir, this->rect)) {
		int move = 1;		//��������ړ���
		//x�����ł̈ړ���
		if (Xmovingflag) {
			if (vx > 0)
				move *= -1;
			while (CheckCircleRect(cir, this->rect)) {
				x += move;
			}
		}
		//y�����̈ړ���
		else
		{
			if (vy > 0)
				move *= -1;
			while (CheckCircleRect(cir, this->rect)) {
				y += move;
			}
		}
	}
}

void Player::Knuckled(Rect rect, int face) {
	if (face == RIGHT) {
		x = *rect.gx + rect.x - (this->rect.x + this->rect.sizeX) - FLOW;
	}
	else if (face == LEFT) {
		x = *rect.gx + rect.x + rect.sizeX - this->rect.x + FLOW;
	}
	else if (face == TOP) {
		y = *rect.gy + rect.y + rect.sizeY - this->rect.y + FLOW;
	}
	else if (face == BOTTOM) {
		y = *rect.gy + rect.y - (this->rect.y + this->rect.sizeY) - FLOW;
	}
}

//�v���C���[�̌`���ς��Ες��
int Player::KnuckledX(Rect rect) {
	int hitface = HitFaceRectRect(rect, this->rect);	//�����̂ǂ��ɂԂ����Ă��邩
	if (hitface &RIGHT) {
		x = *rect.gx + rect.x - (this->rect.x + this->rect.sizeX) - FLOW;
		return RIGHT;
	}
	else if (hitface & LEFT) {
		x = *rect.gx + rect.x + rect.sizeX - this->rect.x + FLOW;
		return LEFT;
	}
	return 0;
}

//�v���C���[�̌`���ς��Ες��
int Player::KnuckledY(Rect rect) {
	int hitface = HitFaceRectRect(rect, this->rect);
	if (hitface &TOP) {
		y = *rect.gy + rect.y + rect.sizeY - this->rect.y + FLOW;
		return TOP;
	}
	else if (hitface & BOTTOM) {
		y = *rect.gy + rect.y - (this->rect.y + this->rect.sizeY) - FLOW;
		return BOTTOM;
	}
	return 0;
}

void Player::Reset() {
	x = WIDTH / 2;
	y = HEIGHT / 2;
	vx = 0;
	vy = 0;
	//�����x������
	ay = GRAVITY;
	ax = 0;

	HP = HITPOINT;

	//���G����������
	matchlessflag = false;
	matchlesstime = 0;
}

//when key pressed, return true once    not while
bool InKeyTrigger(int key, int CheckKey) {
	int count = 0;
	unsigned int i = (unsigned)CheckKey;
	while (i > 1) {
		i = i >> 1;
		count++;
	}
	if (key & CheckKey) {
		if (befKeys[count] == false) {
			befKeys[count] = true;
			return true;
		}
		befKeys[count] = true;
		return false;
	}
	befKeys[count] = false;
	return false;
}