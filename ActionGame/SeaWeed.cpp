#include "SeaWeed.h"
#include "Stage.h"

int SeaWeed::PicHandles[] = { 0 };


SeaWeed::SeaWeed(int _x, int _y, int _width, int _height) {
	x = _x; y = _y; width = _width; height = _height;
}

void SeaWeed::Motion(double ftime) {
	//特に何もない
}

void SeaWeed::Draw() {
	//海藻の左右端のどちらか一方が画面内にあれば、描画
	if (CheckInCam() || CheckInCam(x + SEAWEED_SIZEX * width, y + SEAWEED_SIZEY * height)) {
		//上下の速度もここで指定
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