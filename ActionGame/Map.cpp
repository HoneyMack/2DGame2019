#include "Map.h"
int Map::PicHandle[MAP_MAX] = {};

Map::Map()
{
	numX = VIEW_WIDTH_INDEX;
	numY = VIEW_HEIGHT_INDEX;
	setArray();
	resetMap();
}
Map::Map(int lenX)
{

	numX = lenX;
	numY = VIEW_HEIGHT_INDEX;
	setArray();
	resetMap();
}

Map::~Map()
{
}

void Map::setNum(int x, int y)
{
	numX = x;
	numY = y;

	setArray();
	resetMap();
}

int Map::getNumX() {
	return numX;
}
int Map::getNumY() {
	return numY;
}

void Map::setArray() {
	m_map.resize(numX);	//x方向の配列の長さをnumXに
	for (int i = 0; i < numX; i++) {
		m_map[i].resize(numY);	//x方向一つ一つの配列の要素にy方向の配列（長さnumY）を追加
	}
}

void Map::resetMap()
{
	int i, j;
	//それぞれの配列の要素を初期化
	for (i = 0; i < numX; i++) {
		for (j = 0; j < numY; j++)
			m_map[i][j] = 0;
	}
	setFrame();
}

void Map::setFrame()
{
	//地面&&天井
	for (int i = 0; i < numX; i++) {
		m_map[i][0] = -1;
		m_map[i][numY - 1] = -1;
	}
	//右壁and左壁
	for (int i = 0; i < numY; i++) {
		m_map[numX - 1][i] = -1;
		//m_Map[0][i] = -1;
	}
}

int Map::PosInfo(int x, int y) {
	if (x / DOT >= 0 && x / DOT < numX && y/DOT >=0&& y / DOT < numY) {	//例外処理
		return m_map[x / DOT][y / DOT];
	}
	return -1;
}
		

void Map::Draw(Rect *Camera) {
	//スケールをdotからindexに 
	int sizeX = Camera->sizeX/ DOT;
	int sizeY = Camera->sizeY/ DOT;

	for (int i = 0; i <=sizeX; i++) {
		for (int j = 0; j <= sizeY; j++) {
			if (PosInfo(Camera->x + i*DOT,Camera->y +j*DOT) >0) {
				DrawGraph(i * DOT - Camera->x % DOT, j* DOT - Camera->y % DOT, PicHandle[PosInfo(Camera->x + i*DOT, Camera->y + j*DOT)], TRUE);
			}
		}
	}
}

int ReturnMapIndex(double x) {
	return (int)x / DOT;
}