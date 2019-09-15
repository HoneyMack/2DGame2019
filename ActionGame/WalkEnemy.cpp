 #include "WalkEnemy.h"

int WalkEnemy::PicHandle[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

WalkEnemy::WalkEnemy(int x,int y):Object()
{
	//�����蔻��ʒu�Z�b�g
	this->x = x;
	this->y = y;
	rect.x = 3;
	rect.y = 5;
	rect.sizeX = 25;
	rect.sizeY = 25;

	velocity = WALKENEMY_SPEED;	//���x���Z�b�g
	
}


WalkEnemy::~WalkEnemy()
{
}


void WalkEnemy::Motion(double frametime) {
	if (CheckInCam()) {
		//�n�C�W�����v�p�t���O
		if (waittime < KILLHIGHJUMPTIME) {
			waittime += frametime * 1000;
			//�n�C�W�����v�\�ɂ���
			if (usingP->now_key&PAD_INPUT_10) {
				usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
				PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
				waittime = KILLHIGHJUMPTIME;
			}
		}
		int hitface = 0x0000;

		if (vecX + velocity * frametime>WALKENEMY_MOVEWIDTH / 2 || vecX + velocity * frametime < -WALKENEMY_MOVEWIDTH / 2) {
			velocity = -velocity;
		}

		vecX += velocity * frametime;

		x += velocity*frametime;

		hitface = stepRect_x(rect, frametime);
		if ((hitface &RIGHT) || (hitface & LEFT)) {
			velocity = -velocity;
		}


		hitface = stepRect_y(rect, frametime);		//y�����̎��Ԃ�i�߂�
		if ((hitface &BOTTOM) || (hitface & TOP)) {
			vy = 0.0;
		}
		animation += frametime * 1000;
		if (animation >= 100){
			index++;
			animation = 0;
		}
		
		/*index = animation % 200;
		if (animation > 1600){
			animation = 0;*/
		//}
	}
	//���������Ƃ��Ɏ��ʂ悤�ɂ���
	if (y > HEIGHT)
		deathflag = true;
}

void WalkEnemy::Draw() {
	if (CheckInCam()) {
		
		if(velocity<= 0)
			DrawGraph(RelativePosX(),RelativePosY(),PicHandle[index%8],TRUE);
		else
			DrawTurnGraph(RelativePosX(), RelativePosY(), PicHandle[index%8], TRUE);
#ifdef DEBUG
		rect.Draw(*Camera);
#endif			

	}
}

bool WalkEnemy::HitCheck(Rect rect) {
	
	if (CheckRectRect(rect, this->rect)) {
		//�v���C���[���������Ă��āA�����̏�ɂ������Ă����玩��������Ńv���C���[�Ƀ_���[�W�͓���Ȃ�
		if (HitFaceRectRect(rect, this->rect) & TOP && usingP->vy > 0 && usingP->Ymovingflag&& !(HitFaceRectRect(rect, this->rect) & BOTTOM )) {
			killedenemy++;
			PlaySoundMem(Sound::sounds[SOUND_ENEMYTREAD], DX_PLAYTYPE_BACK);
			deathflag = true;
			usingP->Knuckled(this->rect, BOTTOM);
			
			waittime = 0;
			//�n�C�W�����v�\�ɂ���
			usingP->Animation(JUMP); 
			if (usingP->now_key& PAD_INPUT_10) {
				
				usingP->highjumpcounter = (CANHIGHJUMPTIME - KILLHIGHJUMPLIMIT) / 1000.0;
				PlaySoundMem(Sound::sounds[SOUND_PLAYERJUMP], DX_PLAYTYPE_BACK);
				waittime = KILLHIGHJUMPTIME;
				//usingP->vy = -JUMPSPEED;
			}
			usingP->vy = -KILLJUMP;
		}
		else
			HitPlayer();
		
		
		return true;
	}
	else
		return false;
}

void WalkEnemy::HitPlayer() {
	usingP->Damage(WALKENEMY_HITDAMAGE,ENEMYMATCHLESSTIME);
}