#include "Rope.h"

int Rope::rope_PicHandle = 0;
int Rope::fixture_PicHandle = 0;
int Rope::FsizeX = 0;
int Rope::FsizeY = 0;

Rope::Rope(int x, int y,int ropenum)
{
	this->x = x;
	this->y = y;
	this->ropenum = ropenum;
	//�摜���킹
	GetGraphSize(rope_PicHandle, &rope.x, &ropelen);
	rope.x /= 2;
	rope.x -= rope.sizeX / 2;

	ropelen--;	//������
	rope.sizeY = ropenum *ropelen - 15;

	GetGraphSize(fixture_PicHandle, &FsizeX, &FsizeY);

	
	//�T�C�Y���킹
	fixture.sizeX = 20;
	fixture.sizeY = 18;
	//�ʒu���킹
	fixture.x = (rope.sizeX/2 + rope.x ) - fixture.sizeX/2;
	fixture.y -= fixture.sizeY + 4;

	catchflag = false;
}

Rope::~Rope()
{
}

void Rope::Motion(double frametime)
{
	//�v���C���[�����[�v��ɂ��邩
	if (usingP->HitCheck(rope)) {
		////����ŏ��߂Ă̏�����
		//if (!catchflag) {
		//	usingP->vy = 0;
		//	usingP->ay = 0;
		//	catchflag = true;
		//}
		//���[�v�ɂ���ł��ăW�����v���ǂ���
		if (vy < 0  && catchflag) {
			usingP->y += vy* frametime;
			vy += GRAVITY * frametime;
			//�����Œ蕔���ɂ������Ă��܂��Ă�����
			if (usingP->HitCheck(fixture)){	
				usingP->y -= vy* frametime;
				vy = 0;
			}
		}	
		//���[�v�㉺�ړ�
		if (usingP->now_key & PAD_INPUT_UP)
			usingP->y -= ROPE_UPDOWN * frametime;
		if (usingP->now_key & PAD_INPUT_DOWN)
			usingP->y += ROPE_UPDOWN * frametime;
		
	}
	else {
		//���߂ă��[�v���痣�ꂽ��
		if (catchflag == true) {
			//���[�v���珉�߂ė��ꂽ�Ƃ��̃W�����v�ʂŕ���
			if (vy < 0) {
				if (vy < -2*ROPE_JUMPSPEED / 3)	usingP->vy -= ROPE_HIGHJUMP - ROPE_JUMPSPEED * (vy / ROPE_JUMPSPEED);		//��������
				else 					usingP->vy -= ROPE_LOWJUMP - ROPE_JUMPSPEED * (vy / ROPE_JUMPSPEED);	//������艺
			}
			usingP->ay = GRAVITY;
		}
		catchflag = false;
	}
}

bool Rope::HitCheck(Rect rope)
{
	//�������Ă��邩
	if (CheckRectRect(rope, this->rope)|| CheckRectRect(rope, this->fixture)) {
		//���[�v������ł��邩
		if (CheckRectRect(rope, this->rope)) {
			//����ŏ��߂Ă̏�����
       			if (!catchflag) {
				usingP->vy = 0;
				usingP->ay = 0;
				catchflag = true;
			}
			//���[�v������ł���Ƃ��̍��E�ړ�����
			if (usingP->keypressed) {
				usingP->vx *= 0.75;
			}
			else {
				usingP->vx *= 0.60;
			}
			//���[�v������ł��Ă��L�[��������Ă�����W�����v�\
			if (InKeyTrigger(usingP->now_key, PAD_INPUT_10)) {
				PlaySoundMem(Sound::sounds[SOUND_ROPEJUMP], DX_PLAYTYPE_BACK);
				vy = -ROPE_JUMPSPEED;
			}
			//�A�j���[�V�������s��
			usingP->Animation(ROPE);
			//���[�v�ɂ��񂾂̂œo�葱���Ȃ��悤�ɂ���
			usingP->highjumpcounter = CANHIGHJUMPTIME;
		}
		//�Œ��ɂԂ����Ă��邩
		if (CheckRectRect(rope, this->fixture)) {
			//���[�v������ł��Ȃ���
			if (!CheckRectRect(rope, this->rope)) {
				//���E�ړ������Ă�����
				if (usingP->Xmovingflag == true) {
					//usingP->KnuckledX(rect);
					if (usingP->vx > 0) {
						usingP->Knuckled(fixture, RIGHT);
					}
					else
						usingP->Knuckled(fixture, LEFT);

					usingP->vx = 0;		//���ɂ������Ă���̂�x�����O��
				}
			}
			//�㉺�ړ������Ă�����
			if (usingP->Ymovingflag == true) {

				if (usingP->vy > 0) {
					usingP->Knuckled(fixture, BOTTOM);
					usingP->vy = 0;		//�㉺�œ������Ă���̂�y����0��
					usingP->Animation(STAND);		//�A�j���[�V����

					usingP->Jump();
					if (usingP->keypressed)
						usingP->vx *= 0.9;			//�L�[��������Ă���Ƃ��̉����x������
					else
						usingP->vx *= 0.6;			//�L�[��������Ă��Ȃ��Ƃ��̉����x������
				}
				else {
					usingP->Knuckled(fixture, TOP);
					usingP->vy = 0;		//�㉺�œ������Ă���̂�y����0��
				}
			}
		}
		return true;
	}
	else
		return false;
}

void Rope::Draw(){
	if (CheckInCam()) {
		for(int i = 0; i < ropenum;i++)
			DrawGraph(RelativePosX() , RelativePosY() + i *ropelen, rope_PicHandle, TRUE);				//���[�v
		
		DrawGraph(RelativePosX() +(rope.sizeX / 2 + rope.x) - FsizeX /2, RelativePosY() - FsizeY +6, fixture_PicHandle, TRUE);		//�Œ��
#ifdef DEBUG
		fixture.Draw(*Camera);
		rope.Draw(*Camera);
#endif
	}
}
