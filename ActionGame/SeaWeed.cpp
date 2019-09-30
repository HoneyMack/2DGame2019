#include "SeaWeed.h"
#include "Stage.h"

int SeaWeed::PicHandles[] = { 0,0,0,0,0 };


SeaWeed::SeaWeed(int _x, int _y, int _width, int _height) {
	x = _x; y = _y; width = _width; height = _height;
}

void SeaWeed::Motion(double ftime) {
	//特に何もない
}

void SeaWeed::Draw() {
	//海藻の左右端のどちらか一方が画面内にあれば、描画
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