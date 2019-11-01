#include "SeaWeed.h"
#include "Stage.h"

int SeaWeed::PicHandles[] = { 0 };


SeaWeed::SeaWeed(int _x, int _y, int _width, int _height) {
	x = _x; y = _y; width = _width; height = _height;
}

void SeaWeed::Motion(double ftime) {
	//���ɉ����Ȃ�
}

void SeaWeed::Draw() {
	//�C���̍��E�[�̂ǂ��炩�������ʓ��ɂ���΁A�`��
	if (CheckInCam() || CheckInCam(x + SEAWEED_SIZEX * width, y + SEAWEED_SIZEY * height)) {
		//�㉺�̑��x�������Ŏw��
		int upWidth = ((Stage::limit / 800)*8) % SEAWEED_SIZEY;

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				DrawRectGraph(RelativePosX() + SEAWEED_SIZEX * i,
					RelativePosY() + SEAWEED_SIZEY * j, 0, SEAWEED_SIZEY - upWidth
					, SEAWEED_SIZEX, upWidth, PicHandles[0], TRUE);
				DrawRectGraph(RelativePosX() + SEAWEED_SIZEX * i,
					RelativePosY() + SEAWEED_SIZEY * j + upWidth, 0, 0
					, SEAWEED_SIZEX, SEAWEED_SIZEY - upWidth, PicHandles[0], TRUE);
			}
		}
	}
}