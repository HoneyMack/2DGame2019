#include "Stage.h"

int Stage::limit = 0;

Stage::Stage()
{
	Camera = new Rect(WIDTH, HEIGHT, nullptr, nullptr);	//�J�����̑傫�����w��
	usingP = new Player();				//�v���C���[���쐬
	usingM = new Map();					//�}�b�v���쐬						


	usingP->map = usingM;				//�v���C���[�Ƀ}�b�v���Z�b�g
	usingP->Camera = Camera;			//�v���C���[�ɃJ�������Z�b�g	
	Object::Camera = Camera;			//Mob�ɃJ�����ƃ}�b�v����^����
	Object::map = usingM;
	Object::usingP = usingP;			//�v���C���[��set
}

Stage::~Stage()
{
	Mob::AllDelete();
	Fence::AllDelete();

	//���I���������������J��
	delete Camera;
	delete usingP;
	delete usingM;
}


void Stage::AllUpdate(double ftime) {
	//�w�i�摜�K�؂ɕ`�揈��(�J�����Ō����Ă���Ƃ��낾��)
	int i = Camera->x / MAPPARTS_X  -1;
	while (i *MAPPARTS_X < Camera->x + WIDTH) {
		//�摜�������ƘA������悤�ɂ���.�摜���Ȃ��Ƃ���͔�����
		DrawGraph(i*MAPPARTS_X-Camera->x, 0, mapparts[i % ACCOUNTFORMAPPARTS], TRUE);
		i++;
	}

	//�c�莞�Ԍ���
	limit -= ftime * 1000;
	//��������̃t���b�V���u���b�N�������ꂽ���𔻒�̂���true = �����Ă���
	FlashBlock::flashingflag = false;

	Update(ftime);
	switch (mode) {
	case CROSSKEYANDJUMP:
		usingP->Motion(ftime);
		//���Ƃ��ăv���C���[�𒆐S�Ɉړ��B�������A�z������Ȃ��悤�ɂ���
		if (usingP ->x - WIDTH / 2 > 0 && usingP->x + WIDTH / 2 < usingM->getNumX() *DOT)
			Camera->x = usingP->x - WIDTH / 2;
		break;
	case FORCEHORIZONTALSCROLL:
		//�����X�N���[��������
		Camera->x += ftime *SCROLLSPEED;
		usingP->Motion(ftime);
		break;
	}

}

void Stage::AllDraw() {
	usingP->Draw();
	usingM->Draw(Camera);

	Draw();
	AddDraw();
}
void Stage::Update(double ftime) {
	//�G�̏����̊�{�`
	Mob* mob = Mob::first;
	if (mob != nullptr) {		//�C���X�^���X��ێ����Ă��邩
		if (mob->deathflag == false)
		mob->Motion(ftime);
		while (mob->HasNext()) {	//���̃C���X�^���X��ێ����Ă�����
			mob = mob->next;
			if (mob->deathflag == false)
			mob->Motion(ftime);
		}
	}
}
void Stage::Draw() {
	//�G�̕`��̊�{�`
	Mob* mob = Mob::first;
	if (mob != nullptr) {		//�C���X�^���X��ێ����Ă��邩
		if (mob->deathflag == false)
		mob->Draw();
		while (mob->HasNext()) {	//���̃C���X�^���X��ێ����Ă�����
			mob = mob->next;
			if(mob ->deathflag ==false)
			mob->Draw();
		}
	}
}

void Stage::AddDraw() {
	//�G�̕`��̊�{�`
	Mob* mob = Mob::first;
	if (mob != nullptr) {		//�C���X�^���X��ێ����Ă��邩
		if (mob->deathflag == false)
			mob->AddDraw();
		while (mob->HasNext()) {	//���̃C���X�^���X��ێ����Ă�����
			mob = mob->next;
			if (mob->deathflag == false)
				mob->AddDraw();
		}
	}
}

void Stage::AllReset() {
	Camera->x = 0;
	Camera->y = 0;

	usingM->resetMap();
	usingP->Reset();

	//�c��^�C��,�|�����G��0��
	limit = 0;
	Mob::killedenemy = 0;

	//�}�b�v���甲����Ƃ��ɏ����R�C�����[����
	Coin::hadcoins = 0;

	//�C���X�^���X�̍�������
	Mob::AllDelete();
	Fence::AllDelete();
	Sea::AllDelete();
}
