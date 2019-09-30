#include "SeaWeed.h"
#include "Stage.h"

int SeaWeed::PicHandles[] = { 0,0,0,0,0 };


SeaWeed::SeaWeed(int _x, int _y, int _width, int _height) {
	x = _x; y = _y; width = _width; height = _height;
}

void SeaWeed::Motion(double ftime) {
	//���ɉ����Ȃ�
}

void SeaWeed::Draw() {
	//�C���̍��E�[�̂ǂ��炩�������ʓ��ɂ���΁A�`��
	if (CheckInCam() || CheckInCam(x + SEAWEED_SIZEX * width, y + SEAWEED_SIZEY * height)) {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				DrawGraph(RelativePosX() + SEAWEED_SIZEX * i,
					RelativePosY() + SEAWEED_SIZEY * j,
					PicHandles[(Stage::limit / SEAWEED_SWITCHTIME) % SEAWEED_TOTALPICTURES], TRUE);
			}
		}
	}
}